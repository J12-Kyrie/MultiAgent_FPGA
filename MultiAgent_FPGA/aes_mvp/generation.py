"""Generation-first contracts and draft-workspace helpers for the AES MVP."""

from __future__ import annotations

import json
import shutil
from datetime import UTC, datetime
from pathlib import Path
from typing import Any

from MultiAgent_FPGA.aes_mvp.artifacts import (
    ModuleContract,
    ModuleDesignBrief,
    NodeWorkspaceRecord,
    NodeWorkspaceState,
    PlanDAG,
    PlanDAGNode,
    PortSpec,
    PromotionRecord,
    SpecIR,
    TestbenchContract,
)
from MultiAgent_FPGA.aes_mvp.executor_contracts import summarize_required_checkpoints
from MultiAgent_FPGA.aes_mvp.skill_refs import select_skill_refs

DEFAULT_REPAIR_BUDGET = 2

_MODULE_SUMMARIES = {
    'aes_sbox': 'Implement the combinational AES S-box byte substitution.',
    'aes_key_schedule_128': 'Implement the AES-128 round-key expansion helper.',
    'aes_round_transform': 'Implement one AES round transform with optional final-round bypass.',
    'aes128_encrypt_core': 'Implement the iterative AES-128 encrypt core with block-level handshake.',
}

_MODULE_PORTS = {
    'aes_sbox': [
        ('in_byte', 'input', 8, 'Input byte to substitute.'),
        ('out_byte', 'output', 8, 'Substituted output byte.'),
    ],
    'aes_key_schedule_128': [
        (
            'key',
            'input',
            128,
            'Current key input used to derive the requested round key.',
        ),
        ('round_index', 'input', 4, 'Round selector in the range 0..10.'),
        (
            'round_key',
            'output',
            128,
            'Derived AES-128 round key for the requested round.',
        ),
    ],
    'aes_round_transform': [
        ('state_in', 'input', 128, 'Input AES state before the round transform.'),
        ('round_key', 'input', 128, 'Round key for AddRoundKey.'),
        ('final_round', 'input', 1, 'When asserted, bypass MixColumns.'),
        ('sub_bytes_state', 'output', 128, 'Intermediate state after SubBytes.'),
        ('shift_rows_state', 'output', 128, 'Intermediate state after ShiftRows.'),
        (
            'mix_columns_state',
            'output',
            128,
            'Intermediate state after MixColumns or bypass.',
        ),
        ('state_out', 'output', 128, 'Final state after the round transform.'),
    ],
    'aes128_encrypt_core': [
        ('clk', 'input', 1, 'Primary rising-edge clock.'),
        ('rst_n', 'input', 1, 'Active-low reset.'),
        ('start', 'input', 1, 'Start pulse sampled when busy is low.'),
        ('key', 'input', 128, 'AES-128 key input.'),
        ('plaintext', 'input', 128, 'AES plaintext input block.'),
        ('busy', 'output', 1, 'Busy indicator for the active encryption window.'),
        ('done', 'output', 1, 'Single-cycle completion pulse.'),
        ('ciphertext', 'output', 128, 'Ciphertext output block.'),
    ],
}

_DESIGN_GOALS = {
    'aes_sbox': [
        'Preserve the frozen aes_sbox interface exactly.',
        'Implement pure combinational substitution with no sequential state.',
        'Produce CHK_SBOX_MATCH through the self-checking .cpp testbench.',
    ],
    'aes_key_schedule_128': [
        'Preserve the frozen aes_key_schedule_128 interface exactly.',
        'Support round_index values 0 through 10.',
        'Produce CHK_ROUNDKEY_MATCH through the self-checking .cpp testbench.',
    ],
    'aes_round_transform': [
        'Preserve the frozen aes_round_transform interface exactly.',
        'Support both normal rounds and final-round bypass of MixColumns.',
        'Produce CHK_ROUND_STATE_MATCH through the self-checking .cpp testbench.',
    ],
    'aes128_encrypt_core': [
        'Preserve the frozen top-level handshake and signal names exactly.',
        'Honor the 11-cycle latency target and ignore start while busy.',
        'Produce the frozen top-level checkpoint set through the self-checking .cpp testbench.',
    ],
}

_TB_VECTOR_FORMATS = {
    'aes_sbox': 'Exhaustive byte sweep plus optional vecfile with in_hex/out_hex pairs.',
    'aes_key_schedule_128': 'Key/value file with round_key_0 through round_key_10 entries.',
    'aes_round_transform': 'Key/value file describing intermediate round states and outputs.',
    'aes128_encrypt_core': 'Key/value file with key, plaintext, ciphertext, and optional L2 profiles.',
}

