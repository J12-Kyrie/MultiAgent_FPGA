"""CLI entrypoint for the AES MVP framework package."""

from __future__ import annotations

import argparse
import json
import os
from dataclasses import asdict
from pathlib import Path

from MultiAgent_FPGA.aes_mvp.artifacts import (
    IntegrationRegressionManifest,
    NodeWorkspaceState,
    ValidationFailurePhase,
)
from MultiAgent_FPGA.aes_mvp.executors import (
    IntegrationRegressionExecutor,
    L0Executor,
    L1Executor,
    L2CampaignExecutor,
)
from MultiAgent_FPGA.aes_mvp.generation import (
    build_promoted_node,
    build_workspace_node,
    clear_repair_artifacts,
    evaluate_validation_result,
    increment_validation_runs,
    initialize_node_workspace,
    load_repair_contract,
    load_workspace_record,
    promote_workspace,
    repair_budget_for_node,
    verify_repair_edit,
    workspace_promoted_root,
    write_edit_receipt,
    write_generation_result,
    write_repair_request,
    write_validation_error,
    write_validation_summary,
    write_workspace_record,
)
from MultiAgent_FPGA.aes_mvp.llm_profiles import run_deepseek_preflight_suite
from MultiAgent_FPGA.aes_mvp.runtime import (
    ExecutionSession,
    RuntimeBootstrap,
    discover_sdk_environment,
)
from MultiAgent_FPGA.aes_mvp.synthesis import (
    IntegrationReadinessResolver,
    NodePolicyEngine,
    synthesize_integration_manifest,
)


def _validate_summary() -> dict[str, object]:
    bootstrap = RuntimeBootstrap.build(allow_placeholder_api_key=True)
    return bootstrap.to_summary()


def _smoke_sdk_summary() -> dict[str, object]:
    bootstrap = RuntimeBootstrap.build(allow_placeholder_api_key=True)
    session = ExecutionSession.create(bootstrap)
    try:
        conversation_summary = session.runner.describe(session.conversation)
        summary = bootstrap.to_summary()
        summary.update(
            {
                'sdk_available': discover_sdk_environment().available,
                'orchestrator_agent': session.conversation.agent.__class__.__name__,
                'conversation_id': session.conversation_id.hex,
                'conversation_summary': asdict(conversation_summary),
                'delegate_registrations': list(session.delegate_registrations),
                'report_root': str(session.report_root),
                'state_trace_path': str(session.state_trace_path),
                'report_tree_path': str(session.report_tree_path),
            }
        )
        return summary
    finally:
        session.conversation.close()


def _smoke_provider_summary() -> dict[str, object]:
    suite = run_deepseek_preflight_suite()
    return {
        'request_model': suite['request_model'],
        'resolved_model': suite['resolved_model'],
        'results': {
            'fast': asdict(suite['fast']),
            'thinking': asdict(suite['thinking']),
        },
    }


def _resolve_promoted_root(
    *, workspace_path: Path | None, promoted_root: str | None
) -> Path | None:
    if promoted_root:
        return Path(promoted_root).resolve()
    if workspace_path is not None:
        return workspace_promoted_root(workspace_path)
    return None


def _workspace_run_node_command(
    module_id: str,
    *,
    workspace_path: Path,
    promoted_path: Path | None,
) -> str:
    command = (
        'PYTHONPATH=. /opt/anaconda3/envs/openhands/bin/python '
        f'-m MultiAgent_FPGA.aes_mvp run-node {module_id} '
        f'--workspace-root {workspace_path}'
    )
    if promoted_path is not None:
        command += f' --promoted-root {promoted_path}'
    command += ' --strict-validation'
    return command


def _workspace_record_repair_edit_command(
    module_id: str,
    *,
    workspace_path: Path,
) -> str:
    return (
        'PYTHONPATH=. /opt/anaconda3/envs/openhands/bin/python '
        f'-m MultiAgent_FPGA.aes_mvp record-repair-edit {module_id} '
        f'--workspace-root {workspace_path} '
        '--strict'
    )


