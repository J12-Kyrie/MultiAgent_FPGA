from __future__ import annotations

import json

from MultiAgent_FPGA.aes_mvp.agents import (
    build_finalizer_orchestrator_spec,
    build_l2_campaign_spec,
    build_module_worker_spec,
    build_repair_worker_spec,
    build_workflow_orchestrator_spec,
)
from MultiAgent_FPGA.aes_mvp.artifacts import (
    NodeWorkspaceState,
    ValidationFailurePhase,
)
from MultiAgent_FPGA.aes_mvp.generation import (
    build_module_contract,
    build_module_design_brief,
    build_testbench_contract,
    evaluate_validation_result,
    increment_validation_runs,
    initialize_node_workspace,
    load_repair_contract,
    promote_workspace,
    verify_repair_edit,
    write_generation_result,
    write_repair_request,
    write_validation_error,
    write_validation_summary,
    write_workspace_record,
)
from MultiAgent_FPGA.aes_mvp.llm_profiles import (
    DEEPSEEK_BASE_URL,
    DEEPSEEK_CHAT_MODEL,
    DEEPSEEK_REASONER_MODEL,
    DEEPSEEK_RESOLVED_MODEL,
    SDK_DEEPSEEK_MODEL,
    SDK_REASONING_EFFORT_FAST,
    SDK_REASONING_EFFORT_THINKING,
    build_sdk_deepseek_official_fast_kwargs,
    build_sdk_deepseek_official_thinking_kwargs,
    parse_deepseek_response,
    run_deepseek_preflight,
    run_deepseek_preflight_suite,
)
from MultiAgent_FPGA.aes_mvp.memory import MemoryStore
from MultiAgent_FPGA.aes_mvp.orchestrator import AESWorkflowOrchestrator
from MultiAgent_FPGA.aes_mvp.policy import (
    LLMProfileName,
    OrchestratorState,
    SubagentPolicy,
)
from MultiAgent_FPGA.aes_mvp.prompts import (
    build_execution_orchestrator_prompt,
    build_l2_campaign_prompt,
    build_module_worker_prompt,
)
from MultiAgent_FPGA.aes_mvp.skill_refs import (
    get_all_skill_refs,
    get_documentation_skill_refs,
    get_memory_skill_refs,
    get_runtime_skill_refs,
)
from MultiAgent_FPGA.aes_mvp.synthesis import (
    DEFAULT_AUTONOMOUS_GOAL,
    IntegrationReadinessResolver,
    synthesize_agent_execution_policy,
    synthesize_integration_manifest,
    synthesize_plan_dag,
    synthesize_spec_ir,
)


def _synthesized_context():
    spec_ir = synthesize_spec_ir(system_goal=DEFAULT_AUTONOMOUS_GOAL)
    plan_dag = synthesize_plan_dag(spec_ir)
    manifest = synthesize_integration_manifest(spec_ir, plan_dag)
    return spec_ir, plan_dag, manifest


def test_synthesized_spec_ir_matches_autonomous_aes_scope():
    spec_ir, _, _ = _synthesized_context()
    assert spec_ir.algorithm == 'AES'
    assert spec_ir.variant == 'AES-128'
    assert spec_ir.operation == 'encrypt'
    assert spec_ir.interface_style == 'block_handshake'
    assert spec_ir.microarchitecture == 'iterative_10_round'
    assert spec_ir.latency_target_cycles == 11
    assert spec_ir.system_goal == DEFAULT_AUTONOMOUS_GOAL


def test_synthesized_plan_dag_has_dynamic_design_context_and_sink():
    spec_ir, plan_dag, manifest = _synthesized_context()
    resolver = IntegrationReadinessResolver()
    assert spec_ir.module_candidates == [node.module_id for node in plan_dag.nodes]
    assert all(node.design_context for node in plan_dag.nodes)
    assert resolver.select_primary_sink(plan_dag).module_id == manifest.top_module
    assert resolver.ready_sink_modules(
        plan_dag,
        promoted_modules={node.module_id for node in plan_dag.nodes},
    ) == ['aes128_encrypt_core']


def test_synthesized_policy_routes_thinking_and_subagents():
    policy = synthesize_agent_execution_policy()
    assert (
        policy.profile_for_state(OrchestratorState.SPEC_INTAKE)
        == LLMProfileName.DEEPSEEK_OFFICIAL_THINKING
    )
    assert (
        policy.profile_for_state(OrchestratorState.MODULE_L0)
        == LLMProfileName.DEEPSEEK_OFFICIAL_FAST
    )
    assert (
        policy.subagent_policy_for_state(OrchestratorState.PLANNING)
        == SubagentPolicy.FORBIDDEN
    )
    assert (
        policy.subagent_policy_for_state(OrchestratorState.MODULE_L2_OPTIONAL)
        == SubagentPolicy.L2_CAMPAIGN_ALLOWED
    )


def test_prompts_encode_autonomous_generate_rules():
    _, plan_dag, _ = _synthesized_context()
    node = plan_dag.nodes[0]
    policy = synthesize_agent_execution_policy()

    orchestrator_prompt = build_execution_orchestrator_prompt()
    module_prompt = build_module_worker_prompt(node)
    l2_prompt = build_l2_campaign_prompt(
        plan_dag.nodes[-1],
        profile='rand_small',
        vecfile='vectors/aes128/aes128_encrypt_core_l2_rand_small.txt',
        cases=32,
        seed=1001,
    )

    assert 'execution-phase Workflow Orchestrator' in orchestrator_prompt
    assert (
        'The framework, not you, owns batch progression and workflow completion'
        in orchestrator_prompt
    )
    assert 'Never exceed the provided max_children limit' in orchestrator_prompt
    assert 'promote only into session-scoped promoted artifacts' in orchestrator_prompt
    assert 'Do not call finish' in orchestrator_prompt
    assert 'mode: generate, validate, repair, or l2_execute' in module_prompt
    assert 'generation_result.json, workspace_state.json' in module_prompt
    assert 'repair_request.json is present' in module_prompt
    assert "Use the 'run_executor' tool as the only allowed way" in module_prompt
    assert 'Do not edit repository canonical RTL/TB files directly' in module_prompt
    assert "Progress the campaign only through 'run_executor'" in l2_prompt
    assert policy.should_escalate(2) is True
    assert policy.should_escalate(1, cross_module_issue=True) is True


