"""CLI entrypoint for the AES MVP framework package."""

from __future__ import annotations

import argparse
import json
from dataclasses import asdict
from pathlib import Path

from MultiAgent_FPGA.aes_mvp.artifacts import NodeWorkspaceState
from MultiAgent_FPGA.aes_mvp.executors import (
    IntegrationRegressionExecutor,
    L0Executor,
    L1Executor,
    L2CampaignExecutor,
)
from MultiAgent_FPGA.aes_mvp.generation import (
    DEFAULT_REPAIR_BUDGET,
    build_workspace_node,
    evaluate_validation_result,
    increment_validation_runs,
    initialize_node_workspace,
    promote_workspace,
    write_generation_result,
    write_workspace_record,
)
from MultiAgent_FPGA.aes_mvp.llm_profiles import run_deepseek_preflight_suite
from MultiAgent_FPGA.aes_mvp.runtime import (
    ExecutionSession,
    RuntimeBootstrap,
    discover_sdk_environment,
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


def _run_node(
    module_id: str,
    l2_profile: str | None,
    *,
    vecfile: str | None = None,
    cases: int | None = None,
    seed: int | None = None,
    workspace_root: str | None = None,
) -> dict[str, object]:
    bootstrap = RuntimeBootstrap.build(allow_placeholder_api_key=True)
    orchestrator = bootstrap.orchestrator()
    node = orchestrator.get_node(module_id)
    adapter = bootstrap.create_verilator_adapter()
    l0 = L0Executor(adapter=adapter, package_root=bootstrap.workspace_root)
    l1 = L1Executor(adapter=adapter, package_root=bootstrap.workspace_root)

    manifest_override = None
    execution_node = node
    workspace_path: Path | None = None
    workspace_record = None
    if workspace_root:
        workspace_path = Path(workspace_root).resolve()
        workspace_record = initialize_node_workspace(
            spec_ir=bootstrap.spec_ir,
            plan_dag=bootstrap.plan_dag,
            node=node,
            workspace_root=workspace_path,
        )
        dependency_rtl_files = None
        if node.module_id == bootstrap.integration_manifest.top_module:
            dependency_rtl_files = [
                str((bootstrap.workspace_root / dep_node.rtl_files[0]).resolve())
                for dep_node in bootstrap.plan_dag.nodes
                if dep_node.module_id in node.depends_on
            ]
        execution_node = build_workspace_node(
            node=node,
            workspace_record=workspace_record,
            dependency_rtl_files=dependency_rtl_files,
        )
        manifest_override = None

    compile_result = l0.run(execution_node, manifest=manifest_override)
    simulate_result = l1.run(execution_node, manifest=manifest_override)
    simulate_payload = json.loads(simulate_result.path.read_text(encoding='utf-8'))
    validation_status, validation_details = evaluate_validation_result(
        node=node,
        l1_payload=simulate_payload,
    )
    summary: dict[str, object] = {
        'module_id': module_id,
        'compile_result_path': str(compile_result.path),
        'simulate_result_path': str(simulate_result.path),
        'l0_status': 'passed',
        'l1_status': validation_status,
        'validation_status': validation_status,
        'checkpoint_summary': validation_details['checkpoint_summary'],
        'missing_checkpoints': validation_details['missing_checkpoints'],
        'failed_checkpoints': validation_details['failed_checkpoints'],
    }
    if l2_profile:
        l2 = L2CampaignExecutor(adapter=adapter, package_root=bootstrap.workspace_root)
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
    return summary


def _run_integration() -> dict[str, object]:
    bootstrap = RuntimeBootstrap.build(allow_placeholder_api_key=True)
    adapter = bootstrap.create_verilator_adapter()
    executor = IntegrationRegressionExecutor(
        adapter=adapter,
        package_root=bootstrap.workspace_root,
    )
    result = executor.run(bootstrap.integration_manifest)
    return {
        'top_module': bootstrap.integration_manifest.top_module,
        'integration_result_path': str(result.path),
        'status': result.payload.get('status'),
    }


def _generate_node(
    module_id: str,
    *,
    workspace_root: str | None = None,
) -> dict[str, object]:
    bootstrap = RuntimeBootstrap.build(allow_placeholder_api_key=True)
    orchestrator = bootstrap.orchestrator()
    node = orchestrator.get_node(module_id)
    resolved_workspace = (
        Path(workspace_root).resolve()
        if workspace_root
        else (bootstrap.persistence_dir / 'manual_generation' / module_id).resolve()
    )
    workspace_record = initialize_node_workspace(
        spec_ir=bootstrap.spec_ir,
        plan_dag=bootstrap.plan_dag,
        node=node,
        workspace_root=resolved_workspace,
    )
    workspace_record = increment_validation_runs(workspace_record)

    try:
        node_summary = _run_node(
            module_id,
            None,
            workspace_root=str(resolved_workspace),
        )
        validation_status = str(node_summary['validation_status'])
        checkpoint_summary = dict(node_summary['checkpoint_summary'])
        missing_checkpoints = list(node_summary.get('missing_checkpoints', []))
        failed_checkpoints = list(node_summary.get('failed_checkpoints', []))
    except Exception as exc:  # pragma: no cover - defensive path for real tool errors
        validation_status = 'failed'
        checkpoint_summary = {}
        missing_checkpoints = list(node.pass_criteria.l1.coverage_checkpoints)
        failed_checkpoints = []
        node_summary = {
            'module_id': module_id,
            'workspace_root': str(resolved_workspace),
            'validation_status': validation_status,
            'error': {'type': type(exc).__name__, 'message': str(exc)},
        }

    promoted = False
    changed_files: list[str] = []
    state = NodeWorkspaceState.GENERATED
    promotion_record_path = None
    if validation_status == 'passed':
        promotion_record = promote_workspace(
            package_root=bootstrap.workspace_root,
            node=node,
            workspace_record=workspace_record,
            checkpoint_summary=checkpoint_summary,
        )
        promoted = True
        changed_files = list(promotion_record.canonical_targets)
        promotion_record_path = (
            resolved_workspace / 'promotion' / 'promotion_record.json'
        ).resolve()
        state = NodeWorkspaceState.PROMOTED
    elif workspace_record.validation_runs > DEFAULT_REPAIR_BUDGET:
        state = NodeWorkspaceState.BLOCKED
    elif workspace_record.validation_runs > 1:
        state = NodeWorkspaceState.REPAIRING

    workspace_record = workspace_record.model_copy(update={'state': state})
    write_workspace_record(workspace_record)
    generation_result_path = write_generation_result(
        workspace_record=workspace_record,
        node=node,
        validation_status=validation_status,
        promoted=promoted,
        changed_files=changed_files,
        checkpoint_summary=checkpoint_summary,
        missing_checkpoints=missing_checkpoints,
        failed_checkpoints=failed_checkpoints,
    )

    payload = {
        'module_id': module_id,
        'workspace_root': str(resolved_workspace),
        'workspace_state': state.value,
        'workspace_state_path': str(resolved_workspace / 'workspace_state.json'),
        'generation_result_path': str(generation_result_path),
        'promotion_record_path': str(promotion_record_path)
        if promotion_record_path
        else None,
        'promoted': promoted,
        **node_summary,
    }
    return payload


def _run_aes_mvp(message: str, dry_run: bool, execution_mode: str) -> dict[str, object]:
    bootstrap = RuntimeBootstrap.build(allow_placeholder_api_key=dry_run)
    if dry_run:
        summary = bootstrap.to_summary()
        summary['dry_run'] = True
        summary['execution_mode'] = execution_mode
        return summary

    session = ExecutionSession.create(bootstrap)
    return asdict(
        session.run(
            message,
            execute_green_path=True,
            execution_mode=execution_mode,  # type: ignore[arg-type]
        )
    )


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(prog='python -m MultiAgent_FPGA.aes_mvp')
    subparsers = parser.add_subparsers(dest='command', required=False)

    subparsers.add_parser('validate')
    subparsers.add_parser('smoke-sdk')
    subparsers.add_parser('smoke-provider')
    subparsers.add_parser('run-integration')

    run_node = subparsers.add_parser('run-node')
    run_node.add_argument('module_id')
    run_node.add_argument('--l2-profile', default=None)
    run_node.add_argument('--vecfile', default=None)
    run_node.add_argument('--cases', type=int, default=None)
    run_node.add_argument('--seed', type=int, default=None)
    run_node.add_argument('--workspace-root', default=None)
    run_node.add_argument('--strict-validation', action='store_true')

    generate_node = subparsers.add_parser('generate-node')
    generate_node.add_argument('module_id')
    generate_node.add_argument('--workspace-root', default=None)
    generate_node.add_argument('--strict-validation', action='store_true')

    run_mvp = subparsers.add_parser('run-aes-mvp')
    run_mvp.add_argument(
        '--message',
        default='Build and validate the AES MVP according to the frozen SpecIR and PlanDAG.',
    )
    run_mvp.add_argument('--dry-run', action='store_true')
    run_mvp.add_argument(
        '--execution-mode',
        choices=(
            'deterministic-review',
            'hybrid-delegate',
            'hybrid-build',
            'hybrid-generate',
        ),
        default='deterministic-review',
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
        payload = _run_integration()
    elif command == 'run-node':
        payload = _run_node(
            args.module_id,
            args.l2_profile,
            vecfile=args.vecfile,
            cases=args.cases,
            seed=args.seed,
            workspace_root=args.workspace_root,
        )
    elif command == 'generate-node':
        payload = _generate_node(
            args.module_id,
            workspace_root=args.workspace_root,
        )
    elif command == 'run-aes-mvp':
        payload = _run_aes_mvp(args.message, args.dry_run, args.execution_mode)
    else:
        parser.error(f'Unknown command: {command}')
        return 2

    print(json.dumps(payload, indent=2, sort_keys=True))
    if command in {'run-node', 'generate-node'} and getattr(
        args, 'strict_validation', False
    ):
        if payload.get('validation_status') != 'passed':
            return 3
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