def _promoted_dependency_rtl_files(
    *,
    bootstrap: RuntimeBootstrap,
    node,
    promoted_path: Path | None,
) -> list[str] | None:
    if promoted_path is None or not node.depends_on:
        return None
    nodes_by_id = {
        candidate.module_id: candidate for candidate in bootstrap.plan_dag.nodes
    }
    # Transitive closure: collect all dependency RTL files (direct + indirect).
    visited: set[str] = set()
    queue = list(node.depends_on)
    dependency_rtl_files: list[str] = []
    while queue:
        dep_id = queue.pop(0)
        if dep_id in visited:
            continue
        visited.add(dep_id)
        dependency_node = nodes_by_id[dep_id]
        for rtl_file in dependency_node.rtl_files:
            dependency_rtl_files.append(
                str((promoted_path / dep_id / 'rtl' / Path(rtl_file).name).resolve())
            )
        queue.extend(dependency_node.depends_on)
    return dependency_rtl_files


def _build_promoted_integration_manifest(
    *,
    bootstrap: RuntimeBootstrap,
    promoted_path: Path,
    output_root: Path | None,
) -> IntegrationRegressionManifest:
    resolver = IntegrationReadinessResolver()
    promoted_modules = {
        child.name for child in promoted_path.iterdir() if child.is_dir()
    }
    sink = resolver.select_primary_sink(
        bootstrap.plan_dag, promoted_modules=promoted_modules
    )
    base_manifest = synthesize_integration_manifest(
        bootstrap.spec_ir, bootstrap.plan_dag
    )
    required_modules = resolver.dependency_closure(bootstrap.plan_dag, sink.module_id)
    nodes_by_id = {node.module_id: node for node in bootstrap.plan_dag.nodes}
    rtl_files: list[str] = []
    for module_id in required_modules:
        dependency_node = nodes_by_id[module_id]
        for rtl_file in dependency_node.rtl_files:
            rtl_files.append(
                str((promoted_path / module_id / 'rtl' / Path(rtl_file).name).resolve())
            )
    tb_file = str(
        (promoted_path / sink.module_id / 'tb' / Path(sink.tb_file).name).resolve()
    )
    integration_output_root = (
        output_root or (promoted_path.parent / 'integration')
    ).resolve()
    return base_manifest.model_copy(
        update={
            'top_module': sink.module_id,
            'rtl_files': rtl_files,
            'tb_file': tb_file,
            'required_modules': required_modules,
            'build_output_dir': str((integration_output_root / 'obj_dir').resolve()),
            'sim_output_dir': str(integration_output_root),
        }
    )


