"""Direct OpenHands MCP client demo for verilator-mcp."""

from __future__ import annotations

import asyncio
import json
import os
import shutil
import sys
from pathlib import Path

from openhands.core.config.mcp_config import MCPStdioServerConfig
from openhands.events.action.mcp import MCPAction
from openhands.events.observation.mcp import MCPObservation
from openhands.mcp.utils import call_tool_mcp, create_mcp_clients

VERILATOR_MCP_ENTRYPOINT_ENV = "VERILATOR_MCP_ENTRYPOINT"
VERILATOR_BIN = Path("/opt/homebrew/bin/verilator")
EXAMPLE_DIR = Path(__file__).resolve().parent
RTL_DIR = EXAMPLE_DIR / "rtl"
TB_DIR = EXAMPLE_DIR / "tb"
BUILD_DIR = EXAMPLE_DIR / "build" / "obj_dir"
SIM_OUTPUT_DIR = EXAMPLE_DIR / "sim_output"


def _require_entrypoint() -> str:
    entrypoint = os.environ.get(VERILATOR_MCP_ENTRYPOINT_ENV)
    if not entrypoint:
        raise RuntimeError(
            f"Set {VERILATOR_MCP_ENTRYPOINT_ENV} to your built verilator-mcp dist/index.js"
        )
    if not Path(entrypoint).is_file():
        raise RuntimeError(
            f"{VERILATOR_MCP_ENTRYPOINT_ENV} points to a missing file: {entrypoint}"
        )
    return entrypoint


def _build_stdio_server(entrypoint: str) -> MCPStdioServerConfig:
    node = shutil.which("node")
    if node is None:
        raise RuntimeError("node is required to launch verilator-mcp")
    if not VERILATOR_BIN.is_file():
        raise RuntimeError(f"Expected Verilator at {VERILATOR_BIN}")

    env = dict(os.environ)
    current_path = env.get("PATH", "")
    homebrew_bin = str(VERILATOR_BIN.parent)
    if current_path:
        if not current_path.startswith(f"{homebrew_bin}:") and current_path != homebrew_bin:
            env["PATH"] = f"{homebrew_bin}:{current_path}"
    else:
        env["PATH"] = homebrew_bin
    env["HOME"] = str(Path.home())
    env["LOG_LEVEL"] = "info"

    return MCPStdioServerConfig(
        name="verilator",
        command=node,
        args=[entrypoint],
        env=env,
    )


def _extract_text(observation: MCPObservation) -> str:
    payload = json.loads(observation.content)
    if payload.get("isError", False):
        raise RuntimeError(json.dumps(payload, indent=2))

    content = payload.get("content", [])
    if not content or content[0].get("type") != "text":
        raise RuntimeError(f"Unexpected MCP payload: {payload}")
    return content[0]["text"]


def _reset_generated_dirs() -> None:
    for path in (BUILD_DIR.parent, SIM_OUTPUT_DIR):
        if path.exists():
            shutil.rmtree(path)
    BUILD_DIR.mkdir(parents=True, exist_ok=True)
    SIM_OUTPUT_DIR.mkdir(parents=True, exist_ok=True)


async def main() -> int:
    entrypoint = _require_entrypoint()
    stdio_server = _build_stdio_server(entrypoint)
    _reset_generated_dirs()

    mcp_clients = await create_mcp_clients(
        sse_servers=[],
        shttp_servers=[],
        conversation_id="verilator-direct-demo",
        stdio_servers=[stdio_server],
    )
    if not mcp_clients:
        raise RuntimeError("Failed to connect to verilator-mcp")

    tool_names = [tool.name for client in mcp_clients for tool in client.tools]
    required_tools = {"verilator_compile", "verilator_simulate"}
    missing_tools = required_tools.difference(tool_names)
    if missing_tools:
        raise RuntimeError(
            f"verilator-mcp is missing expected tools: {sorted(missing_tools)}; got {tool_names}"
        )

    compile_observation = await call_tool_mcp(
        mcp_clients,
        MCPAction(
            name="verilator_compile",
            arguments={
                "files": [
                    str(RTL_DIR / "counter.v"),
                    str(TB_DIR / "counter_main.cpp"),
                ],
                "topModule": "counter",
                "outputDir": str(BUILD_DIR),
                "optimization": 2,
                "trace": True,
                "verilatorFlags": ["-CFLAGS", "-std=c++17"],
            },
        ),
    )
    compile_text = _extract_text(compile_observation)
    print("=== verilator_compile ===")
    print(compile_text)
    if "Compilation Successful" not in compile_text:
        raise RuntimeError("verilator_compile did not report success")

    simulate_observation = await call_tool_mcp(
        mcp_clients,
        MCPAction(
            name="verilator_simulate",
            arguments={
                "design": str(BUILD_DIR),
                "topModule": "counter",
                "useExistingBuild": True,
                "autoGenerateTestbench": False,
                "enableWaveform": True,
                "outputDir": str(SIM_OUTPUT_DIR),
                "simulationTime": 32,
                "timeout": 120000,
            },
        ),
    )
    simulate_text = _extract_text(simulate_observation)
    print("\n=== verilator_simulate ===")
    print(simulate_text)
    if "Simulation Passed" not in simulate_text:
        raise RuntimeError("verilator_simulate did not report success")

    expected_files = [
        BUILD_DIR / "Vcounter",
        SIM_OUTPUT_DIR / "simulation.log",
        SIM_OUTPUT_DIR / "simulation.vcd",
    ]
    missing_files = [str(path) for path in expected_files if not path.exists()]
    if missing_files:
        raise RuntimeError(f"Expected simulation artifacts are missing: {missing_files}")

    print("\nArtifacts:")
    for artifact in expected_files:
        print(f"- {artifact}")

    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(asyncio.run(main()))
    except KeyboardInterrupt:
        raise SystemExit(130)
    except Exception as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)
