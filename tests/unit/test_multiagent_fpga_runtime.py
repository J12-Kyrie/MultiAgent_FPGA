from __future__ import annotations

import json
from pathlib import Path
from types import SimpleNamespace
from uuid import uuid4

import pytest

from MultiAgent_FPGA.fpga_flow.__main__ import _run_node, build_parser
from MultiAgent_FPGA.fpga_flow.artifacts import NodeWorkspaceRecord, NodeWorkspaceState
from MultiAgent_FPGA.fpga_flow.generation import (
    increment_validation_runs,
    initialize_node_workspace,
    load_workspace_record,
    workspace_promoted_root,
    write_generation_result,
    write_repair_request,
    write_workspace_record,
)
from MultiAgent_FPGA.fpga_flow.llm_profiles import (
    DEEPSEEK_RESOLVED_MODEL,
    SDK_DEEPSEEK_MODEL,
    SDK_REASONING_EFFORT_FAST,
    SDK_REASONING_EFFORT_THINKING,
    build_sdk_deepseek_official_fast_kwargs,
    build_sdk_deepseek_official_thinking_kwargs,
)
from MultiAgent_FPGA.fpga_flow.runtime import (
    ConversationRunner,
    ConversationSummary,
    ExecutionSession,
    RuntimeBootstrap,
    SdkAgentFactory,
    discover_sdk_environment,
)
from MultiAgent_FPGA.fpga_flow.runtime.context_assembler import BatchMessageEnvelope
from MultiAgent_FPGA.fpga_flow.runtime.execution_tools import RunExecutor
from MultiAgent_FPGA.fpga_flow.runtime.factory import VERILATOR_ALLOWED_MCP_REGEX
from MultiAgent_FPGA.fpga_flow.runtime.runner import BatchRunSummary
from MultiAgent_FPGA.fpga_flow.synthesis import (
    DEFAULT_AUTONOMOUS_GOAL,
    DAGBatchPlanner,
    FragilityMemory,
    FragilitySignal,
    IntegrationReadinessResolver,
    L2AdaptivePlanner,
    NodePolicyEngine,
    synthesize_integration_manifest,
    synthesize_plan_dag,
    synthesize_spec_ir,
)

EXPECTED_DELEGATE_REGISTRATIONS = [
    'module_worker__aes_sbox',
    'module_repair__aes_sbox',
    'module_worker__aes_key_schedule_128',
    'module_repair__aes_key_schedule_128',
    'module_worker__aes_round_transform',
    'module_repair__aes_round_transform',
    'module_worker__aes128_encrypt_core',
    'module_repair__aes128_encrypt_core',
]

EXPECTED_DELEGATE_REGISTRATIONS_WITH_L2 = [
    'module_worker__aes_sbox',
    'module_repair__aes_sbox',
    'module_worker__aes_key_schedule_128',
    'module_repair__aes_key_schedule_128',
    'l2_campaign__aes_key_schedule_128__rand_small',
    'module_worker__aes_round_transform',
    'module_repair__aes_round_transform',
    'l2_campaign__aes_round_transform__rand_small',
    'module_worker__aes128_encrypt_core',
    'module_repair__aes128_encrypt_core',
    'l2_campaign__aes128_encrypt_core__rand_small',
]


def _synthesized_context():
    spec_ir = synthesize_spec_ir(system_goal=DEFAULT_AUTONOMOUS_GOAL)
    plan_dag = synthesize_plan_dag(spec_ir)
    manifest = synthesize_integration_manifest(spec_ir, plan_dag)
    return spec_ir, plan_dag, manifest


def test_sdk_environment_is_discoverable_in_poetry_env():
    status = discover_sdk_environment()
    assert status.available is True
    assert status.package_name == 'openhands.sdk'


def test_sdk_shim_loads_explicit_site_packages_modules():
    from MultiAgent_FPGA.fpga_flow.runtime.sdk_shim import load_sdk_modules

    sdk_modules = load_sdk_modules()
    assert sdk_modules.sdk.__name__ == 'openhands.sdk'
    assert sdk_modules.register_agent_if_absent is not None
    assert sdk_modules.DelegateTool.name == 'delegate'


def test_sdk_llm_kwargs_use_deepseek_chat_runtime(monkeypatch):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    thinking = build_sdk_deepseek_official_thinking_kwargs()
    fast = build_sdk_deepseek_official_fast_kwargs()
    assert thinking['model'] == SDK_DEEPSEEK_MODEL
    assert fast['model'] == SDK_DEEPSEEK_MODEL
    assert thinking['model_canonical_name'] == DEEPSEEK_RESOLVED_MODEL
    assert fast['model_canonical_name'] == DEEPSEEK_RESOLVED_MODEL
    assert fast.get('litellm_extra_body') is None
    assert thinking.get('litellm_extra_body') is None
    assert thinking['reasoning_effort'] == SDK_REASONING_EFFORT_THINKING
    assert fast['reasoning_effort'] == SDK_REASONING_EFFORT_FAST


def test_runtime_bootstrap_loads_synthesized_autonomous_context(monkeypatch):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(system_goal=DEFAULT_AUTONOMOUS_GOAL)
    assert len(bootstrap.runtime_skills) == 5
    assert bootstrap.synthesis_source == 'autonomous'
    assert bootstrap.system_goal == DEFAULT_AUTONOMOUS_GOAL
    assert bootstrap.integration_manifest.top_module == 'aes128_encrypt_core'
    assert 'aes-verilator-profile' in bootstrap.runtime_skill_names
    assert 'aes-module-patterns' in bootstrap.runtime_skill_names
    env = bootstrap.mcp_config['mcpServers']['verilator']['env']
    assert 'DEEPSEEK_API_KEY' not in env
    assert 'CHATFIRE_API_KEY' not in env


def test_factory_creates_execution_and_finalizer_orchestrators(monkeypatch):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(system_goal=DEFAULT_AUTONOMOUS_GOAL)
    factory = SdkAgentFactory(bootstrap)
    orchestrator = factory.create_execution_orchestrator()
    finalizer = factory.create_finalizer_orchestrator()
    worker = factory.create_module_worker(bootstrap.plan_dag.nodes[0])
    repair_worker = factory.create_module_repair_worker(bootstrap.plan_dag.nodes[0])
    registrations = factory.register_delegate_agents()

    assert orchestrator.llm.model == SDK_DEEPSEEK_MODEL
    assert finalizer.llm.model == SDK_DEEPSEEK_MODEL
    assert worker.llm.model == SDK_DEEPSEEK_MODEL
    assert repair_worker.llm.model == SDK_DEEPSEEK_MODEL
    assert orchestrator.llm.model_canonical_name == DEEPSEEK_RESOLVED_MODEL
    assert worker.llm.model_canonical_name == DEEPSEEK_RESOLVED_MODEL
    assert repair_worker.llm.model_canonical_name == DEEPSEEK_RESOLVED_MODEL
    assert any(tool.name == 'delegate' for tool in orchestrator.tools)
    assert any(tool.name == 'terminal' for tool in orchestrator.tools)
    assert all(tool.name != 'file_editor' for tool in orchestrator.tools)
    assert all(tool.name != 'task_tracker' for tool in orchestrator.tools)
    assert all(tool.name != 'delegate' for tool in finalizer.tools)
    assert all(tool.name != 'delegate' for tool in worker.tools)
    assert all(tool.name != 'delegate' for tool in repair_worker.tools)
    assert any(tool.name == 'terminal' for tool in worker.tools)
    assert all(tool.name != 'terminal' for tool in repair_worker.tools)
    assert any(tool.name == 'file_editor' for tool in repair_worker.tools)
    assert any(tool.name == 'task_tracker' for tool in repair_worker.tools)
    assert orchestrator.include_default_tools == ['ThinkTool']
    assert all(
        getattr(tool, 'name', '').lower() != 'finish' for tool in orchestrator.tools
    )
    assert finalizer.include_default_tools == ['FinishTool', 'ThinkTool']
    assert orchestrator.filter_tools_regex == VERILATOR_ALLOWED_MCP_REGEX
    assert finalizer.filter_tools_regex is None
    assert worker.filter_tools_regex is None
    assert repair_worker.filter_tools_regex is None
    assert worker.mcp_config == {}
    assert repair_worker.mcp_config == {}
    assert registrations == EXPECTED_DELEGATE_REGISTRATIONS