def _run_node(
    module_id: str,
    l2_profile: str | None,
    vecfile: str | None = None,
    cases: int | None = None,
    seed: int | None = None,
    workspace_root: str | None = None,
    promoted_root: str | None = None,
    increment_workspace_validation: bool = True,
) -> dict[str, object]:
    bootstrap = RuntimeBootstrap.build(allow_placeholder_api_key=True)
    orchestrator = bootstrap.orchestrator()
    node = orchestrator.get_node(module_id)
    adapter = bootstrap.create_verilator_adapter()
    l0 = L0Executor(
        adapter=adapter,
        package_root=bootstrap.workspace_root,
        integration_manifest=bootstrap.integration_manifest,
    )
    l1 = L1Executor(
        adapter=adapter,
        package_root=bootstrap.workspace_root,
        integration_manifest=bootstrap.integration_manifest,
    )

    manifest_override = None
    execution_node = node
    workspace_path: Path | None = None
    workspace_record = None
    promoted_path: Path | None = None
    policy_engine = NodePolicyEngine()
    repair_contract = None
    should_increment_validation = (
        bool(increment_workspace_validation) and l2_profile is None
    )
    if workspace_root:
        workspace_path = Path(workspace_root).resolve()
        workspace_record = initialize_node_workspace(
            spec_ir=bootstrap.spec_ir,
            plan_dag=bootstrap.plan_dag,
            node=node,
            workspace_root=workspace_path,
        )
        promoted_path = _resolve_promoted_root(
            workspace_path=workspace_path, promoted_root=promoted_root
        )
        dependency_rtl_files = _promoted_dependency_rtl_files(
            bootstrap=bootstrap,
            node=node,
            promoted_path=promoted_path,
        )
        if l2_profile:
            execution_node = build_promoted_node(
                node=node,
                workspace_record=workspace_record,
                promoted_root=promoted_path or workspace_promoted_root(workspace_path),
                dependency_rtl_files=dependency_rtl_files,
            )
        else:
            execution_node = build_workspace_node(
                node=node,
                workspace_record=workspace_record,
                dependency_rtl_files=dependency_rtl_files,
            )
            repair_request_path = workspace_path / 'repair_request.json'
            if (
                workspace_record.state == NodeWorkspaceState.REPAIRING
                and repair_request_path.is_file()
            ):
                repair_contract = load_repair_contract(workspace_path)
                edit_receipt_path = workspace_path / 'edit_receipt.json'
                if not edit_receipt_path.is_file():
                    validation_status = 'failed'
                    validation_details = {
                        'checkpoint_summary': {},
                        'missing_checkpoints': list(
                            node.pass_criteria.l1.coverage_checkpoints
                        ),
                        'failed_checkpoints': [],
                        'failure_phase': ValidationFailurePhase.L1_SIM.value,
                    }
                    summary = {
                        'module_id': module_id,
                        'l0_status': 'not_run',
                        'l1_status': validation_status,
                        'validation_status': validation_status,
                        'failure_phase': validation_details['failure_phase'],
                        'checkpoint_summary': {},
                        'missing_checkpoints': validation_details[
                            'missing_checkpoints'
                        ],
                        'failed_checkpoints': [],
                        'error': {
                            'type': 'RepairContractViolation',
                            'message': (
                                'repair phase must create edit_receipt.json '
                                'before revalidation'
                            ),
                        },
                    }
                    write_validation_error(
                        workspace_record=workspace_record,
                        payload=summary,
                    )
                    write_validation_summary(
                        workspace_record=workspace_record,
                        payload=summary,
                    )
                    state = policy_engine.next_state(
                        workspace_record=workspace_record,
                        validation_status=validation_status,
                        repair_budget=repair_budget_for_node(node),
                    )
                    workspace_record = workspace_record.model_copy(
                        update={'state': state}
                    )
                    write_workspace_record(workspace_record)
                    recommended_mode = policy_engine.decide_next_mode(
                        workspace_record=workspace_record,
                        validation_status=validation_status,
                        repair_budget=repair_budget_for_node(node),
                    )
                    generation_result_path = write_generation_result(
                        workspace_record=workspace_record,
                        node=node,
                        validation_status=validation_status,
                        failure_phase=validation_details['failure_phase'],
                        promoted=False,
                        changed_files=[],
                        checkpoint_summary={},
                        missing_checkpoints=validation_details['missing_checkpoints'],
                        failed_checkpoints=[],
                        recommended_mode=recommended_mode.value
                        if recommended_mode
                        else None,
                    )
                    if (
                        recommended_mode is not None
                        and recommended_mode.value == 'repair'
                    ):
                        write_repair_request(
                            workspace_record=workspace_record,
                            node=node,
                            generation_result_path=generation_result_path,
                            failure_phase=validation_details['failure_phase'],
                            missing_checkpoints=validation_details[
                                'missing_checkpoints'
                            ],
                            failed_checkpoints=[],
                            rerun_command=_workspace_run_node_command(
                                module_id,
                                workspace_path=workspace_path,
                                promoted_path=promoted_path,
                            ),
                        )
                    summary['workspace_root'] = str(workspace_path)
                    summary['workspace_state_path'] = str(
                        workspace_path / 'workspace_state.json'
                    )
                    summary['generation_result_path'] = str(generation_result_path)
                    summary['repair_request_path'] = str(
                        workspace_path / 'repair_request.json'
                    )
                    summary['edit_receipt_path'] = str(edit_receipt_path)
                    return summary
                (
                    repair_valid,
                    edited_files,
                    repair_message,
                ) = verify_repair_edit(
                    workspace_root=workspace_path,
                    repair_contract=repair_contract,
                )
                if repair_valid:
                    workspace_record = workspace_record.model_copy(
                        update={
                            'repair_edit_count': workspace_record.repair_edit_count + 1
                        }
                    )
                    write_workspace_record(workspace_record)
                if not repair_valid:
                    validation_status = 'failed'
                    validation_details = {
                        'checkpoint_summary': {},
                        'missing_checkpoints': list(
                            node.pass_criteria.l1.coverage_checkpoints
                        ),
                        'failed_checkpoints': [],
                        'failure_phase': ValidationFailurePhase.L1_SIM.value,
                    }
                    summary: dict[str, object] = {
                        'module_id': module_id,
                        'l0_status': 'not_run',
                        'l1_status': validation_status,
                        'validation_status': validation_status,
                        'failure_phase': validation_details['failure_phase'],
                        'checkpoint_summary': {},
                        'missing_checkpoints': validation_details[
                            'missing_checkpoints'
                        ],
                        'failed_checkpoints': [],
                        'error': {
                            'type': 'RepairContractViolation',
                            'message': repair_message,
                        },
                    }
                    write_validation_error(
                        workspace_record=workspace_record,
                        payload=summary,
                    )
                    write_validation_summary(
                        workspace_record=workspace_record,
                        payload=summary,
                    )
                    state = policy_engine.next_state(
                        workspace_record=workspace_record,
                        validation_status=validation_status,
                        repair_budget=repair_budget_for_node(node),
                    )
                    workspace_record = workspace_record.model_copy(
                        update={'state': state}
                    )
                    write_workspace_record(workspace_record)
                    recommended_mode = policy_engine.decide_next_mode(
                        workspace_record=workspace_record,
                        validation_status=validation_status,
                        repair_budget=repair_budget_for_node(node),
                    )
                    generation_result_path = write_generation_result(
                        workspace_record=workspace_record,
                        node=node,
                        validation_status=validation_status,
                        failure_phase=validation_details['failure_phase'],
                        promoted=False,
                        changed_files=[],
                        checkpoint_summary={},
                        missing_checkpoints=validation_details['missing_checkpoints'],
                        failed_checkpoints=[],
                        recommended_mode=recommended_mode.value
                        if recommended_mode
                        else None,
                    )
                    if (
                        recommended_mode is not None
                        and recommended_mode.value == 'repair'
                    ):
                        write_repair_request(
                            workspace_record=workspace_record,
                            node=node,
                            generation_result_path=generation_result_path,
                            failure_phase=validation_details['failure_phase'],
                            missing_checkpoints=validation_details[
                                'missing_checkpoints'
                            ],
                            failed_checkpoints=[],
                            rerun_command=_workspace_run_node_command(
                                module_id,
                                workspace_path=workspace_path,
                                promoted_path=promoted_path,
                            ),
                        )
                    summary['workspace_root'] = str(workspace_path)
                    summary['workspace_state_path'] = str(
                        workspace_path / 'workspace_state.json'
                    )
                    summary['generation_result_path'] = str(generation_result_path)
                    summary['repair_request_path'] = str(
                        workspace_path / 'repair_request.json'
                    )
                    summary['edit_receipt_path'] = str(
                        workspace_path / 'edit_receipt.json'
                    )
                    return summary
    if (
        workspace_path is not None
        and workspace_record is not None
        and should_increment_validation
    ):
        workspace_record = increment_validation_runs(workspace_record)
        write_workspace_record(workspace_record)
    compile_result = None
    try:
        compile_result = l0.run(execution_node, manifest=manifest_override)
        l0_compile_text = str(compile_result.payload.get('compile_result', ''))
        simulate_result = l1.run(
            execution_node,
            manifest=manifest_override,
            skip_compile=True,
            reuse_compile_result=l0_compile_text,
        )
        simulate_payload = json.loads(simulate_result.path.read_text(encoding='utf-8'))
        validation_status, validation_details = evaluate_validation_result(
            node=node,
            l1_payload=simulate_payload,
        )
        summary = {
            'module_id': module_id,
            'compile_result_path': str(compile_result.path),
            'simulate_result_path': str(simulate_result.path),
            'l0_status': 'passed',
            'l1_status': validation_status,
            'validation_status': validation_status,
            'failure_phase': validation_details['failure_phase'],
            'checkpoint_summary': validation_details['checkpoint_summary'],
            'missing_checkpoints': validation_details['missing_checkpoints'],
            'failed_checkpoints': validation_details['failed_checkpoints'],
        }
    except Exception as exc:
        validation_status = 'failed'
        failure_phase = (
            ValidationFailurePhase.L1_SIM.value
            if compile_result is not None
            else ValidationFailurePhase.L0_COMPILE.value
        )
        validation_details = {
            'checkpoint_summary': {},
            'missing_checkpoints': list(node.pass_criteria.l1.coverage_checkpoints),
            'failed_checkpoints': [],
            'failure_phase': failure_phase,
        }
        l0_finished = compile_result is not None
        summary = {
            'module_id': module_id,
            'l0_status': 'passed' if l0_finished else 'failed',
            'l1_status': validation_status,
            'validation_status': validation_status,
            'failure_phase': failure_phase,
            'checkpoint_summary': {},
            'missing_checkpoints': validation_details['missing_checkpoints'],
            'failed_checkpoints': [],
            'error': {'type': type(exc).__name__, 'message': str(exc)},
        }
        if l0_finished:
            summary['compile_result_path'] = str(compile_result.path)
    if l2_profile:
        l2 = L2CampaignExecutor(
            adapter=adapter,
            package_root=bootstrap.workspace_root,
            integration_manifest=bootstrap.integration_manifest,
        )
        l2_result = l2.run(
            execution_node,
            profile=l2_profile,
            vecfile=vecfile,
            cases=cases,
            seed=seed,
            manifest=manifest_override,
        )
        summary['l2_result_path'] = str(l2_result.path)
    if workspace_path is not None and workspace_record is not None:
        summary['workspace_root'] = str(workspace_path)
        summary['workspace_state_path'] = str(workspace_path / 'workspace_state.json')
        summary['promoted_root'] = str(
            promoted_path or workspace_promoted_root(workspace_path)
        )
        if l2_profile is None:
            if 'error' in summary:
                write_validation_error(
                    workspace_record=workspace_record,
                    payload=summary,
                )
            write_validation_summary(
                workspace_record=workspace_record,
                payload=summary,
            )
            promoted = False
            changed_files: list[str] = []
            promotion_record_path = None
            if validation_status == 'passed':
                clear_repair_artifacts(workspace_path)
                promotion_record = promote_workspace(
                    node=node,
                    workspace_record=workspace_record,
                    checkpoint_summary=summary['checkpoint_summary'],  # type: ignore[arg-type]
                )
                promoted = True
                changed_files = list(promotion_record.promoted_targets)
                promotion_record_path = (
                    workspace_path / 'promotion' / 'promotion_record.json'
                ).resolve()
                state = NodeWorkspaceState.PROMOTED
            else:
                state = policy_engine.next_state(
                    workspace_record=workspace_record,
                    validation_status=validation_status,
                    repair_budget=repair_budget_for_node(node),
                )
            workspace_record = workspace_record.model_copy(update={'state': state})
            write_workspace_record(workspace_record)
            recommended_mode = policy_engine.decide_next_mode(
                workspace_record=workspace_record,
                validation_status=validation_status,
                repair_budget=repair_budget_for_node(node),
            )
            generation_result_path = write_generation_result(
                workspace_record=workspace_record,
                node=node,
                validation_status=validation_status,
                failure_phase=summary.get('failure_phase'),
                promoted=promoted,
                changed_files=changed_files,
                checkpoint_summary=summary['checkpoint_summary'],  # type: ignore[arg-type]
                missing_checkpoints=summary['missing_checkpoints'],  # type: ignore[arg-type]
                failed_checkpoints=summary['failed_checkpoints'],  # type: ignore[arg-type]
                recommended_mode=recommended_mode.value if recommended_mode else None,
            )
            if (
                validation_status != 'passed'
                and recommended_mode is not None
                and recommended_mode.value == 'repair'
            ):
                write_repair_request(
                    workspace_record=workspace_record,
                    node=node,
                    generation_result_path=generation_result_path,
                    failure_phase=summary.get('failure_phase'),
                    missing_checkpoints=list(summary['missing_checkpoints']),  # type: ignore[arg-type]
                    failed_checkpoints=list(summary['failed_checkpoints']),  # type: ignore[arg-type]
                    rerun_command=_workspace_run_node_command(
                        module_id,
                        workspace_path=workspace_path,
                        promoted_path=promoted_path,
                    ),
                )
            summary['generation_result_path'] = str(generation_result_path)
            summary['repair_request_path'] = str(workspace_path / 'repair_request.json')
            summary['edit_receipt_path'] = str(workspace_path / 'edit_receipt.json')
            summary['promotion_record_path'] = (
                str(promotion_record_path) if promotion_record_path else None
            )
            summary['promoted'] = promoted
            summary['changed_files'] = changed_files
    return summary