_TB_PLUSARGS = {
    'aes_sbox': ['+profile=rand_small|rand_medium', '+cases', '+seed', '+vecfile'],
    'aes_key_schedule_128': [
        '+profile=rand_small|rand_medium',
        '+cases',
        '+seed',
        '+vecfile',
    ],
    'aes_round_transform': [
        '+profile=rand_small|rand_medium',
        '+cases',
        '+seed',
        '+vecfile',
    ],
    'aes128_encrypt_core': [
        '+profile=rand_small|rand_medium|back_to_back|mid_reset',
        '+cases',
        '+seed',
        '+vecfile',
    ],
}


def _json_dump(path: Path, payload: dict[str, Any]) -> Path:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(payload, indent=2, sort_keys=True), encoding='utf-8')
    return path


def build_module_contract(*, spec_ir: SpecIR, node: PlanDAGNode) -> ModuleContract:
    del spec_ir
    ports = [
        PortSpec(
            name=name,
            direction=direction,
            width=width,
            description=description,
        )
        for name, direction, width, description in _MODULE_PORTS[node.module_id]
    ]
    dependency_interfaces = [
        f'{dependency} must remain compatible with the frozen AES MVP taxonomy.'
        for dependency in node.depends_on
    ]
    return ModuleContract(
        module_id=node.module_id,
        summary=_MODULE_SUMMARIES[node.module_id],
        ports=ports,
        dependencies=list(node.depends_on),
        dependency_interfaces=dependency_interfaces,
        required_checkpoints=list(node.pass_criteria.l1.coverage_checkpoints),
        prohibited_constructs=[
            'Do not introduce SystemVerilog-only syntax.',
            'Do not rename frozen ports or checkpoint identifiers.',
            'Do not edit cross-module architecture from a node-local generation task.',
        ],
        writable_targets=[*node.rtl_files, node.tb_file],
        canonical_rtl_targets=list(node.rtl_files),
        canonical_tb_target=node.tb_file,
    )


def build_testbench_contract(
    *,
    spec_ir: SpecIR,
    node: PlanDAGNode,
) -> TestbenchContract:
    del spec_ir
    return TestbenchContract(
        module_id=node.module_id,
        tb_language='cpp',
        vector_format=_TB_VECTOR_FORMATS[node.module_id],
        checkpoint_names=list(node.pass_criteria.l1.coverage_checkpoints),
        plusargs=list(_TB_PLUSARGS[node.module_id]),
        success_rules=[
            'Emit the required CHECKPOINT lines to simulation.log.',
            'Remain self-checking and deterministic for frozen vectors.',
            'Do not rely on auto-generated testbenches.',
        ],
        writable_target=node.tb_file,
    )


def build_module_design_brief(
    *,
    spec_ir: SpecIR,
    plan_dag: PlanDAG,
    node: PlanDAGNode,
) -> ModuleDesignBrief:
    dependency_notes = []
    for dependency in node.depends_on:
        dependency_node = next(
            candidate
            for candidate in plan_dag.nodes
            if candidate.module_id == dependency
        )
        dependency_notes.append(
            f'{dependency} must remain compatible with {dependency_node.top_module} and '
            f'its frozen checkpoint contract {dependency_node.pass_criteria.l1.checkpoint_contract}.'
        )
    skill_paths = [
        str(ref.path)
        for ref in select_skill_refs(
            'aes_verilator_profile',
            'verilog_verilator',
            'deepseek_official_sdk',
            'verilator_mcp_setup',
        )
    ]
    return ModuleDesignBrief(
        module_id=node.module_id,
        summary=(
            f'Generate the {node.module_id} RTL/TB pair for the {spec_ir.variant} '
            f'{spec_ir.operation} MVP.'
        ),
        design_goals=list(_DESIGN_GOALS[node.module_id]),
        dependency_notes=dependency_notes,
        vectors=[node.pass_criteria.l1.vector_set],
        checkpoints=list(node.pass_criteria.l1.coverage_checkpoints),
        skill_paths=skill_paths,
        workspace_strategy=(
            'Generate and edit only draft files under the session workspace. '
            'Promote to canonical RTL/TB only after L0 and L1 pass.'
        ),
    )


def conversation_workspace_root(report_root: Path, module_id: str) -> Path:
    return (report_root / 'workspaces' / module_id).resolve()


