"""Generation-first contracts and draft-workspace helpers."""

from __future__ import annotations

import hashlib
import json
import shutil
from datetime import UTC, datetime
from pathlib import Path
from typing import Any

from MultiAgent_FPGA.aes_mvp.artifacts import (
    EditReceipt,
    ModuleContract,
    ModuleDesignBrief,
    NodeWorkspaceRecord,
    NodeWorkspaceState,
    PlanDAG,
    PlanDAGNode,
    PromotionRecord,
    RepairContract,
    SpecIR,
    TestbenchContract,
)
from MultiAgent_FPGA.aes_mvp.executor_contracts import summarize_required_checkpoints
from MultiAgent_FPGA.aes_mvp.paths import PACKAGE_ROOT
from MultiAgent_FPGA.aes_mvp.synthesis import ContractCompiler, resolve_vector_path

DEFAULT_REPAIR_BUDGET = 2
TOP_MODULE_REPAIR_BUDGET = 3
_DEFAULT_FILE_EXCERPT_LINES = 120
_TB_SUPPORT_HEADERS = ('aes_tb_common.hpp',)
_RTL_INCLUDE_SUFFIXES = ('.vh', '.svh')


def repair_budget_for_node(node: PlanDAGNode) -> int:
    if node.integration_role in ('top', 'sink'):
        return TOP_MODULE_REPAIR_BUDGET
    return DEFAULT_REPAIR_BUDGET


def _json_dump(path: Path, payload: dict[str, Any]) -> Path:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(payload, indent=2, sort_keys=True), encoding='utf-8')
    return path


def _file_digest(path: Path) -> str:
    digest = hashlib.sha256()
    digest.update(path.read_bytes())
    return digest.hexdigest()


def build_module_contract(
    *, spec_ir: SpecIR, plan_dag: PlanDAG, node: PlanDAGNode
) -> ModuleContract:
    compiler = ContractCompiler(spec_ir=spec_ir, plan_dag=plan_dag)
    return compiler.compile_module_contract(node)


def build_testbench_contract(
    *,
    spec_ir: SpecIR,
    plan_dag: PlanDAG,
    node: PlanDAGNode,
) -> TestbenchContract:
    compiler = ContractCompiler(spec_ir=spec_ir, plan_dag=plan_dag)
    return compiler.compile_testbench_contract(node)


def build_module_design_brief(
    *,
    spec_ir: SpecIR,
    plan_dag: PlanDAG,
    node: PlanDAGNode,
) -> ModuleDesignBrief:
    compiler = ContractCompiler(spec_ir=spec_ir, plan_dag=plan_dag)
    return compiler.compile_design_brief(node)


def conversation_workspace_root(report_root: Path, module_id: str) -> Path:
    return (report_root / 'workspaces' / module_id).resolve()


def conversation_promoted_root(report_root: Path) -> Path:
    return (report_root / 'promoted').resolve()


def workspace_promoted_root(workspace_root: Path) -> Path:
    return conversation_promoted_root(workspace_root.parent.parent)


def workspace_repair_request_path(workspace_root: Path) -> Path:
    return (workspace_root / 'repair_request.json').resolve()


def workspace_edit_receipt_path(workspace_root: Path) -> Path:
    return (workspace_root / 'edit_receipt.json').resolve()


def _draft_rtl_paths(node: PlanDAGNode, workspace_root: Path) -> dict[str, str]:
    return {
        Path(rtl).name: str(
            (workspace_root / 'draft' / 'rtl' / Path(rtl).name).resolve()
        )
        for rtl in node.rtl_files
    }


def _draft_tb_path(node: PlanDAGNode, workspace_root: Path) -> str:
    return str((workspace_root / 'draft' / 'tb' / Path(node.tb_file).name).resolve())


def _promoted_rtl_paths(node: PlanDAGNode, promoted_root: Path) -> dict[str, str]:
    return {
        Path(rtl).name: str(
            (promoted_root / node.module_id / 'rtl' / Path(rtl).name).resolve()
        )
        for rtl in node.rtl_files
    }