def _run_integration(
    *,
    promoted_root: str | None = None,
    output_root: str | None = None,
) -> dict[str, object]:
    bootstrap = RuntimeBootstrap.build(allow_placeholder_api_key=True)
    adapter = bootstrap.create_verilator_adapter()
    manifest = bootstrap.integration_manifest
    if promoted_root is not None:
        manifest = _build_promoted_integration_manifest(
            bootstrap=bootstrap,
            promoted_path=Path(promoted_root).resolve(),
            output_root=Path(output_root).resolve() if output_root else None,
        )
    executor = IntegrationRegressionExecutor(
        adapter=adapter,
        package_root=bootstrap.workspace_root,
        integration_manifest=bootstrap.integration_manifest,
    )
    result = executor.run(manifest)
    return {
        'top_module': manifest.top_module,
        'integration_result_path': str(result.path),
        'status': result.payload.get('status'),
    }


def _record_repair_edit(module_id: str, workspace_root: str) -> dict[str, object]:
    workspace_path = Path(workspace_root).resolve()
    workspace_record = load_workspace_record(workspace_path)
    repair_contract = load_repair_contract(workspace_path)
    (
        repair_valid,
        edited_files,
        repair_message,
    ) = verify_repair_edit(
        workspace_root=workspace_path,
        repair_contract=repair_contract,
    )
    if not repair_valid:
        return {
            'module_id': module_id,
            'workspace_root': str(workspace_path),
            'workspace_state': workspace_record.state.value,
            'repair_status': 'failed',
            'edited_files': edited_files,
            'edit_receipt_path': str(workspace_path / 'edit_receipt.json'),
            'error': {
                'type': 'RepairContractViolation',
                'message': repair_message,
            },
        }

    receipt_path = write_edit_receipt(
        workspace_root=workspace_path,
        repair_contract=repair_contract,
        edited_files=edited_files,
        first_edit_summary=repair_contract.required_first_edit,
    )
    return {
        'module_id': module_id,
        'workspace_root': str(workspace_path),
        'workspace_state': workspace_record.state.value,
        'repair_status': 'recorded',
        'edited_files': edited_files,
        'edit_receipt_path': str(receipt_path),
        'rerun_command': repair_contract.rerun_command,
    }


