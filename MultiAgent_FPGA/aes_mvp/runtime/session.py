"""Execution-session helpers for the AES MVP runtime."""

from __future__ import annotations

import json
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Any, Literal
from uuid import UUID, uuid4

from MultiAgent_FPGA.aes_mvp.delegation import (
    DelegateBatchPlan,
    DelegateBatchTask,
    NodeExecutionRequest,
    SubagentWorkMode,
)
from MultiAgent_FPGA.aes_mvp.executor_contracts import (
    resolve_l2_campaign_inputs,
    resolve_path,
)
from MultiAgent_FPGA.aes_mvp.executors import (
    IntegrationRegressionExecutor,
    L0Executor,
    L1Executor,
    L2CampaignExecutor,
)
from MultiAgent_FPGA.aes_mvp.generation import (
    conversation_workspace_root,
    initialize_node_workspace,
)
from MultiAgent_FPGA.aes_mvp.orchestrator import AESWorkflowOrchestrator
from MultiAgent_FPGA.aes_mvp.policy import OrchestratorState
from MultiAgent_FPGA.aes_mvp.runtime.bootstrap import RuntimeBootstrap
from MultiAgent_FPGA.aes_mvp.runtime.factory import SdkAgentFactory
from MultiAgent_FPGA.aes_mvp.runtime.runner import (
    ConversationRunner,
    ConversationSummary,
)

