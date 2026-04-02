from __future__ import annotations

import json
import logging
import sys
import types

if 'pythonjsonlogger.json' not in sys.modules:
    pythonjsonlogger = types.ModuleType('pythonjsonlogger')
    pythonjsonlogger.__path__ = []  # type: ignore[attr-defined]
    pythonjsonlogger_json = types.ModuleType('pythonjsonlogger.json')

    class JsonFormatter(logging.Formatter):
        pass

    pythonjsonlogger_json.JsonFormatter = JsonFormatter
    pythonjsonlogger.json = pythonjsonlogger_json  # type: ignore[attr-defined]
    sys.modules['pythonjsonlogger'] = pythonjsonlogger
    sys.modules['pythonjsonlogger.json'] = pythonjsonlogger_json

if 'google.api_core.exceptions' not in sys.modules:
    try:
        import google  # type: ignore[import-not-found]
    except Exception:
        google = types.ModuleType('google')
        google.__path__ = []  # type: ignore[attr-defined]
        sys.modules['google'] = google
    google_api_core = types.ModuleType('google.api_core')
    google_api_core.__path__ = []  # type: ignore[attr-defined]
    google_api_core_exceptions = types.ModuleType('google.api_core.exceptions')

    class NotFound(Exception):
        pass

    google_api_core_exceptions.NotFound = NotFound
    google_api_core.exceptions = google_api_core_exceptions  # type: ignore[attr-defined]
    google_cloud = types.ModuleType('google.cloud')
    google_cloud.__path__ = []  # type: ignore[attr-defined]
    google_cloud_storage = types.ModuleType('google.cloud.storage')
    google_cloud_storage.__path__ = []  # type: ignore[attr-defined]
    google_cloud_storage_blob = types.ModuleType('google.cloud.storage.blob')
    google_cloud_storage_bucket = types.ModuleType('google.cloud.storage.bucket')
    google_cloud_storage_client = types.ModuleType('google.cloud.storage.client')

    class Blob:
        pass

    class Bucket:
        pass

    class Client:
        pass

    google_cloud_storage_blob.Blob = Blob
    google_cloud_storage_bucket.Bucket = Bucket
    google_cloud_storage_client.Client = Client
    google_cloud_storage.Blob = Blob  # type: ignore[attr-defined]
    google_cloud_storage.Bucket = Bucket  # type: ignore[attr-defined]
    google_cloud_storage.Client = Client  # type: ignore[attr-defined]
    google_cloud_storage.blob = google_cloud_storage_blob  # type: ignore[attr-defined]
    google_cloud_storage.bucket = google_cloud_storage_bucket  # type: ignore[attr-defined]
    google_cloud_storage.client = google_cloud_storage_client  # type: ignore[attr-defined]
    google_cloud.storage = google_cloud_storage  # type: ignore[attr-defined]
    google.api_core = google_api_core  # type: ignore[attr-defined]
    google.api_core.exceptions = google_api_core_exceptions  # type: ignore[attr-defined]
    sys.modules['google.api_core'] = google_api_core
    sys.modules['google.api_core.exceptions'] = google_api_core_exceptions
    sys.modules['google.cloud'] = google_cloud
    sys.modules['google.cloud.storage'] = google_cloud_storage
    sys.modules['google.cloud.storage.blob'] = google_cloud_storage_blob
    sys.modules['google.cloud.storage.bucket'] = google_cloud_storage_bucket
    sys.modules['google.cloud.storage.client'] = google_cloud_storage_client

if 'openhands.core.config' not in sys.modules:
    openhands_core = types.ModuleType('openhands.core')
    openhands_core.__path__ = []  # type: ignore[attr-defined]
    openhands_core_config = types.ModuleType('openhands.core.config')
    openhands_core_config.__path__ = []  # type: ignore[attr-defined]

    class LLMConfig:
        def __init__(
            self,
            *,
            model: str = '',
            api_key=None,
            base_url: str | None = None,
            completion_kwargs: dict | None = None,
            **kwargs,
        ) -> None:
            self.model = model
            self.api_key = api_key
            self.base_url = base_url
            self.completion_kwargs = completion_kwargs
            for key, value in kwargs.items():
                setattr(self, key, value)

    openhands_core_config.LLMConfig = LLMConfig
    openhands_core.config = openhands_core_config  # type: ignore[attr-defined]
    sys.modules['openhands.core'] = openhands_core
    sys.modules['openhands.core.config'] = openhands_core_config