def _generate_node(
    module_id: str,
    *,
    workspace_root: str | None = None,
) -> dict[str, object]:
    resolved_workspace = (
        Path(workspace_root).resolve()
        if workspace_root
        else (
            RuntimeBootstrap.build(allow_placeholder_api_key=True).persistence_dir
            / 'manual_generation'
            / module_id
        ).resolve()
    )
    return _run_node(
        module_id,
        None,
        workspace_root=str(resolved_workspace),
        promoted_root=str(workspace_promoted_root(resolved_workspace)),
        increment_workspace_validation=True,
    )


def _run_aes_mvp(message: str, dry_run: bool) -> dict[str, object]:
    bootstrap = RuntimeBootstrap.build(
        allow_placeholder_api_key=dry_run,
        system_goal=message,
    )
    if dry_run:
        summary = bootstrap.to_summary()
        summary['dry_run'] = True
        summary['execution_mode'] = 'autonomous-generate'
        return summary

    session = ExecutionSession.create(bootstrap)
    return asdict(session.run(message))


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(prog='python -m MultiAgent_FPGA.aes_mvp')
    subparsers = parser.add_subparsers(dest='command', required=False)

    subparsers.add_parser('validate')
    subparsers.add_parser('smoke-sdk')
    subparsers.add_parser('smoke-provider')
    run_integration = subparsers.add_parser('run-integration')
    run_integration.add_argument('--promoted-root', default=None)
    run_integration.add_argument('--output-root', default=None)

    run_node = subparsers.add_parser('run-node')
    run_node.add_argument('module_id')
    run_node.add_argument('--l2-profile', default=None)
    run_node.add_argument('--vecfile', default=None)
    run_node.add_argument('--cases', type=int, default=None)
    run_node.add_argument('--seed', type=int, default=None)
    run_node.add_argument('--workspace-root', default=None)
    run_node.add_argument('--promoted-root', default=None)
    run_node.add_argument('--strict-validation', action='store_true')

    record_repair = subparsers.add_parser('record-repair-edit')
    record_repair.add_argument('module_id')
    record_repair.add_argument('--workspace-root', required=True)
    record_repair.add_argument('--strict', action='store_true')

    generate_node = subparsers.add_parser('generate-node')
    generate_node.add_argument('module_id')
    generate_node.add_argument('--workspace-root', default=None)
    generate_node.add_argument('--strict-validation', action='store_true')

    run_mvp = subparsers.add_parser('run-aes-mvp')
    run_mvp.add_argument(
        '--message',
        default=(
            'Autonomously synthesize, implement, validate, repair, and integrate '
            'the AES-128 full-system.'
        ),
    )
    run_mvp.add_argument('--dry-run', action='store_true')
    run_mvp.add_argument(
        '--enable-l2',
        action='store_true',
        help='Enable L2 robustness campaigns (disabled by default).',
    )
    return parser