def _draft_rtl_paths(node: PlanDAGNode, workspace_root: Path) -> dict[str, str]:
    return {
        Path(rtl).name: str(
            (workspace_root / 'draft' / 'rtl' / Path(rtl).name).resolve()
        )
        for rtl in node.rtl_files
    }


def _draft_tb_path(node: PlanDAGNode, workspace_root: Path) -> str:
    return str((workspace_root / 'draft' / 'tb' / Path(node.tb_file).name).resolve())


def _validation_paths(node: PlanDAGNode, workspace_root: Path) -> dict[str, str]:
    validation_root = (workspace_root / 'validation').resolve()
    return {
        'l0_result': str((validation_root / 'l0_result.json').resolve()),
        'module_run_result': str(
            (validation_root / 'sim' / 'module_run_result.json').resolve()
        ),
        'simulation_log': str((validation_root / 'sim' / 'simulation.log').resolve()),
        'waveform': str((validation_root / 'sim' / 'simulation.vcd').resolve()),
    }


def build_node_workspace_record(
    *,
    node: PlanDAGNode,
    workspace_root: Path,
    previous: NodeWorkspaceRecord | None = None,
) -> NodeWorkspaceRecord:
    state = previous.state if previous is not None else NodeWorkspaceState.MISSING
    validation_runs = previous.validation_runs if previous is not None else 0
    snapshot_paths = previous.snapshot_paths if previous is not None else []
    return NodeWorkspaceRecord(
        module_id=node.module_id,
        workspace_root=str(workspace_root),
        state=state,
        validation_runs=validation_runs,
        contract_paths={
            'module_contract': str(
                (workspace_root / 'contracts' / 'module_contract.json').resolve()
            ),
            'testbench_contract': str(
                (workspace_root / 'contracts' / 'testbench_contract.json').resolve()
            ),
            'design_brief': str(
                (workspace_root / 'contracts' / 'design_brief.json').resolve()
            ),
        },
        draft_paths={
            'rtl': json.dumps(_draft_rtl_paths(node, workspace_root), sort_keys=True),
            'tb': _draft_tb_path(node, workspace_root),
        },
        validation_paths=_validation_paths(node, workspace_root),
        canonical_targets=[
            *[str(path) for path in node.rtl_files],
            node.tb_file,
        ],
        snapshot_paths=list(snapshot_paths),
    )


def _module_scaffold(node: PlanDAGNode) -> str:
    if node.module_id == 'aes_sbox':
        return '\n'.join(
            [
                'module aes_sbox (',
                '    input [7:0] in_byte,',
                '    output reg [7:0] out_byte',
                ');',
                '    // TODO: replace scaffold logic with the AES S-box implementation.',
                '    always @* begin',
                "        out_byte = 8'h00;",
                '    end',
                'endmodule',
                '',
            ]
        )
    if node.module_id == 'aes_key_schedule_128':
        return '\n'.join(
            [
                'module aes_key_schedule_128 (',
                '    input [127:0] key,',
                '    input [3:0] round_index,',
                '    output reg [127:0] round_key',
                ');',
                '    // TODO: replace scaffold logic with the AES-128 key schedule.',
                '    always @* begin',
                "        round_key = key ^ {124'h0, round_index};",
                '    end',
                'endmodule',
                '',
            ]
        )
    if node.module_id == 'aes_round_transform':
        return '\n'.join(
            [
                'module aes_round_transform (',
                '    input [127:0] state_in,',
                '    input [127:0] round_key,',
                '    input final_round,',
                '    output reg [127:0] sub_bytes_state,',
                '    output reg [127:0] shift_rows_state,',
                '    output reg [127:0] mix_columns_state,',
                '    output reg [127:0] state_out',
                ');',
                '    // TODO: replace scaffold logic with the AES round transform.',
                '    always @* begin',
                '        sub_bytes_state = state_in;',
                '        shift_rows_state = state_in;',
                '        mix_columns_state = state_in;',
                "        state_out = state_in ^ round_key ^ {127'h0, final_round};",
                '    end',
                'endmodule',
                '',
            ]
        )
    return '\n'.join(
        [
            'module aes128_encrypt_core (',
            '    input clk,',
            '    input rst_n,',
            '    input start,',
            '    input [127:0] key,',
            '    input [127:0] plaintext,',
            '    output reg busy,',
            '    output reg done,',
            '    output reg [127:0] ciphertext',
            ');',
            '    // TODO: replace scaffold logic with the iterative AES-128 encrypt core.',
            '    always @(posedge clk or negedge rst_n) begin',
            '        if (!rst_n) begin',
            "            busy <= 1'b0;",
            "            done <= 1'b0;",
            "            ciphertext <= 128'h0;",
            '        end else begin',
            "            busy <= 1'b0;",
            "            done <= 1'b0;",
            '            if (start) begin',
            '                ciphertext <= plaintext ^ key;',
            "                done <= 1'b1;",
            '            end',
            '        end',
            '    end',
            'endmodule',
            '',
        ]
    )