def _promoted_tb_path(node: PlanDAGNode, promoted_root: Path) -> str:
    return str(
        (promoted_root / node.module_id / 'tb' / Path(node.tb_file).name).resolve()
    )


def _stage_rtl_include_files(target_dir: Path) -> list[str]:
    """Copy .vh/.svh include files from source RTL into the workspace draft RTL dir."""
    staged: list[str] = []
    target_dir.mkdir(parents=True, exist_ok=True)
    rtl_source = PACKAGE_ROOT / 'rtl'
    if not rtl_source.is_dir():
        return staged
    for source in rtl_source.iterdir():
        if source.suffix.lower() in _RTL_INCLUDE_SUFFIXES and source.is_file():
            target = (target_dir / source.name).resolve()
            shutil.copyfile(source, target)
            staged.append(str(target))
    return staged


def _stage_tb_support_headers(target_dir: Path) -> list[str]:
    staged: list[str] = []
    target_dir.mkdir(parents=True, exist_ok=True)
    for name in _TB_SUPPORT_HEADERS:
        source = (PACKAGE_ROOT / 'tb' / name).resolve()
        if not source.is_file():
            continue
        target = (target_dir / name).resolve()
        shutil.copyfile(source, target)
        staged.append(str(target))
    return staged


def _validation_paths(node: PlanDAGNode, workspace_root: Path) -> dict[str, str]:
    validation_root = (workspace_root / 'validation').resolve()
    return {
        'l0_result': str((validation_root / 'l0_result.json').resolve()),
        'module_run_result': str(
            (validation_root / 'sim' / 'module_run_result.json').resolve()
        ),
        'simulation_log': str((validation_root / 'sim' / 'simulation.log').resolve()),
        'waveform': str((validation_root / 'sim' / 'simulation.vcd').resolve()),
        'validation_summary': str(
            (validation_root / 'validation_summary.json').resolve()
        ),
        'validation_error': str((validation_root / 'validation_error.json').resolve()),
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
        promoted_paths={
            'rtl': json.dumps(
                _promoted_rtl_paths(node, workspace_promoted_root(workspace_root)),
                sort_keys=True,
            ),
            'tb': _promoted_tb_path(node, workspace_promoted_root(workspace_root)),
        },
        validation_paths=_validation_paths(node, workspace_root),
        canonical_targets=[*list(node.rtl_files), node.tb_file],
        snapshot_paths=list(snapshot_paths),
    )


def _validation_error_message(workspace_record: NodeWorkspaceRecord) -> str | None:
    for key in ('validation_summary', 'validation_error'):
        candidate = Path(workspace_record.validation_paths[key])
        if not candidate.is_file():
            continue
        try:
            payload = json.loads(candidate.read_text(encoding='utf-8'))
        except json.JSONDecodeError:
            continue
        error = payload.get('error')
        if isinstance(error, dict):
            message = error.get('message')
            if isinstance(message, str) and message.strip():
                return message
    return None


def _repair_guidance(
    *,
    workspace_record: NodeWorkspaceRecord,
    node: PlanDAGNode,
    missing_checkpoints: list[str],
    failed_checkpoints: list[str],
) -> list[str]:
    guidance: list[str] = []
    if missing_checkpoints:
        guidance.append(
            'Update the draft testbench so it emits the required CHECKPOINT lines '
            f'using the frozen contract {node.pass_criteria.l1.checkpoint_contract}: '
            + ', '.join(missing_checkpoints)
        )
    if failed_checkpoints:
        guidance.append(
            'Fix the first failed checkpoint before broader cleanup: '
            + ', '.join(failed_checkpoints)
        )
    error_message = _validation_error_message(workspace_record)
    if error_message and 'Compilation failed' in error_message:
        guidance.append(
            'Resolve compile or elaboration warnings/errors before rerunning the executor command.'
        )
    if not guidance:
        guidance.append(
            'Read the design brief and validation artifacts, make one focused draft edit, then rerun the executor command.'
        )
    return guidance