def main(argv: list[str] | None = None) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)
    command = args.command or 'validate'

    if command == 'validate':
        payload = _validate_summary()
    elif command == 'smoke-sdk':
        payload = _smoke_sdk_summary()
    elif command == 'smoke-provider':
        payload = _smoke_provider_summary()
    elif command == 'run-integration':
        payload = _run_integration(
            promoted_root=args.promoted_root,
            output_root=args.output_root,
        )
    elif command == 'run-node':
        payload = _run_node(
            args.module_id,
            args.l2_profile,
            vecfile=args.vecfile,
            cases=args.cases,
            seed=args.seed,
            workspace_root=args.workspace_root,
            promoted_root=args.promoted_root,
        )
    elif command == 'record-repair-edit':
        payload = _record_repair_edit(args.module_id, args.workspace_root)
    elif command == 'generate-node':
        payload = _generate_node(
            args.module_id,
            workspace_root=args.workspace_root,
        )
    elif command == 'run-aes-mvp':
        if args.enable_l2:
            os.environ['AES_MVP_ENABLE_L2'] = '1'
        payload = _run_aes_mvp(args.message, args.dry_run)
    else:
        parser.error(f'Unknown command: {command}')
        return 2

    print(json.dumps(payload, indent=2, sort_keys=True))
    if command in {'run-node', 'generate-node'} and getattr(
        args, 'strict_validation', False
    ):
        if payload.get('validation_status') != 'passed':
            return 3
    if command == 'record-repair-edit' and getattr(args, 'strict', False):
        if payload.get('repair_status') != 'recorded':
            return 4
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