ExecutionMode = Literal[
    'deterministic-review',
    'hybrid-delegate',
    'hybrid-build',
    'hybrid-generate',
]
MAX_DELEGATE_CHILDREN = 5


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
    execution_mode: ExecutionMode
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

    @classmethod
    def create(
        cls,
        bootstrap: RuntimeBootstrap,
        *,
        conversation_id: UUID | None = None,
        focus_module_id: str | None = None,
    ) -> 'ExecutionSession':
        factory = SdkAgentFactory(bootstrap)
        delegate_registrations = factory.register_delegate_agents()
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
        conversation = runner.create_orchestrator_conversation(
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
        l2_output_dir = (
            resolve_path(self.bootstrap.workspace_root, node.sim_output_dir)
            / 'l2'
            / profile
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

    def _prepare_generation_artifacts(self) -> dict[str, Any]:
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
            node_payload = {
                'module_id': node.module_id,
                'workspace_root': str(workspace_root),
                'contract_paths': dict(record.contract_paths),
                'draft_rtl_paths': list(rtl_drafts.values()),
                'draft_tb_path': record.draft_paths['tb'],
                'validation_paths': dict(record.validation_paths),
                'canonical_targets': list(record.canonical_targets),
            }
            nodes.append(node_payload)
            promotion_targets.append(
                {
                    'module_id': node.module_id,
                    'canonical_targets': list(record.canonical_targets),
                }
            )

        generation_plan = {
            'conversation_id': str(self.conversation_id),
            'execution_mode': 'hybrid-generate',
            'report_root': str(self.report_root),
            'nodes': nodes,
        }
        brief_generation_summary = {
            'conversation_id': str(self.conversation_id),
            'generated_node_count': len(nodes),
            'promotion_targets': promotion_targets,
            'workspace_roots': [entry['workspace_root'] for entry in nodes],
        }
        self._write_json(self.generation_plan_path, generation_plan)
        self._write_json(
            self.brief_generation_summary_path,
            brief_generation_summary,
        )
        return generation_plan

    def _materialize_delegate_plan(
        self, delegate_plan: dict[str, Any]
    ) -> dict[str, Any]:
        for batch in delegate_plan.get('batches', []):
            batch_id = str(batch.get('batch_id', 'batch'))
            delegate_tasks = batch.get('delegate', {}).get('tasks', {})
            for task in batch.get('tasks', []):
                worker_id = str(task.get('worker_id'))
                request_path = (
                    self.delegate_requests_dir / f'{batch_id}__{worker_id}.json'
                ).resolve()
                request_payload = {
                    'batch_id': batch_id,
                    'execution_mode': delegate_plan.get('execution_mode'),
                    'report_root': str(self.report_root),
                    'task': task,
                }
                self._write_json(request_path, request_payload)
                task['request_path'] = str(request_path)
                prompt = str(task.get('prompt', ''))
                prompt += '\n'.join(
                    [
                        '',
                        f'Task contract file: {request_path}',
                        f'Working directory: {task["request"].get("working_directory")}',
                        'Do not inspect unrelated paths before using this task contract.',
                    ]
                )
                task['prompt'] = prompt
                if worker_id in delegate_tasks:
                    delegate_tasks[worker_id] = prompt
        return delegate_plan

    def _report_tree_payload(self) -> dict[str, Any]:
        return {
            'conversation_id': str(self.conversation_id),
            'focus_module_id': self.focus_module_id,
            'root': str(self.report_root),
            'paths': {
                'base_state': str(self.base_state_path),
                'state_trace': str(self.state_trace_path),
                'session_summary': str(self.session_summary_path),
                'report_tree': str(self.report_tree_path),
                'delegate_plan': str(self.delegate_plan_path),
                'delegate_results': str(self.delegate_results_path),
                'delegate_fallbacks': str(self.delegate_fallbacks_path),
                'final_acceptance_summary': str(self.final_acceptance_summary_path),
                'generation_plan': str(self.generation_plan_path),
                'brief_generation_summary': str(self.brief_generation_summary_path),
                'generation_results_dir': str(self.generation_results_dir),
                'promotion_events': str(self.promotion_events_path),
                'promotion_failures': str(self.promotion_failures_path),
                'delegate_requests_dir': str(self.delegate_requests_dir),
                'module_results_dir': str(self.module_results_dir),
                'integration_summary': str(self.integration_summary_path),
                'deterministic_execution': str(self.deterministic_execution_path),
                'events_dir': str(self.events_dir),
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

    def _run_deterministic_green_path(self) -> dict[str, Any]:
        adapter = self.bootstrap.create_verilator_adapter(
            conversation_id=self.conversation_id.hex
        )
        l0 = L0Executor(adapter=adapter, package_root=self.bootstrap.workspace_root)
        l1 = L1Executor(adapter=adapter, package_root=self.bootstrap.workspace_root)
        l2 = L2CampaignExecutor(
            adapter=adapter, package_root=self.bootstrap.workspace_root
        )
        integration = IntegrationRegressionExecutor(
            adapter=adapter,
            package_root=self.bootstrap.workspace_root,
        )

        module_summaries: dict[str, dict[str, Any]] = {}
        for node in self.bootstrap.plan_dag.nodes:
            l0_report = l0.run(node)
            l1_report = l1.run(node)
            module_summary: dict[str, Any] = {
                'module_id': node.module_id,
                'l0_result_path': str(l0_report.path),
                'l1_result_path': str(l1_report.path),
                'l2_result_path': None,
            }
            if node.l2_policy != 'skip':
                l2_kwargs: dict[str, Any] = {'profile': 'rand_small'}
                if node.module_id != self.bootstrap.integration_manifest.top_module:
                    l2_kwargs.update({'cases': 8, 'seed': 7})
                l2_report = l2.run(node, **l2_kwargs)
                module_summary['l2_result_path'] = str(l2_report.path)
            module_summaries[node.module_id] = module_summary
            self._write_json(
                self.module_results_dir / f'{node.module_id}.json',
                module_summary,
            )

        integration_report = integration.run(self.bootstrap.integration_manifest)
        integration_summary = {
            'result_path': str(integration_report.path),
            'status': integration_report.payload.get('status'),
            'campaign_count': len(
                integration_report.payload.get('campaign_results', [])
            ),
        }
        self._write_json(self.integration_summary_path, integration_summary)

        deterministic_summary = {
            'conversation_id': str(self.conversation_id),
            'focus_module_id': self.focus_module_id,
            'module_results_dir': str(self.module_results_dir),
            'integration_summary_path': str(self.integration_summary_path),
            'modules': module_summaries,
            'integration': integration_summary,
        }
        self._write_json(self.deterministic_execution_path, deterministic_summary)
        self._write_json(self.report_tree_path, self._report_tree_payload())
        return deterministic_summary

    def _build_delegate_plan(
        self,
        deterministic_summary: dict[str, Any] | None,
        *,
        execution_mode: ExecutionMode,
    ) -> dict[str, Any]:
        if execution_mode == 'hybrid-generate':
            nodes_by_id = {
                node.module_id: node for node in self.bootstrap.plan_dag.nodes
            }
            top_module = self.bootstrap.integration_manifest.top_module
            generation_plan = self._prepare_generation_artifacts()
            generation_nodes = {
                str(entry['module_id']): entry for entry in generation_plan['nodes']
            }

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
                if l2_profile:
                    command += f' --l2-profile {l2_profile}'
                if vecfile:
                    command += f' --vecfile {vecfile}'
                if cases is not None:
                    command += f' --cases {cases}'
                if seed is not None:
                    command += f' --seed {seed}'
                return command

            def build_generate_task(module_id: str) -> DelegateBatchTask:
                node = nodes_by_id[module_id]
                generation_entry = generation_nodes[module_id]
                command = generate_node_command(module_id)
                generation_result_path = str(
                    (
                        Path(generation_entry['workspace_root'])
                        / 'generation_result.json'
                    ).resolve()
                )
                workspace_state_path = str(
                    (
                        Path(generation_entry['workspace_root'])
                        / 'workspace_state.json'
                    ).resolve()
                )
                prompt = '\n'.join(
                    [
                        f'Generate and validate the AES node {node.module_id}.',
                        'Mode: generate.',
                        'Use the task contract file as the source of truth.',
                        f'workspace_root: {generation_entry["workspace_root"]}',
                        f'writable_draft_paths: {", ".join([*generation_entry["draft_rtl_paths"], generation_entry["draft_tb_path"]])}',
                        f'generation_result_path: {generation_result_path}',
                        f'workspace_state_path: {workspace_state_path}',
                        'validation_artifact_paths:',
                        *[
                            f'- {path}'
                            for path in generation_entry['validation_paths'].values()
                        ],
                        'Run the provided executor_command first. It prepares the draft workspace, validates the current draft with L0/L1, and promotes only if validation passes.',
                        'The first scaffold-only executor run is expected to fail validation. Treat that as the start of repair, not as a finished task.',
                        'If executor_command returns a non-zero status or reports validation_status=failed, missing_checkpoints, or failed_checkpoints, immediately read generation_result.json, workspace_state.json, and the validation artifacts under workspace_root.',
                        'After reading those result files, inspect only the draft RTL/TB files and contract files under workspace_root, repair the draft, and rerun the same executor_command.',
                        'Do not stop after the first failed run. Continue until the node is promoted, blocked, or the repair_budget is exhausted.',
                        'Do not edit canonical repository RTL/TB files directly.',
                        'Do not call raw verilator_compile or verilator_simulate.',
                        f'executor_command: {command}',
                        'Return a compact JSON-style summary with keys: module_id, workspace_state, changed_files, validation_status, checkpoint_summary, promoted, repair_attempts, escalated.',
                    ]
                )
                return DelegateBatchTask(
                    worker_id=f'module_build__{node.module_id}',
                    agent_type=self.factory.module_worker_registry_name(node),
                    mode=SubagentWorkMode.GENERATE,
                    request=NodeExecutionRequest(
                        module_id=node.module_id,
                        stage=OrchestratorState.MODULE_DESIGN,
                        repair_budget=self.bootstrap.policy.repair_attempt_threshold,
                        writable_paths=[
                            *generation_entry['draft_rtl_paths'],
                            generation_entry['draft_tb_path'],
                        ],
                        artifact_paths=[
                            *generation_entry['contract_paths'].values(),
                            *generation_entry['validation_paths'].values(),
                        ],
                        executor_command=command,
                        working_directory=str(self.bootstrap.workspace_root),
                        workspace_root=str(generation_entry['workspace_root']),
                        contract_paths=dict(generation_entry['contract_paths']),
                        result_paths={
                            'generation_result': generation_result_path,
                            'workspace_state': workspace_state_path,
                        },
                        canonical_targets=list(generation_entry['canonical_targets']),
                    ),
                    prompt=prompt,
                )

            def build_l2_task(module_id: str, *, profile: str) -> DelegateBatchTask:
                node = nodes_by_id[module_id]
                l2_kwargs: dict[str, object] = {'profile': profile}
                if node.module_id != top_module:
                    l2_kwargs.update({'cases': 8, 'seed': 7})
                resolved = resolve_l2_campaign_inputs(
                    package_root=self.bootstrap.workspace_root,
                    node=node,
                    profile=profile,
                    cases=l2_kwargs.get('cases'),  # type: ignore[arg-type]
                    seed=l2_kwargs.get('seed'),  # type: ignore[arg-type]
                )
                command = node_executor_command(
                    node.module_id,
                    l2_profile=profile,
                    vecfile=str(resolved.vecfile),
                    cases=resolved.cases,
                    seed=resolved.seed,
                )
                prompt = '\n'.join(
                    [
                        f'Execute the frozen L2 campaign for {node.module_id}.',
                        'Mode: l2_execute.',
                        'Run the provided executor_command first from the terminal tool.',
                        'Do not edit RTL or testbench files.',
                        'Do not call raw verilator_compile or verilator_simulate.',
                        f'executor_command: {command}',
                        'Return a compact JSON-style summary with keys: module_id, profile, l2_status, failing_checkpoints, output_paths, escalated.',
                    ]
                )
                return DelegateBatchTask(
                    worker_id=f'module_build__{node.module_id}',
                    agent_type=self.factory.module_worker_registry_name(node),
                    mode=SubagentWorkMode.L2_EXECUTE,
                    request=NodeExecutionRequest(
                        module_id=node.module_id,
                        stage=OrchestratorState.MODULE_L2_OPTIONAL,
                        repair_budget=self.bootstrap.policy.repair_attempt_threshold,
                        artifact_paths=self._expected_l2_artifact_paths(
                            node, profile=profile
                        ),
                        l2_profile=profile,
                        vecfile=str(resolved.vecfile),
                        cases=resolved.cases,
                        seed=resolved.seed,
                        executor_command=command,
                        working_directory=str(self.bootstrap.workspace_root),
                        writable_paths=[],
                    ),
                    prompt=prompt,
                )

            def build_batches(
                *,
                batch_id_prefix: str,
                stage: OrchestratorState,
                tasks: list[DelegateBatchTask],
                include_spawn: bool,
            ) -> list[dict[str, Any]]:
                batches: list[dict[str, Any]] = []
                for index, start in enumerate(
                    range(0, len(tasks), MAX_DELEGATE_CHILDREN), start=1
                ):
                    batch = DelegateBatchPlan(
                        batch_id=f'{batch_id_prefix}_{index}',
                        stage=stage,
                        max_children=MAX_DELEGATE_CHILDREN,
                        fallback_policy='orchestrator_takeover',
                        tasks=tasks[start : start + MAX_DELEGATE_CHILDREN],
                    )
                    batches.append(
                        {
                            **batch.model_dump(),
                            'spawn': (
                                batch.spawn_payload()
                                if include_spawn
                                else {
                                    'command': 'spawn',
                                    'ids': [],
                                    'agent_types': [],
                                }
                            ),
                            'delegate': batch.delegate_payload(),
                        }
                    )
                return batches

            leaf_generate_tasks = [
                build_generate_task(node.module_id)
                for node in self.bootstrap.plan_dag.nodes
                if node.module_id != top_module
            ]
            top_generate_tasks = [build_generate_task(top_module)]
            l2_tasks = [
                build_l2_task(node.module_id, profile='rand_small')
                for node in self.bootstrap.plan_dag.nodes
                if node.l2_policy != 'skip'
            ]

            return self._materialize_delegate_plan(
                {
                    'execution_mode': 'hybrid-generate',
                    'delegate_enabled': True,
                    'max_children': MAX_DELEGATE_CHILDREN,
                    'generation_plan_path': str(self.generation_plan_path),
                    'brief_generation_summary_path': str(
                        self.brief_generation_summary_path
                    ),
                    'integration_command': (
                        f'PYTHONPATH={self.bootstrap.repo_root} '
                        f'/opt/anaconda3/envs/openhands/bin/python '
                        '-m MultiAgent_FPGA.aes_mvp run-integration'
                    ),
                    'batches': [
                        *build_batches(
                            batch_id_prefix='leaf_module_generations',
                            stage=OrchestratorState.MODULE_DESIGN,
                            tasks=leaf_generate_tasks,
                            include_spawn=True,
                        ),
                        *build_batches(
                            batch_id_prefix='top_module_generation',
                            stage=OrchestratorState.MODULE_DESIGN,
                            tasks=top_generate_tasks,
                            include_spawn=True,
                        ),
                        *build_batches(
                            batch_id_prefix='l2_campaigns',
                            stage=OrchestratorState.MODULE_L2_OPTIONAL,
                            tasks=l2_tasks,
                            include_spawn=False,
                        ),
                    ],
                }
            )

        if execution_mode == 'hybrid-build':
            nodes_by_id = {
                node.module_id: node for node in self.bootstrap.plan_dag.nodes
            }
            top_module = self.bootstrap.integration_manifest.top_module

            def node_executor_command(
                module_id: str,
                *,
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
                if l2_profile:
                    command += f' --l2-profile {l2_profile}'
                if vecfile:
                    command += f' --vecfile {vecfile}'
                if cases is not None:
                    command += f' --cases {cases}'
                if seed is not None:
                    command += f' --seed {seed}'
                return command

            def build_module_task(module_id: str) -> DelegateBatchTask:
                node = nodes_by_id[module_id]
                command = node_executor_command(node.module_id)
                prompt = '\n'.join(
                    [
                        f'Build and validate the AES node {node.module_id}.',
                        'Mode: build.',
                        'Use the task contract file as the source of truth.',
                        'Run the provided executor_command first to validate the node-local L0 and L1 path before inspecting or editing files.',
                        'You may edit only the writable RTL/TB files for this node, and only after the first executor run fails or reports missing checkpoints.',
                        'Do not call raw verilator_compile or verilator_simulate.',
                        f'executor_command: {command}',
                        'If the node is already green, validate it with the executor_command and return a compact JSON-style summary with keys: module_id, changed_files, l0_status, l1_status, checkpoint_summary, acceptance_decision, repair_attempts, escalated.',
                    ]
                )
                return DelegateBatchTask(
                    worker_id=f'module_build__{node.module_id}',
                    agent_type=self.factory.module_worker_registry_name(node),
                    mode=SubagentWorkMode.BUILD,
                    request=NodeExecutionRequest(
                        module_id=node.module_id,
                        stage=OrchestratorState.MODULE_L1,
                        repair_budget=self.bootstrap.policy.repair_attempt_threshold,
                        writable_paths=self._absolute_node_writable_paths(node),
                        artifact_paths=self._expected_module_artifact_paths(node),
                        executor_command=command,
                        working_directory=str(self.bootstrap.workspace_root),
                    ),
                    prompt=prompt,
                )

            def build_l2_task(module_id: str, *, profile: str) -> DelegateBatchTask:
                node = nodes_by_id[module_id]
                l2_kwargs: dict[str, object] = {'profile': profile}
                if node.module_id != top_module:
                    l2_kwargs.update({'cases': 8, 'seed': 7})
                resolved = resolve_l2_campaign_inputs(
                    package_root=self.bootstrap.workspace_root,
                    node=node,
                    profile=profile,
                    cases=l2_kwargs.get('cases'),  # type: ignore[arg-type]
                    seed=l2_kwargs.get('seed'),  # type: ignore[arg-type]
                )
                command = node_executor_command(
                    node.module_id,
                    l2_profile=profile,
                    vecfile=str(resolved.vecfile),
                    cases=resolved.cases,
                    seed=resolved.seed,
                )
                prompt = '\n'.join(
                    [
                        f'Execute the frozen L2 campaign for {node.module_id}.',
                        'Mode: l2_execute.',
                        'Use the task contract file as the source of truth.',
                        'Do not edit RTL or testbench files.',
                        'Run the provided executor_command first from the terminal tool.',
                        'Do not call raw verilator_compile or verilator_simulate.',
                        f'executor_command: {command}',
                        'Return a compact JSON-style summary with keys: module_id, profile, l2_status, failing_checkpoints, output_paths, escalated.',
                    ]
                )
                return DelegateBatchTask(
                    worker_id=f'module_build__{node.module_id}',
                    agent_type=self.factory.module_worker_registry_name(node),
                    mode=SubagentWorkMode.L2_EXECUTE,
                    request=NodeExecutionRequest(
                        module_id=node.module_id,
                        stage=OrchestratorState.MODULE_L2_OPTIONAL,
                        repair_budget=self.bootstrap.policy.repair_attempt_threshold,
                        artifact_paths=self._expected_l2_artifact_paths(
                            node, profile=profile
                        ),
                        l2_profile=profile,
                        vecfile=str(resolved.vecfile),
                        cases=resolved.cases,
                        seed=resolved.seed,
                        executor_command=command,
                        working_directory=str(self.bootstrap.workspace_root),
                        writable_paths=self._absolute_node_writable_paths(node),
                    ),
                    prompt=prompt,
                )

            def build_batches(
                *,
                batch_id_prefix: str,
                stage: OrchestratorState,
                tasks: list[DelegateBatchTask],
                include_spawn: bool,
            ) -> list[dict[str, Any]]:
                batches: list[dict[str, Any]] = []
                for index, start in enumerate(
                    range(0, len(tasks), MAX_DELEGATE_CHILDREN), start=1
                ):
                    batch = DelegateBatchPlan(
                        batch_id=f'{batch_id_prefix}_{index}',
                        stage=stage,
                        max_children=MAX_DELEGATE_CHILDREN,
                        fallback_policy='orchestrator_takeover',
                        tasks=tasks[start : start + MAX_DELEGATE_CHILDREN],
                    )
                    batches.append(
                        {
                            **batch.model_dump(),
                            'spawn': (
                                batch.spawn_payload()
                                if include_spawn
                                else {
                                    'command': 'spawn',
                                    'ids': [],
                                    'agent_types': [],
                                }
                            ),
                            'delegate': batch.delegate_payload(),
                        }
                    )
                return batches

            leaf_build_tasks = [
                build_module_task(node.module_id)
                for node in self.bootstrap.plan_dag.nodes
                if node.module_id != top_module
            ]
            top_build_tasks = [build_module_task(top_module)]
            l2_tasks = [
                build_l2_task(node.module_id, profile='rand_small')
                for node in self.bootstrap.plan_dag.nodes
                if node.l2_policy != 'skip'
            ]

            return self._materialize_delegate_plan(
                {
                    'execution_mode': 'hybrid-build',
                    'delegate_enabled': True,
                    'max_children': MAX_DELEGATE_CHILDREN,
                    'integration_command': (
                        f'PYTHONPATH={self.bootstrap.repo_root} '
                        f'/opt/anaconda3/envs/openhands/bin/python '
                        '-m MultiAgent_FPGA.aes_mvp run-integration'
                    ),
                    'batches': [
                        *build_batches(
                            batch_id_prefix='leaf_module_builds',
                            stage=OrchestratorState.MODULE_L1,
                            tasks=leaf_build_tasks,
                            include_spawn=True,
                        ),
                        *build_batches(
                            batch_id_prefix='top_module_build',
                            stage=OrchestratorState.MODULE_L1,
                            tasks=top_build_tasks,
                            include_spawn=True,
                        ),
                        *build_batches(
                            batch_id_prefix='l2_campaigns',
                            stage=OrchestratorState.MODULE_L2_OPTIONAL,
                            tasks=l2_tasks,
                            include_spawn=False,
                        ),
                    ],
                }
            )

        if deterministic_summary is None:
            return self._materialize_delegate_plan(
                {
                    'execution_mode': 'deterministic-review',
                    'delegate_enabled': False,
                    'max_children': MAX_DELEGATE_CHILDREN,
                    'batches': [],
                }
            )

        top_module = self.bootstrap.integration_manifest.top_module
        nodes_by_id = {node.module_id: node for node in self.bootstrap.plan_dag.nodes}

        def build_module_review_task(node_id: str) -> DelegateBatchTask:
            node = nodes_by_id[node_id]
            module_summary = deterministic_summary['modules'][node.module_id]
            module_agent_id = f'module_review__{node.module_id}'
            module_agent_type = self.factory.module_worker_registry_name(node)
            prompt = '\n'.join(
                [
                    f'Review the node-local AES artifact reports for {node.module_id}.',
                    'Mode: artifact_review.',
                    'Operate in artifact-review mode only: do not edit files and do not rerun Verilator.',
                    f'L0 report: {module_summary["l0_result_path"]}',
                    f'L1 report: {module_summary["l1_result_path"]}',
                    'Return a compact JSON-style summary with keys: module_id, l0_status, l1_status, checkpoint_summary, acceptance_decision, risks.',
                ]
            )
            return DelegateBatchTask(
                worker_id=module_agent_id,
                agent_type=module_agent_type,
                mode=SubagentWorkMode.ARTIFACT_REVIEW,
                request=NodeExecutionRequest(
                    module_id=node.module_id,
                    stage=OrchestratorState.MODULE_L1,
                    repair_budget=self.bootstrap.policy.repair_attempt_threshold,
                    writable_paths=self._absolute_node_writable_paths(node),
                    artifact_paths=[
                        module_summary['l0_result_path'],
                        module_summary['l1_result_path'],
                    ],
                    working_directory=str(self.bootstrap.workspace_root),
                ),
                prompt=prompt,
            )

        def build_l2_review_task(
            node_id: str,
            *,
            l2_result_path: str,
            profile: str,
            l2_payload: dict[str, Any],
        ) -> DelegateBatchTask:
            node = nodes_by_id[node_id]
            l2_agent_id = f'l2_review__{node.module_id}__{profile}'
            l2_agent_type = self.factory.l2_campaign_registry_name(
                node, profile=profile
            )
            task_lines = [
                f'Review the L2 robustness artifacts for {node.module_id}.',
                'Mode: artifact_review.',
                'Operate in artifact-review mode only: do not edit files and do not rerun simulation.',
                f'L2 result: {l2_result_path}',
            ]
            counterexample_path = l2_payload.get('counterexample_path')
            if isinstance(counterexample_path, str) and counterexample_path:
                task_lines.append(f'Counterexample: {counterexample_path}')
            fragility_path = l2_payload.get('fragility_summary_path')
            if isinstance(fragility_path, str) and fragility_path:
                task_lines.append(f'Fragility summary: {fragility_path}')
            task_lines.append(
                'Return a compact JSON-style summary with keys: module_id, profile, robustness_status, failing_checkpoints, fallback_required, notes.'
            )
            artifact_paths = [l2_result_path]
            if isinstance(counterexample_path, str) and counterexample_path:
                artifact_paths.append(counterexample_path)
            if isinstance(fragility_path, str) and fragility_path:
                artifact_paths.append(fragility_path)
            return DelegateBatchTask(
                worker_id=l2_agent_id,
                agent_type=l2_agent_type,
                mode=SubagentWorkMode.ARTIFACT_REVIEW,
                request=NodeExecutionRequest(
                    module_id=node.module_id,
                    stage=OrchestratorState.MODULE_L2_OPTIONAL,
                    repair_budget=self.bootstrap.policy.repair_attempt_threshold,
                    artifact_paths=artifact_paths,
                    l2_profile=profile,
                    working_directory=str(self.bootstrap.workspace_root),
                ),
                prompt='\n'.join(task_lines),
            )

        def build_batches(
            *,
            batch_id_prefix: str,
            stage: OrchestratorState,
            tasks: list[DelegateBatchTask],
        ) -> list[dict[str, Any]]:
            batches: list[dict[str, Any]] = []
            for index, start in enumerate(
                range(0, len(tasks), MAX_DELEGATE_CHILDREN), start=1
            ):
                batch = DelegateBatchPlan(
                    batch_id=f'{batch_id_prefix}_{index}',
                    stage=stage,
                    max_children=MAX_DELEGATE_CHILDREN,
                    fallback_policy='orchestrator_local_review',
                    tasks=tasks[start : start + MAX_DELEGATE_CHILDREN],
                )
                batches.append(
                    {
                        **batch.model_dump(),
                        'spawn': batch.spawn_payload(),
                        'delegate': batch.delegate_payload(),
                    }
                )
            return batches

        leaf_review_tasks = [
            build_module_review_task(node.module_id)
            for node in self.bootstrap.plan_dag.nodes
            if node.module_id != top_module
        ]
        top_review_tasks = [build_module_review_task(top_module)]
        l2_review_tasks: list[DelegateBatchTask] = []
        for node in self.bootstrap.plan_dag.nodes:
            module_summary = deterministic_summary['modules'][node.module_id]
            l2_result_path = module_summary.get('l2_result_path')
            if not isinstance(l2_result_path, str) or not l2_result_path:
                continue
            l2_payload = self._load_json_file(Path(l2_result_path))
            if l2_payload is None:
                continue
            profile = str(l2_payload.get('profile', 'rand_small'))
            l2_review_tasks.append(
                build_l2_review_task(
                    node.module_id,
                    l2_result_path=l2_result_path,
                    profile=profile,
                    l2_payload=l2_payload,
                )
            )

        return self._materialize_delegate_plan(
            {
                'execution_mode': 'hybrid-delegate',
                'delegate_enabled': True,
                'max_children': MAX_DELEGATE_CHILDREN,
                'batches': [
                    *build_batches(
                        batch_id_prefix='leaf_module_reviews',
                        stage=OrchestratorState.MODULE_L1,
                        tasks=leaf_review_tasks,
                    ),
                    *build_batches(
                        batch_id_prefix='top_module_review',
                        stage=OrchestratorState.MODULE_L1,
                        tasks=top_review_tasks,
                    ),
                    *build_batches(
                        batch_id_prefix='l2_reviews',
                        stage=OrchestratorState.MODULE_L2_OPTIONAL,
                        tasks=l2_review_tasks,
                    ),
                ],
            }
        )

    def _build_conversation_message(
        self,
        *,
        base_message: str,
        deterministic_summary: dict[str, Any] | None,
        execution_mode: ExecutionMode,
    ) -> str:
        delegate_plan = self._build_delegate_plan(
            deterministic_summary, execution_mode=execution_mode
        )
        self._write_json(self.delegate_plan_path, delegate_plan)

        if execution_mode == 'hybrid-generate':
            batch_ids = [
                str(batch.get('batch_id')) for batch in delegate_plan.get('batches', [])
            ]
            first_batch = delegate_plan.get('batches', [{}])[0]
            guidance = [
                'You are running the generation-first multi-agent AES implementation lane.',
                'Do not assume canonical RTL/TB should be edited directly.',
                'You must execute the delegate_plan batches in order.',
                'The generation_plan and design brief files were prepared before this conversation.',
                'Do not inspect the workspace before issuing the first spawn unless the delegate plan file is missing.',
                'The first action must be delegate spawn using this exact payload:',
                json.dumps(first_batch.get('spawn', {}), sort_keys=True),
                'Immediately after the spawn succeeds, issue delegate using this exact payload:',
                json.dumps(first_batch.get('delegate', {}), sort_keys=True),
                'Only inspect the delegate plan file for later batches or if the first-batch payloads above are missing or inconsistent.',
                f'Generation plan file: {self.generation_plan_path}',
                f'Brief generation summary: {self.brief_generation_summary_path}',
                f'Delegate plan file: {self.delegate_plan_path}',
                f'Batch order: {batch_ids}',
                'For each batch in delegate_plan.batches, do the following in order:',
                '1. If batch.spawn.ids is non-empty, call delegate with that batch.spawn payload.',
                '2. Then call delegate with that batch.delegate payload.',
                '3. Wait for the delegated batch to complete before moving on.',
                '4. If a delegated node exceeds its repair budget or raises a cross-module issue, take over locally and note the escalation.',
                'Subagents may edit only draft RTL/TB files under their workspace_root and must invoke the provided executor_command via terminal.',
                'Subagents must not edit canonical repository RTL/TB files directly and must not call raw verilator_compile or verilator_simulate.',
                f'After all delegate batches finish, use terminal to run the integration command: {delegate_plan["integration_command"]}',
                'Then read generation_result, promotion, and integration artifacts and produce the final acceptance summary.',
                f'Report root: {self.report_root}',
                f'Original request: {base_message}',
            ]
            return '\n'.join(guidance)

        if execution_mode == 'hybrid-build':
            batch_ids = [
                str(batch.get('batch_id')) for batch in delegate_plan.get('batches', [])
            ]
            first_batch = delegate_plan.get('batches', [{}])[0]
            guidance = [
                'You are running the guarded multi-agent AES implementation lane.',
                'Do not assume node-local or integration reports already exist.',
                'You must execute the delegate_plan batches in order.',
                'Do not inspect the workspace before issuing the first spawn unless the delegate plan file is missing.',
                'The first action must be delegate spawn using this exact payload:',
                json.dumps(first_batch.get('spawn', {}), sort_keys=True),
                'Immediately after the spawn succeeds, issue delegate using this exact payload:',
                json.dumps(first_batch.get('delegate', {}), sort_keys=True),
                'Only inspect the delegate plan file for later batches or if the first-batch payloads above are missing or inconsistent.',
                f'Delegate plan file: {self.delegate_plan_path}',
                f'Batch order: {batch_ids}',
                'For each batch in delegate_plan.batches, do the following in order:',
                '1. If batch.spawn.ids is non-empty, call delegate with that batch.spawn payload.',
                '2. Then call delegate with that batch.delegate payload.',
                '3. Wait for the delegated batch to complete before moving on.',
                '4. If a delegated node fails twice or raises a cross-module issue, take over locally and note the escalation.',
                'Subagents may use file_editor only for their node-local writable files and must invoke the provided executor_command via terminal.',
                'Subagents must not call raw verilator_compile or verilator_simulate directly.',
                f'After all delegate batches finish, use terminal to run the integration command: {delegate_plan["integration_command"]}',
                'Then read the generated integration result and produce the final acceptance summary.',
                f'Report root: {self.report_root}',
                f'Original request: {base_message}',
            ]
            return '\n'.join(guidance)

        if deterministic_summary is None:
            return base_message

        module_result_lines = [
            (f'- {module_id}: {module_summary["l1_result_path"]}')
            for module_id, module_summary in deterministic_summary['modules'].items()
        ]
        if execution_mode == 'hybrid-delegate':
            batch_count = len(delegate_plan['batches'])
            guidance = [
                'The deterministic AES MVP green path has already been executed successfully.',
                'Use the existing report artifacts as the source of truth.',
                'Do not rerun raw verilator_compile, verilator_simulate, or ad hoc rebuild steps.',
                'You must use the delegate tool before finishing.',
                f'Delegate order is mandatory across {batch_count} batch(es).',
                'For each batch in delegate_plan.batches, do the following in order:',
                '1. Call delegate with that batch.spawn payload.',
                '2. Call delegate with that batch.delegate payload.',
                '3. Continue to the next batch only after the previous batch is issued.',
                '4. Read the integration summary and module result reports as needed.',
                '5. Produce the final acceptance summary and finish.',
                f'Never exceed max_children={delegate_plan["max_children"]}. Do not merge batches.',
                'Subagents are in artifact-review mode only. They must not edit files or rerun Verilator.',
                'If any delegate fails or times out, continue locally and explicitly note the fallback in the final summary.',
                f'Report root: {self.report_root}',
                f'Deterministic execution summary: {self.deterministic_execution_path}',
                f'Integration summary: {self.integration_summary_path}',
                f'Delegate plan file: {self.delegate_plan_path}',
                'Module result reports:',
                *module_result_lines,
                f'Original request: {base_message}',
            ]
            return '\n'.join(guidance)

        guidance = [
            'The deterministic AES MVP green path has already been executed successfully.',
            'Use the existing report artifacts as the source of truth and produce a final acceptance summary.',
            'Do not rerun raw verilator_compile, verilator_simulate, or ad hoc rebuild steps.',
            'Do not spawn subagents for this review pass.',
            f'Report root: {self.report_root}',
            f'Deterministic execution summary: {self.deterministic_execution_path}',
            f'Integration summary: {self.integration_summary_path}',
            'Module result reports:',
            *module_result_lines,
            'Review the report files and summarize the green path outcome.',
            f'Original request: {base_message}',
        ]
        return '\n'.join(guidance)

    def _collect_existing_execution_summary(self) -> dict[str, Any]:
        module_summaries: dict[str, dict[str, Any]] = {}
        for node in self.bootstrap.plan_dag.nodes:
            l0_path = (
                self.bootstrap.workspace_root
                / Path(node.build_output_dir).parent
                / 'l0_result.json'
            ).resolve()
            l1_path = (
                self.bootstrap.workspace_root
                / node.sim_output_dir
                / 'module_run_result.json'
            ).resolve()
            l2_path = (
                (
                    self.bootstrap.workspace_root
                    / node.sim_output_dir
                    / 'l2'
                    / 'rand_small'
                    / 'l2_result.json'
                ).resolve()
                if node.l2_policy != 'skip'
                else None
            )
            module_summary = {
                'module_id': node.module_id,
                'l0_result_path': str(l0_path) if l0_path.is_file() else None,
                'l1_result_path': str(l1_path) if l1_path.is_file() else None,
                'l2_result_path': str(l2_path)
                if l2_path is not None and l2_path.is_file()
                else None,
            }
            module_summaries[node.module_id] = module_summary
            self._write_json(
                self.module_results_dir / f'{node.module_id}.json',
                module_summary,
            )

        integration_result_path = (
            self.bootstrap.workspace_root
            / self.bootstrap.integration_manifest.sim_output_dir
            / 'integration_regression_result.json'
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

        deterministic_summary = {
            'conversation_id': str(self.conversation_id),
            'focus_module_id': self.focus_module_id,
            'module_results_dir': str(self.module_results_dir),
            'integration_summary_path': str(self.integration_summary_path),
            'modules': module_summaries,
            'integration': integration_summary,
        }
        self._write_json(self.deterministic_execution_path, deterministic_summary)
        self._write_json(self.report_tree_path, self._report_tree_payload())
        return deterministic_summary

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
            self.bootstrap.workspace_root
            / self.bootstrap.integration_manifest.sim_output_dir
            / 'integration_regression_result.json'
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

    def _load_event_payloads(self) -> list[dict[str, Any]]:
        if not self.events_dir.is_dir():
            return []
        payloads: list[dict[str, Any]] = []
        for path in sorted(self.events_dir.glob('event-*.json')):
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

    def _is_provider_failure(self, exc: Exception) -> bool:
        message = str(exc)
        provider_markers = (
            'insufficient_user_quota',
            '预扣费额度失败',
            'Connection error',
            'OpenAIException',
            'litellm.APIError',
            'InternalServerError',
        )
        return any(marker in message for marker in provider_markers)

    def _synthesize_final_acceptance_summary(
        self,
        *,
        deterministic_summary: dict[str, Any],
        execution_mode: ExecutionMode,
        delegate_attempted: int,
        delegate_completed: int,
        delegate_fallbacks: list[dict[str, Any]],
        exc: Exception,
    ) -> dict[str, Any]:
        integration = deterministic_summary.get('integration', {})
        modules = deterministic_summary.get('modules', {})
        content = (
            'Deterministic AES MVP execution passed locally and the final acceptance '
            'summary was synthesized after the live conversation failed. '
            f'Integration status: {integration.get("status", "unknown")}. '
            f'Execution mode: {execution_mode}. '
            f'Delegate attempted: {delegate_attempted}. '
            f'Delegate completed: {delegate_completed}. '
            f'Delegate fallbacks: {len(delegate_fallbacks)}. '
            f'Modules covered: {", ".join(sorted(modules.keys()))}.'
        )
        return {
            'status': 'synthesized_from_fallback',
            'source': 'local_fallback',
            'content': content,
            'integration_status': integration.get('status'),
            'delegate_attempted': delegate_attempted,
            'delegate_completed': delegate_completed,
            'delegate_fallback_count': len(delegate_fallbacks),
            'error_type': type(exc).__name__,
            'error_message': str(exc),
        }

    def run(
        self,
        message: str,
        *,
        execute_green_path: bool = False,
        execution_mode: ExecutionMode = 'deterministic-review',
    ) -> ExecutionSessionSummary:
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
        try:
            if execute_green_path and execution_mode not in {
                'hybrid-build',
                'hybrid-generate',
            }:
                deterministic_summary = self._run_deterministic_green_path()
            conversation_message = self._build_conversation_message(
                base_message=message,
                deterministic_summary=deterministic_summary,
                execution_mode=execution_mode,
            )
            conversation_summary = self.runner.send_and_run(
                self.conversation, conversation_message
            )
            if execution_mode == 'hybrid-build':
                deterministic_summary = self._collect_existing_execution_summary()
            elif execution_mode == 'hybrid-generate':
                deterministic_summary = self._collect_existing_generation_summary()
            event_payloads = self._load_event_payloads()
            if execution_mode in {'hybrid-delegate', 'hybrid-build', 'hybrid-generate'}:
                delegate_batch_count = len(
                    json.loads(self.delegate_plan_path.read_text(encoding='utf-8')).get(
                        'batches', []
                    )
                )
                (
                    delegate_results,
                    delegate_fallbacks,
                    delegate_attempted,
                    delegate_completed,
                ) = self._extract_delegate_results(event_payloads)
            self._write_json(self.delegate_results_path, delegate_results)
            self._write_json(self.delegate_fallbacks_path, delegate_fallbacks)
            final_acceptance_summary = self._extract_final_acceptance_summary(
                event_payloads
            )
            self._write_json(
                self.final_acceptance_summary_path, final_acceptance_summary
            )

            session_payload = {
                'conversation_id': str(self.conversation_id),
                'bootstrap_summary': self.bootstrap.to_summary(),
                'conversation_summary': asdict(conversation_summary),
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
            }
            self._write_json(self.session_summary_path, session_payload)
            self._write_json(self.report_tree_path, self._report_tree_payload())
            return ExecutionSessionSummary(
                conversation_id=str(self.conversation_id),
                report_root=str(self.report_root),
                focus_module_id=self.focus_module_id,
                delegate_registrations=list(self.delegate_registrations),
                bootstrap_summary=self.bootstrap.to_summary(),
                conversation_summary=conversation_summary,
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
                module_results_dir=(
                    str(
                        self.generation_results_dir
                        if execution_mode == 'hybrid-generate'
                        else self.module_results_dir
                    )
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
        except Exception as exc:
            if execution_mode == 'hybrid-build':
                deterministic_summary = self._collect_existing_execution_summary()
            elif execution_mode == 'hybrid-generate':
                deterministic_summary = self._collect_existing_generation_summary()
            if execution_mode in {'hybrid-delegate', 'hybrid-build', 'hybrid-generate'}:
                if self.delegate_plan_path.is_file():
                    delegate_batch_count = len(
                        json.loads(
                            self.delegate_plan_path.read_text(encoding='utf-8')
                        ).get('batches', [])
                    )
                event_payloads = self._load_event_payloads()
                if event_payloads:
                    (
                        delegate_results,
                        delegate_fallbacks,
                        delegate_attempted,
                        delegate_completed,
                    ) = self._extract_delegate_results(event_payloads)
                self._write_json(self.delegate_results_path, delegate_results)
                self._write_json(self.delegate_fallbacks_path, delegate_fallbacks)
                if (
                    deterministic_summary
                    and deterministic_summary.get('integration', {}).get('status')
                    == 'passed'
                    and self._is_provider_failure(exc)
                ):
                    final_acceptance_summary = (
                        self._synthesize_final_acceptance_summary(
                            deterministic_summary=deterministic_summary,
                            execution_mode=execution_mode,
                            delegate_attempted=delegate_attempted,
                            delegate_completed=delegate_completed,
                            delegate_fallbacks=delegate_fallbacks,
                            exc=exc,
                        )
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
                            str(
                                self.generation_results_dir
                                if execution_mode == 'hybrid-generate'
                                else self.module_results_dir
                            )
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