def initialize_node_workspace(
    *,
    spec_ir: SpecIR,
    plan_dag: PlanDAG,
    node: PlanDAGNode,
    workspace_root: Path,
) -> NodeWorkspaceRecord:
    module_contract = build_module_contract(
        spec_ir=spec_ir, plan_dag=plan_dag, node=node
    )
    testbench_contract = build_testbench_contract(
        spec_ir=spec_ir,
        plan_dag=plan_dag,
        node=node,
    )
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

    # Pre-populate drafts from verified memory via MemoryStore.
    from MultiAgent_FPGA.aes_mvp.memory import MemoryStore

    store = MemoryStore()
    written = store.populate_workspace(node.module_id, workspace_root)

    # Also populate any additional RTL paths (e.g. top-module includes both files)
    draft_rtl_targets = _draft_rtl_paths(node, workspace_root)
    for draft_path in draft_rtl_targets.values():
        candidate = Path(draft_path)
        if candidate != written.get('rtl') and not candidate.exists():
            candidate.parent.mkdir(parents=True, exist_ok=True)
            if written.get('rtl') and written['rtl'].exists():
                shutil.copy2(str(written['rtl']), str(candidate))

    # Stage RTL include files (.vh/.svh) into draft RTL directory.
    draft_rtl_dir = list(draft_rtl_targets.values())[0] if draft_rtl_targets else None
    if draft_rtl_dir:
        _stage_rtl_include_files(Path(draft_rtl_dir).parent)

    draft_tb_path = Path(_draft_tb_path(node, workspace_root))
    if draft_tb_path != written.get('tb'):
        draft_tb_path.parent.mkdir(parents=True, exist_ok=True)
    _stage_tb_support_headers(draft_tb_path.parent)

    record = build_node_workspace_record(
        node=node,
        workspace_root=workspace_root,
        previous=previous,
    )
    if previous is None:
        record = record.model_copy(update={'state': NodeWorkspaceState.DRAFT_READY})
    _json_dump(workspace_state_path, record.model_dump())
    return record


def load_workspace_record(workspace_root: Path) -> NodeWorkspaceRecord:
    path = workspace_root / 'workspace_state.json'
    return NodeWorkspaceRecord.model_validate_json(path.read_text(encoding='utf-8'))


def load_repair_contract(workspace_root: Path) -> RepairContract:
    path = (
        workspace_root
        if workspace_root.is_file()
        else workspace_repair_request_path(workspace_root)
    )
    return RepairContract.model_validate_json(path.read_text(encoding='utf-8'))


def clear_repair_artifacts(workspace_root: Path) -> None:
    for candidate in (
        workspace_repair_request_path(workspace_root),
        workspace_edit_receipt_path(workspace_root),
    ):
        if candidate.is_file():
            candidate.unlink()


def write_workspace_record(record: NodeWorkspaceRecord) -> Path:
    return _json_dump(
        Path(record.workspace_root) / 'workspace_state.json',
        record.model_dump(),
    )


def _file_contains_tokens(path: Path, tokens: list[str]) -> bool:
    if not tokens or not path.is_file():
        return False
    contents = path.read_text(encoding='utf-8')
    return all(token in contents for token in tokens)


def _materialize_checkpoint_contract(
    checkpoint_contract: str | None,
    checkpoint_name: str | None,
) -> str | None:
    if checkpoint_name:
        if checkpoint_contract:
            materialized = checkpoint_contract.replace('CHK_*', checkpoint_name)
            if checkpoint_name in materialized:
                return materialized
        return f'CHECKPOINT|{checkpoint_name}|PASS|<detail>'
    if checkpoint_contract:
        return checkpoint_contract
    return None


def _checkpoint_contract_prefixes(
    *,
    node: PlanDAGNode,
    checkpoint_names: list[str],
) -> list[str]:
    prefixes: list[str] = []
    for checkpoint_name in checkpoint_names:
        materialized = _materialize_checkpoint_contract(
            node.pass_criteria.l1.checkpoint_contract,
            checkpoint_name,
        )
        if materialized:
            prefixes.append(materialized.replace('<detail>', ''))
    return prefixes