if 'openhands.core.config.mcp_config' not in sys.modules:
    openhands_core_config_mcp = types.ModuleType('openhands.core.config.mcp_config')

    class MCPStdioServerConfig:
        def __init__(self, *, name: str, command: str, args=None, env=None) -> None:
            self.name = name
            self.command = command
            self.args = list(args or [])
            self.env = dict(env or {})

    openhands_core_config_mcp.MCPStdioServerConfig = MCPStdioServerConfig
    sys.modules['openhands.core.config.mcp_config'] = openhands_core_config_mcp

if 'openhands.events.action.mcp' not in sys.modules:
    openhands_events_action = types.ModuleType('openhands.events.action')
    openhands_events_action.__path__ = []  # type: ignore[attr-defined]
    openhands_events_action_mcp = types.ModuleType('openhands.events.action.mcp')

    class MCPAction:
        def __init__(self, *, name: str, arguments: dict | None = None) -> None:
            self.name = name
            self.arguments = arguments or {}

    openhands_events_action_mcp.MCPAction = MCPAction
    sys.modules['openhands.events.action'] = openhands_events_action
    sys.modules['openhands.events.action.mcp'] = openhands_events_action_mcp

if 'openhands.events.observation.mcp' not in sys.modules:
    openhands_events_observation = types.ModuleType('openhands.events.observation')
    openhands_events_observation.__path__ = []  # type: ignore[attr-defined]
    openhands_events_observation_mcp = types.ModuleType(
        'openhands.events.observation.mcp'
    )

    class MCPObservation:
        def __init__(self, *, content: str, name: str = '', arguments=None) -> None:
            self.content = content
            self.name = name
            self.arguments = arguments or {}

    openhands_events_observation_mcp.MCPObservation = MCPObservation
    sys.modules['openhands.events.observation'] = openhands_events_observation
    sys.modules['openhands.events.observation.mcp'] = openhands_events_observation_mcp

if 'openhands.mcp.utils' not in sys.modules:
    openhands_mcp = types.ModuleType('openhands.mcp')
    openhands_mcp.__path__ = []  # type: ignore[attr-defined]
    openhands_mcp_utils = types.ModuleType('openhands.mcp.utils')

    async def create_mcp_clients(*args, **kwargs):
        return []

    async def call_tool_mcp(*args, **kwargs):
        raise RuntimeError('stubbed MCP helper')

    openhands_mcp_utils.create_mcp_clients = create_mcp_clients
    openhands_mcp_utils.call_tool_mcp = call_tool_mcp
    sys.modules['openhands.mcp'] = openhands_mcp
    sys.modules['openhands.mcp.utils'] = openhands_mcp_utils

from MultiAgent_FPGA.aes_mvp.agents import (
    build_l2_campaign_spec,
    build_module_worker_spec,
    build_workflow_orchestrator_spec,
)
from MultiAgent_FPGA.aes_mvp.artifacts import (
    NodeWorkspaceState,
    load_default_integration_manifest,
    load_default_plan_dag,
    load_default_spec_ir,
)
from MultiAgent_FPGA.aes_mvp.generation import (
    build_module_contract,
    build_module_design_brief,
    build_testbench_contract,
    evaluate_validation_result,
    increment_validation_runs,
    initialize_node_workspace,
    write_generation_result,
)
from MultiAgent_FPGA.aes_mvp.llm_profiles import (
    DEEPSEEK_BASE_URL,
    DEEPSEEK_CHAT_MODEL,
    DEEPSEEK_REASONER_MODEL,
    DEEPSEEK_RESOLVED_MODEL,
    SDK_DEEPSEEK_MODEL,
    build_deepseek_official_fast,
    build_deepseek_official_thinking,
    build_sdk_deepseek_official_fast_kwargs,
    build_sdk_deepseek_official_thinking_kwargs,
    parse_deepseek_response,
    run_deepseek_preflight,
    run_deepseek_preflight_suite,
)
from MultiAgent_FPGA.aes_mvp.orchestrator import AESWorkflowOrchestrator
from MultiAgent_FPGA.aes_mvp.policy import (
    LLMProfileName,
    OrchestratorState,
    SubagentPolicy,
    load_default_agent_execution_policy,
)
from MultiAgent_FPGA.aes_mvp.prompts import (
    build_l2_campaign_prompt,
    build_module_worker_prompt,
    build_workflow_orchestrator_prompt,
)
from MultiAgent_FPGA.aes_mvp.skill_refs import get_runtime_skill_refs