def test_aes128_encrypt_core_module_worker_prompt_defers_detail_to_skills():
    _, plan_dag, _ = _synthesized_context()
    node = next(n for n in plan_dag.nodes if n.module_id == 'aes128_encrypt_core')
    default_node = next(n for n in plan_dag.nodes if n.module_id == 'aes_sbox')
    prompt = build_module_worker_prompt(node)
    default_prompt = build_module_worker_prompt(default_node)
    assert 'Module Worker SubAgent for aes128_encrypt_core' in prompt
    assert 'aes_tb_common.hpp' in prompt
    assert 'aes-tb-contracts' in prompt

    # Both prompts now inline memory content; verify the specialized prompt
    # has fewer non-memory instruction lines than the default.
    def _non_memory_lines(p: str) -> list[str]:
        in_memory = False
        out: list[str] = []
        for line in p.splitlines():
            if line.startswith('=== MEMORY:'):
                in_memory = True
            elif line.startswith('=== END MEMORY'):
                in_memory = False
            elif not in_memory:
                out.append(line)
        return out

    assert len(_non_memory_lines(prompt)) <= len(_non_memory_lines(default_prompt))


def test_deepseek_official_profiles_are_pinned_for_tool_capable_runtime(monkeypatch):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    sdk_thinking = build_sdk_deepseek_official_thinking_kwargs()
    sdk_fast = build_sdk_deepseek_official_fast_kwargs()

    assert sdk_thinking['model'] == SDK_DEEPSEEK_MODEL
    assert sdk_fast['model'] == SDK_DEEPSEEK_MODEL
    assert sdk_thinking['model_canonical_name'] == DEEPSEEK_RESOLVED_MODEL
    assert sdk_fast['model_canonical_name'] == DEEPSEEK_RESOLVED_MODEL
    assert sdk_thinking['base_url'] == DEEPSEEK_BASE_URL
    assert sdk_fast['base_url'] == DEEPSEEK_BASE_URL
    # M3: profiles must be differentiated by reasoning_effort
    assert sdk_thinking['reasoning_effort'] == SDK_REASONING_EFFORT_THINKING
    assert sdk_fast['reasoning_effort'] == SDK_REASONING_EFFORT_FAST
    assert sdk_thinking['reasoning_effort'] != sdk_fast['reasoning_effort']


def test_deepseek_official_profiles_record_reasoner_but_do_not_runtime_route_to_it():
    assert DEEPSEEK_REASONER_MODEL == 'deepseek-reasoner'
    assert DEEPSEEK_CHAT_MODEL == 'deepseek-chat'


def test_parse_deepseek_response_extracts_optional_reasoning_fields():
    parsed = parse_deepseek_response(
        {
            'model': DEEPSEEK_RESOLVED_MODEL,
            'choices': [
                {
                    'message': {
                        'content': 'ok',
                        'reasoning_content': 'trace',
                    }
                }
            ],
            'usage': {
                'completion_tokens_details': {
                    'reasoning_tokens': 64,
                }
            },
        }
    )
    assert parsed.content == 'ok'
    assert parsed.resolved_model == DEEPSEEK_RESOLVED_MODEL
    assert parsed.reasoning_content == 'trace'
    assert parsed.reasoning_tokens == 64


def test_deepseek_preflight_handles_success(monkeypatch):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')

    class FakeResponse:
        def __init__(self, thinking_enabled: bool) -> None:
            self.status_code = 200
            self.ok = True
            self.text = 'ok'
            self._thinking_enabled = thinking_enabled

        def json(self):
            message = {'content': 'ok'}
            usage = {}
            if self._thinking_enabled:
                message['reasoning_content'] = 'trace'
                usage = {'completion_tokens_details': {'reasoning_tokens': 42}}
            return {
                'model': DEEPSEEK_RESOLVED_MODEL,
                'choices': [{'message': message}],
                'usage': usage,
            }

    def fake_post(url, *, headers, json, timeout):
        assert url == f'{DEEPSEEK_BASE_URL}/chat/completions'
        assert headers['Authorization'] == 'Bearer test-secret'
        assert timeout == 60
        return FakeResponse(
            thinking_enabled='internal deliberation' in json['messages'][0]['content']
        )

    monkeypatch.setattr(
        'MultiAgent_FPGA.aes_mvp.llm_profiles.requests.post',
        fake_post,
    )

    fast = run_deepseek_preflight(thinking_enabled=False)
    thinking = run_deepseek_preflight(thinking_enabled=True)
    suite = run_deepseek_preflight_suite()

    assert fast.ok is True
    assert fast.request_model == DEEPSEEK_CHAT_MODEL
    assert fast.resolved_model == DEEPSEEK_RESOLVED_MODEL
    assert fast.reasoning_content is None
    assert thinking.ok is True
    assert thinking.reasoning_content == 'trace'
    assert thinking.reasoning_tokens == 42
    assert suite['request_model'] == DEEPSEEK_CHAT_MODEL
    assert suite['resolved_model'] == DEEPSEEK_RESOLVED_MODEL