def test_factory_register_delegate_agents_with_l2(monkeypatch):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(system_goal=DEFAULT_AUTONOMOUS_GOAL)
    factory = SdkAgentFactory(bootstrap)
    registrations = factory.register_delegate_agents(enable_l2=True)
    assert registrations == EXPECTED_DELEGATE_REGISTRATIONS_WITH_L2


def test_node_policy_engine_selects_generate_then_repair_and_blocked():
    engine = NodePolicyEngine()
    record = NodeWorkspaceRecord(
        module_id='aes_sbox',
        workspace_root='/tmp/workspace',
        state=NodeWorkspaceState.DRAFT_READY,
        validation_runs=0,
        contract_paths={},
        draft_paths={},
        promoted_paths={},
        validation_paths={},
        canonical_targets=[],
    )
    assert (
        engine.decide_next_mode(
            workspace_record=record,
            validation_status=None,
            repair_budget=2,
        ).value
        == 'generate'
    )
    first_failed = record.model_copy(
        update={
            'state': NodeWorkspaceState.REPAIRING,
            'validation_runs': 1,
            'repair_edit_count': 0,
        }
    )
    assert (
        engine.decide_next_mode(
            workspace_record=first_failed,
            validation_status='failed',
            repair_budget=2,
        ).value
        == 'repair'
    )
    assert (
        engine.next_state(
            workspace_record=first_failed,
            validation_status='failed',
            repair_budget=2,
        )
        == NodeWorkspaceState.REPAIRING
    )
    repaired = record.model_copy(
        update={
            'state': NodeWorkspaceState.REPAIRING,
            'validation_runs': 2,
            'repair_edit_count': 2,
        }
    )
    assert (
        engine.decide_next_mode(
            workspace_record=repaired,
            validation_status='failed',
            repair_budget=2,
        ).value
        == 'repair'
    )
    blocked = repaired.model_copy(update={'validation_runs': 3, 'repair_edit_count': 3})
    assert (
        engine.next_state(
            workspace_record=blocked,
            validation_status='failed',
            repair_budget=2,
        )
        == NodeWorkspaceState.BLOCKED
    )


def test_dag_batch_planner_uses_dependency_layers_and_l2_batches():
    _, plan_dag, manifest = _synthesized_context()
    planner = DAGBatchPlanner()
    batches = planner.plan(
        plan_dag=plan_dag,
        integration_manifest=manifest,
        fragility_memory=FragilityMemory(),
        max_children=5,
        l2_planner=L2AdaptivePlanner(),
        enable_l2=True,
    )
    assert [batch.batch_id for batch in batches] == [
        'generation_layer_1_1',
        'generation_layer_2_1',
        'generation_layer_3_1',
        'l2_campaigns_1',
    ]
    assert [task.module_id for task in batches[0].tasks] == ['aes_sbox']
    assert {task.module_id for task in batches[1].tasks} == {
        'aes_key_schedule_128',
        'aes_round_transform',
    }
    assert [task.module_id for task in batches[2].tasks] == ['aes128_encrypt_core']
    assert all(task.mode.value == 'l2_execute' for task in batches[-1].tasks)


def test_dag_batch_planner_excludes_l2_when_disabled():
    _, plan_dag, manifest = _synthesized_context()
    planner = DAGBatchPlanner()
    batches = planner.plan(
        plan_dag=plan_dag,
        integration_manifest=manifest,
        fragility_memory=FragilityMemory(),
        max_children=5,
        l2_planner=L2AdaptivePlanner(),
    )
    assert [batch.batch_id for batch in batches] == [
        'generation_layer_1_1',
        'generation_layer_2_1',
        'generation_layer_3_1',
    ]
    assert all(
        task.mode.value != 'l2_execute' for batch in batches for task in batch.tasks
    )


def test_l2_adaptive_planner_uses_fragility_history_to_escalate():
    _, plan_dag, manifest = _synthesized_context()
    planner = L2AdaptivePlanner()
    top_node = plan_dag.nodes[-1]
    memory = FragilityMemory(
        module_history={
            top_node.module_id: [
                FragilitySignal(
                    profile='rand_small',
                    status='failed',
                    failing_checkpoints=['CHK_CIPHERTEXT_MATCH'],
                )
            ]
        }
    )
    request = planner.plan(
        node=top_node,
        fragility_memory=memory,
        integration_manifest=manifest,
    )
    assert request is not None
    assert request.profile == 'rand_medium'


def test_integration_readiness_resolver_uses_dependency_closure():
    _, plan_dag, _ = _synthesized_context()
    resolver = IntegrationReadinessResolver()
    assert resolver.dependency_closure(plan_dag, 'aes128_encrypt_core') == [
        'aes_sbox',
        'aes_key_schedule_128',
        'aes_round_transform',
        'aes128_encrypt_core',
    ]
    assert (
        resolver.ready_sink_modules(
            plan_dag,
            promoted_modules={
                'aes_sbox',
                'aes_key_schedule_128',
                'aes_round_transform',
            },
        )
        == []
    )
    assert resolver.ready_sink_modules(
        plan_dag,
        promoted_modules={
            'aes_sbox',
            'aes_key_schedule_128',
            'aes_round_transform',
            'aes128_encrypt_core',
        },
    ) == ['aes128_encrypt_core']


def test_runner_can_pause_after_batch_gate(tmp_path: Path):
    conversation_id = uuid4()
    artifact_path = tmp_path / 'generation_result.json'

    class FakeConversation:
        def __init__(self) -> None:
            self.state = SimpleNamespace(
                id=conversation_id,
                execution_status='idle',
                events=[],
                persistence_dir=str(tmp_path),
            )
            self.workspace = SimpleNamespace(working_dir=str(tmp_path))
            self.messages: list[str] = []

        def send_message(self, message: str) -> None:
            self.messages.append(message)

        def run(self) -> None:
            import time

            self.state.execution_status = 'running'
            time.sleep(0.05)
            artifact_path.write_text('{"ok":true}', encoding='utf-8')
            while self.state.execution_status != 'paused':
                time.sleep(0.01)

        def pause(self) -> None:
            self.state.execution_status = 'paused'

    monkeypatch = pytest.MonkeyPatch()
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(system_goal=DEFAULT_AUTONOMOUS_GOAL)
    factory = SdkAgentFactory(bootstrap)
    runner = ConversationRunner(bootstrap, factory)
    conversation = FakeConversation()

    summary = runner.run_current_batch_until_gate(
        conversation,
        'run current batch',
        batch_gate=lambda: artifact_path.is_file(),
        timeout_s=2.0,
        poll_interval_s=0.01,
    )

    assert summary.gate_satisfied is True
    assert summary.timed_out is False
    assert summary.pause_reason == 'batch_gate_satisfied'
    assert summary.conversation_summary.execution_status == 'paused'
    monkeypatch.undo()