def write_edit_receipt(
    *,
    workspace_root: Path,
    repair_contract: RepairContract,
    edited_files: list[str],
    first_edit_summary: str,
) -> Path:
    receipt = EditReceipt(
        module_id=repair_contract.module_id,
        workspace_root=str(workspace_root),
        repair_request_path=str(workspace_repair_request_path(workspace_root)),
        edited_files=edited_files,
        first_edit_summary=first_edit_summary,
        rerun_command=repair_contract.rerun_command,
    )
    return _json_dump(workspace_edit_receipt_path(workspace_root), receipt.model_dump())


def _select_repair_targets(
    *,
    workspace_record: NodeWorkspaceRecord,
    node: PlanDAGNode,
    missing_checkpoints: list[str],
    failed_checkpoints: list[str],
) -> tuple[str, list[str]]:
    draft_rtl_map = json.loads(workspace_record.draft_paths['rtl'])
    rtl_paths = list(draft_rtl_map.values())
    tb_path = workspace_record.draft_paths['tb']
    _file_contains_tokens(
        Path(tb_path),
        _checkpoint_contract_prefixes(
            node=node,
            checkpoint_names=[*missing_checkpoints, *failed_checkpoints],
        ),
    )

    error_message = _validation_error_message(workspace_record)
    is_compile_failure = bool(error_message and 'Compilation failed' in error_message)

    if is_compile_failure and rtl_paths:
        primary = rtl_paths[0]
    elif failed_checkpoints:
        primary = (rtl_paths or [tb_path])[0]
    elif missing_checkpoints:
        if node.integration_role == 'top':
            primary = (rtl_paths or [tb_path])[0]
        else:
            primary = tb_path
    elif rtl_paths:
        primary = rtl_paths[0]
    else:
        primary = tb_path

    secondary = [path for path in [*rtl_paths, tb_path] if path != primary]
    return primary, secondary


def _file_excerpt(path: Path, *, max_lines: int = 12) -> str | None:
    if not path.is_file():
        return None
    lines = path.read_text(encoding='utf-8').splitlines()
    return '\n'.join(lines[:max_lines]).strip() or None


def _repair_target_reason(
    *,
    primary_target_file: str,
    workspace_record: NodeWorkspaceRecord,
    missing_checkpoints: list[str],
    failed_checkpoints: list[str],
) -> str:
    tb_path = workspace_record.draft_paths['tb']
    if primary_target_file == tb_path and (missing_checkpoints or failed_checkpoints):
        return (
            'testbench-first repair: validation failed on missing or failed '
            'checkpoints, so the shortest meaningful first edit is to make the '
            'draft testbench emit the expected CHECKPOINT contract line.'
        )
    if primary_target_file.endswith('.cpp'):
        return 'testbench-first repair: draft testbench needs concrete harness logic.'
    return 'rtl-first repair: draft RTL contains incorrect logic or failed functional behavior.'


def _build_first_edit_steps(
    *,
    node: PlanDAGNode,
    primary_target_file: str,
    expected_checkpoint: str | None,
    expected_checkpoint_contract: str | None,
) -> tuple[list[str], list[str]]:
    must_add_tokens: list[str] = []
    first_edit_steps = [
        f'Open {primary_target_file} and fix the identified error with concrete logic or checks.',
    ]
    if primary_target_file.endswith('.cpp') and expected_checkpoint:
        checkpoint_prefix = (expected_checkpoint_contract or '').replace(
            '<detail>', ''
        ) or f'CHECKPOINT|{expected_checkpoint}|PASS|'
        must_add_tokens.append(checkpoint_prefix)
        first_edit_steps.append(
            'Add code that emits the exact CHECKPOINT contract prefix '
            f'"{checkpoint_prefix}" on the passing path.'
        )
    elif primary_target_file.endswith('.v'):
        first_edit_steps.append(
            'Fix incorrect RTL assignments with correct combinational or sequential behavior.'
        )
        if node.integration_role == 'top':
            must_add_tokens.extend(
                [
                    'STATE_IDLE',
                    'STATE_BUSY',
                    'if (!rst_n)',
                    'if (start)',
                    "done <= 1'b1",
                ]
            )
            first_edit_steps.extend(
                [
                    'In the first RTL edit, install the top-core handshake FSM skeleton: STATE_IDLE/STATE_BUSY/STATE_DONE, reset handling, start acceptance, busy gating, and done pulse behavior.',
                    'Latch key/plaintext on start, hold busy high through the active window, and structure the control so the ciphertext is released on the 11-cycle completion boundary.',
                    'Keep the AES datapath hook local to this module for the MVP; you may use a local aes128_encrypt_block helper function or equivalent behavioral round helper.',
                ]
            )
        vector_hint = _rtl_vector_hint(node)
        if vector_hint:
            first_edit_steps.append(vector_hint)
    first_edit_steps.append(
        'Save the primary file before running the repair receipt command.'
    )
    return first_edit_steps, must_add_tokens