def test_deepseek_preflight_handles_provider_errors(monkeypatch):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')

    class FakeErrorResponse:
        status_code = 503
        ok = False
        text = 'provider down'

        @staticmethod
        def json():
            return {'error': {'message': '当前分组无可用渠道'}}

    monkeypatch.setattr(
        'MultiAgent_FPGA.aes_mvp.llm_profiles.requests.post',
        lambda *args, **kwargs: FakeErrorResponse(),
    )

    result = run_deepseek_preflight(thinking_enabled=False)
    assert result.ok is False
    assert result.status_code == 503
    assert result.error == '当前分组无可用渠道'


def test_skill_references_point_to_existing_skill_files():
    refs = get_all_skill_refs()
    assert set(refs) == {
        'verilator_mcp_setup',
        'verilog_verilator',
        'aes_verilator_profile',
        'aes_spec_decomposition',
        'aes_module_patterns',
        'aes_tb_contracts',
        'aes_repair_heuristics',
        'openhands_sdk_bootstrap',
        'openhands_sdk_mcp_integration',
        'openhands_sdk_subagent_delegation',
        'openhands_sdk_observability',
        'aes_memory_sbox',
        'aes_memory_key_schedule',
        'aes_memory_round_transform',
        'aes_memory_encrypt_core',
        'aes_memory_shared',
    }
    assert all(ref.path.is_file() for ref in refs.values())


def test_agent_specs_follow_role_contract():
    _, plan_dag, _ = _synthesized_context()
    node = plan_dag.nodes[0]
    orchestrator_spec = build_workflow_orchestrator_spec()
    module_spec = build_module_worker_spec(node)
    l2_spec = build_l2_campaign_spec(
        plan_dag.nodes[-1],
        profile='rand_small',
        vecfile='vectors/aes128/aes128_encrypt_core_l2_rand_small.txt',
        cases=32,
        seed=1001,
    )

    assert orchestrator_spec.llm_profile == LLMProfileName.DEEPSEEK_OFFICIAL_FAST
    assert module_spec.llm_profile == LLMProfileName.DEEPSEEK_OFFICIAL_FAST
    assert l2_spec.llm_profile == LLMProfileName.DEEPSEEK_OFFICIAL_FAST
    assert node.tb_file in module_spec.writable_paths
    assert 'run_executor' in orchestrator_spec.custom_tools
    assert 'run_executor' in module_spec.custom_tools
    assert 'run_executor' in l2_spec.custom_tools
    assert 'openhands_sdk_subagent_delegation' in orchestrator_spec.skill_keys
    assert 'openhands_sdk_bootstrap' not in orchestrator_spec.skill_keys
    assert 'openhands_sdk_observability' not in orchestrator_spec.skill_keys
    assert 'aes_tb_contracts' in module_spec.skill_keys
    assert 'verilog_verilator' not in module_spec.skill_keys


def test_repair_worker_spec_module_specific_memory():
    spec_sbox = build_repair_worker_spec(module_id='aes_sbox')
    spec_core = build_repair_worker_spec(module_id='aes128_encrypt_core')
    spec_none = build_repair_worker_spec()
    # All repair specs include aes_repair_heuristics as a skill key
    assert 'aes_repair_heuristics' in spec_sbox.skill_keys
    assert 'aes_repair_heuristics' in spec_core.skill_keys
    assert 'aes_repair_heuristics' in spec_none.skill_keys
    # Repair workers do NOT get full memory prompt blocks — the draft files
    # on disk are the current truth and may have been modified by prior repairs.
    assert '=== MEMORY:' not in spec_sbox.system_prompt
    assert '=== MEMORY:' not in spec_core.system_prompt
    assert '=== MEMORY:' not in spec_none.system_prompt
    # Instead they get the REPAIR_MEMORY_DIRECTIVE telling them to trust disk state.
    assert 'on-disk draft files are the current truth' in spec_sbox.system_prompt
    assert 'on-disk draft files are the current truth' in spec_core.system_prompt


def test_finalizer_has_no_skills():
    spec = build_finalizer_orchestrator_spec()
    assert len(spec.skill_keys) == 0


def test_orchestrator_loads_synthesized_defaults_and_routes_module_work():
    orchestrator = AESWorkflowOrchestrator.from_defaults()
    work_order = orchestrator.build_module_work_order(
        'aes_key_schedule_128',
        OrchestratorState.MODULE_DESIGN,
    )
    assert work_order.node.module_id == 'aes_key_schedule_128'
    assert orchestrator.integration_manifest.top_module == 'aes128_encrypt_core'
    assert (
        orchestrator.next_state_after_success(
            OrchestratorState.MODULE_L1,
            requires_l2=True,
        )
        == OrchestratorState.MODULE_L2_OPTIONAL
    )
    trace = orchestrator.describe_state_progression()
    assert trace[0].state == 'SPEC_INTAKE'
    assert trace[-1].state == 'DONE'


def test_generation_artifacts_auto_derive_from_synthesized_spec_and_plan(tmp_path):
    spec_ir, plan_dag, _ = _synthesized_context()
    node = plan_dag.nodes[0]

    module_contract = build_module_contract(
        spec_ir=spec_ir, plan_dag=plan_dag, node=node
    )
    tb_contract = build_testbench_contract(
        spec_ir=spec_ir, plan_dag=plan_dag, node=node
    )
    design_brief = build_module_design_brief(
        spec_ir=spec_ir,
        plan_dag=plan_dag,
        node=node,
    )
    workspace = initialize_node_workspace(
        spec_ir=spec_ir,
        plan_dag=plan_dag,
        node=node,
        workspace_root=tmp_path / node.module_id,
    )

    assert module_contract.module_id == 'aes_sbox'
    assert module_contract.ports[0].name == 'in_byte'
    assert tb_contract.tb_language == 'cpp'
    assert tb_contract.checkpoint_contract == 'CHECKPOINT|CHK_SBOX_MATCH|PASS|<detail>'
    assert 'vecfile' in tb_contract.vector_format.lower()
    assert any(
        'CHECKPOINT|CHK_SBOX_MATCH|PASS|<detail>' in item
        for item in tb_contract.success_rules
    )
    assert any(
        'CHECKPOINT|CHK_SBOX_MATCH|PASS|<detail>' in item
        for item in design_brief.repair_hints
    )
    assert design_brief.implementation_hints
    assert any("8'h00 -> 8'h63" in item for item in design_brief.implementation_hints)
    assert design_brief.repair_hints
    assert design_brief.skill_paths
    assert workspace.state == NodeWorkspaceState.DRAFT_READY
    assert (tmp_path / node.module_id / 'contracts' / 'module_contract.json').is_file()
    assert (tmp_path / node.module_id / 'draft' / 'rtl' / 'aes_sbox.v').is_file()
    assert (tmp_path / node.module_id / 'draft' / 'tb' / 'aes_sbox_tb.cpp').is_file()