def test_runner_marks_finished_before_gate_pause_reason(tmp_path: Path):
    conversation_id = uuid4()

    class FakeConversation:
        def __init__(self) -> None:
            self.state = SimpleNamespace(
                id=conversation_id,
                execution_status='idle',
                events=[],
                persistence_dir=str(tmp_path),
            )
            self.workspace = SimpleNamespace(working_dir=str(tmp_path))
            self.messages: list[str] = []

        def send_message(self, message: str) -> None:
            self.messages.append(message)

        def run(self) -> None:
            self.state.execution_status = 'finished'

        def pause(self) -> None:
            self.state.execution_status = 'paused'

    monkeypatch = pytest.MonkeyPatch()
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(system_goal=DEFAULT_AUTONOMOUS_GOAL)
    factory = SdkAgentFactory(bootstrap)
    runner = ConversationRunner(bootstrap, factory)
    conversation = FakeConversation()

    summary = runner.run_current_batch_until_gate(
        conversation,
        'run current batch',
        batch_gate=lambda: False,
        timeout_s=2.0,
        poll_interval_s=0.01,
    )

    assert summary.gate_satisfied is False
    assert summary.pause_reason == 'conversation_finished_before_gate'
    assert summary.conversation_summary.execution_status == 'paused'
    monkeypatch.undo()


def test_resolve_vector_path_finds_package_vectors():
    from MultiAgent_FPGA.fpga_flow.synthesis import (
        resolve_vector_path,
        synthesize_plan_dag,
        synthesize_spec_ir,
    )

    spec = synthesize_spec_ir(system_goal=DEFAULT_AUTONOMOUS_GOAL)
    plan = synthesize_plan_dag(spec)
    missing = []
    for node in plan.nodes:
        p = resolve_vector_path(node.pass_criteria.l1.vector_set)
        if p is None:
            missing.append(node.pass_criteria.l1.vector_set)
    assert not missing


def test_repair_batch_gate_materializes_edit_receipt(monkeypatch, tmp_path: Path):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(
        persistence_dir=tmp_path / 'conversations',
        system_goal=DEFAULT_AUTONOMOUS_GOAL,
    )
    session = ExecutionSession.create(
        bootstrap,
        conversation_id=uuid4(),
        focus_module_id='aes128_encrypt_core',
    )
    generation_plan = session._prepare_generation_artifacts()
    generation_entry = next(
        entry for entry in generation_plan['nodes'] if entry['module_id'] == 'aes_sbox'
    )
    workspace_root = Path(generation_entry['workspace_root'])
    node = next(
        candidate
        for candidate in bootstrap.plan_dag.nodes
        if candidate.module_id == 'aes_sbox'
    )
    workspace_record = load_workspace_record(workspace_root).model_copy(
        update={'state': NodeWorkspaceState.REPAIRING, 'validation_runs': 1}
    )
    write_workspace_record(workspace_record)
    generation_result_path = write_generation_result(
        workspace_record=workspace_record,
        node=node,
        validation_status='failed',
        promoted=False,
        changed_files=[],
        checkpoint_summary={},
        missing_checkpoints=['CHK_SBOX_MATCH'],
        failed_checkpoints=[],
        recommended_mode='repair',
    )
    write_repair_request(
        workspace_record=workspace_record,
        node=node,
        generation_result_path=generation_result_path,
        missing_checkpoints=['CHK_SBOX_MATCH'],
        failed_checkpoints=[],
        rerun_command='python -m MultiAgent_FPGA.fpga_flow run-node aes_sbox',
    )

    draft_tb_path = workspace_root / 'draft' / 'tb' / 'aes_sbox_tb.cpp'
    draft_tb_path.write_text(
        '\n'.join(
            [
                '#include <verilated.h>',
                '#include <iostream>',
                '#include "Vaes_sbox.h"',
                'int main(int argc, char** argv) {',
                '    Verilated::commandArgs(argc, argv);',
                '    Vaes_sbox dut;',
                '    dut.eval();',
                '    std::cout << "CHECKPOINT|CHK_SBOX_MATCH|PASS|known_answer" << std::endl;',
                '    return 0;',
                '}',
                '',
            ]
        ),
        encoding='utf-8',
    )

    current_batch = {
        'batch_id': 'generation_layer_1_1_repair_1',
        'phase': 'repair_edit',
        'tasks': [
            {
                'request': {
                    'workspace_root': str(workspace_root),
                    'result_paths': {
                        'edit_receipt': str(workspace_root / 'edit_receipt.json')
                    },
                }
            }
        ],
    }
    baseline = session._artifact_snapshot([str(workspace_root / 'edit_receipt.json')])

    gate = session._build_batch_gate(current_batch=current_batch, baseline=baseline)

    assert gate() is True
    receipt_payload = json.loads(
        (workspace_root / 'edit_receipt.json').read_text(encoding='utf-8')
    )
    assert receipt_payload['module_id'] == 'aes_sbox'
    assert str(draft_tb_path) in receipt_payload['edited_files']


def test_materialize_current_batch_inlines_repair_contract(monkeypatch, tmp_path: Path):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(
        persistence_dir=tmp_path / 'conversations',
        system_goal=DEFAULT_AUTONOMOUS_GOAL,
    )
    session = ExecutionSession.create(
        bootstrap,
        conversation_id=uuid4(),
        focus_module_id='aes128_encrypt_core',
    )
    generation_plan = session._prepare_generation_artifacts()
    generation_entry = next(
        entry for entry in generation_plan['nodes'] if entry['module_id'] == 'aes_sbox'
    )
    workspace_root = Path(generation_entry['workspace_root'])
    node = next(
        candidate
        for candidate in bootstrap.plan_dag.nodes
        if candidate.module_id == 'aes_sbox'
    )
    workspace_record = load_workspace_record(workspace_root).model_copy(
        update={'state': NodeWorkspaceState.REPAIRING, 'validation_runs': 1}
    )
    write_workspace_record(workspace_record)
    generation_result_path = write_generation_result(
        workspace_record=workspace_record,
        node=node,
        validation_status='failed',
        promoted=False,
        changed_files=[],
        checkpoint_summary={},
        missing_checkpoints=[],
        failed_checkpoints=['CHK_SBOX_MATCH'],
        recommended_mode='repair',
    )
    write_repair_request(
        workspace_record=workspace_record,
        node=node,
        generation_result_path=generation_result_path,
        missing_checkpoints=[],
        failed_checkpoints=['CHK_SBOX_MATCH'],
        rerun_command='python -m MultiAgent_FPGA.fpga_flow run-node aes_sbox',
    )

    batch = {
        'batch_id': 'generation_layer_1_1_aes_sbox_repair_2',
        'phase': 'repair_edit',
        'stage': 'MODULE_L1',
        'repair_round': 2,
        'spawn': {'command': 'spawn', 'ids': [], 'agent_types': []},
        'tasks': [
            {
                'worker_id': 'module_repair__aes_sbox',
                'agent_type': 'module_repair__aes_sbox',
                'prompt': 'primary_target_file: read from repair_request.json at execution time',
                'request': {
                    'module_id': 'aes_sbox',
                    'workspace_root': str(workspace_root),
                    'manual_receipt_command': 'python -m MultiAgent_FPGA.fpga_flow record-repair-edit aes_sbox',
                    'writable_paths': [
                        str(workspace_root / 'draft' / 'rtl' / 'aes_sbox.v'),
                        str(workspace_root / 'draft' / 'tb' / 'aes_sbox_tb.cpp'),
                    ],
                    'artifact_paths': list(
                        generation_entry['validation_paths'].values()
                    ),
                    'result_paths': {
                        'generation_result': str(
                            workspace_root / 'generation_result.json'
                        ),
                        'workspace_state': str(workspace_root / 'workspace_state.json'),
                        'validation_summary': generation_entry['validation_paths'][
                            'validation_summary'
                        ],
                        'validation_error': generation_entry['validation_paths'][
                            'validation_error'
                        ],
                        'repair_request': str(workspace_root / 'repair_request.json'),
                        'edit_receipt': str(workspace_root / 'edit_receipt.json'),
                    },
                },
            }
        ],
    }

    materialized_delegate_plan = session._materialize_delegate_plan(
        {'batches': [batch], 'delegate_enabled': True}
    )
    materialized_batch = materialized_delegate_plan['batches'][0]
    current_batch = session._materialize_current_batch(
        batch=materialized_batch, selected_tasks=materialized_batch['tasks']
    )
    assert current_batch['spawn']['ids'] == ['module_repair__aes_sbox']
    assert current_batch['spawn']['agent_types'] == ['module_repair__aes_sbox']
    prompt = current_batch['delegate']['tasks']['module_repair__aes_sbox']
    task_request = current_batch['tasks'][0]['request']

    assert 'Use the inlined repair contract below' in prompt
    assert task_request['writable_paths'] == [
        str(workspace_root / 'draft' / 'rtl' / 'aes_sbox.v'),
        str(workspace_root.resolve() / 'escalation_signal.json'),
    ]