def _rtl_vector_hint(node: PlanDAGNode) -> str | None:
    vector_path = resolve_vector_path(node.pass_criteria.l1.vector_set)
    if vector_path is None:
        return None
    examples = [
        line.strip()
        for line in vector_path.read_text(encoding='utf-8').splitlines()
        if line.strip() and not line.lstrip().startswith('#')
    ]
    if not examples:
        return None
    if node.module_id == 'aes_sbox':
        mappings = []
        for example in examples:
            if ',' not in example:
                continue
            input_hex, output_hex = (part.strip() for part in example.split(',', 1))
            mappings.append(f"8'h{input_hex} -> 8'h{output_hex}")
        if mappings:
            return (
                'Implement these frozen AES S-box KAT mappings in the RTL first: '
                + ', '.join(mappings)
                + '. A case statement covering these entries is acceptable for the current vector set.'
            )
    if node.integration_role == 'top':
        extra_examples: list[str] = []
        for candidate_name in (
            'aes128_encrypt_core_zero.txt',
            'aes128_encrypt_core_regress.txt',
        ):
            candidate_path = vector_path.with_name(candidate_name)
            if not candidate_path.is_file():
                continue
            extra_lines = [
                line.strip()
                for line in candidate_path.read_text(encoding='utf-8').splitlines()
                if line.strip() and not line.lstrip().startswith('#')
            ]
            if extra_lines:
                extra_examples.extend(extra_lines)
        if extra_examples:
            examples = [*examples, *extra_examples]
    return (
        'Preserve these frozen vector anchors from '
        f'{node.pass_criteria.l1.vector_set}: ' + '; '.join(examples) + '.'
    )