def test_generation_result_records_missing_checkpoint_details_and_recommended_mode(
    tmp_path,
):
    spec_ir, plan_dag, _ = _synthesized_context()
    node = plan_dag.nodes[0]
    workspace = initialize_node_workspace(
        spec_ir=spec_ir,
        plan_dag=plan_dag,
        node=node,
        workspace_root=tmp_path / node.module_id,
    )
    workspace = increment_validation_runs(workspace)
    result_path = write_generation_result(
        workspace_record=workspace,
        node=node,
        validation_status='failed',
        failure_phase=ValidationFailurePhase.CHECKPOINT_MISSING,
        promoted=False,
        changed_files=[],
        checkpoint_summary={},
        missing_checkpoints=['CHK_SBOX_MATCH'],
        failed_checkpoints=[],
        recommended_mode='repair',
    )
    payload = json.loads(result_path.read_text(encoding='utf-8'))

    assert payload['validation_paths']['module_run_result'].endswith(
        'module_run_result.json'
    )
    assert payload['validation_paths']['validation_summary'].endswith(
        'validation_summary.json'
    )
    assert payload['validation_paths']['validation_error'].endswith(
        'validation_error.json'
    )
    assert payload['missing_checkpoints'] == ['CHK_SBOX_MATCH']
    assert payload['failed_checkpoints'] == []
    assert payload['failure_phase'] == 'checkpoint_missing'
    assert any('CHK_SBOX_MATCH' in item for item in payload['repair_guidance'])
    assert payload['recommended_mode'] == 'repair'
    assert payload['repair_request_path'].endswith('repair_request.json')
    assert payload['edit_receipt_path'].endswith('edit_receipt.json')


def test_repair_request_targets_draft_files_only(tmp_path):
    spec_ir, plan_dag, _ = _synthesized_context()
    node = plan_dag.nodes[0]
    workspace = initialize_node_workspace(
        spec_ir=spec_ir,
        plan_dag=plan_dag,
        node=node,
        workspace_root=tmp_path / node.module_id,
    )
    workspace = increment_validation_runs(workspace)
    generation_result_path = write_generation_result(
        workspace_record=workspace,
        node=node,
        validation_status='failed',
        failure_phase=ValidationFailurePhase.CHECKPOINT_MISSING,
        promoted=False,
        changed_files=[],
        checkpoint_summary={},
        missing_checkpoints=['CHK_SBOX_MATCH'],
        failed_checkpoints=[],
        recommended_mode='repair',
    )
    stale_receipt = tmp_path / node.module_id / 'edit_receipt.json'
    stale_receipt.write_text('{"stale": true}', encoding='utf-8')
    repair_request_path = write_repair_request(
        workspace_record=workspace,
        node=node,
        generation_result_path=generation_result_path,
        failure_phase=ValidationFailurePhase.CHECKPOINT_MISSING,
        missing_checkpoints=['CHK_SBOX_MATCH'],
        failed_checkpoints=[],
        rerun_command='python -m MultiAgent_FPGA.aes_mvp run-node aes_sbox --workspace-root /tmp/work --strict-validation',
    )
    contract = load_repair_contract(tmp_path / node.module_id)

    assert repair_request_path.is_file()
    assert contract.failure_phase == ValidationFailurePhase.CHECKPOINT_MISSING
    assert contract.primary_target_file.startswith(
        str(tmp_path / node.module_id / 'draft')
    )
    assert all(
        target.startswith(str(tmp_path / node.module_id / 'draft'))
        for target in contract.secondary_target_files
    )
    assert contract.required_first_edit
    assert contract.primary_target_reason
    assert contract.primary_file_excerpt
    assert contract.first_edit_steps
    assert contract.must_add_tokens == ['CHECKPOINT|CHK_SBOX_MATCH|PASS|']
    assert not stale_receipt.exists()