def test_orchestrator_batch_snapshot_payload_is_slim(monkeypatch, tmp_path: Path):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(
        persistence_dir=tmp_path / 'conversations',
        system_goal=DEFAULT_AUTONOMOUS_GOAL,
    )
    session = ExecutionSession.create(
        bootstrap,
        conversation_id=uuid4(),
        focus_module_id='aes128_encrypt_core',
    )
    req_path = str(tmp_path / 'delegate_requests' / 'b1__w1.json')
    snap = session._build_orchestrator_batch_snapshot_payload(
        current_batch={
            'batch_id': 'b1',
            'phase': 'repair_edit',
            'spawn': {'command': 'spawn', 'ids': ['w1'], 'agent_types': ['t1']},
            'tasks': [
                {
                    'worker_id': 'w1',
                    'agent_type': 't1',
                    'mode': 'repair',
                    'request_path': req_path,
                    'prompt': 'LONG_PROMPT' * 200,
                    'request': {'workspace_root': '/tmp', 'module_id': 'm'},
                }
            ],
        },
        workflow_gate={'decision': 'continue', 'next_batch_ids': ['next_b']},
        expected_artifacts=['/tmp/artifact.json'],
    )
    assert 'delegate' not in snap
    assert 'workflow_gate' not in snap
    assert snap['workflow_gate_path']
    assert snap['workflow_gate_summary']['decision'] == 'continue'
    assert snap['workflow_gate_summary']['next_batch_ids'] == ['next_b']
    assert snap['delegate_requests_dir']
    assert 'manual_command_policy' in snap
    row = snap['tasks'][0]
    assert row['worker_id'] == 'w1'
    assert row['agent_type'] == 't1'
    assert row['mode'] == 'repair'
    assert row['request_path'] == req_path
    assert 'prompt' not in row
    assert 'request' not in row


def test_context_assembler_builds_thin_batch_message(monkeypatch, tmp_path: Path):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(
        persistence_dir=tmp_path / 'conversations',
        system_goal=DEFAULT_AUTONOMOUS_GOAL,
    )
    session = ExecutionSession.create(
        bootstrap,
        conversation_id=uuid4(),
        focus_module_id='aes128_encrypt_core',
    )
    message = session.context_assembler.build_batch_message(
        base_message=DEFAULT_AUTONOMOUS_GOAL,
        envelope=BatchMessageEnvelope(
            batch_id='b1',
            phase='generate_validate',
            snapshot_path=session.current_batch_snapshot_path,
            workflow_gate_path=session.workflow_gate_path,
            delegate_requests_dir=session.delegate_requests_dir,
            report_root=session.report_root,
            expected_artifacts=('/tmp/generation_result.json',),
            handoff_digest_path=session.autonomous_handoff_digest_path,
        ),
    )
    assert 'batch_id: b1' in message
    assert 'current_batch_snapshot:' in message
    assert 'delegate_requests_dir:' in message
    assert 'expected_artifacts:' in message
    assert 'Allowed actions:' not in message
    assert 'Framework-known next eligible batch ids' not in message


def test_run_executor_returns_structured_observation(monkeypatch, tmp_path: Path):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(
        persistence_dir=tmp_path / 'conversations',
        system_goal=DEFAULT_AUTONOMOUS_GOAL,
    )
    session = ExecutionSession.create(
        bootstrap,
        conversation_id=uuid4(),
        focus_module_id='aes128_encrypt_core',
    )
    delegate_plan = session._build_delegate_plan()  # type: ignore[attr-defined]
    first_task = delegate_plan['batches'][0]['tasks'][0]
    monkeypatch.setattr(
        'MultiAgent_FPGA.fpga_flow.runtime.execution_tools._dispatch_executor',
        lambda task, executor_kind: {
            'module_id': task.request.module_id,
            'validation_status': 'failed',
            'generation_result_path': task.request.result_paths['generation_result'],
            'workspace_state_path': task.request.result_paths['workspace_state'],
            'repair_request_path': task.request.result_paths['repair_request'],
            'recommended_mode': 'repair',
        },
    )

    executor = RunExecutor()
    observation = executor(
        SimpleNamespace(request_path=str(first_task['request_path']))  # type: ignore[arg-type]
    )

    assert observation.executor_kind.value == 'generate_node'
    assert observation.phase == 'generate'
    assert observation.module_id == first_task['request']['module_id']
    assert observation.request_path == first_task['request_path']
    assert 'generation_result' in observation.result_paths
    assert observation.next_read_paths
    assert observation.workflow_gate_hint == 'framework_will_schedule_repair_or_block'
    assert observation.recommended_next_phase == 'repair_edit'


def test_autonomous_execution_loop_writes_hook_events(monkeypatch, tmp_path: Path):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(
        persistence_dir=tmp_path / 'conversations',
        system_goal=DEFAULT_AUTONOMOUS_GOAL,
    )
    session = ExecutionSession.create(
        bootstrap,
        conversation_id=uuid4(),
        focus_module_id='aes128_encrypt_core',
    )
    artifact_path = tmp_path / 'generation_result.json'
    artifact_path.write_text('{"ok": true}', encoding='utf-8')
    current_batch = {
        'batch_id': 'b1',
        'phase': 'generate_validate',
        'tasks': [
            {
                'worker_id': 'w1',
                'request': {'module_id': 'aes_sbox'},
            }
        ],
    }

    monkeypatch.setattr(
        session,
        '_collect_existing_generation_summary',
        lambda: {'modules': {}, 'integration': {'status': 'missing'}},
    )
    monkeypatch.setattr(session, '_collect_fragility_memory', lambda: None)
    monkeypatch.setattr(
        session,
        '_evaluate_workflow_gate',
        lambda **kwargs: (
            {'decision': 'continue', 'next_batch_ids': ['b1']}
            if not kwargs['processed_batch_ids']
            else {
                'decision': 'success',
                'primary_sink': 'aes128_encrypt_core',
                'required_modules': [],
                'next_batch_ids': [],
                'integration_status': 'passed',
            }
        ),
    )
    monkeypatch.setattr(
        session,
        '_next_eligible_autonomous_batch',
        lambda **kwargs: (current_batch, [])
        if not kwargs['processed_batch_ids']
        else (None, []),
    )
    monkeypatch.setattr(
        session,
        '_batch_expected_artifact_paths',
        lambda batch: [str(artifact_path)],
    )
    monkeypatch.setattr(
        session,
        '_artifact_snapshot',
        lambda paths: {path: None for path in paths},
    )
    monkeypatch.setattr(
        session,
        '_artifact_updated',
        lambda **kwargs: True,
    )
    monkeypatch.setattr(
        session.runner,
        'create_execution_conversation',
        lambda **kwargs: SimpleNamespace(
            state=SimpleNamespace(
                id=kwargs.get('conversation_id', uuid4()),
                execution_status='idle',
                events=[],
                persistence_dir=str(session.report_root),
            ),
            workspace=SimpleNamespace(
                working_dir=str(session.bootstrap.workspace_root)
            ),
        ),
    )
    monkeypatch.setattr(
        session.runner,
        'run_current_batch_until_gate',
        lambda *args, **kwargs: BatchRunSummary(
            conversation_summary=ConversationSummary(
                conversation_id='execution-conv',
                execution_status='paused',
                event_count=1,
                workspace_root=str(session.bootstrap.workspace_root),
                persistence_dir=str(session.report_root),
            ),
            gate_satisfied=True,
            pause_reason='batch_gate_satisfied',
            timed_out=False,
        ),
    )

    session._run_autonomous_execution_loop(
        message=DEFAULT_AUTONOMOUS_GOAL,
        delegate_plan={'batches': []},
    )

    before_batch = session.hook_events_dir / 'before_batch__b1.json'
    after_executor = session.hook_events_dir / 'after_executor__b1.json'
    after_batch_gate = session.hook_events_dir / 'after_batch_gate__b1.json'
    assert before_batch.is_file()
    assert after_executor.is_file()
    assert after_batch_gate.is_file()
    after_gate_payload = json.loads(after_batch_gate.read_text(encoding='utf-8'))
    assert after_gate_payload['gate_satisfied'] is True