def write_repair_request(
    *,
    workspace_record: NodeWorkspaceRecord,
    node: PlanDAGNode,
    generation_result_path: Path,
    failure_phase: str | None = None,
    missing_checkpoints: list[str],
    failed_checkpoints: list[str],
    rerun_command: str,
) -> Path:
    workspace_root = Path(workspace_record.workspace_root)
    receipt_path = workspace_edit_receipt_path(workspace_root)
    if receipt_path.is_file():
        receipt_path.unlink()
    primary_target_file, secondary_target_files = _select_repair_targets(
        workspace_record=workspace_record,
        node=node,
        missing_checkpoints=missing_checkpoints,
        failed_checkpoints=failed_checkpoints,
    )
    expected_checkpoint = None
    if failed_checkpoints:
        expected_checkpoint = failed_checkpoints[0]
    elif missing_checkpoints:
        expected_checkpoint = missing_checkpoints[0]
    expected_checkpoint_contract = _materialize_checkpoint_contract(
        node.pass_criteria.l1.checkpoint_contract,
        expected_checkpoint,
    )

    primary_path = Path(primary_target_file)
    primary_target_reason = _repair_target_reason(
        primary_target_file=primary_target_file,
        workspace_record=workspace_record,
        missing_checkpoints=missing_checkpoints,
        failed_checkpoints=failed_checkpoints,
    )
    first_edit_steps, must_add_tokens = _build_first_edit_steps(
        node=node,
        primary_target_file=primary_target_file,
        expected_checkpoint=expected_checkpoint,
        expected_checkpoint_contract=expected_checkpoint_contract,
    )
    required_first_edit = (
        f'Edit {primary_target_file} first. Fix the identified error '
        f'until {expected_checkpoint or node.module_id} is actionable.'
    )
    error_excerpt = _validation_error_message(workspace_record)
    tracked_files = [primary_target_file, *secondary_target_files]
    baseline_hashes = {
        path: _file_digest(Path(path)) for path in tracked_files if Path(path).is_file()
    }
    from MultiAgent_FPGA.aes_mvp.artifacts import ValidationFailurePhase

    resolved_phase = None
    if failure_phase is not None:
        if isinstance(failure_phase, ValidationFailurePhase):
            resolved_phase = failure_phase
        elif isinstance(failure_phase, str):
            resolved_phase = ValidationFailurePhase(failure_phase)
    contract = RepairContract(
        module_id=node.module_id,
        workspace_root=str(workspace_root),
        generation_result_path=str(generation_result_path),
        workspace_state_path=str((workspace_root / 'workspace_state.json').resolve()),
        validation_summary_path=workspace_record.validation_paths['validation_summary'],
        validation_error_path=workspace_record.validation_paths['validation_error'],
        failure_phase=resolved_phase,
        primary_target_file=primary_target_file,
        primary_target_reason=primary_target_reason,
        primary_file_excerpt=_file_excerpt(primary_path),
        secondary_target_files=secondary_target_files,
        required_first_edit=required_first_edit,
        first_edit_steps=first_edit_steps,
        must_add_tokens=must_add_tokens,
        expected_checkpoint=expected_checkpoint,
        error_excerpt=error_excerpt,
        rerun_command=rerun_command,
        edit_verification={
            'receipt_path': str(workspace_edit_receipt_path(workspace_root)),
            'baseline_hashes': baseline_hashes,
            'required_changed_file': primary_target_file,
        },
    )
    return _json_dump(
        workspace_repair_request_path(workspace_root), contract.model_dump()
    )


def verify_repair_edit(
    *,
    workspace_root: Path,
    repair_contract: RepairContract,
) -> tuple[bool, list[str], str]:
    baseline_hashes = {
        str(path): str(digest)
        for path, digest in dict(repair_contract.edit_verification)
        .get('baseline_hashes', {})
        .items()
    }
    edited_files: list[str] = []
    for path_str, baseline in baseline_hashes.items():
        candidate = Path(path_str)
        if candidate.is_file() and _file_digest(candidate) != baseline:
            edited_files.append(str(candidate))

    if repair_contract.primary_target_file not in edited_files:
        return (
            False,
            edited_files,
            'repair phase must edit the primary_target_file before revalidation',
        )

    if repair_contract.must_add_tokens:
        primary_text = Path(repair_contract.primary_target_file).read_text(
            encoding='utf-8'
        )

        def _token_present(token: str, text: str) -> bool:
            if token in text:
                return True
            # Accept emit_checkpoint helper as equivalent to literal CHECKPOINT| line.
            # Token format: CHECKPOINT|<name>|PASS|
            if token.startswith('CHECKPOINT|') and token.endswith('|'):
                checkpoint_name = token.split('|')[1]
                if f'emit_checkpoint("{checkpoint_name}"' in text:
                    return True
                if f"emit_checkpoint('{checkpoint_name}'" in text:
                    return True
            return False

        missing_tokens = [
            token
            for token in repair_contract.must_add_tokens
            if not _token_present(token, primary_text)
        ]
        if missing_tokens:
            return (
                False,
                edited_files,
                'repair phase did not add the required first-edit tokens: '
                + ', '.join(missing_tokens),
            )

    return True, edited_files, 'repair edit verified'