def _tb_scaffold(node: PlanDAGNode) -> str:
    top_header = f'V{node.top_module}.h'
    top_class = f'V{node.top_module}'
    return '\n'.join(
        [
            '#include <verilated.h>',
            '',
            '#include <iostream>',
            '',
            f'#include "{top_header}"',
            '',
            'int main(int argc, char** argv) {',
            '    Verilated::commandArgs(argc, argv);',
            f'    {top_class} dut;',
            '    dut.eval();',
            '    std::cout << "TODO: scaffold testbench, no checkpoints emitted yet." << std::endl;',
            '    return 0;',
            '}',
            '',
        ]
    )


def initialize_node_workspace(
    *,
    spec_ir: SpecIR,
    plan_dag: PlanDAG,
    node: PlanDAGNode,
    workspace_root: Path,
) -> NodeWorkspaceRecord:
    module_contract = build_module_contract(spec_ir=spec_ir, node=node)
    testbench_contract = build_testbench_contract(spec_ir=spec_ir, node=node)
    design_brief = build_module_design_brief(
        spec_ir=spec_ir,
        plan_dag=plan_dag,
        node=node,
    )

    previous: NodeWorkspaceRecord | None = None
    workspace_state_path = workspace_root / 'workspace_state.json'
    if workspace_state_path.is_file():
        previous = NodeWorkspaceRecord.model_validate_json(
            workspace_state_path.read_text(encoding='utf-8')
        )

    workspace_root.mkdir(parents=True, exist_ok=True)
    _json_dump(
        workspace_root / 'contracts' / 'module_contract.json',
        module_contract.model_dump(),
    )
    _json_dump(
        workspace_root / 'contracts' / 'testbench_contract.json',
        testbench_contract.model_dump(),
    )
    _json_dump(
        workspace_root / 'contracts' / 'design_brief.json',
        design_brief.model_dump(),
    )

    draft_rtl_targets = _draft_rtl_paths(node, workspace_root)
    for draft_path in draft_rtl_targets.values():
        candidate = Path(draft_path)
        candidate.parent.mkdir(parents=True, exist_ok=True)
        if not candidate.exists():
            candidate.write_text(_module_scaffold(node), encoding='utf-8')

    draft_tb_path = Path(_draft_tb_path(node, workspace_root))
    draft_tb_path.parent.mkdir(parents=True, exist_ok=True)
    if not draft_tb_path.exists():
        draft_tb_path.write_text(_tb_scaffold(node), encoding='utf-8')

    record = build_node_workspace_record(
        node=node,
        workspace_root=workspace_root,
        previous=previous,
    )
    record = record.model_copy(update={'state': NodeWorkspaceState.DRAFT_READY})
    _json_dump(workspace_state_path, record.model_dump())
    return record


def load_workspace_record(workspace_root: Path) -> NodeWorkspaceRecord:
    path = workspace_root / 'workspace_state.json'
    return NodeWorkspaceRecord.model_validate_json(path.read_text(encoding='utf-8'))


def write_workspace_record(record: NodeWorkspaceRecord) -> Path:
    return _json_dump(
        Path(record.workspace_root) / 'workspace_state.json',
        record.model_dump(),
    )


def write_generation_result(
    *,
    workspace_record: NodeWorkspaceRecord,
    node: PlanDAGNode,
    validation_status: str,
    promoted: bool,
    changed_files: list[str],
    checkpoint_summary: dict[str, str],
    missing_checkpoints: list[str],
    failed_checkpoints: list[str],
) -> Path:
    workspace_root = Path(workspace_record.workspace_root)
    draft_rtl_paths = json.loads(workspace_record.draft_paths['rtl'])
    payload = {
        'module_id': node.module_id,
        'workspace_state': workspace_record.state.value,
        'design_brief_path': workspace_record.contract_paths['design_brief'],
        'draft_rtl_paths': list(draft_rtl_paths.values()),
        'draft_tb_path': workspace_record.draft_paths['tb'],
        'validation_status': validation_status,
        'validation_paths': dict(workspace_record.validation_paths),
        'workspace_state_path': str(
            (workspace_root / 'workspace_state.json').resolve()
        ),
        'repair_attempts': max(0, workspace_record.validation_runs - 1),
        'promoted': promoted,
        'canonical_targets': workspace_record.canonical_targets,
        'changed_files': changed_files,
        'checkpoint_summary': checkpoint_summary,
        'missing_checkpoints': list(missing_checkpoints),
        'failed_checkpoints': list(failed_checkpoints),
    }
    return _json_dump(workspace_root / 'generation_result.json', payload)