def test_execution_orchestrator_condenser_attached_by_default(
    monkeypatch, tmp_path: Path
):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    monkeypatch.delenv('FPGA_FLOW_DISABLE_EXECUTION_CONDENSER', raising=False)
    bootstrap = RuntimeBootstrap.build(
        persistence_dir=tmp_path / 'conversations',
        system_goal=DEFAULT_AUTONOMOUS_GOAL,
    )
    factory = SdkAgentFactory(bootstrap)
    agent = factory.create_execution_orchestrator()
    assert getattr(agent, 'condenser', None) is not None


def test_execution_orchestrator_condenser_disabled(monkeypatch, tmp_path: Path):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    monkeypatch.setenv('FPGA_FLOW_DISABLE_EXECUTION_CONDENSER', '1')
    bootstrap = RuntimeBootstrap.build(
        persistence_dir=tmp_path / 'conversations',
        system_goal=DEFAULT_AUTONOMOUS_GOAL,
    )
    factory = SdkAgentFactory(bootstrap)
    agent = factory.create_execution_orchestrator()
    assert getattr(agent, 'condenser', None) is None


def test_autonomous_execution_loop_recovers_post_run_repair_receipt(
    monkeypatch, tmp_path: Path
):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(
        persistence_dir=tmp_path / 'conversations',
        system_goal=DEFAULT_AUTONOMOUS_GOAL,
    )
    session = ExecutionSession.create(
        bootstrap,
        conversation_id=uuid4(),
        focus_module_id='aes128_encrypt_core',
    )
    generation_plan = session._prepare_generation_artifacts()
    generation_entry = next(
        entry for entry in generation_plan['nodes'] if entry['module_id'] == 'aes_sbox'
    )
    workspace_root = Path(generation_entry['workspace_root'])
    node = next(
        candidate
        for candidate in bootstrap.plan_dag.nodes
        if candidate.module_id == 'aes_sbox'
    )
    workspace_record = load_workspace_record(workspace_root).model_copy(
        update={'state': NodeWorkspaceState.REPAIRING, 'validation_runs': 1}
    )
    write_workspace_record(workspace_record)
    generation_result_path = write_generation_result(
        workspace_record=workspace_record,
        node=node,
        validation_status='failed',
        promoted=False,
        changed_files=[],
        checkpoint_summary={},
        missing_checkpoints=['CHK_SBOX_MATCH'],
        failed_checkpoints=[],
        recommended_mode='repair',
    )
    write_repair_request(
        workspace_record=workspace_record,
        node=node,
        generation_result_path=generation_result_path,
        missing_checkpoints=['CHK_SBOX_MATCH'],
        failed_checkpoints=[],
        rerun_command='python -m MultiAgent_FPGA.fpga_flow run-node aes_sbox',
    )

    draft_tb_path = workspace_root / 'draft' / 'tb' / 'aes_sbox_tb.cpp'
    draft_tb_path.write_text(
        '\n'.join(
            [
                '#include <verilated.h>',
                '#include <iostream>',
                '#include "Vaes_sbox.h"',
                'int main(int argc, char** argv) {',
                '    Verilated::commandArgs(argc, argv);',
                '    Vaes_sbox dut;',
                '    dut.eval();',
                '    std::cout << "CHECKPOINT|CHK_SBOX_MATCH|PASS|known_answer" << std::endl;',
                '    return 0;',
                '}',
                '',
            ]
        ),
        encoding='utf-8',
    )

    current_batch = {
        'batch_id': 'generation_layer_1_1_repair_1',
        'phase': 'repair_edit',
        'tasks': [
            {
                'request': {
                    'workspace_root': str(workspace_root),
                    'result_paths': {
                        'edit_receipt': str(workspace_root / 'edit_receipt.json')
                    },
                }
            }
        ],
    }

    protocol_violations: list[str | None] = []

    def fake_collect_existing_generation_summary():
        return {'modules': {}, 'integration': {'status': 'missing'}}

    def fake_collect_fragility_memory():
        return None

    def fake_evaluate_workflow_gate(
        *,
        delegate_plan,
        processed_batch_ids,
        deterministic_summary,
        protocol_violation,
        integration_attempts,
    ):
        del delegate_plan, deterministic_summary, integration_attempts
        protocol_violations.append(protocol_violation)
        if not processed_batch_ids:
            return {'decision': 'continue'}
        return {
            'decision': 'success',
            'primary_sink': 'aes128_encrypt_core',
            'required_modules': ['aes_sbox'],
            'next_batch_ids': [],
            'integration_status': 'passed',
        }

    def fake_next_eligible_autonomous_batch(*, delegate_plan, processed_batch_ids):
        del delegate_plan
        if processed_batch_ids:
            return None, []
        return current_batch, []

    def fake_build_autonomous_batch_message(
        *, base_message, current_batch, workflow_gate
    ):
        del base_message, current_batch, workflow_gate
        return 'run current batch'

    def fake_run_current_batch_until_gate(
        conversation,
        message,
        *,
        batch_gate,
        timeout_s=180.0,
        poll_interval_s=0.2,
        max_turns=None,
    ):
        del conversation, message, batch_gate, timeout_s, poll_interval_s, max_turns
        return BatchRunSummary(
            conversation_summary=ConversationSummary(
                conversation_id='execution-conv',
                execution_status='paused',
                event_count=1,
                workspace_root=str(session.bootstrap.workspace_root),
                persistence_dir=str(session.report_root),
            ),
            gate_satisfied=False,
            pause_reason='timeout',
            timed_out=True,
        )

    monkeypatch.setattr(
        session,
        '_collect_existing_generation_summary',
        fake_collect_existing_generation_summary,
    )
    monkeypatch.setattr(
        session,
        '_collect_fragility_memory',
        fake_collect_fragility_memory,
    )
    monkeypatch.setattr(
        session,
        '_evaluate_workflow_gate',
        fake_evaluate_workflow_gate,
    )
    monkeypatch.setattr(
        session,
        '_next_eligible_autonomous_batch',
        fake_next_eligible_autonomous_batch,
    )
    monkeypatch.setattr(
        session,
        '_build_autonomous_batch_message',
        fake_build_autonomous_batch_message,
    )

    def fake_create_execution_conversation(
        *,
        conversation_id=None,
        persistence_dir=None,
        delete_on_close=True,
        max_iteration_per_run=100,
    ):
        del persistence_dir, delete_on_close, max_iteration_per_run
        cid = conversation_id or uuid4()
        return SimpleNamespace(
            state=SimpleNamespace(
                id=cid,
                execution_status='idle',
                events=[],
                persistence_dir=str(session.report_root),
            ),
            workspace=SimpleNamespace(
                working_dir=str(session.bootstrap.workspace_root)
            ),
        )

    monkeypatch.setattr(
        session.runner,
        'create_execution_conversation',
        fake_create_execution_conversation,
    )
    monkeypatch.setattr(
        session.runner,
        'run_current_batch_until_gate',
        fake_run_current_batch_until_gate,
    )

    (
        execution_summary,
        _deterministic_summary,
        workflow_gate,
        batch_history,
        _finalizer,
    ) = session._run_autonomous_execution_loop(
        message=DEFAULT_AUTONOMOUS_GOAL,
        delegate_plan={'batches': []},
    )

    assert protocol_violations == [None, None]
    assert execution_summary.execution_status == 'idle'
    assert workflow_gate['decision'] == 'success'
    assert batch_history[0]['status'] == 'completed'
    assert batch_history[0]['pause_reason'] == 'post_run_gate_satisfied'
    assert (workspace_root / 'edit_receipt.json').is_file()


