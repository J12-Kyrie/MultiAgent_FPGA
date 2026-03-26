"""Runtime integration test for Verilator MCP through LocalRuntime."""

import asyncio
import json
import os
import shlex
import shutil
from pathlib import Path

import pytest
from conftest import _close_test_runtime, _load_runtime

from openhands.core.config import MCPConfig
from openhands.core.config.mcp_config import MCPStdioServerConfig
from openhands.events.action import CmdRunAction, MCPAction
from openhands.events.observation import CmdOutputObservation, MCPObservation
from openhands.mcp.utils import create_mcp_clients

pytestmark = pytest.mark.skipif(
    os.environ.get('TEST_RUNTIME') != 'local',
    reason='This test exercises the LocalRuntime MCP proxy against a local Verilator installation.',
)

VERILATOR_MCP_ENTRYPOINT_ENV = 'VERILATOR_MCP_ENTRYPOINT'
VERILATOR_BIN = Path('/opt/homebrew/bin/verilator')
PROJECT_DIRNAME = 'verilator_mcp_runtime_test'

COUNTER_VERILOG = """module counter #(
  parameter WIDTH = 8,
  parameter MAX_COUNT = 255
)(
  input  wire               clk,
  input  wire               rst_n,
  input  wire               enable,
  input  wire               clear,
  output reg  [WIDTH-1:0]   count,
  output wire               overflow
);

  assign overflow = (count == MAX_COUNT) && enable;

  always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      count <= {WIDTH{1'b0}};
    end else if (clear) begin
      count <= {WIDTH{1'b0}};
    end else if (enable) begin
      if (count == MAX_COUNT) begin
        count <= {WIDTH{1'b0}};
      end else begin
        count <= count + 1'b1;
      end
    end
  end

endmodule
"""

COUNTER_MAIN_CPP = """#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vcounter.h"

vluint64_t sim_time = 0;
double sc_time_stamp() { return sim_time; }

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    Vcounter dut;
    VerilatedVcdC trace;
    dut.trace(&trace, 5);
    trace.open("simulation.vcd");

    dut.clk = 0;
    dut.rst_n = 0;
    dut.enable = 0;
    dut.clear = 0;

    for (int i = 0; i < 5; ++i) {
        dut.clk = !dut.clk;
        dut.eval();
        trace.dump(sim_time++);
    }

    dut.rst_n = 1;
    dut.enable = 1;

    for (int i = 0; i < 20; ++i) {
        dut.clk = !dut.clk;
        dut.eval();
        trace.dump(sim_time++);
    }

    dut.final();
    trace.close();
    return 0;
}
"""


def _require_verilator_entrypoint() -> str:
    entrypoint = os.environ.get(VERILATOR_MCP_ENTRYPOINT_ENV)
    if not entrypoint:
        pytest.skip(
            f'{VERILATOR_MCP_ENTRYPOINT_ENV} must be set to a built verilator-mcp entrypoint.'
        )

    if not Path(entrypoint).is_file():
        pytest.skip(
            f'{VERILATOR_MCP_ENTRYPOINT_ENV} points to a missing file: {entrypoint}'
        )

    return entrypoint


def _build_verilator_stdio_server(entrypoint: str) -> MCPStdioServerConfig:
    node = shutil.which('node')
    assert node is not None, 'node executable is required to launch verilator-mcp'
    assert VERILATOR_BIN.is_file(), f'Expected Verilator at {VERILATOR_BIN}'

    env = dict(os.environ)
    current_path = env.get('PATH', '')
    homebrew_bin = str(VERILATOR_BIN.parent)
    env['PATH'] = (
        current_path
        if current_path.startswith(f'{homebrew_bin}:') or current_path == homebrew_bin
        else f'{homebrew_bin}:{current_path}' if current_path else homebrew_bin
    )
    env['HOME'] = str(Path.home())
    env['LOG_LEVEL'] = 'info'

    return MCPStdioServerConfig(
        name='verilator',
        command=node,
        args=[entrypoint],
        env=env,
    )


def _write_runtime_test_project(temp_dir: str) -> dict[str, str]:
    host_root = Path(temp_dir) / PROJECT_DIRNAME
    rtl_dir = host_root / 'rtl'
    tb_dir = host_root / 'tb'
    build_dir = host_root / 'build' / 'obj_dir'
    sim_output_dir = host_root / 'sim_output'

    for directory in (rtl_dir, tb_dir, build_dir, sim_output_dir):
        directory.mkdir(parents=True, exist_ok=True)

    (rtl_dir / 'counter.v').write_text(COUNTER_VERILOG, encoding='utf-8')
    # The explicit C++ testbench avoids the known upstream auto-generated TB failure path.
    (tb_dir / 'counter_main.cpp').write_text(COUNTER_MAIN_CPP, encoding='utf-8')

    # LocalRuntime uses the host workspace path directly instead of a /workspace mount.
    runtime_root = host_root
    return {
        'design': str(runtime_root / 'rtl' / 'counter.v'),
        'testbench': str(runtime_root / 'tb' / 'counter_main.cpp'),
        'build_dir': str(runtime_root / 'build' / 'obj_dir'),
        'sim_output_dir': str(runtime_root / 'sim_output'),
        'executable': str(runtime_root / 'build' / 'obj_dir' / 'Vcounter'),
        'simulation_log': str(runtime_root / 'sim_output' / 'simulation.log'),
        'simulation_vcd': str(runtime_root / 'sim_output' / 'simulation.vcd'),
    }