def write_generation_result(
    *,
    workspace_record: NodeWorkspaceRecord,
    node: PlanDAGNode,
    validation_status: str,
    failure_phase: str | None = None,
    promoted: bool,
    changed_files: list[str],
    checkpoint_summary: dict[str, str],
    missing_checkpoints: list[str],
    failed_checkpoints: list[str],
    recommended_mode: str | None = None,
) -> Path:
    workspace_root = Path(workspace_record.workspace_root)
    draft_rtl_paths = json.loads(workspace_record.draft_paths['rtl'])
    repair_guidance = _repair_guidance(
        workspace_record=workspace_record,
        node=node,
        missing_checkpoints=missing_checkpoints,
        failed_checkpoints=failed_checkpoints,
    )
    payload = {
        'module_id': node.module_id,
        'workspace_state': workspace_record.state.value,
        'design_brief_path': workspace_record.contract_paths['design_brief'],
        'draft_rtl_paths': list(draft_rtl_paths.values()),
        'draft_tb_path': workspace_record.draft_paths['tb'],
        'validation_status': validation_status,
        'failure_phase': failure_phase.value
        if hasattr(failure_phase, 'value')
        else failure_phase,
        'validation_paths': dict(workspace_record.validation_paths),
        'workspace_state_path': str(
            (workspace_root / 'workspace_state.json').resolve()
        ),
        'repair_attempts': max(0, workspace_record.validation_runs - 1),
        'promoted': promoted,
        'promoted_targets': workspace_record.promoted_paths,
        'changed_files': changed_files,
        'checkpoint_summary': checkpoint_summary,
        'missing_checkpoints': list(missing_checkpoints),
        'failed_checkpoints': list(failed_checkpoints),
        'repair_guidance': repair_guidance,
        'recommended_mode': recommended_mode,
        'repair_request_path': str(workspace_repair_request_path(workspace_root)),
        'edit_receipt_path': str(workspace_edit_receipt_path(workspace_root)),
    }
    return _json_dump(workspace_root / 'generation_result.json', payload)


def write_cascade_block_result(
    *,
    workspace_root: Path,
    module_id: str,
    blocked_by: str,
) -> Path:
    """Write a generation_result.json marking a module as cascade-blocked."""
    payload = {
        'module_id': module_id,
        'workspace_state': NodeWorkspaceState.BLOCKED.value,
        'validation_status': 'blocked',
        'failure_phase': None,
        'cascade_blocked_by': blocked_by,
        'promoted': False,
        'checkpoint_summary': {},
        'missing_checkpoints': [],
        'failed_checkpoints': [],
        'recommended_mode': None,
    }
    return _json_dump(workspace_root / 'generation_result.json', payload)


def write_budget_exhausted_result(
    *,
    workspace_root: Path,
    module_id: str,
    repair_rounds_consumed: int,
) -> Path:
    """Write generation_result.json marking a module as blocked due to repair budget exhaustion."""
    payload = {
        'module_id': module_id,
        'workspace_state': NodeWorkspaceState.BLOCKED.value,
        'validation_status': 'failed',
        'failure_phase': 'repair_budget_exhausted',
        'repair_budget_exhausted': True,
        'repair_rounds_consumed': repair_rounds_consumed,
        'promoted': False,
        'checkpoint_summary': {},
        'missing_checkpoints': [],
        'failed_checkpoints': [],
        'recommended_mode': None,
    }
    return _json_dump(workspace_root / 'generation_result.json', payload)


def write_defensive_failure_result(
    *,
    workspace_root: Path,
    module_id: str,
    failure_reason: str,
) -> Path:
    """Write a minimal generation_result.json when the executor crashes/times out."""
    payload = {
        'module_id': module_id,
        'workspace_state': NodeWorkspaceState.FAILED.value,
        'validation_status': 'failed',
        'failure_phase': 'executor_crash',
        'failure_reason': failure_reason,
        'promoted': False,
        'checkpoint_summary': {},
        'missing_checkpoints': [],
        'failed_checkpoints': [],
        'recommended_mode': None,
    }
    return _json_dump(workspace_root / 'generation_result.json', payload)


def increment_validation_runs(record: NodeWorkspaceRecord) -> NodeWorkspaceRecord:
    return record.model_copy(update={'validation_runs': record.validation_runs + 1})


def write_validation_summary(
    *,
    workspace_record: NodeWorkspaceRecord,
    payload: dict[str, Any],
) -> Path:
    return _json_dump(
        Path(workspace_record.validation_paths['validation_summary']),
        payload,
    )