def test_autonomous_batch_timeout_is_extended_for_primary_sink(
    tmp_path: Path, monkeypatch
):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(
        persistence_dir=tmp_path / 'conversations',
        system_goal=DEFAULT_AUTONOMOUS_GOAL,
    )
    session = ExecutionSession.create(
        bootstrap,
        conversation_id=uuid4(),
        focus_module_id='aes128_encrypt_core',
    )

    top_batch = {
        'batch_id': 'generation_layer_3_1_aes128_encrypt_core_repair_1',
        'phase': 'repair_edit',
        'tasks': [{'request': {'module_id': 'aes128_encrypt_core'}}],
    }
    leaf_batch = {
        'batch_id': 'generation_layer_1_1_aes_sbox_repair_1',
        'phase': 'repair_edit',
        'tasks': [{'request': {'module_id': 'aes_sbox'}}],
    }
    integration_batch = {'batch_id': 'integration', 'phase': 'integration'}

    assert session._autonomous_batch_timeout_s(top_batch) == 600.0
    revalidate_batch = {
        'batch_id': 'generation_layer_3_1_aes128_encrypt_core_revalidate_2',
        'phase': 'revalidate',
        'tasks': [{'request': {'module_id': 'aes128_encrypt_core'}}],
    }
    assert session._autonomous_batch_timeout_s(revalidate_batch) == 600.0
    assert session._autonomous_batch_timeout_s(leaf_batch) == 420.0
    assert session._autonomous_batch_timeout_s(integration_batch) == 300.0


def test_run_node_missing_edit_receipt_does_not_consume_validation_budget(
    tmp_path: Path,
):
    spec_ir, plan_dag, _ = _synthesized_context()
    node = plan_dag.nodes[0]
    workspace_root = tmp_path / node.module_id
    workspace = initialize_node_workspace(
        spec_ir=spec_ir,
        plan_dag=plan_dag,
        node=node,
        workspace_root=workspace_root,
    )
    workspace = increment_validation_runs(workspace).model_copy(
        update={'state': NodeWorkspaceState.REPAIRING}
    )
    write_workspace_record(workspace)

    generation_result_path = write_generation_result(
        workspace_record=workspace,
        node=node,
        validation_status='failed',
        promoted=False,
        changed_files=[],
        checkpoint_summary={},
        missing_checkpoints=['CHK_SBOX_MATCH'],
        failed_checkpoints=[],
        recommended_mode='repair',
    )
    write_repair_request(
        workspace_record=workspace,
        node=node,
        generation_result_path=generation_result_path,
        missing_checkpoints=['CHK_SBOX_MATCH'],
        failed_checkpoints=[],
        rerun_command='python -m MultiAgent_FPGA.fpga_flow run-node aes_sbox --workspace-root /tmp/work --strict-validation',
    )

    before = load_workspace_record(workspace_root)
    summary = _run_node(
        node.module_id,
        None,
        workspace_root=str(workspace_root),
        promoted_root=str(workspace_promoted_root(workspace_root)),
        increment_workspace_validation=True,
    )
    after = load_workspace_record(workspace_root)
    generation_payload = json.loads(
        (workspace_root / 'generation_result.json').read_text(encoding='utf-8')
    )

    assert summary['error']['type'] == 'RepairContractViolation'
    assert before.validation_runs == 1
    assert after.validation_runs == 1
    assert after.state == NodeWorkspaceState.REPAIRING
    assert generation_payload['workspace_state'] == 'repairing'
    assert generation_payload['repair_attempts'] == 0


def test_execution_session_writes_framework_owned_autonomous_reports(
    monkeypatch, tmp_path: Path
):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(
        persistence_dir=tmp_path / 'conversations',
        system_goal=DEFAULT_AUTONOMOUS_GOAL,
    )
    conversation_id = uuid4()

    class FakeConversation:
        def __init__(
            self, *, conversation_id, persistence_dir: Path, workspace_root: Path
        ) -> None:
            conversation_dir = persistence_dir / conversation_id.hex
            conversation_dir.mkdir(parents=True, exist_ok=True)
            (conversation_dir / 'base_state.json').write_text(
                '{"id":"fake"}',
                encoding='utf-8',
            )
            self.state = SimpleNamespace(
                id=conversation_id,
                execution_status='idle',
                events=[],
                persistence_dir=str(conversation_dir),
            )
            self.workspace = SimpleNamespace(working_dir=str(workspace_root))

        def close(self) -> None:
            return None

    def fake_create_conversation(
        self,
        *,
        conversation_id=None,
        persistence_dir=None,
        delete_on_close=True,
        max_iteration_per_run=100,
    ):
        return FakeConversation(
            conversation_id=conversation_id,
            persistence_dir=Path(persistence_dir),
            workspace_root=self.bootstrap.workspace_root,
        )

    def fake_execution_loop(self, *, message, delegate_plan):
        deterministic_summary = {
            'conversation_id': str(conversation_id),
            'focus_module_id': 'aes128_encrypt_core',
            'modules': {
                'aes_sbox': {'module_id': 'aes_sbox', 'promoted': True},
                'aes_key_schedule_128': {
                    'module_id': 'aes_key_schedule_128',
                    'promoted': True,
                },
                'aes_round_transform': {
                    'module_id': 'aes_round_transform',
                    'promoted': True,
                },
                'aes128_encrypt_core': {
                    'module_id': 'aes128_encrypt_core',
                    'promoted': True,
                },
            },
            'integration': {'status': 'passed', 'result_path': '/tmp/integration'},
        }
        workflow_gate = {
            'decision': 'success',
            'primary_sink': 'aes128_encrypt_core',
            'required_modules': [
                'aes_sbox',
                'aes_key_schedule_128',
                'aes_round_transform',
                'aes128_encrypt_core',
            ],
            'next_batch_ids': [],
        }
        return (
            ConversationSummary(
                conversation_id=str(conversation_id),
                execution_status='paused',
                event_count=1,
                workspace_root=str(self.bootstrap.workspace_root),
                persistence_dir=str(self.report_root),
            ),
            deterministic_summary,
            workflow_gate,
            [],
            None,
        )

    def fake_run_finalizer(
        self, *, message, deterministic_summary, workflow_gate, batch_history
    ):
        return ConversationSummary(
            conversation_id='finalizer-conv',
            execution_status='finished',
            event_count=1,
            workspace_root=str(self.bootstrap.workspace_root),
            persistence_dir=str(self.report_root / 'finalizer'),
        ), {
            'status': 'success',
            'source': 'finalizer',
            'content': 'Accepted.',
        }

    monkeypatch.setattr(
        ConversationRunner, 'create_execution_conversation', fake_create_conversation
    )
    monkeypatch.setattr(
        ExecutionSession,
        '_run_autonomous_execution_loop',
        fake_execution_loop,
    )
    monkeypatch.setattr(
        ExecutionSession,
        '_run_autonomous_finalizer',
        fake_run_finalizer,
    )

    session = ExecutionSession.create(
        bootstrap,
        conversation_id=conversation_id,
        focus_module_id='aes128_encrypt_core',
    )
    summary = session.run(DEFAULT_AUTONOMOUS_GOAL)

    assert summary.execution_mode == 'autonomous-generate'
    # 21 batches with L2 disabled: top module (aes128_encrypt_core) gets 3 repair
    # rounds via repair_budget_for_node() instead of the global threshold of 2.
    assert summary.delegate_batch_count == 21
    assert Path(summary.delegate_plan_path).is_file()
    assert session.batch_plan_path.is_file()
    assert session.spec_ir_artifact_path.is_file()
    assert session.plan_dag_artifact_path.is_file()
    assert session.fragility_memory_path.is_file()
    report_tree_payload = json.loads(
        session.report_tree_path.read_text(encoding='utf-8')
    )
    assert (
        report_tree_payload['manual_command_policy']['manual_executor_command']
        == 'Manual reproduction only. Runtime dispatch uses executor_kind plus executor_inputs.'
    )
    assert 'batch_plan' in report_tree_payload['paths']
    assert 'fragility_memory' in report_tree_payload['paths']
    assert 'workflow_gate' in report_tree_payload['paths']
    assert 'batch_history' in report_tree_payload['paths']
    assert 'current_batch_snapshot' in report_tree_payload['paths']
    assert 'finalizer_input' in report_tree_payload['paths']
    session_payload = json.loads(
        session.session_summary_path.read_text(encoding='utf-8')
    )
    assert session_payload['conversation_summary']['execution_status'] == 'finished'
    assert session_payload['execution_conversation_summary']['execution_status'] == (
        'paused'
    )
    assert session_payload['finalizer_conversation_summary']['execution_status'] == (
        'finished'
    )
    assert session_payload['finalizer_conversation_id'] == 'finalizer-conv'