def increment_validation_runs(record: NodeWorkspaceRecord) -> NodeWorkspaceRecord:
    return record.model_copy(update={'validation_runs': record.validation_runs + 1})


def build_workspace_node(
    *,
    node: PlanDAGNode,
    workspace_record: NodeWorkspaceRecord,
    dependency_rtl_files: list[str] | None = None,
) -> PlanDAGNode:
    draft_rtl_map = json.loads(workspace_record.draft_paths['rtl'])
    draft_rtl_files = list(draft_rtl_map.values())
    if dependency_rtl_files and node.module_id == 'aes128_encrypt_core':
        compile_rtl_files = [*dependency_rtl_files, *draft_rtl_files]
    else:
        compile_rtl_files = draft_rtl_files
    workspace_root = Path(workspace_record.workspace_root)
    return node.model_copy(
        update={
            'rtl_files': compile_rtl_files,
            'tb_file': workspace_record.draft_paths['tb'],
            'build_output_dir': str(
                (workspace_root / 'validation' / 'build').resolve()
            ),
            'sim_output_dir': str((workspace_root / 'validation' / 'sim').resolve()),
        }
    )


def evaluate_validation_result(
    *,
    node: PlanDAGNode,
    l1_payload: dict[str, Any] | None,
) -> tuple[str, dict[str, Any]]:
    if not l1_payload:
        return 'failed', {
            'checkpoint_summary': {},
            'missing_checkpoints': list(node.pass_criteria.l1.coverage_checkpoints),
            'failed_checkpoints': [],
        }
    checkpoint_summary = l1_payload.get('checkpoint_summary', {})
    if not isinstance(checkpoint_summary, dict):
        checkpoint_summary = {}
    rollup = summarize_required_checkpoints(
        checkpoint_summary,
        tuple(node.pass_criteria.l1.coverage_checkpoints),
    )
    validation_status = (
        'passed' if not rollup['missing'] and not rollup['failed'] else 'failed'
    )
    return validation_status, {
        'checkpoint_summary': checkpoint_summary,
        'missing_checkpoints': rollup['missing'],
        'failed_checkpoints': rollup['failed'],
    }


def promote_workspace(
    *,
    package_root: Path,
    node: PlanDAGNode,
    workspace_record: NodeWorkspaceRecord,
    checkpoint_summary: dict[str, str],
) -> PromotionRecord:
    workspace_root = Path(workspace_record.workspace_root)
    draft_rtl_map = json.loads(workspace_record.draft_paths['rtl'])
    draft_targets = [Path(path) for path in draft_rtl_map.values()]
    draft_tb = Path(workspace_record.draft_paths['tb'])
    snapshot_root = (workspace_root / 'promotion' / 'snapshots').resolve()
    snapshot_root.mkdir(parents=True, exist_ok=True)

    snapshot_paths: list[str] = []
    promoted_targets: list[str] = []
    for source, target in zip(
        [*draft_targets, draft_tb],
        [
            *[(package_root / path).resolve() for path in node.rtl_files],
            (package_root / node.tb_file).resolve(),
        ],
        strict=True,
    ):
        target.parent.mkdir(parents=True, exist_ok=True)
        if target.exists():
            snapshot_path = (snapshot_root / target.name).resolve()
            shutil.copyfile(target, snapshot_path)
            snapshot_paths.append(str(snapshot_path))
        shutil.copyfile(source, target)
        promoted_targets.append(str(target))

    record = PromotionRecord(
        module_id=node.module_id,
        promoted_at=datetime.now(UTC).isoformat(),
        draft_paths=[str(path) for path in [*draft_targets, draft_tb]],
        canonical_targets=promoted_targets,
        snapshot_paths=snapshot_paths,
        validation_paths=list(workspace_record.validation_paths.values()),
        checkpoint_summary=checkpoint_summary,
    )
    _json_dump(
        workspace_root / 'promotion' / 'promotion_record.json',
        record.model_dump(),
    )
    return record