def test_repair_request_switches_to_rtl_when_tb_has_checkpoint_and_rtl_is_placeholder(
    tmp_path,
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
    draft_tb = workspace_root / 'draft' / 'tb' / 'aes_sbox_tb.cpp'
    draft_tb.write_text(
        '\n'.join(
            [
                '#include <verilated.h>',
                '#include <iostream>',
                '#include "Vaes_sbox.h"',
                'int main(int argc, char** argv) {',
                '    Verilated::commandArgs(argc, argv);',
                '    Vaes_sbox dut;',
                '    dut.eval();',
                '    std::cout << "CHECKPOINT: CHK_SBOX_MATCH" << std::endl;',
                '    return 0;',
                '}',
                '',
            ]
        ),
        encoding='utf-8',
    )
    compile_failure = {
        'module_id': node.module_id,
        'l0_status': 'failed',
        'l1_status': 'failed',
        'validation_status': 'failed',
        'checkpoint_summary': {},
        'missing_checkpoints': ['CHK_SBOX_MATCH'],
        'failed_checkpoints': [],
        'error': {
            'type': 'RuntimeError',
            'message': 'Error: Compilation failed: Exiting due to 1 warning(s)',
        },
    }
    write_validation_summary(workspace_record=workspace, payload=compile_failure)
    write_validation_error(workspace_record=workspace, payload=compile_failure)
    generation_result_path = write_generation_result(
        workspace_record=workspace,
        node=node,
        validation_status='failed',
        failure_phase=ValidationFailurePhase.L0_COMPILE,
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
        rerun_command='python -m MultiAgent_FPGA.aes_mvp run-node aes_sbox --workspace-root /tmp/work --strict-validation',
    )
    contract = load_repair_contract(workspace_root)

    assert contract.primary_target_file.endswith('draft/rtl/aes_sbox.v')
    assert contract.primary_target_reason.startswith('rtl-first repair')
    assert any("8'h00 -> 8'h63" in step for step in contract.first_edit_steps)


def test_repair_request_keeps_tb_primary_when_tb_only_has_bare_checkpoint_name(
    tmp_path,
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
    draft_tb = workspace_root / 'draft' / 'tb' / 'aes_sbox_tb.cpp'
    draft_tb.write_text(
        '\n'.join(
            [
                '#include <verilated.h>',
                '#include <iostream>',
                '#include "Vaes_sbox.h"',
                'int main(int argc, char** argv) {',
                '    Verilated::commandArgs(argc, argv);',
                '    Vaes_sbox dut;',
                '    dut.eval();',
                '    std::cout << "CHK_SBOX_MATCH" << std::endl;',
                '    return 0;',
                '}',
                '',
            ]
        ),
        encoding='utf-8',
    )
    validation_failure = {
        'module_id': node.module_id,
        'l0_status': 'passed',
        'l1_status': 'failed',
        'validation_status': 'failed',
        'checkpoint_summary': {},
        'missing_checkpoints': ['CHK_SBOX_MATCH'],
        'failed_checkpoints': [],
        'error': None,
    }
    write_validation_summary(workspace_record=workspace, payload=validation_failure)
    write_validation_error(workspace_record=workspace, payload=validation_failure)
    generation_result_path = write_generation_result(
        workspace_record=workspace,
        node=node,
        validation_status='failed',
        failure_phase=ValidationFailurePhase.CHECKPOINT_MISSING,
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
        failure_phase=ValidationFailurePhase.CHECKPOINT_MISSING,
        missing_checkpoints=['CHK_SBOX_MATCH'],
        failed_checkpoints=[],
        rerun_command='python -m MultiAgent_FPGA.aes_mvp run-node aes_sbox --workspace-root /tmp/work --strict-validation',
    )
    contract = load_repair_contract(workspace_root)

    assert contract.primary_target_file.endswith('draft/tb/aes_sbox_tb.cpp')
    assert contract.failure_phase == ValidationFailurePhase.CHECKPOINT_MISSING
    assert contract.must_add_tokens == ['CHECKPOINT|CHK_SBOX_MATCH|PASS|']


def test_verify_repair_edit_accepts_emit_checkpoint_helper(tmp_path):
    spec_ir, plan_dag, _ = _synthesized_context()
    node = next(
        item for item in plan_dag.nodes if item.module_id == 'aes_round_transform'
    )
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
        failure_phase=ValidationFailurePhase.CHECKPOINT_MISSING,
        promoted=False,
        changed_files=[],
        checkpoint_summary={},
        missing_checkpoints=['CHK_ROUND_STATE_MATCH'],
        failed_checkpoints=[],
        recommended_mode='repair',
    )
    write_repair_request(
        workspace_record=workspace,
        node=node,
        generation_result_path=generation_result_path,
        missing_checkpoints=['CHK_ROUND_STATE_MATCH'],
        failed_checkpoints=[],
        rerun_command='python -m MultiAgent_FPGA.aes_mvp run-node aes_round_transform --workspace-root /tmp/work --strict-validation',
    )
    contract = load_repair_contract(workspace_root)
    tb_path = workspace_root / 'draft' / 'tb' / 'aes_round_transform_tb.cpp'
    tb_path.write_text(
        '\n'.join(
            [
                '#include <verilated.h>',
                '#include <iostream>',
                '#include "Vaes_round_transform.h"',
                '#include "aes_tb_common.hpp"',
                '',
                'int main(int argc, char** argv) {',
                '    Verilated::commandArgs(argc, argv);',
                '    Vaes_round_transform dut;',
                '    dut.eval();',
                '    aes_tb::emit_checkpoint("CHK_ROUND_STATE_MATCH", "helper_path");',
                '    return 0;',
                '}',
                '',
            ]
        ),
        encoding='utf-8',
    )

    repair_valid, edited_files, message = verify_repair_edit(
        workspace_root=workspace_root,
        repair_contract=contract,
    )
    assert repair_valid is True
    assert str(tb_path) in edited_files
    assert message == 'repair edit verified'


def test_top_workspace_draft_contains_handshake_and_vector_harness(tmp_path):
    spec_ir, plan_dag, _ = _synthesized_context()
    node = next(
        item for item in plan_dag.nodes if item.module_id == 'aes128_encrypt_core'
    )
    workspace_root = tmp_path / node.module_id
    initialize_node_workspace(
        spec_ir=spec_ir,
        plan_dag=plan_dag,
        node=node,
        workspace_root=workspace_root,
    )

    rtl_path = workspace_root / 'draft' / 'rtl' / 'aes128_encrypt_core.v'
    tb_path = workspace_root / 'draft' / 'tb' / 'aes128_encrypt_core_tb.cpp'

    rtl_text = rtl_path.read_text(encoding='utf-8')
    tb_text = tb_path.read_text(encoding='utf-8')

    # Memory-pre-populated RTL uses structural FSM (STATE_IDLE/STATE_ROUND/STATE_DONE)
    assert 'STATE_IDLE' in rtl_text
    assert 'STATE_ROUND' in rtl_text or 'STATE_BUSY' in rtl_text
    assert 'run_transaction' in tb_text
    assert 'aes128_encrypt_core_zero.txt' in tb_text
    assert 'aes128_encrypt_core_regress.txt' in tb_text
    assert 'resolve_named_vector_file(argc, argv' in tb_text
    assert 'aes_tb::resolve_path(argc, argv' in tb_text
    assert (workspace_root / 'draft' / 'tb' / 'aes_tb_common.hpp').is_file()


def test_top_workspace_promotion_copies_tb_support_headers(tmp_path):
    spec_ir, plan_dag, _ = _synthesized_context()
    node = next(
        item for item in plan_dag.nodes if item.module_id == 'aes128_encrypt_core'
    )
    workspace_root = tmp_path / node.module_id
    workspace = initialize_node_workspace(
        spec_ir=spec_ir,
        plan_dag=plan_dag,
        node=node,
        workspace_root=workspace_root,
    )

    promote_workspace(
        node=node,
        workspace_record=workspace,
        checkpoint_summary={},
    )

    promoted_tb_root = (
        workspace_root.parent.parent / 'promoted' / 'aes128_encrypt_core' / 'tb'
    ).resolve()
    assert (promoted_tb_root / 'aes128_encrypt_core_tb.cpp').is_file()
    assert (promoted_tb_root / 'aes_tb_common.hpp').is_file()


def test_top_repair_request_requires_handshake_first_edit_tokens(tmp_path):
    spec_ir, plan_dag, _ = _synthesized_context()
    node = next(
        item for item in plan_dag.nodes if item.module_id == 'aes128_encrypt_core'
    )
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
        failure_phase=ValidationFailurePhase.L0_COMPILE,
        promoted=False,
        changed_files=[],
        checkpoint_summary={},
        missing_checkpoints=[
            'CHK_RESET_CLEAR',
            'CHK_START_ACCEPTED',
            'CHK_BUSY_ASSERTED',
        ],
        failed_checkpoints=[],
        recommended_mode='repair',
    )

    write_repair_request(
        workspace_record=workspace,
        node=node,
        generation_result_path=generation_result_path,
        missing_checkpoints=[
            'CHK_RESET_CLEAR',
            'CHK_START_ACCEPTED',
            'CHK_BUSY_ASSERTED',
        ],
        failed_checkpoints=[],
        rerun_command='python -m MultiAgent_FPGA.aes_mvp run-node aes128_encrypt_core --workspace-root /tmp/work --promoted-root /tmp/promoted --strict-validation',
    )
    contract = load_repair_contract(workspace_root)

    assert contract.primary_target_file.endswith('draft/rtl/aes128_encrypt_core.v')
    assert 'STATE_IDLE' in contract.must_add_tokens
    assert 'STATE_BUSY' in contract.must_add_tokens
    assert any('11-cycle' in step for step in contract.first_edit_steps)
    assert any(
        '66e94bd4ef8a2c3b884cfa59ca342b2e' in step for step in contract.first_edit_steps
    )