def test_autonomous_generate_marks_protocol_violation_blocked(
    monkeypatch, tmp_path: Path
):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(
        persistence_dir=tmp_path / 'conversations',
        system_goal=DEFAULT_AUTONOMOUS_GOAL,
    )
    conversation_id = uuid4()

    class FakeConversation:
        def __init__(
            self, *, conversation_id, persistence_dir: Path, workspace_root: Path
        ) -> None:
            conversation_dir = persistence_dir / conversation_id.hex
            conversation_dir.mkdir(parents=True, exist_ok=True)
            (conversation_dir / 'base_state.json').write_text(
                '{"id":"fake"}',
                encoding='utf-8',
            )
            self.state = SimpleNamespace(
                id=conversation_id,
                execution_status='idle',
                events=[],
                persistence_dir=str(conversation_dir),
            )
            self.workspace = SimpleNamespace(working_dir=str(workspace_root))

        def close(self) -> None:
            return None

    def fake_create_conversation(
        self,
        *,
        conversation_id=None,
        persistence_dir=None,
        delete_on_close=True,
        max_iteration_per_run=100,
    ):
        return FakeConversation(
            conversation_id=conversation_id,
            persistence_dir=Path(persistence_dir),
            workspace_root=self.bootstrap.workspace_root,
        )

    blocked_generation_summary = {
        'conversation_id': str(conversation_id),
        'focus_module_id': 'aes128_encrypt_core',
        'modules': {
            'aes_sbox': {'module_id': 'aes_sbox', 'promoted': True},
            'aes_key_schedule_128': {
                'module_id': 'aes_key_schedule_128',
                'promoted': False,
                'workspace_state': 'repairing',
            },
            'aes_round_transform': {
                'module_id': 'aes_round_transform',
                'promoted': False,
                'workspace_state': 'repairing',
            },
            'aes128_encrypt_core': {
                'module_id': 'aes128_encrypt_core',
                'promoted': False,
                'workspace_state': 'missing',
            },
        },
        'integration': {'status': 'missing', 'result_path': None, 'campaign_count': 0},
    }

    blocked_gate = {
        'decision': 'blocked',
        'primary_sink': 'aes128_encrypt_core',
        'required_modules': [
            'aes_sbox',
            'aes_key_schedule_128',
            'aes_round_transform',
            'aes128_encrypt_core',
        ],
        'pending_modules': [
            'aes_key_schedule_128',
            'aes_round_transform',
            'aes128_encrypt_core',
        ],
        'blocked_modules': [],
        'integration_status': 'missing',
        'reasons': ['execution_conversation_finished'],
        'protocol_violation': 'execution_conversation_finished',
    }

    monkeypatch.setattr(
        ConversationRunner, 'create_execution_conversation', fake_create_conversation
    )
    monkeypatch.setattr(
        ExecutionSession,
        '_run_autonomous_execution_loop',
        lambda self, *, message, delegate_plan: (
            ConversationSummary(
                conversation_id=str(conversation_id),
                execution_status='finished',
                event_count=1,
                workspace_root=str(self.bootstrap.workspace_root),
                persistence_dir=str(self.report_root),
            ),
            blocked_generation_summary,
            blocked_gate,
            [],
            None,
        ),
    )
    monkeypatch.setattr(
        ExecutionSession,
        '_run_autonomous_finalizer',
        lambda self, *, message, deterministic_summary, workflow_gate, batch_history: (
            ConversationSummary(
                conversation_id='finalizer-blocked',
                execution_status='finished',
                event_count=1,
                workspace_root=str(self.bootstrap.workspace_root),
                persistence_dir=str(self.report_root / 'finalizer'),
            ),
            {
                'status': 'blocked',
                'content': 'Execution protocol violated.',
                'workflow_gate': workflow_gate,
            },
        ),
    )

    session = ExecutionSession.create(
        bootstrap,
        conversation_id=conversation_id,
        focus_module_id='aes128_encrypt_core',
    )
    summary = session.run(DEFAULT_AUTONOMOUS_GOAL)

    assert summary.conversation_summary.execution_status == 'finished_blocked'
    session_payload = json.loads(
        session.session_summary_path.read_text(encoding='utf-8')
    )
    assert session_payload['execution_conversation_summary']['execution_status'] == (
        'finished'
    )
    assert (
        session_payload['conversation_summary']['execution_status']
        == 'finished_blocked'
    )
    final_acceptance = json.loads(
        session.final_acceptance_summary_path.read_text(encoding='utf-8')
    )
    assert final_acceptance['status'] == 'blocked'
    assert final_acceptance['workflow_gate']['protocol_violation'] == (
        'execution_conversation_finished'
    )
    assert blocked_gate['pending_modules'] == [
        'aes_key_schedule_128',
        'aes_round_transform',
        'aes128_encrypt_core',
    ]


def test_build_parser_defaults_to_autonomous_generate():
    parser = build_parser()
    args = parser.parse_args(['run-aes-mvp'])
    assert not hasattr(args, 'execution_mode')


