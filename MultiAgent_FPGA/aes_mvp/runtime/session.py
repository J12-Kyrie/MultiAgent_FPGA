"""Execution-session helpers for the AES MVP runtime."""

from __future__ import annotations

import copy
import json
import logging
import os
import shutil
from collections.abc import Sequence
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Any
from uuid import UUID, uuid4

from MultiAgent_FPGA.aes_mvp.delegation import (
    DelegateBatchPlan,
    DelegateBatchTask,
    NodeExecutionRequest,
    SubagentWorkMode,
)
from MultiAgent_FPGA.aes_mvp.executor_contracts import (
    ExecutorKind,
    resolve_l2_campaign_inputs,
    resolve_path,
)
from MultiAgent_FPGA.aes_mvp.generation import (
    conversation_promoted_root,
    conversation_workspace_root,
    initialize_node_workspace,
    load_repair_contract,
    repair_budget_for_node,
    verify_repair_edit,
    write_budget_exhausted_result,
    write_cascade_block_result,
    write_defensive_failure_result,
    write_edit_receipt,
)
from MultiAgent_FPGA.aes_mvp.orchestrator import AESWorkflowOrchestrator
from MultiAgent_FPGA.aes_mvp.policy import OrchestratorState
from MultiAgent_FPGA.aes_mvp.runtime.bootstrap import RuntimeBootstrap
from MultiAgent_FPGA.aes_mvp.runtime.context_assembler import (
    BatchMessageEnvelope,
    ContextAssembler,
    TaskContractEnvelope,
)
from MultiAgent_FPGA.aes_mvp.runtime.factory import SdkAgentFactory
from MultiAgent_FPGA.aes_mvp.runtime.runner import (
    BatchRunSummary,
    ConversationRunner,
    ConversationSummary,
)
from MultiAgent_FPGA.aes_mvp.synthesis import (
    DAGBatchPlanner,
    FragilityMemory,
    FragilitySignal,
    IntegrationReadinessResolver,
    L2AdaptivePlanner,
)

logger = logging.getLogger(__name__)

MAX_DELEGATE_CHILDREN = 5
MAX_INTEGRATION_RETRIES = (
    1  # Allow 1 retry (2 total attempts) for integration regression
)


@dataclass(frozen=True)
class ExecutionSessionSummary:
    conversation_id: str
    report_root: str
    focus_module_id: str
    delegate_registrations: list[str]
    bootstrap_summary: dict[str, Any]
    conversation_summary: ConversationSummary
    state_trace_path: str
    session_summary_path: str
    report_tree_path: str
    execution_mode: str
    delegate_attempted: int
    delegate_completed: int
    delegate_fallback_count: int
    delegate_batch_count: int
    delegate_plan_path: str
    delegate_results_path: str
    delegate_fallbacks_path: str
    final_acceptance_summary_path: str
    generation_plan_path: str | None = None
    brief_generation_summary_path: str | None = None
    promotion_events_path: str | None = None
    promotion_failures_path: str | None = None
    module_results_dir: str | None = None
    integration_summary_path: str | None = None
    deterministic_execution_path: str | None = None
    batch_history_path: str | None = None
    workflow_gate_path: str | None = None
    current_batch_snapshot_path: str | None = None
    finalizer_input_path: str | None = None
    finalizer_conversation_id: str | None = None