def write_validation_error(
    *,
    workspace_record: NodeWorkspaceRecord,
    payload: dict[str, Any],
) -> Path:
    return _json_dump(
        Path(workspace_record.validation_paths['validation_error']),
        payload,
    )


def build_workspace_node(
    *,
    node: PlanDAGNode,
    workspace_record: NodeWorkspaceRecord,
    dependency_rtl_files: list[str] | None = None,
) -> PlanDAGNode:
    draft_rtl_map = json.loads(workspace_record.draft_paths['rtl'])
    draft_rtl_files = list(draft_rtl_map.values())
    compile_rtl_files = list(draft_rtl_files)
    if dependency_rtl_files:
        compile_rtl_files = [*dependency_rtl_files, *draft_rtl_files]
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


def build_promoted_node(
    *,
    node: PlanDAGNode,
    workspace_record: NodeWorkspaceRecord,
    promoted_root: Path,
    dependency_rtl_files: list[str] | None = None,
) -> PlanDAGNode:
    promoted_rtl_map = json.loads(workspace_record.promoted_paths['rtl'])
    promoted_rtl_files = list(promoted_rtl_map.values())
    compile_rtl_files = list(promoted_rtl_files)
    if dependency_rtl_files:
        compile_rtl_files = [*dependency_rtl_files, *promoted_rtl_files]
    workspace_root = Path(workspace_record.workspace_root)
    promoted_tb = _promoted_tb_path(node, promoted_root)
    return node.model_copy(
        update={
            'rtl_files': compile_rtl_files,
            'tb_file': promoted_tb,
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
            'failure_phase': 'l1_sim',
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
    failure_phase: str | None = None
    if rollup['missing']:
        failure_phase = 'checkpoint_missing'
    elif rollup['failed']:
        failure_phase = 'checkpoint_failed'
    return validation_status, {
        'checkpoint_summary': checkpoint_summary,
        'missing_checkpoints': rollup['missing'],
        'failed_checkpoints': rollup['failed'],
        'failure_phase': failure_phase,
    }


def promote_workspace(
    *,
    node: PlanDAGNode,
    workspace_record: NodeWorkspaceRecord,
    checkpoint_summary: dict[str, str],
) -> PromotionRecord:
    workspace_root = Path(workspace_record.workspace_root)
    promoted_root = workspace_promoted_root(workspace_root)
    draft_rtl_map = json.loads(workspace_record.draft_paths['rtl'])
    promoted_rtl_map = json.loads(workspace_record.promoted_paths['rtl'])
    draft_targets = [Path(path) for path in draft_rtl_map.values()]
    draft_tb = Path(workspace_record.draft_paths['tb'])
    snapshot_root = (workspace_root / 'promotion' / 'snapshots').resolve()
    snapshot_root.mkdir(parents=True, exist_ok=True)

    snapshot_paths: list[str] = []
    promoted_targets: list[str] = []
    for source, target in zip(
        [*draft_targets, draft_tb],
        [
            *[Path(path).resolve() for path in promoted_rtl_map.values()],
            Path(_promoted_tb_path(node, promoted_root)).resolve(),
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

    promoted_rtl_dir = next(
        (Path(p).resolve().parent for p in promoted_rtl_map.values()), None
    )
    if promoted_rtl_dir:
        promoted_rtl_includes = _stage_rtl_include_files(promoted_rtl_dir)
        promoted_targets.extend(promoted_rtl_includes)

    promoted_tb_support = _stage_tb_support_headers(
        Path(_promoted_tb_path(node, promoted_root)).resolve().parent
    )
    promoted_targets.extend(promoted_tb_support)

    record = PromotionRecord(
        module_id=node.module_id,
        promoted_at=datetime.now(UTC).isoformat(),
        draft_paths=[str(path) for path in [*draft_targets, draft_tb]],
        promoted_targets=promoted_targets,
        snapshot_paths=snapshot_paths,
        validation_paths=list(workspace_record.validation_paths.values()),
        checkpoint_summary=checkpoint_summary,
    )
    _json_dump(
        workspace_root / 'promotion' / 'promotion_record.json',
        record.model_dump(),
    )
    return record