def test_default_spec_ir_matches_frozen_aes_scope():
    spec_ir = load_default_spec_ir()
    assert spec_ir.algorithm == 'AES'
    assert spec_ir.variant == 'AES-128'
    assert spec_ir.operation == 'encrypt'
    assert spec_ir.interface_style == 'block_handshake'
    assert spec_ir.microarchitecture == 'iterative_10_round'
    assert spec_ir.latency_target_cycles == 11


def test_default_plan_dag_matches_frozen_node_taxonomy():
    plan_dag = load_default_plan_dag()
    assert [node.module_id for node in plan_dag.nodes] == [
        'aes_sbox',
        'aes_key_schedule_128',
        'aes_round_transform',
        'aes128_encrypt_core',
    ]
    assert plan_dag.nodes[-1].top_module == 'aes128_encrypt_core'
    assert plan_dag.nodes[-1].l2_policy == 'required'


def test_default_policy_routes_thinking_and_subagents():
    policy = load_default_agent_execution_policy()
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


def test_prompts_encode_build_and_batched_delegate_rules():
    plan_dag = load_default_plan_dag()
    node = plan_dag.nodes[0]
    policy = load_default_agent_execution_policy()

    orchestrator_prompt = build_workflow_orchestrator_prompt()
    module_prompt = build_module_worker_prompt(node)
    l2_prompt = build_l2_campaign_prompt(
        plan_dag.nodes[-1],
        profile='rand_small',
        vecfile='vectors/aes128/aes128_encrypt_core_rand_small.txt',
        cases=8,
        seed=7,
    )

    assert 'delegate_plan with batches' in orchestrator_prompt
    assert 'Never exceed the provided max_children limit' in orchestrator_prompt
    assert (
        'framework node executor instead of raw Verilator tools' in orchestrator_prompt
    )
    assert (
        'mode: generate, validate, repair, l2_execute, or artifact_review'
        in module_prompt
    )
    assert 'generation_result.json, workspace_state.json' in module_prompt
    assert 'Do not stop after the first failed generate/validate run' in module_prompt
    assert 'generate mode' in module_prompt
    assert 'executor_command' in module_prompt
    assert 'task contract file path' in module_prompt
    assert 'your first action should be to run that exact command' in module_prompt
    assert 'Follow a bounded node-local loop' in module_prompt
    assert 'In l2_execute mode, do not edit RTL or testbench files' in module_prompt
    assert 'mode: l2_execute or artifact_review' in l2_prompt
    assert 'framework L2 executor wrapper' in l2_prompt
    assert 'executor_command' in l2_prompt
    assert 'task contract file path' in l2_prompt
    assert 'your first action should be to run that exact command' in l2_prompt
    assert policy.should_escalate(2) is True
    assert policy.should_escalate(1, cross_module_issue=True) is True