def test_validate_result_requires_required_checkpoints():
    _, plan_dag, _ = _synthesized_context()
    node = plan_dag.nodes[0]
    passed_status, passed_details = evaluate_validation_result(
        node=node,
        l1_payload={
            'checkpoint_summary': {'CHK_SBOX_MATCH': 'PASS|known_answer_vectors'}
        },
    )
    failed_status, failed_details = evaluate_validation_result(
        node=node,
        l1_payload={'checkpoint_summary': {}},
    )

    assert passed_status == 'passed'
    assert passed_details['failure_phase'] is None
    assert passed_details['missing_checkpoints'] == []
    assert failed_status == 'failed'
    assert failed_details['failure_phase'] == 'checkpoint_missing'
    assert failed_details['missing_checkpoints'] == ['CHK_SBOX_MATCH']


def test_validate_result_marks_failed_checkpoints_phase():
    _, plan_dag, _ = _synthesized_context()
    node = plan_dag.nodes[0]

    failed_status, failed_details = evaluate_validation_result(
        node=node,
        l1_payload={
            'checkpoint_summary': {'CHK_SBOX_MATCH': 'FAIL|mismatch'},
        },
    )

    assert failed_status == 'failed'
    assert failed_details['failure_phase'] == 'checkpoint_failed'
    assert failed_details['failed_checkpoints'] == ['CHK_SBOX_MATCH']


def test_validate_result_marks_missing_payload_as_l1_sim():
    _, plan_dag, _ = _synthesized_context()
    node = plan_dag.nodes[0]

    failed_status, failed_details = evaluate_validation_result(
        node=node,
        l1_payload=None,
    )

    assert failed_status == 'failed'
    assert failed_details['failure_phase'] == 'l1_sim'


# -- Memory-first draft pre-population tests --


def test_memory_store_select_aes_sbox():
    """Verify MemoryStore.select returns artifacts with non-None RTL+TB."""
    store = MemoryStore()
    for module_id in (
        'aes_sbox',
        'aes_key_schedule_128',
        'aes_round_transform',
        'aes128_encrypt_core',
    ):
        arts = store.select(module_id)
        assert len(arts) >= 1, f'{module_id}: no artifacts returned'
        # The module-specific artifact (not shared) should have RTL+TB
        module_art = [a for a in arts if a.key != 'aes_memory_shared']
        assert len(module_art) >= 1, f'{module_id}: no module-specific artifact'
        art = module_art[0]
        assert art.content_rtl is not None, f'{module_id}: no RTL extracted'
        assert art.content_tb is not None, f'{module_id}: no TB extracted'
        assert len(art.content_rtl) > 50, f'{module_id}: RTL too short'
        assert len(art.content_tb) > 50, f'{module_id}: TB too short'