def test_cli_parser_exposes_generate_node_and_run_node_internal_interfaces():
    parser = build_parser()
    node_args = parser.parse_args(
        [
            'generate-node',
            'aes_sbox',
            '--workspace-root',
            '/tmp/work',
            '--strict-validation',
        ]
    )
    run_node_args = parser.parse_args(
        [
            'run-node',
            'aes_sbox',
            '--workspace-root',
            '/tmp/work',
            '--promoted-root',
            '/tmp/promoted',
            '--strict-validation',
        ]
    )
    repair_args = parser.parse_args(
        [
            'record-repair-edit',
            'aes_sbox',
            '--workspace-root',
            '/tmp/work',
            '--strict',
        ]
    )
    integration_args = parser.parse_args(
        [
            'run-integration',
            '--promoted-root',
            '/tmp/promoted',
            '--output-root',
            '/tmp/integration',
        ]
    )

    assert node_args.command == 'generate-node'
    assert node_args.workspace_root == '/tmp/work'
    assert node_args.strict_validation is True
    assert run_node_args.command == 'run-node'
    assert run_node_args.strict_validation is True
    assert run_node_args.promoted_root == '/tmp/promoted'
    assert repair_args.command == 'record-repair-edit'
    assert repair_args.workspace_root == '/tmp/work'
    assert repair_args.strict is True
    assert integration_args.command == 'run-integration'
    assert integration_args.promoted_root == '/tmp/promoted'
    assert integration_args.output_root == '/tmp/integration'


def test_autonomous_delegate_plan_materializes_workspace_contracts(
    monkeypatch, tmp_path: Path
):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(
        persistence_dir=tmp_path / 'conversations',
        system_goal=DEFAULT_AUTONOMOUS_GOAL,
    )
    session = ExecutionSession.create(bootstrap, conversation_id=uuid4())

    delegate_plan = session._build_delegate_plan()  # type: ignore[attr-defined]

    assert delegate_plan['execution_mode'] == 'autonomous-generate'
    assert Path(session.generation_plan_path).is_file()
    assert Path(session.brief_generation_summary_path).is_file()
    assert Path(session.batch_plan_path).is_file()
    assert (
        len(delegate_plan['batches']) == 21
    )  # top module gets 3 repair rounds via repair_budget_for_node()
    assert delegate_plan['batches'][0]['tasks'][0]['mode'] == 'generate'
    assert delegate_plan['batches'][0]['phase'] == 'generate_validate'
    assert delegate_plan['batches'][1]['tasks'][0]['mode'] == 'repair'
    assert delegate_plan['batches'][1]['phase'] == 'repair_edit'
    assert delegate_plan['batches'][1]['repair_round'] == 1
    assert (
        delegate_plan['batches'][1]['tasks'][0]['worker_id']
        == 'module_repair__aes_sbox'
    )
    assert delegate_plan['batches'][1]['spawn']['ids'] == ['module_repair__aes_sbox']
    assert (
        delegate_plan['batches'][1]['condition']['type']
        == 'any_generation_result_requires_repair'
    )
    assert delegate_plan['batches'][2]['tasks'][0]['mode'] == 'validate'
    assert delegate_plan['batches'][2]['phase'] == 'revalidate'
    assert delegate_plan['batches'][2]['repair_round'] == 1
    assert delegate_plan['batches'][2]['spawn']['ids'] == ['module_build__aes_sbox']
    assert delegate_plan['batches'][2]['spawn']['agent_types'] == [
        'module_worker__aes_sbox'
    ]
    assert (
        delegate_plan['batches'][2]['condition']['type']
        == 'any_generation_result_requires_repair'
    )
    assert delegate_plan['batches'][3]['phase'] == 'repair_edit'
    assert delegate_plan['batches'][3]['repair_round'] == 2
    assert delegate_plan['batches'][3]['spawn']['ids'] == ['module_repair__aes_sbox']
    assert delegate_plan['batches'][4]['phase'] == 'revalidate'
    assert delegate_plan['batches'][4]['repair_round'] == 2
    assert (
        delegate_plan['batches'][5]['batch_id']
        == 'generation_layer_2_1_generate_validate'
    )
    assert delegate_plan['batches'][6]['batch_id'] == (
        'generation_layer_2_1_aes_key_schedule_128_repair_1'
    )
    assert delegate_plan['batches'][6]['spawn']['ids'] == [
        'module_repair__aes_key_schedule_128'
    ]
    assert delegate_plan['batches'][10]['batch_id'] == (
        'generation_layer_2_1_aes_round_transform_repair_1'
    )
    assert delegate_plan['batches'][-1]['tasks'][0]['mode'] == 'validate'

    first_task = delegate_plan['batches'][0]['tasks'][0]
    request = first_task['request']
    assert request['workspace_root'].startswith(str(session.report_root))
    assert (
        'python -m MultiAgent_FPGA.fpga_flow generate-node'
        in request['manual_executor_command']
    )
    assert request['result_paths']['generation_result'].endswith(
        'generation_result.json'
    )
    assert request['result_paths']['workspace_state'].endswith('workspace_state.json')
    assert request['result_paths']['validation_summary'].endswith(
        'validation_summary.json'
    )
    assert request['result_paths']['validation_error'].endswith('validation_error.json')
    assert request['result_paths']['repair_request'].endswith('repair_request.json')
    assert request['result_paths']['edit_receipt'].endswith('edit_receipt.json')
    repair_task = delegate_plan['batches'][1]['tasks'][0]
    assert 'Task contract file:' in repair_task['prompt']
    assert 'Phase: repair_edit' in repair_task['prompt']
    assert (
        'Repair phase: use repair_request.primary_target_file' in repair_task['prompt']
    )
    assert 'run-integration' in delegate_plan['manual_integration_command']
    assert '--promoted-root' in delegate_plan['manual_integration_command']
    assert '--output-root' in delegate_plan['manual_integration_command']
    assert request['contract_paths']['design_brief'].endswith('design_brief.json')
    assert 'generate-node' in request['manual_executor_command']
    assert '--strict-validation' in request['manual_executor_command']
    assert Path(first_task['request_path']).is_file()
    request_contract = json.loads(
        Path(first_task['request_path']).read_text(encoding='utf-8')
    )
    assert (
        request_contract['manual_command_policy']['manual_receipt_command']
        == 'Manual repair receipt reproduction only. Runtime dispatch uses preflight_record_repair_edit.'
    )

    repair_task = delegate_plan['batches'][1]['tasks'][0]
    assert repair_task['request']['manual_executor_command'] is None
    assert repair_task['request']['preflight_record_repair_edit'] is False
    assert any(
        path.endswith('draft/tb/aes_sbox_tb.cpp')
        for path in repair_task['request']['writable_paths']
    )
    assert repair_task['request']['result_paths']['repair_request'].endswith(
        'repair_request.json'
    )
    assert repair_task['request']['result_paths']['edit_receipt'].endswith(
        'edit_receipt.json'
    )
    assert 'Task contract file:' in repair_task['prompt']
    assert 'Phase: repair_edit' in repair_task['prompt']
    assert (
        'Repair phase: use repair_request.primary_target_file' in repair_task['prompt']
    )

    revalidate_task = delegate_plan['batches'][2]['tasks'][0]
    assert revalidate_task['request']['preflight_record_repair_edit'] is True
    assert 'Task contract file:' in revalidate_task['prompt']
    assert (
        "Advance this phase only through 'run_executor'." in revalidate_task['prompt']
    )

    generation_plan = json.loads(session.generation_plan_path.read_text('utf-8'))
    assert generation_plan['nodes'][0]['module_id'] == 'aes_sbox'
    assert Path(
        generation_plan['nodes'][0]['contract_paths']['module_contract']
    ).is_file()
    assert generation_plan['nodes'][0]['promoted_targets']
    assert generation_plan['nodes'][0]['repair_request_path'].endswith(
        'repair_request.json'
    )

    session.conversation.close()