class ExecutionSession:
    """Drive an AES MVP conversation and persist a conversation-scoped report tree."""

    def __init__(
        self,
        *,
        bootstrap: RuntimeBootstrap,
        factory: SdkAgentFactory,
        runner: ConversationRunner,
        orchestrator: AESWorkflowOrchestrator,
        conversation,
        conversation_id: UUID,
        report_root: Path,
        focus_module_id: str,
        delegate_registrations: list[str],
        state_trace: list[dict[str, Any]],
    ) -> None:
        self.bootstrap = bootstrap
        self.factory = factory
        self.runner = runner
        self.orchestrator = orchestrator
        self.conversation = conversation
        self.conversation_id = conversation_id
        self.report_root = report_root
        self.focus_module_id = focus_module_id
        self.delegate_registrations = delegate_registrations
        self.state_trace = state_trace
        self.context_assembler = ContextAssembler()
        self._autonomous_batch_event_dirs: list[Path] = []
        self._autonomous_batch_conversations: list[Any] = []
        self._execution_batch_conversation_ids: list[str] = []
        self._latest_repair_outcomes: dict[str, Any] = {}

    @classmethod
    def create(
        cls,
        bootstrap: RuntimeBootstrap,
        *,
        conversation_id: UUID | None = None,
        focus_module_id: str | None = None,
    ) -> 'ExecutionSession':
        factory = SdkAgentFactory(bootstrap)
        enable_l2 = os.environ.get('AES_MVP_ENABLE_L2', '').lower() in (
            '1',
            'true',
            'yes',
        )
        delegate_registrations = factory.register_delegate_agents(enable_l2=enable_l2)
        runner = ConversationRunner(bootstrap, factory)
        orchestrator = bootstrap.orchestrator()
        resolved_conversation_id = conversation_id or uuid4()
        resolved_focus_module = (
            focus_module_id or bootstrap.integration_manifest.top_module
        )
        report_root = (
            bootstrap.persistence_dir / resolved_conversation_id.hex
        ).resolve()
        report_root.mkdir(parents=True, exist_ok=True)
        # Fix 2: Remove stale conversation directories from previous runs.
        # Left-over directories cause sub-agents to find wrong request paths
        # when they search the filesystem instead of using the explicit path.
        current_hex = resolved_conversation_id.hex
        for child in bootstrap.persistence_dir.iterdir():
            if child.is_dir() and child.name != current_hex:
                try:
                    shutil.rmtree(child)
                    logger.info('Removed stale conversation directory: %s', child.name)
                except OSError:
                    logger.warning('Could not remove stale directory: %s', child)
        conversation = runner.create_execution_conversation(
            conversation_id=resolved_conversation_id,
            persistence_dir=bootstrap.persistence_dir,
            delete_on_close=False,
        )
        state_trace = [
            asdict(step)
            for step in orchestrator.describe_state_progression(
                focus_module_id=resolved_focus_module
            )
        ]
        session = cls(
            bootstrap=bootstrap,
            factory=factory,
            runner=runner,
            orchestrator=orchestrator,
            conversation=conversation,
            conversation_id=resolved_conversation_id,
            report_root=report_root,
            focus_module_id=resolved_focus_module,
            delegate_registrations=delegate_registrations,
            state_trace=state_trace,
        )
        session._write_report_tree()
        return session

    @property
    def base_state_path(self) -> Path:
        return self.report_root / 'base_state.json'

    @property
    def state_trace_path(self) -> Path:
        return self.report_root / 'state_trace.json'

    @property
    def session_summary_path(self) -> Path:
        return self.report_root / 'session_summary.json'

    @property
    def report_tree_path(self) -> Path:
        return self.report_root / 'report_tree.json'

    @property
    def spec_ir_artifact_path(self) -> Path:
        return self.report_root / 'spec_ir.json'

    @property
    def plan_dag_artifact_path(self) -> Path:
        return self.report_root / 'plan_dag.json'

    @property
    def batch_plan_path(self) -> Path:
        return self.report_root / 'batch_plan.json'

    @property
    def fragility_memory_path(self) -> Path:
        return self.report_root / 'fragility_memory.json'

    @property
    def delegate_plan_path(self) -> Path:
        return self.report_root / 'delegate_plan.json'

    @property
    def delegate_results_path(self) -> Path:
        return self.report_root / 'delegate_results.json'

    @property
    def delegate_fallbacks_path(self) -> Path:
        return self.report_root / 'delegate_fallbacks.json'

    @property
    def final_acceptance_summary_path(self) -> Path:
        return self.report_root / 'final_acceptance_summary.json'

    @property
    def generation_plan_path(self) -> Path:
        return self.report_root / 'generation_plan.json'

    @property
    def brief_generation_summary_path(self) -> Path:
        return self.report_root / 'brief_generation_summary.json'

    @property
    def generation_results_dir(self) -> Path:
        return self.report_root / 'generation_results'

    @property
    def batch_history_path(self) -> Path:
        return self.report_root / 'batch_history.json'

    @property
    def workflow_gate_path(self) -> Path:
        return self.report_root / 'workflow_gate.json'

    @property
    def current_batch_snapshot_path(self) -> Path:
        return self.report_root / 'current_batch_snapshot.json'

    @property
    def finalizer_input_path(self) -> Path:
        return self.report_root / 'finalizer_input.json'

    @property
    def integration_request_path(self) -> Path:
        return self.report_root / 'integration_request.json'

    @property
    def promotion_events_path(self) -> Path:
        return self.report_root / 'promotion_events.json'

    @property
    def promotion_failures_path(self) -> Path:
        return self.report_root / 'promotion_failures.json'

    @property
    def delegate_requests_dir(self) -> Path:
        return self.report_root / 'delegate_requests'

    @property
    def module_results_dir(self) -> Path:
        return self.report_root / 'module_results'

    @property
    def integration_summary_path(self) -> Path:
        return self.report_root / 'integration_summary.json'

    @property
    def deterministic_execution_path(self) -> Path:
        return self.report_root / 'deterministic_execution.json'

    @property
    def events_dir(self) -> Path:
        return self.report_root / 'events'

    @property
    def autonomous_handoff_digest_path(self) -> Path:
        return self.report_root / 'autonomous_handoff_digest.json'

    @property
    def hook_events_dir(self) -> Path:
        return self.report_root / 'hooks'

    def _json_default(self, value: object) -> object:
        if hasattr(value, 'model_dump'):
            return value.model_dump()
        if isinstance(value, UUID):
            return str(value)
        if hasattr(value, 'value'):
            return getattr(value, 'value')
        if isinstance(value, Path):
            return str(value)
        if hasattr(value, '__dict__'):
            return value.__dict__
        return str(value)

    def _write_json(self, path: Path, payload: dict[str, Any] | list[Any]) -> Path:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(
            json.dumps(payload, indent=2, sort_keys=True, default=self._json_default),
            encoding='utf-8',
        )
        return path

    def _manual_command_policy(self) -> dict[str, str]:
        return {
            'manual_executor_command': (
                'Manual reproduction only. Runtime dispatch uses executor_kind '
                'plus executor_inputs.'
            ),
            'manual_receipt_command': (
                'Manual repair receipt reproduction only. Runtime dispatch uses '
                'preflight_record_repair_edit.'
            ),
            'manual_integration_command': (
                'Manual integration reproduction only. Runtime dispatch uses '
                'executor_kind=run_integration plus executor_inputs.'
            ),
        }

    def _write_hook_event(self, hook_name: str, payload: dict[str, Any]) -> Path | None:
        import re
        from datetime import datetime, timezone

        payload = {**payload, 'timestamp': datetime.now(timezone.utc).isoformat()}
        raw_id = str(payload.get('batch_id', 'global'))
        batch_id = re.sub(r'[^a-zA-Z0-9_\-]', '_', raw_id)[:128] or 'unknown'
        filename = f'{hook_name}__{batch_id}.json'
        try:
            return self._write_json(self.hook_events_dir / filename, payload)
        except OSError as exc:
            import sys

            print(f'[hook] failed to write {filename}: {exc}', file=sys.stderr)
            return None

    def _before_batch_hook(
        self, *, current_batch: dict[str, Any], workflow_gate: dict[str, Any]
    ) -> None:
        self._write_hook_event(
            'before_batch',
            {
                'batch_id': str(current_batch.get('batch_id', '')),
                'phase': str(current_batch.get('phase', '')),
                'workflow_gate_decision': workflow_gate.get('decision'),
                'next_batch_ids': workflow_gate.get('next_batch_ids', []),
            },
        )

    def _after_executor_hook(
        self,
        *,
        current_batch: dict[str, Any],
        expected_artifacts: list[str],
        observed_artifacts: list[str],
    ) -> None:
        self._write_hook_event(
            'after_executor',
            {
                'batch_id': str(current_batch.get('batch_id', '')),
                'phase': str(current_batch.get('phase', '')),
                'expected_artifacts': expected_artifacts,
                'observed_artifacts': observed_artifacts,
            },
        )

    def _compute_repair_outcomes(
        self,
        *,
        current_batch: dict[str, Any],
    ) -> tuple[dict[str, Any], list[str]]:
        """Pure logic: compute repair outcomes from batch state. No I/O."""
        outcomes: dict[str, Any] = {}
        repair_receipts: list[str] = []
        for task in current_batch.get('tasks', []):
            request = task.get('request', {})
            module_id = request.get('module_id', '')
            result_paths = request.get('result_paths', {})
            receipt = result_paths.get('edit_receipt')
            has_receipt = isinstance(receipt, str) and Path(receipt).is_file()
            if has_receipt:
                repair_receipts.append(receipt)
            ws = request.get('workspace_root', '')
            failure_path = Path(ws) / 'repair_verify_failure.json' if ws else None
            has_failure = failure_path is not None and failure_path.is_file()
            outcomes[module_id] = {
                'edit_verified': has_receipt,
                'verify_failed': bool(has_failure),
                'zero_edits': has_failure and not has_receipt,
            }
        return outcomes, repair_receipts

    def _after_repair_hook(self, *, current_batch: dict[str, Any]) -> dict[str, Any]:
        if str(current_batch.get('phase', '')) != 'repair_edit':
            return {}
        outcomes, repair_receipts = self._compute_repair_outcomes(
            current_batch=current_batch,
        )
        self._write_hook_event(
            'after_repair',
            {
                'batch_id': str(current_batch.get('batch_id', '')),
                'phase': str(current_batch.get('phase', '')),
                'edit_receipts': repair_receipts,
                'outcomes': outcomes,
            },
        )
        return outcomes

    def _after_batch_gate_hook(
        self,
        *,
        current_batch: dict[str, Any],
        gate_satisfied: bool,
        pause_reason: str | None,
    ) -> None:
        self._write_hook_event(
            'after_batch_gate',
            {
                'batch_id': str(current_batch.get('batch_id', '')),
                'phase': str(current_batch.get('phase', '')),
                'gate_satisfied': gate_satisfied,
                'pause_reason': pause_reason,
            },
        )

    def _on_protocol_violation_hook(
        self, *, current_batch: dict[str, Any], protocol_violation: str
    ) -> None:
        self._write_hook_event(
            'on_protocol_violation',
            {
                'batch_id': str(current_batch.get('batch_id', '')),
                'phase': str(current_batch.get('phase', '')),
                'protocol_violation': protocol_violation,
            },
        )

    def _load_json_file(self, path: Path | None) -> dict[str, Any] | None:
        if path is None or not path.is_file():
            return None
        payload = json.loads(path.read_text(encoding='utf-8'))
        if not isinstance(payload, dict):
            raise ValueError(f'Expected JSON object in {path}')
        return payload

    def _absolute_node_writable_paths(self, node) -> list[str]:
        return [
            str(resolve_path(self.bootstrap.workspace_root, path))
            for path in [*node.rtl_files, node.tb_file]
        ]

    def _expected_module_artifact_paths(self, node) -> list[str]:
        sim_output_dir = resolve_path(
            self.bootstrap.workspace_root, node.sim_output_dir
        )
        build_output_dir = resolve_path(
            self.bootstrap.workspace_root, node.build_output_dir
        )
        return [
            str((build_output_dir.parent / 'l0_result.json').resolve()),
            str((sim_output_dir / 'module_run_result.json').resolve()),
            str((sim_output_dir / 'simulation.log').resolve()),
            str((sim_output_dir / 'simulation.vcd').resolve()),
        ]

    def _expected_l2_artifact_paths(self, node, *, profile: str) -> list[str]:
        workspace_root = self._generation_workspace_root(node.module_id)
        l2_output_dir = (
            workspace_root / 'validation' / 'sim' / 'l2' / profile
        ).resolve()
        return [
            str((l2_output_dir / 'l2_result.json').resolve()),
            str((l2_output_dir / 'counterexample.json').resolve()),
            str((l2_output_dir / 'fragility_summary.json').resolve()),
            str((l2_output_dir / 'simulation.log').resolve()),
            str((l2_output_dir / 'simulation.vcd').resolve()),
        ]

    def _generation_workspace_root(self, module_id: str) -> Path:
        return conversation_workspace_root(self.report_root, module_id)

    def _promoted_root(self) -> Path:
        return conversation_promoted_root(self.report_root)

    def _integration_output_root(self) -> Path:
        return (self.report_root / 'integration').resolve()

    def _prepare_generation_artifacts(self) -> dict[str, Any]:
        self._write_json(
            self.spec_ir_artifact_path, self.bootstrap.spec_ir.model_dump()
        )
        self._write_json(
            self.plan_dag_artifact_path, self.bootstrap.plan_dag.model_dump()
        )
        fragility_memory = FragilityMemory()
        self._write_json(self.fragility_memory_path, fragility_memory.model_dump())
        nodes: list[dict[str, Any]] = []
        promotion_targets: list[dict[str, Any]] = []
        for node in self.bootstrap.plan_dag.nodes:
            workspace_root = self._generation_workspace_root(node.module_id)
            record = initialize_node_workspace(
                spec_ir=self.bootstrap.spec_ir,
                plan_dag=self.bootstrap.plan_dag,
                node=node,
                workspace_root=workspace_root,
            )
            rtl_drafts = json.loads(record.draft_paths['rtl'])
            promoted_rtl_paths = json.loads(record.promoted_paths['rtl'])
            node_payload = {
                'module_id': node.module_id,
                'workspace_root': str(workspace_root),
                'promoted_root': str(self._promoted_root()),
                'contract_paths': dict(record.contract_paths),
                'draft_rtl_paths': list(rtl_drafts.values()),
                'draft_tb_path': record.draft_paths['tb'],
                'promoted_rtl_paths': list(promoted_rtl_paths.values()),
                'promoted_tb_path': record.promoted_paths['tb'],
                'promoted_targets': [
                    *list(promoted_rtl_paths.values()),
                    record.promoted_paths['tb'],
                ],
                'validation_paths': dict(record.validation_paths),
                'repair_request_path': str(workspace_root / 'repair_request.json'),
                'edit_receipt_path': str(workspace_root / 'edit_receipt.json'),
            }
            nodes.append(node_payload)
            promotion_targets.append(
                {
                    'module_id': node.module_id,
                    'promoted_targets': [
                        *list(promoted_rtl_paths.values()),
                        record.promoted_paths['tb'],
                    ],
                }
            )

        generation_plan = {
            'conversation_id': str(self.conversation_id),
            'execution_mode': 'autonomous-generate',
            'report_root': str(self.report_root),
            'spec_ir_path': str(self.spec_ir_artifact_path),
            'plan_dag_path': str(self.plan_dag_artifact_path),
            'fragility_memory_path': str(self.fragility_memory_path),
            'nodes': nodes,
        }
        brief_generation_summary = {
            'conversation_id': str(self.conversation_id),
            'generated_node_count': len(nodes),
            'promotion_targets': promotion_targets,
            'workspace_roots': [entry['workspace_root'] for entry in nodes],
            'system_goal': self.bootstrap.system_goal,
        }
        self._write_json(self.generation_plan_path, generation_plan)
        self._write_json(
            self.brief_generation_summary_path,
            brief_generation_summary,
        )
        return generation_plan

    def _task_request_path(self, *, batch_id: str, worker_id: str) -> Path:
        safe_worker = worker_id or 'worker'
        return (
            self.delegate_requests_dir / f'{batch_id}__{safe_worker}.json'
        ).resolve()

    def _write_task_request_contract(
        self, *, batch_id: str, task: dict[str, Any]
    ) -> Path:
        worker_id = str(task.get('worker_id') or 'worker')
        request_path = self._task_request_path(batch_id=batch_id, worker_id=worker_id)
        request_payload = {
            'batch_id': batch_id,
            'report_root': str(self.report_root),
            'manual_command_policy': self._manual_command_policy(),
            'task': task,
        }
        self._write_json(request_path, request_payload)
        return request_path

    def _materialize_delegate_plan(
        self, delegate_plan: dict[str, Any]
    ) -> dict[str, Any]:
        for batch in delegate_plan.get('batches', []):
            batch_id = str(batch.get('batch_id', 'batch'))
            delegate_section = batch.get('delegate', {})
            delegate_tasks = delegate_section.get('tasks', {})
            for task in batch.get('tasks', []):
                worker_id = str(task.get('worker_id'))
                request_path = self._write_task_request_contract(
                    batch_id=batch_id, task=task
                )
                task['request_path'] = str(request_path)
                prompt = self.context_assembler.attach_task_contract_hint(
                    str(task.get('prompt', '')),
                    TaskContractEnvelope(
                        request_path=request_path,
                        working_directory=task.get('request', {}).get(
                            'working_directory'
                        ),
                        phase=str(batch.get('phase', 'delegate')),
                    ),
                )
                task['prompt'] = prompt
                if worker_id in delegate_tasks:
                    delegate_tasks[worker_id] = prompt
                # Keep delegate.request_paths in sync so the orchestrator
                # has a structured, non-paraphrasable path reference.
                rp_map = delegate_section.setdefault('request_paths', {})
                rp_map[worker_id] = str(request_path)
        return delegate_plan

    def _report_tree_payload(self) -> dict[str, Any]:
        return {
            'conversation_id': str(self.conversation_id),
            'focus_module_id': self.focus_module_id,
            'root': str(self.report_root),
            'manual_command_policy': self._manual_command_policy(),
            'paths': {
                'base_state': str(self.base_state_path),
                'state_trace': str(self.state_trace_path),
                'session_summary': str(self.session_summary_path),
                'report_tree': str(self.report_tree_path),
                'spec_ir': str(self.spec_ir_artifact_path),
                'plan_dag': str(self.plan_dag_artifact_path),
                'batch_plan': str(self.batch_plan_path),
                'fragility_memory': str(self.fragility_memory_path),
                'delegate_plan': str(self.delegate_plan_path),
                'delegate_results': str(self.delegate_results_path),
                'delegate_fallbacks': str(self.delegate_fallbacks_path),
                'final_acceptance_summary': str(self.final_acceptance_summary_path),
                'generation_plan': str(self.generation_plan_path),
                'brief_generation_summary': str(self.brief_generation_summary_path),
                'generation_results_dir': str(self.generation_results_dir),
                'batch_history': str(self.batch_history_path),
                'workflow_gate': str(self.workflow_gate_path),
                'current_batch_snapshot': str(self.current_batch_snapshot_path),
                'finalizer_input': str(self.finalizer_input_path),
                'promotion_events': str(self.promotion_events_path),
                'promotion_failures': str(self.promotion_failures_path),
                'delegate_requests_dir': str(self.delegate_requests_dir),
                'module_results_dir': str(self.module_results_dir),
                'integration_summary': str(self.integration_summary_path),
                'deterministic_execution': str(self.deterministic_execution_path),
                'events_dir': str(self.events_dir),
                'hooks_dir': str(self.hook_events_dir),
            },
            'delegate_registrations': list(self.delegate_registrations),
            'state_trace_entries': len(self.state_trace),
        }

    def _write_report_tree(self) -> None:
        self._write_json(
            self.state_trace_path,
            {
                'conversation_id': str(self.conversation_id),
                'focus_module_id': self.focus_module_id,
                'entries': self.state_trace,
            },
        )
        self._write_json(self.report_tree_path, self._report_tree_payload())

    def _build_autonomous_delegate_plan(self) -> dict[str, Any]:
        nodes_by_id = {node.module_id: node for node in self.bootstrap.plan_dag.nodes}
        generation_plan = self._prepare_generation_artifacts()
        generation_nodes = {
            str(entry['module_id']): entry for entry in generation_plan['nodes']
        }
        fragility_memory = FragilityMemory.model_validate_json(
            self.fragility_memory_path.read_text(encoding='utf-8')
        )
        batch_planner = DAGBatchPlanner()
        l2_planner = L2AdaptivePlanner()
        readiness_resolver = IntegrationReadinessResolver()
        enable_l2 = os.environ.get('AES_MVP_ENABLE_L2', '').lower() in (
            '1',
            'true',
            'yes',
        )
        planned_batches = batch_planner.plan(
            plan_dag=self.bootstrap.plan_dag,
            integration_manifest=self.bootstrap.integration_manifest,
            fragility_memory=fragility_memory,
            max_children=MAX_DELEGATE_CHILDREN,
            l2_planner=l2_planner,
            enable_l2=enable_l2,
        )

        def generate_node_command(module_id: str) -> str:
            workspace_root = generation_nodes[module_id]['workspace_root']
            return (
                f'PYTHONPATH={self.bootstrap.repo_root} '
                f'/opt/anaconda3/envs/openhands/bin/python '
                f'-m MultiAgent_FPGA.aes_mvp generate-node {module_id} '
                f'--workspace-root {workspace_root} '
                '--strict-validation'
            )

        def node_executor_command(
            module_id: str,
            *,
            workspace_root: str | None = None,
            promoted_root: str | None = None,
            l2_profile: str | None = None,
            vecfile: str | None = None,
            cases: int | None = None,
            seed: int | None = None,
        ) -> str:
            command = (
                f'PYTHONPATH={self.bootstrap.repo_root} '
                f'/opt/anaconda3/envs/openhands/bin/python '
                f'-m MultiAgent_FPGA.aes_mvp run-node {module_id}'
            )
            if workspace_root:
                command += f' --workspace-root {workspace_root}'
            if promoted_root:
                command += f' --promoted-root {promoted_root}'
            if l2_profile:
                command += f' --l2-profile {l2_profile}'
            if vecfile:
                command += f' --vecfile {vecfile}'
            if cases is not None:
                command += f' --cases {cases}'
            if seed is not None:
                command += f' --seed {seed}'
            return command

        def build_generate_validate_task(module_id: str) -> DelegateBatchTask:
            node = nodes_by_id[module_id]
            generation_entry = generation_nodes[module_id]
            command = generate_node_command(module_id)
            generation_result_path = str(
                (
                    Path(generation_entry['workspace_root']) / 'generation_result.json'
                ).resolve()
            )
            workspace_state_path = str(
                (
                    Path(generation_entry['workspace_root']) / 'workspace_state.json'
                ).resolve()
            )
            validation_summary_path = str(
                Path(
                    generation_entry['validation_paths']['validation_summary']
                ).resolve()
            )
            validation_error_path = str(
                Path(generation_entry['validation_paths']['validation_error']).resolve()
            )
            next_read_paths = [
                generation_result_path,
                workspace_state_path,
                validation_summary_path,
                validation_error_path,
                *[
                    str(path)
                    for path in generation_entry['validation_paths'].values()
                    if isinstance(path, str)
                ],
            ]
            prompt = '\n'.join(
                [
                    f'Run the generate-and-validate pass for {node.module_id}.',
                    'Mode: generate.',
                    'Use the task contract file as the source of truth.',
                    'The draft files are pre-populated from verified memory. Call run_executor to compile and validate.',
                    'If the observation reports failed validation, read only observation.next_read_paths and stop.',
                    'Do not start the repair loop in this phase.',
                    'Do not edit canonical repository RTL/TB files directly.',
                ]
            )
            return DelegateBatchTask(
                worker_id=f'module_build__{node.module_id}',
                agent_type=self.factory.module_worker_registry_name(node),
                mode=SubagentWorkMode.GENERATE,
                request=NodeExecutionRequest(
                    module_id=node.module_id,
                    stage=OrchestratorState.MODULE_DESIGN,
                    repair_budget=repair_budget_for_node(node),
                    writable_paths=[
                        *generation_entry['draft_rtl_paths'],
                        generation_entry['draft_tb_path'],
                    ],
                    artifact_paths=[
                        *generation_entry['contract_paths'].values(),
                        *generation_entry['validation_paths'].values(),
                    ],
                    executor_kind=ExecutorKind.GENERATE_NODE,
                    executor_inputs={
                        'promoted_root': str(generation_entry['promoted_root']),
                        'increment_workspace_validation': True,
                    },
                    manual_executor_command=command,
                    working_directory=str(self.bootstrap.workspace_root),
                    workspace_root=str(generation_entry['workspace_root']),
                    contract_paths=dict(generation_entry['contract_paths']),
                    result_paths={
                        'generation_result': generation_result_path,
                        'workspace_state': workspace_state_path,
                        'validation_summary': validation_summary_path,
                        'validation_error': validation_error_path,
                        'repair_request': generation_entry['repair_request_path'],
                        'edit_receipt': generation_entry['edit_receipt_path'],
                    },
                    promoted_targets=list(generation_entry['promoted_targets']),
                    allowed_progress_actions=['run_executor'],
                    next_read_paths=next_read_paths,
                    workflow_gate_hint='framework_will_schedule_repair_or_block',
                ),
                prompt=prompt,
            )

        def build_repair_task(module_id: str) -> DelegateBatchTask:
            node = nodes_by_id[module_id]
            generation_entry = generation_nodes[module_id]
            manual_receipt_command = (
                f'PYTHONPATH={self.bootstrap.repo_root} '
                f'/opt/anaconda3/envs/openhands/bin/python '
                f'-m MultiAgent_FPGA.aes_mvp record-repair-edit {module_id} '
                f'--workspace-root {generation_entry["workspace_root"]} '
                '--strict'
            )
            generation_result_path = str(
                (
                    Path(generation_entry['workspace_root']) / 'generation_result.json'
                ).resolve()
            )
            workspace_state_path = str(
                (
                    Path(generation_entry['workspace_root']) / 'workspace_state.json'
                ).resolve()
            )
            validation_summary_path = str(
                Path(
                    generation_entry['validation_paths']['validation_summary']
                ).resolve()
            )
            validation_error_path = str(
                Path(generation_entry['validation_paths']['validation_error']).resolve()
            )
            repair_request_path = str(
                Path(generation_entry['repair_request_path']).resolve()
            )
            edit_receipt_path = str(
                Path(generation_entry['edit_receipt_path']).resolve()
            )
            repair_contract_path = Path(repair_request_path)
            repair_contract = (
                load_repair_contract(repair_contract_path)
                if repair_contract_path.is_file()
                else None
            )
            (
                [f'- {step}' for step in repair_contract.first_edit_steps]
                if repair_contract is not None
                else [
                    '- load repair_request.json first_edit_steps and follow them exactly'
                ]
            )
            (
                'must_add_tokens: ' + ', '.join(repair_contract.must_add_tokens)
                if repair_contract is not None and repair_contract.must_add_tokens
                else 'must_add_tokens:'
            )
            (
                [f'- {path}' for path in repair_contract.secondary_target_files]
                if repair_contract is not None
                and repair_contract.secondary_target_files
                else ['- none']
            )
            primary_writable_paths = (
                [repair_contract.primary_target_file]
                if repair_contract is not None
                else [
                    *generation_entry['draft_rtl_paths'],
                    generation_entry['draft_tb_path'],
                ]
            )
            next_read_paths = [
                generation_result_path,
                workspace_state_path,
                validation_summary_path,
                validation_error_path,
                repair_request_path,
                edit_receipt_path,
                *[
                    str(path)
                    for path in generation_entry['validation_paths'].values()
                    if isinstance(path, str)
                ],
            ]
            prompt = (
                f'Repair the node {node.module_id}. '
                'Mode: repair. '
                'Full instructions will be materialized at execution time.'
            )
            return DelegateBatchTask(
                worker_id=self.factory.repair_worker_registry_name(node),
                agent_type=self.factory.repair_worker_registry_name(node),
                mode=SubagentWorkMode.REPAIR,
                request=NodeExecutionRequest(
                    module_id=node.module_id,
                    stage=OrchestratorState.MODULE_L1,
                    repair_budget=repair_budget_for_node(node),
                    writable_paths=primary_writable_paths,
                    artifact_paths=[
                        *generation_entry['contract_paths'].values(),
                        *generation_entry['validation_paths'].values(),
                    ],
                    manual_executor_command=None,
                    manual_receipt_command=manual_receipt_command,
                    preflight_record_repair_edit=False,
                    working_directory=str(self.bootstrap.workspace_root),
                    workspace_root=str(generation_entry['workspace_root']),
                    contract_paths=dict(generation_entry['contract_paths']),
                    result_paths={
                        'generation_result': generation_result_path,
                        'workspace_state': workspace_state_path,
                        'validation_summary': validation_summary_path,
                        'validation_error': validation_error_path,
                        'repair_request': repair_request_path,
                        'edit_receipt': edit_receipt_path,
                    },
                    promoted_targets=list(generation_entry['promoted_targets']),
                    allowed_progress_actions=['file_editor'],
                    next_read_paths=next_read_paths,
                    workflow_gate_hint='framework_will_materialize_revalidate_batch',
                ),
                prompt=prompt,
            )

        def build_revalidate_task(module_id: str) -> DelegateBatchTask:
            node = nodes_by_id[module_id]
            generation_entry = generation_nodes[module_id]
            manual_receipt_command = (
                f'PYTHONPATH={self.bootstrap.repo_root} '
                f'/opt/anaconda3/envs/openhands/bin/python '
                f'-m MultiAgent_FPGA.aes_mvp record-repair-edit {module_id} '
                f'--workspace-root {generation_entry["workspace_root"]} '
                '--strict'
            )
            command = node_executor_command(
                module_id,
                workspace_root=str(generation_entry['workspace_root']),
                promoted_root=str(generation_entry['promoted_root']),
            )
            generation_result_path = str(
                (
                    Path(generation_entry['workspace_root']) / 'generation_result.json'
                ).resolve()
            )
            workspace_state_path = str(
                (
                    Path(generation_entry['workspace_root']) / 'workspace_state.json'
                ).resolve()
            )
            validation_summary_path = str(
                Path(
                    generation_entry['validation_paths']['validation_summary']
                ).resolve()
            )
            validation_error_path = str(
                Path(generation_entry['validation_paths']['validation_error']).resolve()
            )
            repair_request_path = str(
                Path(generation_entry['repair_request_path']).resolve()
            )
            edit_receipt_path = str(
                Path(generation_entry['edit_receipt_path']).resolve()
            )
            next_read_paths = [
                generation_result_path,
                workspace_state_path,
                validation_summary_path,
                validation_error_path,
                repair_request_path,
                edit_receipt_path,
                *[
                    str(path)
                    for path in generation_entry['validation_paths'].values()
                    if isinstance(path, str)
                ],
            ]
            prompt = '\n'.join(
                [
                    f'Revalidate the repaired node {node.module_id}.',
                    'Mode: validate.',
                    'Use the task contract file as the source of truth.',
                    "First action: call 'run_executor' with this task contract.",
                    'The executor will materialize edit_receipt.json first when it is still missing.',
                    'DO NOT edit any RTL or testbench files. This is a read-only validation pass.',
                    'DO NOT add VCD tracing, waveform includes, or any other modifications to source files.',
                    'Return a compact JSON-style summary with keys: module_id, workspace_state, changed_files, validation_status, checkpoint_summary, promoted, repair_attempts, escalated.',
                ]
            )
            return DelegateBatchTask(
                worker_id=f'module_build__{node.module_id}',
                agent_type=self.factory.module_worker_registry_name(node),
                mode=SubagentWorkMode.VALIDATE,
                request=NodeExecutionRequest(
                    module_id=node.module_id,
                    stage=OrchestratorState.MODULE_L1,
                    repair_budget=repair_budget_for_node(node),
                    writable_paths=[],
                    artifact_paths=[
                        *generation_entry['contract_paths'].values(),
                        *generation_entry['validation_paths'].values(),
                    ],
                    executor_kind=ExecutorKind.RUN_NODE,
                    executor_inputs={
                        'promoted_root': str(generation_entry['promoted_root']),
                        'increment_workspace_validation': True,
                    },
                    manual_executor_command=command,
                    manual_receipt_command=manual_receipt_command,
                    preflight_record_repair_edit=True,
                    working_directory=str(self.bootstrap.workspace_root),
                    workspace_root=str(generation_entry['workspace_root']),
                    contract_paths=dict(generation_entry['contract_paths']),
                    result_paths={
                        'generation_result': generation_result_path,
                        'workspace_state': workspace_state_path,
                        'validation_summary': validation_summary_path,
                        'validation_error': validation_error_path,
                        'repair_request': repair_request_path,
                        'edit_receipt': edit_receipt_path,
                    },
                    promoted_targets=list(generation_entry['promoted_targets']),
                    allowed_progress_actions=['run_executor'],
                    next_read_paths=next_read_paths,
                    workflow_gate_hint='framework_will_select_next_eligible_batch',
                ),
                prompt=prompt,
            )

        def build_l2_task(task) -> DelegateBatchTask:
            node = nodes_by_id[task.module_id]
            resolved = resolve_l2_campaign_inputs(
                package_root=self.bootstrap.workspace_root,
                node=node,
                profile=str(task.profile),
                vecfile=task.vecfile,
                cases=task.cases,
                seed=task.seed,
            )
            command = node_executor_command(
                node.module_id,
                workspace_root=str(generation_nodes[node.module_id]['workspace_root']),
                promoted_root=str(generation_nodes[node.module_id]['promoted_root']),
                l2_profile=resolved.profile,
                vecfile=str(resolved.vecfile),
                cases=resolved.cases,
                seed=resolved.seed,
            )
            next_read_paths = self._expected_l2_artifact_paths(
                node, profile=resolved.profile
            )
            prompt = '\n'.join(
                [
                    f'Execute the adaptive L2 campaign for {node.module_id}.',
                    'Mode: l2_execute.',
                    'Use the task contract file as the source of truth.',
                    'Do not edit RTL or testbench files.',
                    "First action: call 'run_executor' with this task contract.",
                    'Return a compact JSON-style summary with keys: module_id, profile, l2_status, failing_checkpoints, output_paths, escalated.',
                ]
            )
            l2_registry_name = self.factory.l2_campaign_registry_name(
                node, profile=resolved.profile
            )
            return DelegateBatchTask(
                worker_id=l2_registry_name,
                agent_type=l2_registry_name,
                mode=SubagentWorkMode.L2_EXECUTE,
                request=NodeExecutionRequest(
                    module_id=node.module_id,
                    stage=OrchestratorState.MODULE_L2_OPTIONAL,
                    repair_budget=repair_budget_for_node(node),
                    artifact_paths=self._expected_l2_artifact_paths(
                        node, profile=resolved.profile
                    ),
                    l2_profile=resolved.profile,
                    vecfile=str(resolved.vecfile),
                    cases=resolved.cases,
                    seed=resolved.seed,
                    executor_kind=ExecutorKind.RUN_NODE,
                    executor_inputs={
                        'promoted_root': str(
                            generation_nodes[node.module_id]['promoted_root']
                        ),
                        'increment_workspace_validation': False,
                    },
                    manual_executor_command=command,
                    working_directory=str(self.bootstrap.workspace_root),
                    writable_paths=[],
                    allowed_progress_actions=['run_executor'],
                    next_read_paths=next_read_paths,
                    workflow_gate_hint='framework_will_select_next_eligible_batch',
                ),
                prompt=prompt,
            )

        materialized_batches: list[dict[str, Any]] = []
        for batch in planned_batches:
            if all(task.mode == SubagentWorkMode.GENERATE for task in batch.tasks):
                generate_tasks = [
                    build_generate_validate_task(task.module_id) for task in batch.tasks
                ]
                generate_batch = DelegateBatchPlan(
                    batch_id=f'{batch.batch_id}_generate_validate',
                    stage=batch.stage,
                    max_children=MAX_DELEGATE_CHILDREN,
                    fallback_policy='orchestrator_takeover',
                    tasks=generate_tasks,
                )
                materialized_batches.append(
                    {
                        **generate_batch.model_dump(),
                        'phase': 'generate_validate',
                        'spawn': (
                            generate_batch.spawn_payload()
                            if batch.include_spawn
                            else {'command': 'spawn', 'ids': [], 'agent_types': []}
                        ),
                        'delegate': generate_batch.delegate_payload(),
                    }
                )

                for task in batch.tasks:
                    module_id = task.module_id
                    node = nodes_by_id[module_id]
                    node_repair_budget = repair_budget_for_node(node)
                    for repair_round in range(1, node_repair_budget + 1):
                        repair_task = build_repair_task(module_id)
                        repair_result_path = repair_task.request.result_paths.get(
                            'generation_result'
                        )
                        repair_batch = DelegateBatchPlan(
                            batch_id=(
                                f'{batch.batch_id}_{module_id}_repair_{repair_round}'
                            ),
                            stage=OrchestratorState.MODULE_L1,
                            max_children=MAX_DELEGATE_CHILDREN,
                            fallback_policy='orchestrator_takeover',
                            tasks=[repair_task],
                        )
                        materialized_batches.append(
                            {
                                **repair_batch.model_dump(),
                                'phase': 'repair_edit',
                                'spawn': repair_batch.spawn_payload(),
                                'delegate': repair_batch.delegate_payload(),
                                'condition': {
                                    'type': 'any_generation_result_requires_repair',
                                    'result_paths': (
                                        [repair_result_path]
                                        if isinstance(repair_result_path, str)
                                        else []
                                    ),
                                },
                                'repair_round': repair_round,
                            }
                        )

                        revalidate_task = build_revalidate_task(module_id)
                        revalidate_result_path = (
                            revalidate_task.request.result_paths.get(
                                'generation_result'
                            )
                        )
                        revalidate_batch = DelegateBatchPlan(
                            batch_id=(
                                f'{batch.batch_id}_{module_id}_revalidate_{repair_round}'
                            ),
                            stage=OrchestratorState.MODULE_L1,
                            max_children=MAX_DELEGATE_CHILDREN,
                            fallback_policy='orchestrator_takeover',
                            tasks=[revalidate_task],
                        )
                        materialized_batches.append(
                            {
                                **revalidate_batch.model_dump(),
                                'phase': 'revalidate',
                                'spawn': revalidate_batch.spawn_payload(),
                                'delegate': revalidate_batch.delegate_payload(),
                                'condition': {
                                    'type': 'any_generation_result_requires_repair',
                                    'result_paths': (
                                        [revalidate_result_path]
                                        if isinstance(revalidate_result_path, str)
                                        else []
                                    ),
                                },
                                'repair_round': repair_round,
                            }
                        )
                continue

            tasks = [build_l2_task(task) for task in batch.tasks]
            delegate_batch = DelegateBatchPlan(
                batch_id=batch.batch_id,
                stage=batch.stage,
                max_children=MAX_DELEGATE_CHILDREN,
                fallback_policy='orchestrator_takeover',
                tasks=tasks,
            )
            materialized_batches.append(
                {
                    **delegate_batch.model_dump(),
                    'phase': 'l2_execute',
                    'spawn': (
                        delegate_batch.spawn_payload()
                        if batch.include_spawn
                        else {'command': 'spawn', 'ids': [], 'agent_types': []}
                    ),
                    'delegate': delegate_batch.delegate_payload(),
                }
            )

        sink = readiness_resolver.select_primary_sink(self.bootstrap.plan_dag)
        delegate_plan = self._materialize_delegate_plan(
            {
                'execution_mode': 'autonomous-generate',
                'delegate_enabled': True,
                'max_children': MAX_DELEGATE_CHILDREN,
                'system_goal': self.bootstrap.system_goal,
                'spec_ir_path': str(self.spec_ir_artifact_path),
                'plan_dag_path': str(self.plan_dag_artifact_path),
                'fragility_memory_path': str(self.fragility_memory_path),
                'generation_plan_path': str(self.generation_plan_path),
                'brief_generation_summary_path': str(
                    self.brief_generation_summary_path
                ),
                'integration_target': sink.module_id,
                'manual_integration_command': (
                    f'PYTHONPATH={self.bootstrap.repo_root} '
                    f'/opt/anaconda3/envs/openhands/bin/python '
                    '-m MultiAgent_FPGA.aes_mvp run-integration '
                    f'--promoted-root {self._promoted_root()} '
                    f'--output-root {self._integration_output_root()}'
                ),
                'batches': materialized_batches,
            }
        )
        self._write_json(self.batch_plan_path, delegate_plan)
        return delegate_plan

    def _build_delegate_plan(self) -> dict[str, Any]:
        return self._build_autonomous_delegate_plan()

    def _collect_existing_generation_summary(self) -> dict[str, Any]:
        generation_results: dict[str, dict[str, Any]] = {}
        promotion_events: list[dict[str, Any]] = []
        promotion_failures: list[dict[str, Any]] = []

        for node in self.bootstrap.plan_dag.nodes:
            workspace_root = self._generation_workspace_root(node.module_id)
            generation_result_path = (
                workspace_root / 'generation_result.json'
            ).resolve()
            generation_payload = self._load_json_file(generation_result_path)
            if generation_payload is None:
                generation_payload = {
                    'module_id': node.module_id,
                    'workspace_state': 'missing',
                    'promoted': False,
                }
            generation_results[node.module_id] = generation_payload
            self._write_json(
                self.generation_results_dir / f'{node.module_id}.json',
                generation_payload,
            )

            promotion_record_path = (
                workspace_root / 'promotion' / 'promotion_record.json'
            ).resolve()
            promotion_payload = self._load_json_file(promotion_record_path)
            if promotion_payload is None:
                promotion_failures.append(
                    {
                        'module_id': node.module_id,
                        'reason': 'promotion_record_missing',
                        'workspace_root': str(workspace_root),
                    }
                )
            else:
                promotion_events.append(promotion_payload)

        self._write_json(
            self.promotion_events_path,
            {'events': promotion_events, 'count': len(promotion_events)},
        )
        self._write_json(
            self.promotion_failures_path,
            {'failures': promotion_failures, 'count': len(promotion_failures)},
        )

        integration_result_path = (
            self._integration_output_root() / 'integration_regression_result.json'
        ).resolve()
        integration_payload = self._load_json_file(integration_result_path)
        integration_summary = {
            'result_path': str(integration_result_path)
            if integration_result_path.is_file()
            else None,
            'status': integration_payload.get('status')
            if integration_payload
            else 'missing',
            'campaign_count': len(integration_payload.get('campaign_results', []))
            if integration_payload
            else 0,
        }
        self._write_json(self.integration_summary_path, integration_summary)

        generation_summary = {
            'conversation_id': str(self.conversation_id),
            'focus_module_id': self.focus_module_id,
            'generation_results_dir': str(self.generation_results_dir),
            'integration_summary_path': str(self.integration_summary_path),
            'modules': generation_results,
            'promotion_events_path': str(self.promotion_events_path),
            'promotion_failures_path': str(self.promotion_failures_path),
            'integration': integration_summary,
        }
        self._write_json(self.deterministic_execution_path, generation_summary)
        self._write_json(self.report_tree_path, self._report_tree_payload())
        return generation_summary

    def _collect_fragility_memory(self) -> FragilityMemory:
        existing_payload = self._load_json_file(self.fragility_memory_path)
        prior_runtime: list[dict[str, Any]] = []
        if existing_payload:
            raw_rt = existing_payload.get('runtime_signals')
            if isinstance(raw_rt, list):
                prior_runtime = [x for x in raw_rt if isinstance(x, dict)]
        memory = FragilityMemory(runtime_signals=prior_runtime)
        for node in self.bootstrap.plan_dag.nodes:
            l2_root = (
                self._generation_workspace_root(node.module_id)
                / 'validation'
                / 'sim'
                / 'l2'
            ).resolve()
            if not l2_root.is_dir():
                continue
            for result_path in sorted(l2_root.glob('*/l2_result.json')):
                payload = self._load_json_file(result_path)
                if payload is None:
                    continue
                memory.module_history.setdefault(node.module_id, []).append(
                    FragilitySignal(
                        profile=str(payload.get('profile', 'unknown')),
                        status='passed'
                        if not payload.get('missing_checkpoints')
                        and not payload.get('failed_checkpoints')
                        else 'failed',
                        failing_checkpoints=list(payload.get('failed_checkpoints', [])),
                        missing_checkpoints=list(
                            payload.get('missing_checkpoints', [])
                        ),
                        counterexample_path=payload.get('counterexample_path'),
                        vecfile=payload.get('vecfile'),
                        seed=payload.get('seed'),
                        cases=payload.get('cases'),
                    )
                )
        self._write_json(self.fragility_memory_path, memory.model_dump())
        return memory

    def _module_fragility_summary(
        self, module_id: str, *, max_signals: int = 3
    ) -> str | None:
        """Return a compact summary of recent fragility signals for a module (B7)."""
        data = self._load_json_file(self.fragility_memory_path)
        if data is None:
            return None
        history = data.get('module_history', {}).get(module_id, [])
        if not history:
            return None
        recent = history[-max_signals:]
        lines = [f'Fragility history for {module_id} (last {len(recent)} signals):']
        for sig in recent:
            status = sig.get('status', 'unknown')
            profile = sig.get('profile', 'unknown')
            failing = sig.get('failing_checkpoints', [])
            missing = sig.get('missing_checkpoints', [])
            detail = f'  profile={profile} status={status}'
            if failing:
                detail += f' failing=[{", ".join(failing)}]'
            if missing:
                detail += f' missing=[{", ".join(missing)}]'
            lines.append(detail)
        return '\n'.join(lines)

    def _append_runtime_fragility_signal(self, signal: dict[str, Any]) -> None:
        data = self._load_json_file(self.fragility_memory_path)
        if data is None:
            data = FragilityMemory().model_dump()
        signals = [x for x in data.get('runtime_signals', []) if isinstance(x, dict)]
        signals.append(signal)
        data['runtime_signals'] = signals
        self._write_json(self.fragility_memory_path, data)

    def _generation_result_requires_repair(self, generation_result_path: Path) -> bool:
        payload = self._load_json_file(generation_result_path)
        if payload is None:
            return False
        recommended_mode = str(payload.get('recommended_mode', '')).strip()
        workspace_state = str(payload.get('workspace_state', '')).strip()
        return (
            recommended_mode == 'repair'
            or workspace_state == 'repairing'
            or workspace_state == 'generated'
        )

    def _upstream_dependencies_promoted(self, batch: dict[str, Any]) -> bool:
        """Check if all upstream DAG dependencies for this batch's modules are promoted.

        Only applies to generate_validate batches — repair/revalidation batches
        operate on existing workspaces and don't need this gate.
        """
        if batch.get('phase') != 'generate_validate':
            return True
        nodes_by_id = {node.module_id: node for node in self.bootstrap.plan_dag.nodes}
        for task in batch.get('tasks', []):
            module_id = task.get('module_id') or task.get('request', {}).get(
                'module_id'
            )
            if not module_id or module_id not in nodes_by_id:
                continue
            for dep_id in nodes_by_id[module_id].depends_on:
                dep_gen_path = (
                    self._generation_workspace_root(dep_id) / 'generation_result.json'
                )
                dep_payload = self._load_json_file(dep_gen_path)
                if dep_payload is None or not dep_payload.get('promoted'):
                    return False
        return True

    def _select_batch_tasks(self, batch: dict[str, Any]) -> list[dict[str, Any]]:
        tasks = [task for task in batch.get('tasks', []) if isinstance(task, dict)]
        condition = batch.get('condition')
        if not isinstance(condition, dict):
            return tasks
        if condition.get('type') != 'any_generation_result_requires_repair':
            return tasks
        selected_tasks: list[dict[str, Any]] = []
        for task in tasks:
            result_paths = task.get('request', {}).get('result_paths', {})
            generation_result_path = result_paths.get('generation_result')
            if isinstance(
                generation_result_path, str
            ) and self._generation_result_requires_repair(Path(generation_result_path)):
                selected_tasks.append(task)
        return selected_tasks

    def _materialize_current_batch(
        self,
        *,
        batch: dict[str, Any],
        selected_tasks: list[dict[str, Any]],
    ) -> dict[str, Any]:
        repair_round = batch.get('repair_round')
        materialized_tasks = [
            self._materialize_selected_task_for_current_batch(
                phase=str(batch.get('phase', 'delegate')),
                task=task,
                repair_round=repair_round,
            )
            for task in selected_tasks
        ]
        batch_id = str(batch.get('batch_id'))
        # Intersect with plan spawn ids when the plan lists them; otherwise derive
        # spawn targets from the selected tasks. Empty plan spawn must not wipe
        # worker ids (legacy batch_plan / stale session files used to emit
        # spawn.ids=[] which caused sub-agents not found on fresh conversations).
        plan_spawn_ids = list(batch.get('spawn', {}).get('ids', []) or [])
        if plan_spawn_ids:
            plan_spawn_set = {str(x) for x in plan_spawn_ids}
            spawn_ids = [
                str(task.get('worker_id'))
                for task in materialized_tasks
                if str(task.get('worker_id') or '') in plan_spawn_set
            ]
        else:
            spawn_ids = [
                str(task.get('worker_id'))
                for task in materialized_tasks
                if task.get('worker_id')
            ]
        agent_type_by_worker = {
            str(task.get('worker_id')): str(task.get('agent_type'))
            for task in materialized_tasks
            if task.get('worker_id')
        }
        return {
            'batch_id': batch_id,
            'phase': str(batch.get('phase', 'delegate')),
            'stage': batch.get('stage'),
            'repair_round': batch.get('repair_round'),
            'tasks': materialized_tasks,
            'spawn': {
                'command': 'spawn',
                'ids': spawn_ids,
                'agent_types': [
                    agent_type_by_worker[worker_id] for worker_id in spawn_ids
                ],
            },
            'delegate': {
                'command': 'delegate',
                'tasks': {
                    str(task.get('worker_id')): str(task.get('prompt', ''))
                    for task in materialized_tasks
                },
            },
            'condition': batch.get('condition'),
        }

    def _materialize_selected_task_for_current_batch(
        self,
        *,
        phase: str,
        task: dict[str, Any],
        repair_round: int | None = None,
    ) -> dict[str, Any]:
        if phase != 'repair_edit':
            return copy.deepcopy(task)
        return self._materialize_repair_task_for_current_batch(
            task,
            repair_round=repair_round,
        )

    def _materialize_repair_task_for_current_batch(
        self,
        task: dict[str, Any],
        *,
        repair_round: int | None = None,
    ) -> dict[str, Any]:
        effective_repair_round = repair_round or 1
        # Use the per-node repair_budget from the task request if available,
        # falling back to the global threshold (A1-d closed-loop fix).
        task_repair_budget = (task.get('request') or {}).get('repair_budget')
        max_repair_rounds = (
            int(task_repair_budget)
            if task_repair_budget is not None
            else self.bootstrap.policy.repair_attempt_threshold
        )
        materialized = copy.deepcopy(task)
        request = materialized.get('request', {})
        if not isinstance(request, dict):
            return materialized
        result_paths = request.get('result_paths', {})
        if not isinstance(result_paths, dict):
            return materialized
        repair_request_path = result_paths.get('repair_request')
        if not isinstance(repair_request_path, str):
            return materialized
        repair_request_file = Path(repair_request_path)
        if not repair_request_file.is_file():
            return materialized
        try:
            repair_contract = load_repair_contract(repair_request_file)
        except (FileNotFoundError, json.JSONDecodeError, ValueError):
            return materialized

        # Build prior-repair context for round 2+
        prior_info: list[str] = []
        if effective_repair_round > 1:
            gen_result_file = Path(result_paths.get('generation_result', ''))
            if gen_result_file.is_file():
                try:
                    gen = json.loads(gen_result_file.read_text(encoding='utf-8'))
                    prior_info = [
                        f'Prior repair round {effective_repair_round - 1} made edits but validation still failed.',
                        f'Prior failure_phase: {gen.get("failure_phase", "unknown")}',
                        f'Prior repair_attempts: {gen.get("repair_attempts", 0)}',
                    ]
                    changed = gen.get('changed_files', [])
                    if changed:
                        prior_info.append(
                            f'Files changed by prior repair: {", ".join(changed)}'
                        )
                    # Surface what specifically failed after the prior repair
                    prior_validation_status = gen.get('validation_status', '')
                    if prior_validation_status and prior_validation_status != 'passed':
                        prior_info.append(
                            f'Prior validation_status: {prior_validation_status}'
                        )
                    prior_missing = gen.get('missing_checkpoints', [])
                    if prior_missing:
                        prior_info.append(
                            f'Checkpoints still missing after prior repair: {", ".join(prior_missing)}'
                        )
                    prior_failed = gen.get('failed_checkpoints', [])
                    if prior_failed:
                        prior_info.append(
                            f'Checkpoints still failing after prior repair: {", ".join(prior_failed)}'
                        )
                except (json.JSONDecodeError, ValueError):
                    prior_info = [
                        f'Repair round {effective_repair_round}: prior repair state unreadable.'
                    ]
            else:
                prior_info = [
                    f'Repair round {effective_repair_round}: prior generation_result not found.'
                ]
            # Inject zero-edit warning from prior repair hook outcomes (B6)
            module_id = repair_contract.module_id
            prior_outcome = self._latest_repair_outcomes.get(module_id, {})
            if prior_outcome.get('zero_edits'):
                prior_info.append(
                    'WARNING: The prior repair round produced ZERO edits. '
                    'The file was not modified at all. You MUST make at least '
                    'one concrete edit this round or the repair will be marked as blocked.'
                )
            # Inject fragility history for the module (B7)
            fragility_summary = self._module_fragility_summary(module_id)
            if fragility_summary:
                prior_info.append(fragility_summary)

        validation_artifact_paths = [
            str(path)
            for path in request.get('artifact_paths', [])
            if isinstance(path, str) and '/validation/' in path
        ]
        generation_result_path = result_paths.get('generation_result', '')
        workspace_state_path = result_paths.get('workspace_state', '')
        validation_summary_path = result_paths.get('validation_summary', '')
        validation_error_path = result_paths.get('validation_error', '')
        edit_receipt_path = result_paths.get('edit_receipt', '')
        manual_receipt_command = request.get('manual_receipt_command') or ''
        first_edit_steps = (
            [f'- {step}' for step in repair_contract.first_edit_steps]
            if repair_contract.first_edit_steps
            else ['- Make the smallest concrete first edit on the primary_target_file.']
        )
        must_add_tokens_line = (
            'must_add_tokens: ' + ', '.join(repair_contract.must_add_tokens)
            if repair_contract.must_add_tokens
            else 'must_add_tokens:'
        )
        secondary_target_lines = (
            [f'- {path}' for path in repair_contract.secondary_target_files]
            if repair_contract.secondary_target_files
            else ['- none']
        )
        prompt = '\n'.join(
            [
                f'Repair the node {repair_contract.module_id} after the initial generate pass failed.',
                'Mode: repair.',
                f'Repair round: {effective_repair_round} of {max_repair_rounds}.',
                *prior_info,
                'Use the inlined repair contract below as the source of truth for the first edit.',
                f'workspace_root: {repair_contract.workspace_root}',
                f'primary_writable_path: {repair_contract.primary_target_file}',
                f'generation_result_path: {generation_result_path}',
                f'workspace_state_path: {workspace_state_path}',
                f'validation_summary_path: {validation_summary_path}',
                f'validation_error_path: {validation_error_path}',
                f'repair_request_path: {repair_request_path}',
                f'edit_receipt_path: {edit_receipt_path}',
                f'primary_target_file: {repair_contract.primary_target_file}',
                f'primary_target_reason: {repair_contract.primary_target_reason or ""}',
                'error_excerpt:',
                repair_contract.error_excerpt or '(no error excerpt available)',
                'simulation_log_excerpt:',
                repair_contract.simulation_log_excerpt
                or '(no simulation log available)',
                'primary_file_excerpt:',
                repair_contract.primary_file_excerpt or '(no excerpt available)',
                'first_edit_steps:',
                *first_edit_steps,
                must_add_tokens_line,
                'secondary_target_files (read-only reference for this phase):',
                *secondary_target_lines,
                'validation_artifact_paths:',
                *[f'- {path}' for path in validation_artifact_paths],
                (
                    'Do not call file_editor view on the primary_target_file '
                    'before the first edit; use the embedded primary_file_excerpt '
                    'and first_edit_steps as the source of truth.'
                    if effective_repair_round <= 1
                    else (
                        f'This is repair round {effective_repair_round}. A prior repair attempt '
                        'already modified this file. You MAY call file_editor view '
                        'on the primary_target_file to understand its current state '
                        'before editing. Focus on fixing the specific error shown in '
                        'error_excerpt and simulation_log_excerpt.'
                    )
                ),
                'Consult repair_request.json only if this inlined repair contract appears inconsistent with the workspace.',
                'Read generation_result.json, workspace_state.json, validation_summary.json, validation_error.json, and the validation artifacts only after you have the primary repair target and first_edit_steps in hand.',
                'If generation_result.json says validation_status=passed or recommended_mode is not repair, do not edit files. Return a skipped summary for this repair phase.',
                'Your first edit must satisfy repair_request.required_first_edit against repair_request.primary_target_file.',
                'Do not edit any secondary_target_files in this phase.',
                'You must make at least one concrete edit to the primary_target_file in this phase.',
                'Do not run compile, simulation, or receipt-recording commands in this phase.',
                'The framework will materialize edit_receipt.json before the next revalidate batch.',
                'Revalidation will happen in the next batch.',
                'Do not edit canonical repository RTL/TB files directly.',
                'Do not call raw verilator_compile or verilator_simulate.',
                f'manual_receipt_command_for_next_phase: {manual_receipt_command}',
                'If the issue is clearly cross-module, interface-level, or beyond your repair scope, '
                'write a JSON file to escalation_signal.json in the workspace_root with keys: '
                'module_id, reason, suggested_action. This signals the framework to escalate to the orchestrator.',
                'Return a compact JSON-style summary with keys: module_id, workspace_state, changed_files, repair_status, escalated.',
            ]
        )
        escalation_path = str(
            (Path(repair_contract.workspace_root) / 'escalation_signal.json').resolve()
        )
        request['writable_paths'] = [
            repair_contract.primary_target_file,
            escalation_path,
        ]
        materialized['request'] = request
        materialized['prompt'] = prompt
        return materialized

    def _batch_expected_artifact_paths(
        self, current_batch: dict[str, Any]
    ) -> list[str]:
        phase = str(current_batch.get('phase', 'delegate'))
        paths: list[str] = []
        for task in current_batch.get('tasks', []):
            request = task.get('request', {})
            result_paths = request.get('result_paths', {})
            artifact_paths = request.get('artifact_paths', [])
            if phase == 'generate_validate':
                generation_result = result_paths.get('generation_result')
                if isinstance(generation_result, str):
                    paths.append(generation_result)
            elif phase == 'repair_edit':
                edit_receipt = result_paths.get('edit_receipt')
                if isinstance(edit_receipt, str):
                    paths.append(edit_receipt)
            elif phase == 'revalidate':
                generation_result = result_paths.get('generation_result')
                if isinstance(generation_result, str):
                    paths.append(generation_result)
            elif phase == 'l2_execute':
                l2_result = next(
                    (
                        str(path)
                        for path in artifact_paths
                        if isinstance(path, str) and path.endswith('l2_result.json')
                    ),
                    None,
                )
                if l2_result is not None:
                    paths.append(l2_result)
            elif phase == 'integration':
                integration_result = result_paths.get('integration_result')
                if isinstance(integration_result, str):
                    paths.append(integration_result)
        return paths

    def _artifact_stat(self, path: str) -> dict[str, Any] | None:
        artifact_path = Path(path)
        if not artifact_path.is_file():
            return None
        stat = artifact_path.stat()
        return {'mtime_ns': stat.st_mtime_ns, 'size': stat.st_size}

    def _artifact_snapshot(self, paths: list[str]) -> dict[str, dict[str, Any] | None]:
        return {path: self._artifact_stat(path) for path in paths}

    def _artifact_updated(
        self,
        *,
        path: str,
        baseline: dict[str, dict[str, Any] | None],
    ) -> bool:
        current = self._artifact_stat(path)
        previous = baseline.get(path)
        if current is None:
            return False
        if previous is None:
            return True
        return (
            current['mtime_ns'] != previous['mtime_ns']
            or current['size'] != previous['size']
        )

    def _materialize_framework_batch_artifacts(
        self, *, current_batch: dict[str, Any]
    ) -> None:
        if str(current_batch.get('phase', '')) != 'repair_edit':
            return
        for task in current_batch.get('tasks', []):
            request = task.get('request', {})
            workspace_root = request.get('workspace_root')
            result_paths = request.get('result_paths', {})
            edit_receipt_path = result_paths.get('edit_receipt')
            if not isinstance(workspace_root, str) or not isinstance(
                edit_receipt_path, str
            ):
                continue
            receipt_path = Path(edit_receipt_path)
            if receipt_path.is_file():
                continue
            workspace_path = Path(workspace_root)
            repair_request_path = workspace_path / 'repair_request.json'
            if not repair_request_path.is_file():
                continue
            try:
                repair_contract = load_repair_contract(workspace_path)
            except (FileNotFoundError, json.JSONDecodeError, ValueError):
                continue
            (
                repair_valid,
                edited_files,
                _repair_message,
            ) = verify_repair_edit(
                workspace_root=workspace_path,
                repair_contract=repair_contract,
            )
            if not repair_valid:
                failure_path = workspace_path / 'repair_verify_failure.json'
                self._write_json(
                    failure_path,
                    {
                        'module_id': repair_contract.module_id,
                        'batch_id': str(current_batch.get('batch_id', '')),
                        'workspace_root': str(workspace_path),
                        'message': _repair_message,
                        'edited_files': edited_files,
                    },
                )
                self._append_runtime_fragility_signal(
                    {
                        'type': 'repair_verify_failed',
                        'module_id': repair_contract.module_id,
                        'batch_id': str(current_batch.get('batch_id', '')),
                        'workspace_root': str(workspace_path),
                        'message': _repair_message,
                    }
                )
                continue
            write_edit_receipt(
                workspace_root=workspace_path,
                repair_contract=repair_contract,
                edited_files=edited_files,
                first_edit_summary=repair_contract.required_first_edit,
            )

    def _batch_escalation_signal_paths(
        self, current_batch: dict[str, Any]
    ) -> list[Path]:
        """Return escalation_signal.json paths for each task in the batch (A6)."""
        paths: list[Path] = []
        for task in current_batch.get('tasks', []):
            request = task.get('request', {})
            ws = request.get('workspace_root', '')
            if ws:
                paths.append(Path(ws) / 'escalation_signal.json')
        return paths

    def _build_batch_gate(
        self,
        *,
        current_batch: dict[str, Any],
        baseline: dict[str, dict[str, Any] | None],
    ):
        expected_paths = self._batch_expected_artifact_paths(current_batch)
        escalation_paths = self._batch_escalation_signal_paths(current_batch)

        def gate() -> bool:
            self._materialize_framework_batch_artifacts(current_batch=current_batch)
            # Check if any worker signaled escalation (A6)
            for esc_path in escalation_paths:
                if esc_path.is_file():
                    return True
            return all(
                self._artifact_updated(path=path, baseline=baseline)
                for path in expected_paths
            )

        return gate

    def _build_orchestrator_batch_snapshot_payload(
        self,
        *,
        current_batch: dict[str, Any],
        workflow_gate: dict[str, Any],
        expected_artifacts: list[str],
    ) -> dict[str, Any]:
        """Write a small on-disk snapshot for the execution orchestrator.

        Full prompts and ``NodeExecutionRequest`` payloads stay in per-task
        ``delegate_requests`` JSON; the canonical gate blob stays at
        ``workflow_gate_path``. This avoids duplicating long text in the snapshot.
        """
        slim_tasks: list[dict[str, Any]] = []
        for task in current_batch.get('tasks', []):
            if not isinstance(task, dict):
                continue
            entry: dict[str, Any] = {
                'worker_id': task.get('worker_id'),
            }
            if task.get('agent_type') is not None:
                entry['agent_type'] = task.get('agent_type')
            if task.get('mode') is not None:
                entry['mode'] = task.get('mode')
            rp = task.get('request_path')
            if isinstance(rp, str) and rp.strip():
                entry['request_path'] = rp
            slim_tasks.append(entry)

        payload: dict[str, Any] = {
            'batch_id': current_batch['batch_id'],
            'phase': current_batch['phase'],
            'tasks': slim_tasks,
            'expected_artifacts': expected_artifacts,
            'manual_command_policy': (
                'manual_*_command fields are operator-facing only; runtime '
                'dispatch uses structured request fields.'
            ),
            'workflow_gate_path': str(self.workflow_gate_path.resolve()),
            'workflow_gate_summary': {
                'decision': workflow_gate.get('decision'),
                'next_batch_ids': workflow_gate.get('next_batch_ids', []),
            },
            'delegate_requests_dir': str(self.delegate_requests_dir.resolve()),
        }
        if 'spawn' in current_batch:
            payload['spawn'] = current_batch['spawn']
        if current_batch.get('phase') == 'integration' and slim_tasks:
            request_path = slim_tasks[0].get('request_path')
            if isinstance(request_path, str) and request_path.strip():
                payload['integration_request_path'] = request_path
        return payload

    def _build_prior_repair_summary(
        self, module_id: str, repair_round: int
    ) -> str | None:
        """Build a condensed summary of a prior repair round for inter-round context."""
        ws = self._generation_workspace_root(module_id)
        lines: list[str] = [f'--- Prior repair round {repair_round} context ---']
        gen_result_path = ws / 'generation_result.json'
        if gen_result_path.is_file():
            try:
                gen = json.loads(gen_result_path.read_text(encoding='utf-8'))
            except (json.JSONDecodeError, ValueError):
                return None
            lines.append(f'Prior validation_status: {gen.get("validation_status")}')
            lines.append(f'Prior failure_phase: {gen.get("failure_phase")}')
            lines.append(f'Prior repair_attempts: {gen.get("repair_attempts")}')
            changed = gen.get('changed_files', [])
            if changed:
                lines.append(f'Prior changed_files: {", ".join(changed)}')
        verr_path = ws / 'validation' / 'validation_error.json'
        if verr_path.is_file():
            try:
                verr = json.loads(verr_path.read_text(encoding='utf-8'))
                err_msg = verr.get('error', {}).get('message', '')
                if err_msg:
                    lines.append(f'Current error: {err_msg[:500]}')
            except (json.JSONDecodeError, ValueError):
                pass
        lines.append('--- End prior context ---')
        return '\n'.join(lines)

    def _build_autonomous_batch_message(
        self,
        *,
        base_message: str,
        current_batch: dict[str, Any],
        workflow_gate: dict[str, Any],
    ) -> str:
        integration_request_path: Path | None = None
        if str(current_batch.get('phase')) == 'integration':
            first_task = next(
                (
                    task
                    for task in current_batch.get('tasks', [])
                    if isinstance(task, dict)
                ),
                None,
            )
            if first_task is not None:
                raw_request_path = first_task.get('request_path')
                if isinstance(raw_request_path, str) and raw_request_path.strip():
                    integration_request_path = Path(raw_request_path)
        return self.context_assembler.build_batch_message(
            base_message=base_message,
            envelope=BatchMessageEnvelope(
                batch_id=str(current_batch.get('batch_id', '')),
                phase=str(current_batch.get('phase', '')),
                snapshot_path=self.current_batch_snapshot_path,
                workflow_gate_path=self.workflow_gate_path,
                delegate_requests_dir=self.delegate_requests_dir,
                report_root=self.report_root,
                expected_artifacts=tuple(
                    self._batch_expected_artifact_paths(current_batch)
                ),
                handoff_digest_path=self.autonomous_handoff_digest_path,
                integration_request_path=integration_request_path,
            ),
        )

    def _build_finalizer_message(self, *, base_message: str) -> str:
        return '\n'.join(
            [
                'Use finalizer_input.json as the source of truth for the completed workflow.',
                'Do not run any delegate, build, repair, L2, or integration work.',
                'Read the terminal workflow gate decision and produce the final acceptance summary.',
                'Call finish exactly once.',
                f'Finalizer input: {self.finalizer_input_path}',
                f'Original request: {base_message}',
            ]
        )

    def _next_eligible_autonomous_batch(
        self,
        *,
        delegate_plan: dict[str, Any],
        processed_batch_ids: set[str],
    ) -> tuple[dict[str, Any] | None, list[dict[str, Any]]]:
        skipped_batches: list[dict[str, Any]] = []
        for batch in delegate_plan.get('batches', []):
            batch_id = str(batch.get('batch_id'))
            if batch_id in processed_batch_ids:
                continue
            # Gate: skip generate_validate batches whose upstream deps aren't promoted.
            # Do NOT add to processed_batch_ids — the batch must be re-evaluated
            # once upstream modules are repaired and promoted (B7-a closed-loop fix).
            if not self._upstream_dependencies_promoted(batch):
                skipped_batches.append(
                    {
                        'batch_id': batch_id,
                        'phase': batch.get('phase'),
                        'status': 'skipped',
                        'reason': 'upstream_not_promoted',
                    }
                )
                continue
            selected_tasks = self._select_batch_tasks(batch)
            if not selected_tasks:
                skipped_batches.append(
                    {
                        'batch_id': batch_id,
                        'phase': batch.get('phase'),
                        'status': 'skipped',
                        'reason': 'condition_false',
                    }
                )
                processed_batch_ids.add(batch_id)
                continue
            return (
                self._materialize_current_batch(
                    batch=batch, selected_tasks=selected_tasks
                ),
                skipped_batches,
            )
        return None, skipped_batches

    def _build_integration_batch(
        self, *, delegate_plan: dict[str, Any]
    ) -> dict[str, Any]:
        integration_result_path = str(
            (
                self._integration_output_root() / 'integration_regression_result.json'
            ).resolve()
        )
        task = {
            'worker_id': 'integration',
            'agent_type': 'framework_integration',
            'mode': SubagentWorkMode.INTEGRATION.value,
            'prompt': '\n'.join(
                [
                    'Execute the framework-owned integration regression.',
                    'Mode: integration.',
                    "First action: call 'run_executor' with this task contract.",
                    'Use the resulting observation to inspect only the named integration artifacts.',
                ]
            ),
            'request': {
                'module_id': self.bootstrap.integration_manifest.top_module,
                'stage': OrchestratorState.INTEGRATION_REGRESSION.value,
                'executor_kind': ExecutorKind.RUN_INTEGRATION.value,
                'executor_inputs': {
                    'promoted_root': str(self._promoted_root()),
                    'output_root': str(self._integration_output_root()),
                },
                'working_directory': str(self.bootstrap.workspace_root),
                'result_paths': {'integration_result': integration_result_path},
                'allowed_progress_actions': ['run_executor'],
                'next_read_paths': [integration_result_path],
                'workflow_gate_hint': 'framework_will_evaluate_terminal_integration_status',
            },
        }
        request_path = self._write_task_request_contract(
            batch_id='integration', task=task
        )
        task['request_path'] = str(request_path)
        task['prompt'] = self.context_assembler.attach_task_contract_hint(
            str(task['prompt']),
            TaskContractEnvelope(
                request_path=request_path,
                working_directory=str(self.bootstrap.workspace_root),
                phase='integration',
            ),
        )
        return {
            'batch_id': 'integration',
            'phase': 'integration',
            'tasks': [task],
            'manual_integration_command': str(
                delegate_plan['manual_integration_command']
            ),
        }

    def _evaluate_workflow_gate(
        self,
        *,
        delegate_plan: dict[str, Any],
        processed_batch_ids: set[str],
        deterministic_summary: dict[str, Any],
        protocol_violation: str | None = None,
        integration_attempts: int = 0,
    ) -> dict[str, Any]:
        completion = self._autonomous_completion_summary(deterministic_summary)
        next_batch, _ = self._next_eligible_autonomous_batch(
            delegate_plan=delegate_plan,
            processed_batch_ids=set(processed_batch_ids),
        )
        next_batch_ids = [next_batch['batch_id']] if next_batch is not None else []
        reasons: list[str] = []
        if protocol_violation is not None:
            decision = 'blocked'
            reasons.append(protocol_violation)
        elif completion['completion_status'] == 'success':
            decision = 'success'
        elif completion['completion_status'] == 'blocked':
            decision = 'blocked'
            reasons.append('required_module_blocked')
        elif next_batch is not None:
            decision = 'continue'
        elif (
            not completion['pending_modules']
            and not completion['blocked_modules']
            and not completion.get('cascade_blocked_modules', [])
            and completion['integration_status'] != 'passed'
            and integration_attempts <= MAX_INTEGRATION_RETRIES
        ):
            decision = 'ready_for_integration'
        else:
            decision = 'blocked'
            if completion['pending_modules']:
                reasons.append('no_remaining_eligible_batches')
            if (
                integration_attempts > MAX_INTEGRATION_RETRIES
                and completion['integration_status'] != 'passed'
            ):
                reasons.append('integration_terminal_failure')
        gate_payload = {
            **completion,
            'decision': decision,
            'reasons': reasons,
            'next_batch_ids': next_batch_ids,
            'processed_batch_ids': sorted(processed_batch_ids),
            'protocol_violation': protocol_violation,
            'integration_attempts': integration_attempts,
        }
        self._write_json(self.workflow_gate_path, gate_payload)
        return gate_payload

    @staticmethod
    def _typed_event_to_payload(event: Any) -> dict[str, Any]:
        """Convert a typed SDK event to the dict format used by extraction methods.

        This adapter enables using the typed EventLog API (conversation.state.events)
        instead of reading raw event-*.json files from the persistence directory.
        """
        payload: dict[str, Any] = {}
        for attr in ('id', 'source', 'tool_name', 'tool_call_id'):
            val = getattr(event, attr, None)
            if val is not None:
                payload[attr] = val
        tool_call = getattr(event, 'tool_call', None)
        if tool_call is not None:
            arguments = getattr(tool_call, 'arguments', None)
            if isinstance(arguments, str):
                try:
                    arguments = json.loads(arguments)
                except (json.JSONDecodeError, TypeError):
                    pass
            payload['tool_call'] = {'arguments': arguments}
        observation = getattr(event, 'observation', None)
        if observation is not None:
            payload['observation'] = {
                'is_error': getattr(observation, 'is_error', False),
                'content': getattr(observation, 'content', []),
            }
        action = getattr(event, 'action', None)
        if action is not None:
            payload['action'] = {'message': getattr(action, 'message', None)}
        return payload

    def _events_from_conversations(
        self,
        conversations: Sequence[Any],
    ) -> list[dict[str, Any]]:
        """Collect events from stored conversation objects using the typed EventLog API."""
        payloads: list[dict[str, Any]] = []
        for conv in conversations:
            try:
                for event in conv.state.events:
                    payload = self._typed_event_to_payload(event)
                    if payload:
                        payloads.append(payload)
            except Exception:  # noqa: BLE001
                logger.warning(
                    'Failed to read typed events from conversation',
                    exc_info=True,
                )
        return payloads

    def _load_event_payloads(
        self,
        events_dir: Path | None = None,
        *,
        extra_event_dirs: Sequence[Path] | None = None,
        extra_conversations: Sequence[Any] | None = None,
    ) -> list[dict[str, Any]]:
        # Prefer typed events from stored conversations (C4: public EventLog API)
        conversations = list(extra_conversations or ())
        if conversations:
            typed_payloads = self._events_from_conversations(conversations)
            if typed_payloads:
                return typed_payloads

        # Fallback: read raw event JSON files from persistence directories
        dirs: list[Path] = []
        primary = events_dir or self.events_dir
        if primary.is_dir():
            dirs.append(primary)
        for extra in extra_event_dirs or ():
            if extra.is_dir() and extra not in dirs:
                dirs.append(extra)
        payloads: list[dict[str, Any]] = []
        for target_dir in dirs:
            for path in sorted(target_dir.glob('event-*.json')):
                payload = json.loads(path.read_text(encoding='utf-8'))
                if isinstance(payload, dict):
                    payloads.append(payload)
        return payloads

    def _extract_delegate_results(
        self, event_payloads: list[dict[str, Any]]
    ) -> tuple[dict[str, Any], list[dict[str, Any]], int, int]:
        attempt_events = [
            payload
            for payload in event_payloads
            if payload.get('source') == 'agent'
            and payload.get('tool_name') == 'delegate'
        ]
        observation_events = [
            payload
            for payload in event_payloads
            if payload.get('source') == 'environment'
            and payload.get('tool_name') == 'delegate'
        ]

        attempts = []
        for payload in attempt_events:
            tool_call = payload.get('tool_call', {})
            attempts.append(
                {
                    'event_id': payload.get('id'),
                    'tool_call_id': payload.get('tool_call_id'),
                    'arguments': tool_call.get('arguments'),
                }
            )

        completions = []
        fallbacks: list[dict[str, Any]] = []
        for payload in observation_events:
            observation = payload.get('observation', {})
            is_error = bool(observation.get('is_error'))
            completion = {
                'event_id': payload.get('id'),
                'tool_call_id': payload.get('tool_call_id'),
                'is_error': is_error,
            }
            completions.append(completion)
            if is_error:
                fallbacks.append(
                    {
                        'reason': 'delegate_error',
                        'event_id': payload.get('id'),
                        'tool_call_id': payload.get('tool_call_id'),
                    }
                )

        attempted_count = len(attempts)
        completed_count = sum(
            1 for completion in completions if not completion['is_error']
        )
        if attempted_count == 0:
            fallbacks.append({'reason': 'delegate_not_used'})
        elif completed_count == 0 and not fallbacks:
            fallbacks.append({'reason': 'delegate_missing_observation'})

        results = {
            'attempts': attempts,
            'completions': completions,
            'attempted': attempted_count,
            'completed': completed_count,
        }
        return results, fallbacks, attempted_count, completed_count

    def _extract_final_acceptance_summary(
        self, event_payloads: list[dict[str, Any]]
    ) -> dict[str, Any]:
        for payload in reversed(event_payloads):
            if (
                payload.get('tool_name') == 'finish'
                and payload.get('source') == 'environment'
            ):
                observation = payload.get('observation', {})
                content_blocks = observation.get('content', [])
                if isinstance(content_blocks, list):
                    for block in content_blocks:
                        if isinstance(block, dict) and isinstance(
                            block.get('text'), str
                        ):
                            return {
                                'event_id': payload.get('id'),
                                'tool_call_id': payload.get('tool_call_id'),
                                'source': 'environment',
                                'content': block['text'],
                            }
            if (
                payload.get('tool_name') == 'finish'
                and payload.get('source') == 'agent'
            ):
                action = payload.get('action', {})
                message = action.get('message')
                if isinstance(message, str):
                    return {
                        'event_id': payload.get('id'),
                        'tool_call_id': payload.get('tool_call_id'),
                        'source': 'agent',
                        'content': message,
                    }
        return {'status': 'not_available'}

    def _propagate_cascade_block(
        self,
        blocked_module_id: str,
        deterministic_summary: dict[str, Any],
    ) -> list[str]:
        """Mark all transitive downstream dependents as cascade-blocked.

        Returns the list of newly cascade-blocked module IDs.
        """
        dag = self.bootstrap.plan_dag
        # Build reverse adjacency: module_id -> list of modules that depend on it
        dependents: dict[str, list[str]] = {n.module_id: [] for n in dag.nodes}
        for node in dag.nodes:
            for dep in node.depends_on:
                dependents[dep].append(node.module_id)
        # BFS from blocked_module_id to find all transitive dependents
        cascade_blocked: list[str] = []
        queue = list(dependents.get(blocked_module_id, []))
        visited = {blocked_module_id}
        while queue:
            mid = queue.pop(0)
            if mid in visited:
                continue
            visited.add(mid)
            # Only cascade-block if not already promoted
            modules = deterministic_summary.get('modules', {})
            payload = modules.get(mid, {})
            if payload.get('promoted'):
                continue
            # Write cascade block result
            ws_root = self._generation_workspace_root(mid)
            write_cascade_block_result(
                workspace_root=ws_root,
                module_id=mid,
                blocked_by=blocked_module_id,
            )
            cascade_blocked.append(mid)
            # Continue BFS to transitive dependents
            for child in dependents.get(mid, []):
                queue.append(child)
        if cascade_blocked:
            logger.info(
                'Cascade-blocked %s due to %s', cascade_blocked, blocked_module_id
            )
        return cascade_blocked

    def _autonomous_completion_summary(
        self, deterministic_summary: dict[str, Any]
    ) -> dict[str, Any]:
        resolver = IntegrationReadinessResolver()
        primary_sink = resolver.select_primary_sink(self.bootstrap.plan_dag)
        required_modules = resolver.dependency_closure(
            self.bootstrap.plan_dag, primary_sink.module_id
        )
        modules = deterministic_summary.get('modules', {})
        promoted_modules = {
            module_id
            for module_id, payload in modules.items()
            if payload.get('promoted') is True
        }
        ready_sinks = resolver.ready_sink_modules(
            self.bootstrap.plan_dag, promoted_modules=promoted_modules
        )
        blocked_modules: list[str] = []
        cascade_blocked_modules: list[str] = []
        pending_modules: list[str] = []
        for module_id in required_modules:
            payload = modules.get(module_id, {})
            workspace_state = str(payload.get('workspace_state', 'missing'))
            promoted = bool(payload.get('promoted'))
            if promoted:
                continue
            if workspace_state in ('blocked', 'failed'):
                if payload.get('cascade_blocked_by'):
                    cascade_blocked_modules.append(module_id)
                else:
                    blocked_modules.append(module_id)
            else:
                pending_modules.append(module_id)
        integration_status = (deterministic_summary.get('integration', {}) or {}).get(
            'status', 'missing'
        )
        if (
            not pending_modules
            and not blocked_modules
            and not cascade_blocked_modules
            and integration_status == 'passed'
        ):
            completion_status = 'success'
        elif blocked_modules or cascade_blocked_modules:
            completion_status = 'blocked'
        else:
            completion_status = 'incomplete'
        return {
            'completion_status': completion_status,
            'primary_sink': primary_sink.module_id,
            'required_modules': required_modules,
            'promoted_modules': sorted(promoted_modules),
            'pending_modules': pending_modules,
            'blocked_modules': blocked_modules,
            'cascade_blocked_modules': cascade_blocked_modules,
            'ready_sink_modules': ready_sinks,
            'integration_status': integration_status,
        }

    def _append_batch_history(
        self,
        *,
        batch_history: list[dict[str, Any]],
        batch_id: str,
        phase: str,
        status: str,
        expected_artifacts: list[str],
        observed_artifacts: list[str],
        pause_reason: str | None = None,
        framework_decision: str | None = None,
    ) -> None:
        batch_history.append(
            {
                'batch_id': batch_id,
                'phase': phase,
                'status': status,
                'expected_artifacts': expected_artifacts,
                'observed_artifacts': observed_artifacts,
                'pause_reason': pause_reason,
                'framework_decision': framework_decision,
            }
        )
        self._write_json(
            self.batch_history_path,
            {'batches': batch_history, 'count': len(batch_history)},
        )

    def _run_autonomous_execution_loop(
        self,
        *,
        message: str,
        delegate_plan: dict[str, Any],
    ) -> tuple[
        ConversationSummary,
        dict[str, Any],
        dict[str, Any],
        list[dict[str, Any]],
        ConversationSummary | None,
    ]:
        processed_batch_ids: set[str] = set()
        provider_error_retries: dict[str, int] = {}
        max_provider_retries = 2
        batch_history: list[dict[str, Any]] = []
        protocol_violation: str | None = None
        integration_attempts = 0
        self._autonomous_batch_event_dirs = []
        self._autonomous_batch_conversations = []
        self._execution_batch_conversation_ids = []
        _PHASE_MAX_TURNS: dict[str, int] = {
            'generate_validate': 60,
            'repair_edit': 30,
            'revalidate': 25,
            'l2_execute': 30,
            'integration': 40,
        }

        while True:
            deterministic_summary = self._collect_existing_generation_summary()
            self._collect_fragility_memory()
            workflow_gate = self._evaluate_workflow_gate(
                delegate_plan=delegate_plan,
                processed_batch_ids=processed_batch_ids,
                deterministic_summary=deterministic_summary,
                protocol_violation=protocol_violation,
                integration_attempts=integration_attempts,
            )
            decision = str(workflow_gate['decision'])
            if decision == 'success':
                return (
                    self.runner.describe(self.conversation),
                    deterministic_summary,
                    workflow_gate,
                    batch_history,
                    None,
                )
            if decision == 'blocked':
                return (
                    self.runner.describe(self.conversation),
                    deterministic_summary,
                    workflow_gate,
                    batch_history,
                    None,
                )

            if decision == 'ready_for_integration':
                current_batch = self._build_integration_batch(
                    delegate_plan=delegate_plan
                )
                integration_attempts += 1
            else:
                current_batch, skipped_batches = self._next_eligible_autonomous_batch(
                    delegate_plan=delegate_plan,
                    processed_batch_ids=processed_batch_ids,
                )
                for skipped in skipped_batches:
                    self._append_batch_history(
                        batch_history=batch_history,
                        batch_id=str(skipped['batch_id']),
                        phase=str(skipped['phase']),
                        status='skipped',
                        expected_artifacts=[],
                        observed_artifacts=[],
                        framework_decision='condition_false',
                    )
                if current_batch is None:
                    protocol_violation = protocol_violation or 'no_next_batch_selected'
                    continue

            expected_artifacts = self._batch_expected_artifact_paths(current_batch)
            baseline = self._artifact_snapshot(expected_artifacts)
            self._before_batch_hook(
                current_batch=current_batch, workflow_gate=workflow_gate
            )
            current_batch_snapshot = self._build_orchestrator_batch_snapshot_payload(
                current_batch=current_batch,
                workflow_gate=workflow_gate,
                expected_artifacts=expected_artifacts,
            )
            self._write_json(self.current_batch_snapshot_path, current_batch_snapshot)

            batch_message = self._build_autonomous_batch_message(
                base_message=message,
                current_batch=current_batch,
                workflow_gate=workflow_gate,
            )
            phase = str(current_batch.get('phase', ''))
            batch_modules = [
                str(t.get('request', {}).get('module_id', ''))
                for t in current_batch.get('tasks', [])
                if isinstance(t, dict)
            ]
            max_turns = _PHASE_MAX_TURNS.get(phase, 25)
            batch_conversation = self.runner.create_execution_conversation(
                conversation_id=uuid4(),
                persistence_dir=self.bootstrap.persistence_dir,
                delete_on_close=False,
                max_iteration_per_run=max_turns,
            )
            self.conversation = batch_conversation

            # Inject prior repair summary for round 2+
            if phase == 'repair_edit':
                batch_repair_round = current_batch.get('repair_round', 1)
                if (
                    isinstance(batch_repair_round, int)
                    and batch_repair_round > 1
                    and batch_modules
                ):
                    prior_summary = self._build_prior_repair_summary(
                        module_id=batch_modules[0],
                        repair_round=batch_repair_round - 1,
                    )
                    if prior_summary:
                        batch_message = prior_summary + '\n\n' + batch_message
            try:
                batch_result = self.runner.run_current_batch_until_gate(
                    batch_conversation,
                    batch_message,
                    batch_gate=self._build_batch_gate(
                        current_batch=current_batch,
                        baseline=baseline,
                    ),
                    timeout_s=self._autonomous_batch_timeout_s(current_batch),
                )
            except Exception as batch_exc:
                if not self._is_provider_failure(batch_exc):
                    raise
                # Transient LLM/provider error — degrade to batch failure
                # so the repair chain can attempt recovery on the next batch.
                batch_result = BatchRunSummary(
                    conversation_summary=ConversationSummary(
                        conversation_id=str(
                            getattr(
                                getattr(batch_conversation, 'state', None),
                                'id',
                                uuid4(),
                            )
                        ),
                        execution_status='error',
                        event_count=0,
                        workspace_root=str(self.bootstrap.workspace_root),
                        persistence_dir=str(self.bootstrap.persistence_dir),
                    ),
                    gate_satisfied=False,
                    pause_reason=f'provider_error: {type(batch_exc).__name__}: {batch_exc}',
                    timed_out=False,
                )
            self._materialize_framework_batch_artifacts(current_batch=current_batch)
            post_run_gate_satisfied = all(
                self._artifact_updated(path=path, baseline=baseline)
                for path in expected_artifacts
            )
            effective_gate_satisfied = (
                batch_result.gate_satisfied or post_run_gate_satisfied
            )
            observed_artifacts = [
                path
                for path in expected_artifacts
                if self._artifact_updated(path=path, baseline=baseline)
            ]
            self._after_executor_hook(
                current_batch=current_batch,
                expected_artifacts=expected_artifacts,
                observed_artifacts=observed_artifacts,
            )
            repair_outcomes = self._after_repair_hook(current_batch=current_batch)
            if repair_outcomes:
                self._latest_repair_outcomes = repair_outcomes
            is_provider_error_batch = isinstance(
                batch_result.pause_reason, str
            ) and batch_result.pause_reason.startswith('provider_error:')
            if is_provider_error_batch:
                # Don't consume the batch slot — allow retry if provider recovers.
                # Track retry count to prevent infinite loops.
                retry_key = str(current_batch['batch_id'])
                provider_error_retries[retry_key] = (
                    provider_error_retries.get(retry_key, 0) + 1
                )
                if provider_error_retries[retry_key] >= max_provider_retries:
                    processed_batch_ids.add(retry_key)
            else:
                processed_batch_ids.add(str(current_batch['batch_id']))
            batch_status = 'completed' if effective_gate_satisfied else 'interrupted'
            pause_reason = batch_result.pause_reason
            if not batch_result.gate_satisfied and post_run_gate_satisfied:
                pause_reason = 'post_run_gate_satisfied'
            self._append_batch_history(
                batch_history=batch_history,
                batch_id=str(current_batch['batch_id']),
                phase=str(current_batch['phase']),
                status=batch_status,
                expected_artifacts=expected_artifacts,
                observed_artifacts=observed_artifacts,
                pause_reason=pause_reason,
            )
            self._after_batch_gate_hook(
                current_batch=current_batch,
                gate_satisfied=effective_gate_satisfied,
                pause_reason=pause_reason,
            )
            self._execution_batch_conversation_ids.append(
                batch_result.conversation_summary.conversation_id
            )
            self._autonomous_batch_conversations.append(batch_conversation)
            persist = batch_result.conversation_summary.persistence_dir
            if persist:
                events_path = Path(persist) / 'events'
                if (
                    events_path.is_dir()
                    and events_path not in self._autonomous_batch_event_dirs
                ):
                    self._autonomous_batch_event_dirs.append(events_path)
            execution_status = batch_result.conversation_summary.execution_status
            batch_failure: str | None = None
            if execution_status == 'finished' and not effective_gate_satisfied:
                batch_failure = 'execution_conversation_finished'
            elif execution_status in {'error', 'stuck'}:
                batch_failure = f'execution_conversation_{execution_status}'
            elif batch_result.timed_out and not effective_gate_satisfied:
                batch_failure = 'execution_batch_timeout'
            elif not effective_gate_satisfied:
                batch_failure = 'batch_gate_not_satisfied'
            if batch_failure is not None:
                self._on_protocol_violation_hook(
                    current_batch=current_batch,
                    protocol_violation=batch_failure,
                )
                # Defensive write: if executor crashed before writing
                # generation_result.json, synthesize one so the module
                # doesn't stay 'missing' indefinitely.
                batch_modules = [
                    str(t.get('request', {}).get('module_id', ''))
                    for t in current_batch.get('tasks', [])
                    if isinstance(t, dict) and t.get('request', {}).get('module_id')
                ]
                for mod_id in batch_modules:
                    ws_root = self._generation_workspace_root(mod_id)
                    gen_result_path = ws_root / 'generation_result.json'
                    if not gen_result_path.exists():
                        write_defensive_failure_result(
                            workspace_root=ws_root,
                            module_id=mod_id,
                            failure_reason=batch_failure,
                        )
                        self._propagate_cascade_block(mod_id, deterministic_summary)
            # Batch-level failures (timeout, error, finished) are recorded in
            # batch_history and hook events but do NOT promote to pipeline-
            # terminal protocol_violation.  The module's repair chain handles
            # recovery; the completion summary blocks the pipeline only when
            # all batches for the affected module are exhausted.
            # Only 'no_next_batch_selected' (set before batch execution)
            # acts as a pipeline-terminal loop guard.
            protocol_violation = None
            # Check if this was the last repair batch for any module —
            # force BLOCKED if still repairing after all plan rounds consumed.
            batch_phase = current_batch.get('phase', '')
            if batch_phase in ('repair_edit', 'revalidate'):
                budget_batch_modules = [
                    str(t.get('request', {}).get('module_id', ''))
                    for t in current_batch.get('tasks', [])
                    if isinstance(t, dict) and t.get('request', {}).get('module_id')
                ]
                for mod_id in budget_batch_modules:
                    ws_root = self._generation_workspace_root(mod_id)
                    gen_result_path = ws_root / 'generation_result.json'
                    if not gen_result_path.exists():
                        continue
                    gen_result = json.loads(gen_result_path.read_text(encoding='utf-8'))
                    if gen_result.get('workspace_state') in (
                        'promoted',
                        'blocked',
                        'failed',
                    ) or gen_result.get('promoted'):
                        continue
                    # Count remaining repair/revalidate batches for this module
                    remaining = sum(
                        1
                        for b in delegate_plan.get('batches', [])
                        if b['batch_id'] not in processed_batch_ids
                        and b.get('phase') in ('repair_edit', 'revalidate')
                        and any(
                            str(t.get('request', {}).get('module_id', '')) == mod_id
                            for t in b.get('tasks', [])
                            if isinstance(t, dict)
                        )
                    )
                    if remaining == 0:
                        repair_round = current_batch.get('repair_round', 0)
                        write_budget_exhausted_result(
                            workspace_root=ws_root,
                            module_id=mod_id,
                            repair_rounds_consumed=repair_round,
                        )
                        self._propagate_cascade_block(mod_id, deterministic_summary)
            promoted_modules = sorted(
                module_id
                for module_id, payload in deterministic_summary.get(
                    'modules', {}
                ).items()
                if isinstance(payload, dict) and payload.get('promoted') is True
            )
            self._write_json(
                self.autonomous_handoff_digest_path,
                {
                    'batch_id': str(current_batch['batch_id']),
                    'phase': str(current_batch['phase']),
                    'effective_gate_satisfied': effective_gate_satisfied,
                    'pause_reason': pause_reason,
                    'batch_failure': batch_failure,
                    'protocol_violation': protocol_violation,
                    'promoted_modules': promoted_modules,
                    'focus_module_id': self.focus_module_id,
                },
            )

    def _autonomous_batch_timeout_s(self, current_batch: dict[str, Any]) -> float:
        phase = str(current_batch.get('phase', ''))
        if phase == 'integration':
            return 300.0

        focus_modules = {
            str(task.get('request', {}).get('module_id', ''))
            for task in current_batch.get('tasks', [])
            if isinstance(task, dict)
        }
        if self.focus_module_id in focus_modules:
            if phase in {'generate_validate', 'repair_edit', 'revalidate'}:
                if self.focus_module_id == 'aes128_encrypt_core':
                    return 600.0
                return 420.0
            return 300.0
        if phase in {'generate_validate', 'repair_edit', 'revalidate'}:
            return 420.0
        return 180.0

    def _run_autonomous_finalizer(
        self,
        *,
        message: str,
        deterministic_summary: dict[str, Any],
        workflow_gate: dict[str, Any],
        batch_history: list[dict[str, Any]],
    ) -> tuple[ConversationSummary, dict[str, Any]]:
        finalizer_input = {
            'conversation_id': str(self.conversation_id),
            'system_goal': self.bootstrap.system_goal,
            'spec_ir_path': str(self.spec_ir_artifact_path),
            'plan_dag_path': str(self.plan_dag_artifact_path),
            'workflow_gate': workflow_gate,
            'deterministic_execution': deterministic_summary,
            'batch_history_path': str(self.batch_history_path),
            'batch_history_count': len(batch_history),
            'integration_summary_path': str(self.integration_summary_path),
            'promotion_events_path': str(self.promotion_events_path),
            'promotion_failures_path': str(self.promotion_failures_path),
            'fragility_memory_path': str(self.fragility_memory_path),
        }
        self._write_json(self.finalizer_input_path, finalizer_input)
        finalizer_conversation = self.runner.create_finalizer_conversation(
            conversation_id=uuid4(),
            persistence_dir=self.bootstrap.persistence_dir,
            delete_on_close=False,
        )
        finalizer_summary = self.runner.send_and_run(
            finalizer_conversation,
            self._build_finalizer_message(base_message=message),
        )
        finalizer_events_dir = (
            Path(finalizer_summary.persistence_dir).resolve() / 'events'
            if finalizer_summary.persistence_dir
            else None
        )
        finalizer_events = self._load_event_payloads(finalizer_events_dir)
        final_acceptance_summary = self._extract_final_acceptance_summary(
            finalizer_events
        )
        final_acceptance_summary = {
            **final_acceptance_summary,
            'status': workflow_gate['decision'],
            'workflow_gate': workflow_gate,
            'finalizer_conversation_id': finalizer_summary.conversation_id,
        }
        return finalizer_summary, final_acceptance_summary

    def _is_provider_failure(self, exc: Exception) -> bool:
        message = str(exc)
        provider_markers = (
            'insufficient_user_quota',
            'Insufficient Balance',
            '预扣费额度失败',
            'Connection error',
            'Connection refused',
            'OpenAIException',
            'LLMBadRequestError',
            'LLMServiceUnavailableError',
            'litellm.APIError',
            'litellm.BadRequestError',
            'InternalServerError',
            'ConversationRunError',
        )
        return any(marker in message for marker in provider_markers)

    def _synthesize_final_acceptance_summary(
        self,
        *,
        deterministic_summary: dict[str, Any],
        workflow_gate: dict[str, Any] | None,
        delegate_attempted: int,
        delegate_completed: int,
        delegate_fallbacks: list[dict[str, Any]],
        exc: Exception,
    ) -> dict[str, Any]:
        integration = deterministic_summary.get('integration', {})
        modules = deterministic_summary.get('modules', {})
        gate_decision = (
            workflow_gate.get('decision', 'unknown') if workflow_gate else 'unknown'
        )
        content = (
            'Final acceptance summary synthesized after the finalizer conversation '
            'failed due to a provider error. All execution artifacts are on disk. '
            f'Workflow gate decision: {gate_decision}. '
            f'Integration status: {integration.get("status", "unknown")}. '
            'Execution mode: autonomous-generate. '
            f'Delegate attempted: {delegate_attempted}. '
            f'Delegate completed: {delegate_completed}. '
            f'Delegate fallbacks: {len(delegate_fallbacks)}. '
            f'Modules covered: {", ".join(sorted(modules.keys()))}.'
        )
        summary: dict[str, Any] = {
            'status': gate_decision,
            'source': 'local_fallback',
            'content': content,
            'integration_status': integration.get('status'),
            'delegate_attempted': delegate_attempted,
            'delegate_completed': delegate_completed,
            'delegate_fallback_count': len(delegate_fallbacks),
            'error_type': type(exc).__name__,
            'error_message': str(exc),
        }
        if workflow_gate:
            summary['workflow_gate'] = workflow_gate
        return summary

    def run(
        self,
        message: str,
    ) -> ExecutionSessionSummary:
        execution_mode = 'autonomous-generate'
        deterministic_summary: dict[str, Any] | None = None
        delegate_results: dict[str, Any] = {
            'attempts': [],
            'completions': [],
            'attempted': 0,
            'completed': 0,
        }
        delegate_fallbacks: list[dict[str, Any]] = []
        delegate_attempted = 0
        delegate_completed = 0
        delegate_batch_count = 0
        finalizer_summary: ConversationSummary | None = None
        session_conversation_summary: ConversationSummary | None = None
        workflow_gate: dict[str, Any] | None = None
        try:
            delegate_plan = self._build_delegate_plan()
            self._write_json(self.delegate_plan_path, delegate_plan)
            self._write_json(self.batch_plan_path, delegate_plan)
            delegate_batch_count = len(delegate_plan.get('batches', []))
            (
                execution_conversation_summary,
                deterministic_summary,
                workflow_gate,
                batch_history,
                _,
            ) = self._run_autonomous_execution_loop(
                message=message,
                delegate_plan=delegate_plan,
            )
            finalizer_summary, final_acceptance_summary = (
                self._run_autonomous_finalizer(
                    message=message,
                    deterministic_summary=deterministic_summary,
                    workflow_gate=workflow_gate,
                    batch_history=batch_history,
                )
            )
            event_payloads = self._load_event_payloads(
                extra_event_dirs=self._autonomous_batch_event_dirs,
                extra_conversations=self._autonomous_batch_conversations,
            )
            (
                delegate_results,
                delegate_fallbacks,
                delegate_attempted,
                delegate_completed,
            ) = self._extract_delegate_results(event_payloads)
            self._write_json(self.delegate_results_path, delegate_results)
            self._write_json(self.delegate_fallbacks_path, delegate_fallbacks)
            self._write_json(
                self.final_acceptance_summary_path, final_acceptance_summary
            )
            session_conversation_summary = ConversationSummary(
                conversation_id=str(self.conversation_id),
                execution_status=(
                    'finished'
                    if workflow_gate['decision'] == 'success'
                    else 'finished_blocked'
                ),
                event_count=execution_conversation_summary.event_count,
                workspace_root=execution_conversation_summary.workspace_root,
                persistence_dir=execution_conversation_summary.persistence_dir,
            )
            session_payload = {
                'conversation_id': str(self.conversation_id),
                'bootstrap_summary': self.bootstrap.to_summary(),
                'conversation_summary': asdict(session_conversation_summary),
                'execution_conversation_summary': asdict(
                    execution_conversation_summary
                ),
                'finalizer_conversation_summary': asdict(finalizer_summary),
                'delegate_registrations': list(self.delegate_registrations),
                'focus_module_id': self.focus_module_id,
                'state_trace': self.state_trace,
                'deterministic_execution': deterministic_summary,
                'execution_mode': execution_mode,
                'delegate_attempted': delegate_attempted,
                'delegate_completed': delegate_completed,
                'delegate_fallback_count': len(delegate_fallbacks),
                'delegate_batch_count': delegate_batch_count,
                'delegate_plan_path': str(self.delegate_plan_path),
                'delegate_results_path': str(self.delegate_results_path),
                'delegate_fallbacks_path': str(self.delegate_fallbacks_path),
                'final_acceptance_summary_path': str(
                    self.final_acceptance_summary_path
                ),
                'generation_plan_path': str(self.generation_plan_path),
                'brief_generation_summary_path': str(
                    self.brief_generation_summary_path
                ),
                'promotion_events_path': str(self.promotion_events_path),
                'promotion_failures_path': str(self.promotion_failures_path),
                'spec_ir_path': str(self.spec_ir_artifact_path),
                'plan_dag_path': str(self.plan_dag_artifact_path),
                'batch_plan_path': str(self.batch_plan_path),
                'fragility_memory_path': str(self.fragility_memory_path),
                'batch_history_path': str(self.batch_history_path),
                'workflow_gate_path': str(self.workflow_gate_path),
                'current_batch_snapshot_path': str(self.current_batch_snapshot_path),
                'finalizer_input_path': str(self.finalizer_input_path),
                'finalizer_conversation_id': finalizer_summary.conversation_id,
                'execution_parent_conversation_id': str(self.conversation_id),
                'execution_batch_conversation_ids': list(
                    self._execution_batch_conversation_ids
                ),
                'autonomous_handoff_digest_path': str(
                    self.autonomous_handoff_digest_path
                ),
            }
            self._write_json(self.session_summary_path, session_payload)
            self._write_json(self.report_tree_path, self._report_tree_payload())
            return ExecutionSessionSummary(
                conversation_id=str(self.conversation_id),
                report_root=str(self.report_root),
                focus_module_id=self.focus_module_id,
                delegate_registrations=list(self.delegate_registrations),
                bootstrap_summary=self.bootstrap.to_summary(),
                conversation_summary=session_conversation_summary,
                state_trace_path=str(self.state_trace_path),
                session_summary_path=str(self.session_summary_path),
                report_tree_path=str(self.report_tree_path),
                execution_mode=execution_mode,
                delegate_attempted=delegate_attempted,
                delegate_completed=delegate_completed,
                delegate_fallback_count=len(delegate_fallbacks),
                delegate_batch_count=delegate_batch_count,
                delegate_plan_path=str(self.delegate_plan_path),
                delegate_results_path=str(self.delegate_results_path),
                delegate_fallbacks_path=str(self.delegate_fallbacks_path),
                final_acceptance_summary_path=str(self.final_acceptance_summary_path),
                generation_plan_path=str(self.generation_plan_path),
                brief_generation_summary_path=str(self.brief_generation_summary_path),
                promotion_events_path=str(self.promotion_events_path),
                promotion_failures_path=str(self.promotion_failures_path),
                module_results_dir=str(self.generation_results_dir),
                integration_summary_path=str(self.integration_summary_path),
                deterministic_execution_path=str(self.deterministic_execution_path),
                batch_history_path=str(self.batch_history_path),
                workflow_gate_path=str(self.workflow_gate_path),
                current_batch_snapshot_path=str(self.current_batch_snapshot_path),
                finalizer_input_path=str(self.finalizer_input_path),
                finalizer_conversation_id=finalizer_summary.conversation_id,
            )

        except Exception as exc:
            deterministic_summary = self._collect_existing_generation_summary()
            self._collect_fragility_memory()
            delegate_batch_count = 0
            if self.delegate_plan_path.is_file():
                delegate_batch_count = len(
                    json.loads(self.delegate_plan_path.read_text(encoding='utf-8')).get(
                        'batches', []
                    )
                )
            event_payloads = self._load_event_payloads(
                extra_event_dirs=self._autonomous_batch_event_dirs,
                extra_conversations=self._autonomous_batch_conversations,
            )
            if event_payloads:
                (
                    delegate_results,
                    delegate_fallbacks,
                    delegate_attempted,
                    delegate_completed,
                ) = self._extract_delegate_results(event_payloads)
            self._write_json(self.delegate_results_path, delegate_results)
            self._write_json(self.delegate_fallbacks_path, delegate_fallbacks)
            if deterministic_summary and self._is_provider_failure(exc):
                final_acceptance_summary = self._synthesize_final_acceptance_summary(
                    deterministic_summary=deterministic_summary,
                    workflow_gate=workflow_gate,
                    delegate_attempted=delegate_attempted,
                    delegate_completed=delegate_completed,
                    delegate_fallbacks=delegate_fallbacks,
                    exc=exc,
                )
                self._write_json(
                    self.final_acceptance_summary_path,
                    final_acceptance_summary,
                )
                synthetic_summary = ConversationSummary(
                    conversation_id=str(self.conversation_id),
                    execution_status='finished_with_fallback',
                    event_count=len(event_payloads),
                    workspace_root=str(self.bootstrap.workspace_root),
                    persistence_dir=str(self.report_root),
                )
                session_payload = {
                    'conversation_id': str(self.conversation_id),
                    'bootstrap_summary': self.bootstrap.to_summary(),
                    'conversation_summary': asdict(synthetic_summary),
                    'delegate_registrations': list(self.delegate_registrations),
                    'focus_module_id': self.focus_module_id,
                    'state_trace': self.state_trace,
                    'deterministic_execution': deterministic_summary,
                    'execution_mode': execution_mode,
                    'delegate_attempted': delegate_attempted,
                    'delegate_completed': delegate_completed,
                    'delegate_fallback_count': len(delegate_fallbacks),
                    'delegate_batch_count': delegate_batch_count,
                    'delegate_plan_path': str(self.delegate_plan_path),
                    'delegate_results_path': str(self.delegate_results_path),
                    'delegate_fallbacks_path': str(self.delegate_fallbacks_path),
                    'final_acceptance_summary_path': str(
                        self.final_acceptance_summary_path
                    ),
                    'generation_plan_path': str(self.generation_plan_path),
                    'brief_generation_summary_path': str(
                        self.brief_generation_summary_path
                    ),
                    'promotion_events_path': str(self.promotion_events_path),
                    'promotion_failures_path': str(self.promotion_failures_path),
                    'spec_ir_path': str(self.spec_ir_artifact_path),
                    'plan_dag_path': str(self.plan_dag_artifact_path),
                    'batch_plan_path': str(self.batch_plan_path),
                    'fragility_memory_path': str(self.fragility_memory_path),
                    'fallback_error': {
                        'type': type(exc).__name__,
                        'message': str(exc),
                    },
                }
                self._write_json(self.session_summary_path, session_payload)
                self._write_json(self.report_tree_path, self._report_tree_payload())
                return ExecutionSessionSummary(
                    conversation_id=str(self.conversation_id),
                    report_root=str(self.report_root),
                    focus_module_id=self.focus_module_id,
                    delegate_registrations=list(self.delegate_registrations),
                    bootstrap_summary=self.bootstrap.to_summary(),
                    conversation_summary=synthetic_summary,
                    state_trace_path=str(self.state_trace_path),
                    session_summary_path=str(self.session_summary_path),
                    report_tree_path=str(self.report_tree_path),
                    execution_mode=execution_mode,
                    delegate_attempted=delegate_attempted,
                    delegate_completed=delegate_completed,
                    delegate_fallback_count=len(delegate_fallbacks),
                    delegate_batch_count=delegate_batch_count,
                    delegate_plan_path=str(self.delegate_plan_path),
                    delegate_results_path=str(self.delegate_results_path),
                    delegate_fallbacks_path=str(self.delegate_fallbacks_path),
                    final_acceptance_summary_path=str(
                        self.final_acceptance_summary_path
                    ),
                    generation_plan_path=str(self.generation_plan_path),
                    brief_generation_summary_path=str(
                        self.brief_generation_summary_path
                    ),
                    promotion_events_path=str(self.promotion_events_path),
                    promotion_failures_path=str(self.promotion_failures_path),
                    module_results_dir=(
                        str(self.generation_results_dir)
                        if deterministic_summary
                        else None
                    ),
                    integration_summary_path=(
                        str(self.integration_summary_path)
                        if deterministic_summary
                        else None
                    ),
                    deterministic_execution_path=(
                        str(self.deterministic_execution_path)
                        if deterministic_summary
                        else None
                    ),
                )
            if not self.final_acceptance_summary_path.exists():
                self._write_json(
                    self.final_acceptance_summary_path,
                    {'status': 'not_available'},
                )
            failure_payload = {
                'conversation_id': str(self.conversation_id),
                'bootstrap_summary': self.bootstrap.to_summary(),
                'conversation_summary': None,
                'delegate_registrations': list(self.delegate_registrations),
                'focus_module_id': self.focus_module_id,
                'state_trace': self.state_trace,
                'deterministic_execution': deterministic_summary,
                'execution_mode': execution_mode,
                'delegate_attempted': delegate_attempted,
                'delegate_completed': delegate_completed,
                'delegate_fallback_count': len(delegate_fallbacks),
                'delegate_batch_count': delegate_batch_count,
                'delegate_plan_path': str(self.delegate_plan_path),
                'delegate_results_path': str(self.delegate_results_path),
                'delegate_fallbacks_path': str(self.delegate_fallbacks_path),
                'final_acceptance_summary_path': str(
                    self.final_acceptance_summary_path
                ),
                'generation_plan_path': str(self.generation_plan_path),
                'brief_generation_summary_path': str(
                    self.brief_generation_summary_path
                ),
                'promotion_events_path': str(self.promotion_events_path),
                'promotion_failures_path': str(self.promotion_failures_path),
                'spec_ir_path': str(self.spec_ir_artifact_path),
                'plan_dag_path': str(self.plan_dag_artifact_path),
                'batch_plan_path': str(self.batch_plan_path),
                'fragility_memory_path': str(self.fragility_memory_path),
                'error': {
                    'type': type(exc).__name__,
                    'message': str(exc),
                },
            }
            self._write_json(self.session_summary_path, failure_payload)
            self._write_json(self.report_tree_path, self._report_tree_payload())
            raise
        finally:
            self.conversation.close()