def test_memory_store_retrieve_unknown_key():
    """Verify MemoryStore.retrieve raises KeyError for unknown keys."""
    store = MemoryStore()
    import pytest

    with pytest.raises(KeyError):
        store.retrieve('nonexistent_key')


def test_memory_store_build_prompt_block():
    """Verify MemoryStore.build_prompt_block returns non-empty text."""
    store = MemoryStore()
    block = store.build_prompt_block('aes_sbox')
    assert len(block) > 100, 'prompt block should contain substantial content'
    assert '=== MEMORY:' in block, 'prompt block should contain memory markers'
    assert '=== END MEMORY ===' in block


def test_skill_registries_are_split():
    """Verify runtime, memory, and doc-only registries are disjoint."""
    rt = get_runtime_skill_refs()
    mem = get_memory_skill_refs()
    doc = get_documentation_skill_refs()
    assert len(rt) == 5, f'expected 5 runtime, got {len(rt)}'
    assert len(mem) == 5, f'expected 5 memory, got {len(mem)}'
    assert len(doc) == 6, f'expected 6 doc-only, got {len(doc)}'
    # No overlap
    assert not (set(rt) & set(mem)), 'runtime/memory overlap'
    assert not (set(rt) & set(doc)), 'runtime/doc overlap'
    assert not (set(mem) & set(doc)), 'memory/doc overlap'
    # Runtime should have no memory keys
    assert all(not k.startswith('aes_memory_') for k in rt)
    # Memory should have all memory keys
    assert all(k.startswith('aes_memory_') for k in mem)


def test_build_module_worker_prompt_rejects_repair_mode():
    """Verify build_module_worker_prompt raises ValueError for active_mode='repair'."""
    import pytest

    _, plan_dag, _ = _synthesized_context()
    node = plan_dag.nodes[0]
    with pytest.raises(ValueError, match='repair'):
        build_module_worker_prompt(node, active_mode='repair')


def test_hook_payload_has_timestamp(tmp_path):
    """Verify _write_hook_event injects an ISO-8601 timestamp into the payload."""
    from unittest.mock import MagicMock

    from MultiAgent_FPGA.aes_mvp.runtime.session import ExecutionSession

    session = object.__new__(ExecutionSession)
    session.report_root = tmp_path
    session.context_assembler = MagicMock()

    result = session._write_hook_event('test_hook', {'batch_id': 'b1', 'foo': 'bar'})
    assert result is not None
    payload = json.loads(result.read_text())
    assert 'timestamp' in payload
    # ISO-8601 with timezone: ends with +00:00 or Z
    ts = payload['timestamp']
    assert 'T' in ts
    assert payload['foo'] == 'bar'


def test_hook_io_error_does_not_crash(tmp_path):
    """Verify _write_hook_event catches OSError and returns None."""
    from unittest.mock import MagicMock, patch

    from MultiAgent_FPGA.aes_mvp.runtime.session import ExecutionSession

    session = object.__new__(ExecutionSession)
    session.report_root = tmp_path
    session.context_assembler = MagicMock()

    with patch.object(
        ExecutionSession, '_write_json', side_effect=OSError('disk full')
    ):
        result = session._write_hook_event('failing_hook', {'batch_id': 'b2'})
    assert result is None


# ---------------------------------------------------------------------------
# Closed-loop workflow tests
# ---------------------------------------------------------------------------


def test_subagent_work_mode_has_exactly_five_members():
    """Step 1: BUILD and ARTIFACT_REVIEW removed."""
    from MultiAgent_FPGA.aes_mvp.delegation import SubagentWorkMode

    assert len(SubagentWorkMode) == 5
    expected = {'generate', 'validate', 'repair', 'l2_execute', 'integration'}
    actual = {m.value for m in SubagentWorkMode}
    assert actual == expected


def test_orchestrator_state_has_no_failed():
    """Step 2: OrchestratorState.FAILED orphan removed."""
    assert not hasattr(OrchestratorState, 'FAILED')


def test_node_workspace_state_failed_exists():
    """Step 3: NodeWorkspaceState.FAILED added."""
    assert NodeWorkspaceState.FAILED.value == 'failed'


def test_write_defensive_failure_result(tmp_path):
    """Step 3: Defensive write produces valid generation_result.json."""
    from MultiAgent_FPGA.aes_mvp.generation import write_defensive_failure_result

    result_path = write_defensive_failure_result(
        workspace_root=tmp_path,
        module_id='aes_sbox',
        failure_reason='execution_conversation_error',
    )
    assert result_path.exists()
    payload = json.loads(result_path.read_text())
    assert payload['workspace_state'] == 'failed'
    assert payload['module_id'] == 'aes_sbox'
    assert payload['failure_reason'] == 'execution_conversation_error'
    assert payload['promoted'] is False


def test_node_policy_engine_failed_is_terminal():
    """Step 3: NodePolicyEngine treats FAILED as terminal."""
    from MultiAgent_FPGA.aes_mvp.synthesis import NodePolicyEngine

    engine = NodePolicyEngine()
    # Create a minimal workspace record with FAILED state
    from MultiAgent_FPGA.aes_mvp.artifacts import NodeWorkspaceRecord

    record = NodeWorkspaceRecord(
        module_id='aes_sbox',
        workspace_root='/tmp/ws/aes_sbox',
        state=NodeWorkspaceState.FAILED,
        contract_paths={},
        draft_paths={'rtl': '{}', 'tb': '/tmp/tb'},
        promoted_paths={'rtl': '{}', 'tb': '/tmp/tb'},
        validation_paths={
            'l0_result': '/tmp/l0',
            'module_run_result': '/tmp/mr',
            'simulation_log': '/tmp/sim',
            'waveform': '/tmp/wave',
            'validation_summary': '/tmp/vs',
            'validation_error': '/tmp/ve',
        },
        canonical_targets=['rtl/aes_sbox.v'],
    )
    # decide_next_mode returns None for FAILED
    result = engine.decide_next_mode(
        workspace_record=record, validation_status='failed', repair_budget=2
    )
    assert result is None
    # next_state returns FAILED for FAILED
    state = engine.next_state(
        workspace_record=record, validation_status='failed', repair_budget=2
    )
    assert state == NodeWorkspaceState.FAILED