def test_deepseek_official_profiles_are_pinned_for_tool_capable_runtime(monkeypatch):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    thinking = build_deepseek_official_thinking()
    fast = build_deepseek_official_fast()
    sdk_thinking = build_sdk_deepseek_official_thinking_kwargs()
    sdk_fast = build_sdk_deepseek_official_fast_kwargs()

    assert thinking.model == DEEPSEEK_CHAT_MODEL
    assert fast.model == DEEPSEEK_CHAT_MODEL
    assert thinking.base_url == DEEPSEEK_BASE_URL
    assert fast.base_url == DEEPSEEK_BASE_URL
    assert thinking.completion_kwargs is None
    assert fast.completion_kwargs is None
    assert sdk_thinking['model'] == SDK_DEEPSEEK_MODEL
    assert sdk_fast['model'] == SDK_DEEPSEEK_MODEL
    assert sdk_thinking['model_canonical_name'] == DEEPSEEK_RESOLVED_MODEL
    assert sdk_fast['model_canonical_name'] == DEEPSEEK_RESOLVED_MODEL
    assert 'litellm_extra_body' not in sdk_thinking
    assert 'litellm_extra_body' not in sdk_fast


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
            return {
                'error': {
                    'message': '当前分组无可用渠道',
                }
            }

    monkeypatch.setattr(
        'MultiAgent_FPGA.aes_mvp.llm_profiles.requests.post',
        lambda *args, **kwargs: FakeErrorResponse(),
    )

    result = run_deepseek_preflight(thinking_enabled=False)
    assert result.ok is False
    assert result.status_code == 503
    assert result.error == '当前分组无可用渠道'


def test_skill_references_point_to_existing_skill_files():
    refs = get_runtime_skill_refs()
    assert set(refs) == {
        'verilator_mcp_setup',
        'verilog_verilator',
        'aes_verilator_profile',
        'deepseek_official_sdk',
        'openhands_sdk_bootstrap',
        'openhands_sdk_skill_authoring',
        'openhands_sdk_mcp_integration',
        'openhands_sdk_subagent_delegation',
        'openhands_sdk_observability',
    }
    assert all(ref.path.is_file() for ref in refs.values())


def test_agent_specs_follow_role_contract():
    plan_dag = load_default_plan_dag()
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

    assert orchestrator_spec.llm_profile == LLMProfileName.DEEPSEEK_OFFICIAL_THINKING
    assert module_spec.llm_profile == LLMProfileName.DEEPSEEK_OFFICIAL_FAST
    assert l2_spec.llm_profile == LLMProfileName.DEEPSEEK_OFFICIAL_FAST
    assert node.tb_file in module_spec.writable_paths


def test_orchestrator_loads_defaults_and_routes_module_work():
    orchestrator = AESWorkflowOrchestrator.from_defaults()
    work_order = orchestrator.build_module_work_order(
        'aes_key_schedule_128',
        OrchestratorState.MODULE_DESIGN,
    )
    manifest = load_default_integration_manifest()

    assert work_order.node.module_id == 'aes_key_schedule_128'
    assert manifest.top_module == 'aes128_encrypt_core'
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
    assert trace[-1].next_state is None


def test_generation_artifacts_auto_derive_from_spec_and_plan(tmp_path):
    spec_ir = load_default_spec_ir()
    plan_dag = load_default_plan_dag()
    node = plan_dag.nodes[0]

    module_contract = build_module_contract(spec_ir=spec_ir, node=node)
    tb_contract = build_testbench_contract(spec_ir=spec_ir, node=node)
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
    assert 'vecfile' in tb_contract.vector_format.lower()
    assert design_brief.skill_paths
    assert workspace.state == NodeWorkspaceState.DRAFT_READY
    assert (tmp_path / node.module_id / 'contracts' / 'module_contract.json').is_file()
    assert (tmp_path / node.module_id / 'draft' / 'rtl' / 'aes_sbox.v').is_file()
    assert (tmp_path / node.module_id / 'draft' / 'tb' / 'aes_sbox_tb.cpp').is_file()


def test_generation_result_records_missing_checkpoint_details(tmp_path):
    spec_ir = load_default_spec_ir()
    plan_dag = load_default_plan_dag()
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
        promoted=False,
        changed_files=[],
        checkpoint_summary={},
        missing_checkpoints=['CHK_SBOX_MATCH'],
        failed_checkpoints=[],
    )
    payload = json.loads(result_path.read_text(encoding='utf-8'))

    assert payload['validation_paths']['module_run_result'].endswith(
        'module_run_result.json'
    )
    assert payload['missing_checkpoints'] == ['CHK_SBOX_MATCH']
    assert payload['failed_checkpoints'] == []


def test_validate_result_requires_required_checkpoints():
    node = load_default_plan_dag().nodes[0]
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
    assert passed_details['missing_checkpoints'] == []
    assert failed_status == 'failed'
    assert failed_details['missing_checkpoints'] == ['CHK_SBOX_MATCH']