async def _discover_verilator_tools(runtime) -> tuple[str, str]:
    updated_mcp_config = runtime.get_mcp_config()
    assert updated_mcp_config.sse_servers, 'Runtime did not expose an MCP proxy SSE server'

    last_tool_names: list[str] = []
    for _ in range(5):
        mcp_clients = await create_mcp_clients(
            updated_mcp_config.sse_servers,
            updated_mcp_config.shttp_servers,
            runtime.sid,
        )
        last_tool_names = [
            tool.name for client in mcp_clients for tool in client.tools
        ]
        compile_tool = next(
            (name for name in last_tool_names if name.endswith('verilator_compile')),
            None,
        )
        simulate_tool = next(
            (name for name in last_tool_names if name.endswith('verilator_simulate')),
            None,
        )
        if compile_tool and simulate_tool:
            return compile_tool, simulate_tool
        await asyncio.sleep(1)

    pytest.fail(
        'Could not discover Verilator MCP tools via the runtime proxy. '
        f'Available tools: {last_tool_names}'
    )


def _assert_successful_mcp_observation(
    observation: MCPObservation, expected_fragments: list[str]
) -> str:
    assert isinstance(observation, MCPObservation), (
        'Expected an MCPObservation from runtime.call_tool_mcp'
    )

    payload = json.loads(observation.content)
    assert not payload.get('isError', False), payload

    content = payload.get('content', [])
    assert content, payload
    assert content[0]['type'] == 'text', payload

    text = content[0]['text']
    for fragment in expected_fragments:
        assert fragment in text, text
    return text


def _assert_runtime_file_exists(runtime, path: str) -> None:
    observation = runtime.run_action(CmdRunAction(command=f'test -f {shlex.quote(path)}'))
    assert isinstance(observation, CmdOutputObservation)
    assert observation.exit_code == 0, (
        f'Expected runtime file to exist: {path}\n{observation.content}'
    )


@pytest.mark.asyncio
async def test_verilator_mcp_compile_then_simulate_success(
    temp_dir, runtime_cls, run_as_openhands
):
    entrypoint = _require_verilator_entrypoint()
    project_paths = _write_runtime_test_project(temp_dir)
    override_mcp_config = MCPConfig(
        stdio_servers=[_build_verilator_stdio_server(entrypoint)]
    )

    runtime = None
    try:
        runtime, _ = _load_runtime(
            temp_dir,
            runtime_cls,
            run_as_openhands,
            override_mcp_config=override_mcp_config,
        )

        compile_tool_name, simulate_tool_name = await _discover_verilator_tools(runtime)

        compile_observation = await runtime.call_tool_mcp(
            MCPAction(
                name=compile_tool_name,
                arguments={
                    'files': [project_paths['design'], project_paths['testbench']],
                    'topModule': 'counter',
                    'outputDir': project_paths['build_dir'],
                    'optimization': 2,
                    'trace': True,
                    'verilatorFlags': ['-CFLAGS', '-std=c++17'],
                },
            )
        )
        _assert_successful_mcp_observation(
            compile_observation,
            [
                'Compilation Successful',
                f'Output Directory: {project_paths["build_dir"]}',
            ],
        )

        simulate_observation = await runtime.call_tool_mcp(
            MCPAction(
                name=simulate_tool_name,
                arguments={
                    'design': project_paths['build_dir'],
                    'topModule': 'counter',
                    'useExistingBuild': True,
                    'autoGenerateTestbench': False,
                    'enableWaveform': True,
                    'outputDir': project_paths['sim_output_dir'],
                    'simulationTime': 32,
                    'timeout': 120000,
                },
            )
        )
        _assert_successful_mcp_observation(
            simulate_observation,
            [
                'Simulation Passed',
                f'Log File: {project_paths["simulation_log"]}',
                f'Waveform File: {project_paths["simulation_vcd"]}',
            ],
        )

        _assert_runtime_file_exists(runtime, project_paths['executable'])
        _assert_runtime_file_exists(runtime, project_paths['simulation_log'])
        _assert_runtime_file_exists(runtime, project_paths['simulation_vcd'])
    finally:
        if runtime:
            _close_test_runtime(runtime)