def _make_workspace_record(state: NodeWorkspaceState):
    """Helper to create a minimal NodeWorkspaceRecord for policy engine tests."""
    from MultiAgent_FPGA.aes_mvp.artifacts import NodeWorkspaceRecord

    return NodeWorkspaceRecord(
        module_id='aes_sbox',
        workspace_root='/tmp/ws/aes_sbox',
        state=state,
        repair_edit_count=0,
        contract_paths={},
        draft_paths={'rtl': '{}', 'tb': '/tmp/tb'},
        promoted_paths={'rtl': '{}', 'tb': '/tmp/tb'},
        validation_paths={
            'l0_result': '/tmp/l0',
            'module_run_result': '/tmp/mr',
            'simulation_log': '/tmp/sim',
            'waveform': '/tmp/wave',
            'validation_summary': '/tmp/vs',
            'validation_error': '/tmp/ve',
        },
        canonical_targets=['rtl/aes_sbox.v'],
    )


def test_node_policy_engine_promoted_returns_none():
    """PROMOTED workspace must not be sent to REPAIR even with failed validation."""
    from MultiAgent_FPGA.aes_mvp.synthesis import NodePolicyEngine

    engine = NodePolicyEngine()
    record = _make_workspace_record(NodeWorkspaceState.PROMOTED)
    result = engine.decide_next_mode(
        workspace_record=record, validation_status='failed', repair_budget=5
    )
    assert result is None


def test_node_policy_engine_promoted_state_preserved():
    """next_state must preserve PROMOTED even with failed validation status."""
    from MultiAgent_FPGA.aes_mvp.synthesis import NodePolicyEngine

    engine = NodePolicyEngine()
    record = _make_workspace_record(NodeWorkspaceState.PROMOTED)
    state = engine.next_state(
        workspace_record=record, validation_status='failed', repair_budget=5
    )
    assert state == NodeWorkspaceState.PROMOTED


def test_node_policy_engine_validated_returns_none():
    """VALIDATED workspace must not be sent to REPAIR even with failed validation."""
    from MultiAgent_FPGA.aes_mvp.synthesis import NodePolicyEngine

    engine = NodePolicyEngine()
    record = _make_workspace_record(NodeWorkspaceState.VALIDATED)
    result = engine.decide_next_mode(
        workspace_record=record, validation_status='failed', repair_budget=5
    )
    assert result is None


def test_node_policy_engine_validated_state_preserved():
    """next_state must preserve VALIDATED even with stale failed validation status."""
    from MultiAgent_FPGA.aes_mvp.synthesis import NodePolicyEngine

    engine = NodePolicyEngine()
    record = _make_workspace_record(NodeWorkspaceState.VALIDATED)
    state = engine.next_state(
        workspace_record=record, validation_status='failed', repair_budget=5
    )
    assert state == NodeWorkspaceState.VALIDATED


def test_node_policy_engine_handles_all_workspace_states():
    """Exhaustiveness guard: decide_next_mode handles every NodeWorkspaceState member."""
    from MultiAgent_FPGA.aes_mvp.synthesis import NodePolicyEngine

    engine = NodePolicyEngine()
    for ws_state in NodeWorkspaceState:
        record = _make_workspace_record(ws_state)
        result = engine.decide_next_mode(
            workspace_record=record, validation_status='failed', repair_budget=5
        )
        assert result is None or hasattr(result, 'value'), (
            f'Unexpected result for state {ws_state}: {result}'
        )


def test_write_cascade_block_result(tmp_path):
    """Step 4: Cascade block writes valid generation_result.json."""
    from MultiAgent_FPGA.aes_mvp.generation import write_cascade_block_result

    result_path = write_cascade_block_result(
        workspace_root=tmp_path,
        module_id='aes_round_transform',
        blocked_by='aes_sbox',
    )
    assert result_path.exists()
    payload = json.loads(result_path.read_text())
    assert payload['workspace_state'] == 'blocked'
    assert payload['cascade_blocked_by'] == 'aes_sbox'
    assert payload['module_id'] == 'aes_round_transform'
    assert payload['promoted'] is False


def test_write_budget_exhausted_result(tmp_path):
    """Step 5: Budget exhaustion writes valid generation_result.json."""
    from MultiAgent_FPGA.aes_mvp.generation import write_budget_exhausted_result

    result_path = write_budget_exhausted_result(
        workspace_root=tmp_path,
        module_id='aes_sbox',
        repair_rounds_consumed=2,
    )
    assert result_path.exists()
    payload = json.loads(result_path.read_text())
    assert payload['workspace_state'] == 'blocked'
    assert payload['repair_budget_exhausted'] is True
    assert payload['repair_rounds_consumed'] == 2
    assert payload['module_id'] == 'aes_sbox'


def test_finalizer_spec_no_failed_state():
    """Step 2: Finalizer spec no longer references FAILED state."""
    spec = build_finalizer_orchestrator_spec()
    state_values = {s.value for s in spec.allowed_states}
    assert 'FAILED' not in state_values
    assert 'DONE' in state_values
