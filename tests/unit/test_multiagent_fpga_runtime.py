from __future__ import annotations

import json
import logging
import sys
import types
from pathlib import Path
from types import SimpleNamespace
from uuid import uuid4

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

try:
    import google as google_pkg  # type: ignore[import-not-found]
except Exception:
    google_pkg = types.ModuleType('google')
    google_pkg.__path__ = []  # type: ignore[attr-defined]
    sys.modules['google'] = google_pkg
else:
    if not hasattr(google_pkg, '__path__'):
        google_pkg.__path__ = []  # type: ignore[attr-defined]

if 'google.api_core.exceptions' not in sys.modules:
    google_api_core = types.ModuleType('google.api_core')
    google_api_core.__path__ = []  # type: ignore[attr-defined]
    google_api_core_exceptions = types.ModuleType('google.api_core.exceptions')

    class NotFound(Exception):
        pass

    google_api_core_exceptions.NotFound = NotFound
    google_api_core.exceptions = google_api_core_exceptions  # type: ignore[attr-defined]
    google_pkg.api_core = google_api_core  # type: ignore[attr-defined]
    sys.modules['google.api_core'] = google_api_core
    sys.modules['google.api_core.exceptions'] = google_api_core_exceptions

if 'google.cloud.storage.client' not in sys.modules:
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
    google_pkg.cloud = google_cloud  # type: ignore[attr-defined]
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


from MultiAgent_FPGA.aes_mvp.__main__ import build_parser
from MultiAgent_FPGA.aes_mvp.artifacts import load_default_plan_dag
from MultiAgent_FPGA.aes_mvp.executors import (
    CheckpointParser,
    L0Executor,
    L1Executor,
    L2CampaignExecutor,
)
from MultiAgent_FPGA.aes_mvp.llm_profiles import (
    DEEPSEEK_RESOLVED_MODEL,
    SDK_DEEPSEEK_MODEL,
    SDK_REASONING_EFFORT,
    build_sdk_deepseek_official_fast_kwargs,
    build_sdk_deepseek_official_thinking_kwargs,
)
from MultiAgent_FPGA.aes_mvp.runtime import (
    ConversationRunner,
    ConversationSummary,
    ExecutionSession,
    RuntimeBootstrap,
    SdkAgentFactory,
    discover_sdk_environment,
)
from MultiAgent_FPGA.aes_mvp.runtime.factory import VERILATOR_ALLOWED_MCP_REGEX

EXPECTED_DELEGATE_REGISTRATIONS = [
    'module_worker__aes_sbox',
    'module_worker__aes_key_schedule_128',
    'l2_campaign__aes_key_schedule_128__rand_small',
    'module_worker__aes_round_transform',
    'l2_campaign__aes_round_transform__rand_small',
    'module_worker__aes128_encrypt_core',
    'l2_campaign__aes128_encrypt_core__rand_small',
]


class FakeVerilatorAdapter:
    def __init__(self, package_root: Path) -> None:
        self.package_root = package_root
        self.calls: list[tuple[str, dict]] = []

    async def compile(
        self,
        *,
        files: list[str],
        top_module: str,
        output_dir: str,
        extra_arguments: dict | None = None,
    ) -> str:
        self.calls.append(
            (
                'compile',
                {
                    'files': files,
                    'top_module': top_module,
                    'output_dir': output_dir,
                    'extra_arguments': extra_arguments or {},
                },
            )
        )
        Path(output_dir).mkdir(parents=True, exist_ok=True)
        return f'compiled:{top_module}'

    async def simulate(
        self,
        *,
        design: str,
        top_module: str,
        output_dir: str,
        extra_arguments: dict | None = None,
    ) -> str:
        self.calls.append(
            (
                'simulate',
                {
                    'design': design,
                    'top_module': top_module,
                    'output_dir': output_dir,
                    'extra_arguments': extra_arguments or {},
                },
            )
        )
        out = Path(output_dir)
        out.mkdir(parents=True, exist_ok=True)
        (out / 'simulation.log').write_text(
            'CHECKPOINT|CHK_TEST|PASS|ok\n',
            encoding='utf-8',
        )
        (out / 'simulation.vcd').write_text('wave', encoding='utf-8')
        return f'simulated:{top_module}'


def test_sdk_environment_is_discoverable_in_poetry_env():
    status = discover_sdk_environment()
    assert status.available is True
    assert status.package_name == 'openhands.sdk'


def test_sdk_shim_loads_explicit_site_packages_modules():
    from MultiAgent_FPGA.aes_mvp.runtime.sdk_shim import load_sdk_modules

    sdk_modules = load_sdk_modules()
    assert sdk_modules.sdk.__name__ == 'openhands.sdk'
    assert sdk_modules.register_agent_if_absent is not None
    assert sdk_modules.DelegateTool.name == 'delegate'


def test_sdk_llm_kwargs_disable_reasoning_effort(monkeypatch):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    thinking = build_sdk_deepseek_official_thinking_kwargs()
    fast = build_sdk_deepseek_official_fast_kwargs()

    assert thinking['model'] == SDK_DEEPSEEK_MODEL
    assert fast['model'] == SDK_DEEPSEEK_MODEL
    assert thinking['model_canonical_name'] == DEEPSEEK_RESOLVED_MODEL
    assert fast['model_canonical_name'] == DEEPSEEK_RESOLVED_MODEL
    assert fast.get('litellm_extra_body') is None
    assert thinking.get('litellm_extra_body') is None
    assert thinking['reasoning_effort'] == SDK_REASONING_EFFORT
    assert fast['reasoning_effort'] == SDK_REASONING_EFFORT


def test_runtime_bootstrap_loads_all_runtime_skills(monkeypatch):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build()
    assert len(bootstrap.runtime_skills) == 9
    assert 'deepseek-official-sdk' in bootstrap.runtime_skill_names
    assert 'openhands-sdk-bootstrap' in bootstrap.runtime_skill_names
    assert 'verilator-mcp-setup' in bootstrap.runtime_skill_names
    assert 'verilator' in bootstrap.mcp_config['mcpServers']
    env = bootstrap.mcp_config['mcpServers']['verilator']['env']
    assert env['VERILATOR_PATH'] == '/opt/homebrew/bin/verilator'
    assert env['LOG_LEVEL'] == 'info'
    assert 'DEEPSEEK_API_KEY' not in env
    assert 'CHATFIRE_API_KEY' not in env


def test_factory_creates_orchestrator_and_registers_workers(monkeypatch):
    monkeypatch.setenv('DEEPSEEK_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build()
    factory = SdkAgentFactory(bootstrap)
    orchestrator = factory.create_workflow_orchestrator()
    node = load_default_plan_dag().nodes[0]
    worker = factory.create_module_worker(node)
    registrations = factory.register_delegate_agents()

    assert orchestrator.llm.model == SDK_DEEPSEEK_MODEL
    assert worker.llm.model == SDK_DEEPSEEK_MODEL
    assert orchestrator.llm.model_canonical_name == DEEPSEEK_RESOLVED_MODEL
    assert worker.llm.model_canonical_name == DEEPSEEK_RESOLVED_MODEL
    assert any(tool.name == 'delegate' for tool in orchestrator.tools)
    assert all(tool.name != 'delegate' for tool in worker.tools)
    assert orchestrator.filter_tools_regex == VERILATOR_ALLOWED_MCP_REGEX
    assert worker.filter_tools_regex == VERILATOR_ALLOWED_MCP_REGEX
    assert (
        'openhands-sdk-subagent-delegation'
        in orchestrator.agent_context.system_message_suffix
    )
    assert (
        'openhands-sdk-subagent-delegation'
        not in worker.agent_context.system_message_suffix
    )
    assert (
        'openhands-sdk-skill-authoring'
        not in orchestrator.agent_context.system_message_suffix
    )
    assert registrations == EXPECTED_DELEGATE_REGISTRATIONS


def test_execution_session_writes_conversation_report_tree(monkeypatch, tmp_path: Path):
    monkeypatch.setenv('CHATFIRE_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(persistence_dir=tmp_path / 'conversations')
    conversation_id = uuid4()
    created_calls: dict[str, object] = {}

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
            self.closed = False

        def close(self) -> None:
            self.closed = True

    def fake_create_conversation(
        self,
        *,
        conversation_id=None,
        persistence_dir=None,
        delete_on_close=True,
    ):
        created_calls['conversation_id'] = conversation_id
        created_calls['persistence_dir'] = Path(persistence_dir)
        created_calls['delete_on_close'] = delete_on_close
        return FakeConversation(
            conversation_id=conversation_id,
            persistence_dir=Path(persistence_dir),
            workspace_root=self.bootstrap.workspace_root,
        )

    def fake_send_and_run(self, conversation, message):
        conversation.state.execution_status = 'finished'
        conversation.state.events.append({'message': message})
        return ConversationSummary(
            conversation_id=str(conversation.state.id),
            execution_status='finished',
            event_count=len(conversation.state.events),
            workspace_root=conversation.workspace.working_dir,
            persistence_dir=conversation.state.persistence_dir,
        )

    monkeypatch.setattr(
        ConversationRunner, 'create_orchestrator_conversation', fake_create_conversation
    )
    monkeypatch.setattr(ConversationRunner, 'send_and_run', fake_send_and_run)

    session = ExecutionSession.create(
        bootstrap,
        conversation_id=conversation_id,
        focus_module_id='aes128_encrypt_core',
    )
    assert created_calls['conversation_id'] == conversation_id
    assert created_calls['delete_on_close'] is False
    assert created_calls['persistence_dir'] == bootstrap.persistence_dir
    assert session.report_root == bootstrap.persistence_dir / conversation_id.hex
    assert session.base_state_path.is_file()
    assert session.state_trace_path.is_file()
    assert session.report_tree_path.is_file()

    summary = session.run(
        'Build and validate the AES MVP according to the frozen SpecIR and PlanDAG.'
    )
    assert summary.conversation_id == str(conversation_id)
    assert summary.report_root == str(bootstrap.persistence_dir / conversation_id.hex)
    assert summary.delegate_registrations == EXPECTED_DELEGATE_REGISTRATIONS
    assert summary.execution_mode == 'deterministic-review'
    assert summary.delegate_attempted == 0
    assert summary.delegate_completed == 0
    assert summary.delegate_batch_count == 0
    assert session.session_summary_path.is_file()
    assert Path(summary.delegate_plan_path).is_file()
    assert Path(summary.delegate_results_path).is_file()
    assert Path(summary.delegate_fallbacks_path).is_file()
    assert Path(summary.final_acceptance_summary_path).is_file()
    report_tree_payload = json.loads(
        session.report_tree_path.read_text(encoding='utf-8')
    )
    assert 'delegate_requests_dir' in report_tree_payload['paths']

    report_tree = session.report_tree_path.read_text(encoding='utf-8')
    assert conversation_id.hex in report_tree

    state_trace = session.state_trace_path.read_text(encoding='utf-8')
    assert 'SPEC_INTAKE' in state_trace
    assert 'DONE' in state_trace


def test_execution_session_can_write_deterministic_green_path(
    monkeypatch, tmp_path: Path
):
    monkeypatch.setenv('CHATFIRE_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(persistence_dir=tmp_path / 'conversations')

    class RichFakeVerilatorAdapter(FakeVerilatorAdapter):
        async def simulate(
            self,
            *,
            design: str,
            top_module: str,
            output_dir: str,
            extra_arguments: dict | None = None,
        ) -> str:
            self.calls.append(
                (
                    'simulate',
                    {
                        'design': design,
                        'top_module': top_module,
                        'output_dir': output_dir,
                        'extra_arguments': extra_arguments or {},
                    },
                )
            )
            out = Path(output_dir)
            out.mkdir(parents=True, exist_ok=True)
            checkpoints = [
                'CHK_RESET_CLEAR',
                'CHK_START_ACCEPTED',
                'CHK_BUSY_ASSERTED',
                'CHK_DONE_PULSE',
                'CHK_CIPHERTEXT_MATCH',
                'CHK_BUSY_DEASSERTED',
            ]
            (out / 'simulation.log').write_text(
                '\n'.join(f'CHECKPOINT|{name}|PASS|ok' for name in checkpoints) + '\n',
                encoding='utf-8',
            )
            (out / 'simulation.vcd').write_text('wave', encoding='utf-8')
            return f'simulated:{top_module}'

    def fake_create_adapter(self, *, conversation_id='aes-mvp'):
        return RichFakeVerilatorAdapter(self.workspace_root)

    class FakeConversation:
        def __init__(
            self, *, conversation_id, persistence_dir: Path, workspace_root: Path
        ) -> None:
            conversation_dir = persistence_dir / conversation_id.hex
            conversation_dir.mkdir(parents=True, exist_ok=True)
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
    ):
        return FakeConversation(
            conversation_id=conversation_id,
            persistence_dir=Path(persistence_dir),
            workspace_root=self.bootstrap.workspace_root,
        )

    seen_message: dict[str, str] = {}

    def fake_send_and_run(self, conversation, message):
        seen_message['message'] = message
        conversation.state.execution_status = 'finished'
        conversation.state.events.append({'message': message})
        return ConversationSummary(
            conversation_id=str(conversation.state.id),
            execution_status='finished',
            event_count=len(conversation.state.events),
            workspace_root=conversation.workspace.working_dir,
            persistence_dir=conversation.state.persistence_dir,
        )

    monkeypatch.setattr(
        RuntimeBootstrap,
        'create_verilator_adapter',
        fake_create_adapter,
    )
    monkeypatch.setattr(
        ConversationRunner, 'create_orchestrator_conversation', fake_create_conversation
    )
    monkeypatch.setattr(ConversationRunner, 'send_and_run', fake_send_and_run)

    session = ExecutionSession.create(bootstrap, conversation_id=uuid4())
    summary = session.run('Run green path', execute_green_path=True)

    assert summary.module_results_dir is not None
    assert summary.integration_summary_path is not None
    assert summary.deterministic_execution_path is not None
    assert Path(summary.deterministic_execution_path).is_file()
    assert (Path(summary.module_results_dir) / 'aes128_encrypt_core.json').is_file()
    assert Path(summary.integration_summary_path).is_file()
    assert (
        'deterministic AES MVP green path has already been executed successfully'
        in seen_message['message']
    )
    assert str(Path(summary.deterministic_execution_path)) in seen_message['message']
    assert 'Do not rerun raw verilator_compile' in seen_message['message']
    assert summary.execution_mode == 'deterministic-review'
    assert summary.delegate_attempted == 0
    assert summary.delegate_completed == 0
    assert summary.delegate_batch_count == 0


def test_execution_session_hybrid_delegate_writes_delegate_artifacts(
    monkeypatch, tmp_path: Path
):
    monkeypatch.setenv('CHATFIRE_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(persistence_dir=tmp_path / 'conversations')

    class RichFakeVerilatorAdapter(FakeVerilatorAdapter):
        async def simulate(
            self,
            *,
            design: str,
            top_module: str,
            output_dir: str,
            extra_arguments: dict | None = None,
        ) -> str:
            self.calls.append(
                (
                    'simulate',
                    {
                        'design': design,
                        'top_module': top_module,
                        'output_dir': output_dir,
                        'extra_arguments': extra_arguments or {},
                    },
                )
            )
            out = Path(output_dir)
            out.mkdir(parents=True, exist_ok=True)
            checkpoints = ['CHK_SBOX_MATCH']
            if top_module == 'aes128_encrypt_core':
                checkpoints = [
                    'CHK_RESET_CLEAR',
                    'CHK_START_ACCEPTED',
                    'CHK_BUSY_ASSERTED',
                    'CHK_DONE_PULSE',
                    'CHK_CIPHERTEXT_MATCH',
                    'CHK_BUSY_DEASSERTED',
                ]
            elif top_module == 'aes_key_schedule_128':
                checkpoints = ['CHK_ROUNDKEY_MATCH']
            elif top_module == 'aes_round_transform':
                checkpoints = ['CHK_ROUND_STATE_MATCH']
            (out / 'simulation.log').write_text(
                '\n'.join(f'CHECKPOINT|{name}|PASS|ok' for name in checkpoints) + '\n',
                encoding='utf-8',
            )
            (out / 'simulation.vcd').write_text('wave', encoding='utf-8')
            return f'simulated:{top_module}'

    def fake_create_adapter(self, *, conversation_id='aes-mvp'):
        return RichFakeVerilatorAdapter(self.workspace_root)

    class FakeConversation:
        def __init__(
            self, *, conversation_id, persistence_dir: Path, workspace_root: Path
        ) -> None:
            conversation_dir = persistence_dir / conversation_id.hex
            conversation_dir.mkdir(parents=True, exist_ok=True)
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
    ):
        return FakeConversation(
            conversation_id=conversation_id,
            persistence_dir=Path(persistence_dir),
            workspace_root=self.bootstrap.workspace_root,
        )

    seen_message: dict[str, str] = {}

    def fake_send_and_run(self, conversation, message):
        seen_message['message'] = message
        conversation_dir = Path(conversation.state.persistence_dir)
        events_dir = conversation_dir / 'events'
        events_dir.mkdir(parents=True, exist_ok=True)
        (events_dir / 'event-00001-delegate-action.json').write_text(
            json.dumps(
                {
                    'id': 'delegate-action',
                    'source': 'agent',
                    'tool_name': 'delegate',
                    'tool_call_id': 'call-delegate-1',
                    'tool_call': {
                        'arguments': '{"command":"spawn","ids":["module_review__aes_sbox"]}'
                    },
                }
            ),
            encoding='utf-8',
        )
        (events_dir / 'event-00002-delegate-observation.json').write_text(
            json.dumps(
                {
                    'id': 'delegate-observation',
                    'source': 'environment',
                    'tool_name': 'delegate',
                    'tool_call_id': 'call-delegate-1',
                    'observation': {
                        'is_error': False,
                        'content': [{'type': 'text', 'text': 'delegate ok'}],
                    },
                }
            ),
            encoding='utf-8',
        )
        (events_dir / 'event-00003-finish-action.json').write_text(
            json.dumps(
                {
                    'id': 'finish-action',
                    'source': 'agent',
                    'tool_name': 'finish',
                    'tool_call_id': 'call-finish-1',
                    'action': {'message': 'final summary', 'kind': 'FinishAction'},
                }
            ),
            encoding='utf-8',
        )
        (events_dir / 'event-00004-finish-observation.json').write_text(
            json.dumps(
                {
                    'id': 'finish-observation',
                    'source': 'environment',
                    'tool_name': 'finish',
                    'tool_call_id': 'call-finish-1',
                    'observation': {
                        'is_error': False,
                        'content': [{'type': 'text', 'text': 'final summary'}],
                        'kind': 'FinishObservation',
                    },
                }
            ),
            encoding='utf-8',
        )
        conversation.state.execution_status = 'finished'
        return ConversationSummary(
            conversation_id=str(conversation.state.id),
            execution_status='finished',
            event_count=4,
            workspace_root=conversation.workspace.working_dir,
            persistence_dir=conversation.state.persistence_dir,
        )

    monkeypatch.setattr(
        ConversationRunner, 'create_orchestrator_conversation', fake_create_conversation
    )
    monkeypatch.setattr(ConversationRunner, 'send_and_run', fake_send_and_run)
    monkeypatch.setattr(
        RuntimeBootstrap,
        'create_verilator_adapter',
        fake_create_adapter,
    )

    session = ExecutionSession.create(bootstrap, conversation_id=uuid4())
    summary = session.run(
        'Run hybrid delegate path',
        execute_green_path=True,
        execution_mode='hybrid-delegate',
    )

    assert summary.execution_mode == 'hybrid-delegate'
    assert summary.delegate_batch_count == 3
    assert summary.delegate_attempted == 1
    assert summary.delegate_completed == 1
    assert summary.delegate_fallback_count == 0
    assert 'Delegate plan file:' in seen_message['message']
    assert 'You must use the delegate tool before finishing.' in seen_message['message']
    assert 'For each batch in delegate_plan.batches' in seen_message['message']

    delegate_plan = json.loads(Path(summary.delegate_plan_path).read_text('utf-8'))
    assert delegate_plan['delegate_enabled'] is True
    assert delegate_plan['max_children'] == 5
    assert len(delegate_plan['batches']) == 3
    assert all(len(batch['tasks']) <= 5 for batch in delegate_plan['batches'])
    assert delegate_plan['batches'][0]['spawn']['command'] == 'spawn'
    assert delegate_plan['batches'][0]['delegate']['command'] == 'delegate'
    assert delegate_plan['batches'][0]['tasks'][0]['mode'] == 'artifact_review'
    assert Path(delegate_plan['batches'][0]['tasks'][0]['request_path']).is_file()
    assert delegate_plan['batches'][0]['tasks'][0]['request'][
        'working_directory'
    ] == str(bootstrap.workspace_root)
    assert all(
        path.startswith(str(bootstrap.workspace_root))
        for path in delegate_plan['batches'][0]['tasks'][0]['request']['writable_paths']
    )

    delegate_results = json.loads(
        Path(summary.delegate_results_path).read_text(encoding='utf-8')
    )
    assert delegate_results['attempted'] == 1
    assert delegate_results['completed'] == 1

    delegate_fallbacks = json.loads(
        Path(summary.delegate_fallbacks_path).read_text(encoding='utf-8')
    )
    assert delegate_fallbacks == []

    final_acceptance = json.loads(
        Path(summary.final_acceptance_summary_path).read_text(encoding='utf-8')
    )
    assert final_acceptance['content'] == 'final summary'


def test_execution_session_hybrid_build_writes_build_batches(
    monkeypatch, tmp_path: Path
):
    monkeypatch.setenv('CHATFIRE_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(persistence_dir=tmp_path / 'conversations')

    class FakeConversation:
        def __init__(
            self, *, conversation_id, persistence_dir: Path, workspace_root: Path
        ) -> None:
            conversation_dir = persistence_dir / conversation_id.hex
            conversation_dir.mkdir(parents=True, exist_ok=True)
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
    ):
        return FakeConversation(
            conversation_id=conversation_id,
            persistence_dir=Path(persistence_dir),
            workspace_root=self.bootstrap.workspace_root,
        )

    seen_message: dict[str, str] = {}

    def fake_send_and_run(self, conversation, message):
        seen_message['message'] = message
        conversation_dir = Path(conversation.state.persistence_dir)
        events_dir = conversation_dir / 'events'
        events_dir.mkdir(parents=True, exist_ok=True)
        (events_dir / 'event-00001-delegate-action.json').write_text(
            json.dumps(
                {
                    'id': 'delegate-action',
                    'source': 'agent',
                    'tool_name': 'delegate',
                    'tool_call_id': 'call-delegate-1',
                    'tool_call': {
                        'arguments': '{"command":"spawn","ids":["module_build__aes_sbox"]}'
                    },
                }
            ),
            encoding='utf-8',
        )
        (events_dir / 'event-00002-delegate-observation.json').write_text(
            json.dumps(
                {
                    'id': 'delegate-observation',
                    'source': 'environment',
                    'tool_name': 'delegate',
                    'tool_call_id': 'call-delegate-1',
                    'observation': {
                        'is_error': False,
                        'content': [{'type': 'text', 'text': 'delegate ok'}],
                    },
                }
            ),
            encoding='utf-8',
        )
        (events_dir / 'event-00003-finish-action.json').write_text(
            json.dumps(
                {
                    'id': 'finish-action',
                    'source': 'agent',
                    'tool_name': 'finish',
                    'tool_call_id': 'call-finish-1',
                    'action': {
                        'message': 'hybrid build summary',
                        'kind': 'FinishAction',
                    },
                }
            ),
            encoding='utf-8',
        )
        (events_dir / 'event-00004-finish-observation.json').write_text(
            json.dumps(
                {
                    'id': 'finish-observation',
                    'source': 'environment',
                    'tool_name': 'finish',
                    'tool_call_id': 'call-finish-1',
                    'observation': {
                        'is_error': False,
                        'content': [{'type': 'text', 'text': 'hybrid build summary'}],
                        'kind': 'FinishObservation',
                    },
                }
            ),
            encoding='utf-8',
        )
        conversation.state.execution_status = 'finished'
        return ConversationSummary(
            conversation_id=str(conversation.state.id),
            execution_status='finished',
            event_count=4,
            workspace_root=conversation.workspace.working_dir,
            persistence_dir=conversation.state.persistence_dir,
        )

    def fake_collect_existing(self):
        payload = {
            'conversation_id': str(self.conversation_id),
            'focus_module_id': self.focus_module_id,
            'module_results_dir': str(self.module_results_dir),
            'integration_summary_path': str(self.integration_summary_path),
            'modules': {},
            'integration': {'status': 'passed', 'campaign_count': 3},
        }
        self._write_json(self.deterministic_execution_path, payload)
        self._write_json(self.integration_summary_path, payload['integration'])
        return payload

    monkeypatch.setattr(
        ConversationRunner, 'create_orchestrator_conversation', fake_create_conversation
    )
    monkeypatch.setattr(ConversationRunner, 'send_and_run', fake_send_and_run)
    monkeypatch.setattr(
        ExecutionSession, '_collect_existing_execution_summary', fake_collect_existing
    )

    session = ExecutionSession.create(bootstrap, conversation_id=uuid4())
    summary = session.run(
        'Run hybrid build path',
        execute_green_path=True,
        execution_mode='hybrid-build',
    )

    assert summary.execution_mode == 'hybrid-build'
    assert summary.delegate_batch_count == 3
    assert summary.delegate_attempted == 1
    assert summary.delegate_completed == 1
    assert 'guarded multi-agent AES implementation lane' in seen_message['message']
    assert (
        'The first action must be delegate spawn using this exact payload:'
        in seen_message['message']
    )
    assert (
        'Immediately after the spawn succeeds, issue delegate using this exact payload:'
        in seen_message['message']
    )
    assert 'integration command' in seen_message['message']
    assert 'Delegate plan file:' in seen_message['message']

    delegate_plan = json.loads(Path(summary.delegate_plan_path).read_text('utf-8'))
    assert delegate_plan['execution_mode'] == 'hybrid-build'
    assert delegate_plan['batches'][0]['tasks'][0]['mode'] == 'build'
    assert delegate_plan['batches'][2]['tasks'][0]['mode'] == 'l2_execute'
    assert delegate_plan['batches'][2]['spawn'] == {
        'command': 'spawn',
        'ids': [],
        'agent_types': [],
    }
    assert (
        'Run the provided executor_command first to validate the node-local L0 and L1 path'
        in delegate_plan['batches'][0]['tasks'][0]['prompt']
    )
    assert (
        'run-node aes_sbox'
        in delegate_plan['batches'][0]['tasks'][0]['request']['executor_command']
    )
    assert delegate_plan['batches'][0]['tasks'][0]['request'][
        'working_directory'
    ] == str(bootstrap.workspace_root)
    assert Path(delegate_plan['batches'][0]['tasks'][0]['request_path']).is_file()
    assert all(
        path.startswith(str(bootstrap.workspace_root))
        for path in delegate_plan['batches'][0]['tasks'][0]['request']['writable_paths']
    )
    first_l2_task = delegate_plan['batches'][2]['tasks'][0]
    assert first_l2_task['worker_id'] == 'module_build__aes_key_schedule_128'
    assert first_l2_task['request']['cases'] == 8
    assert first_l2_task['request']['seed'] == 7
    assert first_l2_task['request']['vecfile'].endswith(
        'vectors/aes128/aes_key_schedule_128_kat.txt'
    )
    assert '--cases 8' in first_l2_task['request']['executor_command']
    assert '--seed 7' in first_l2_task['request']['executor_command']
    assert '--vecfile ' in first_l2_task['request']['executor_command']
    assert 'run-integration' in delegate_plan['integration_command']


def test_execution_session_writes_failure_summary_when_conversation_run_fails(
    monkeypatch, tmp_path: Path
):
    monkeypatch.setenv('CHATFIRE_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(persistence_dir=tmp_path / 'conversations')
    conversation_id = uuid4()

    class FakeConversation:
        def __init__(
            self, *, conversation_id, persistence_dir: Path, workspace_root: Path
        ) -> None:
            conversation_dir = persistence_dir / conversation_id.hex
            conversation_dir.mkdir(parents=True, exist_ok=True)
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
    ):
        return FakeConversation(
            conversation_id=conversation_id,
            persistence_dir=Path(persistence_dir),
            workspace_root=self.bootstrap.workspace_root,
        )

    def fake_send_and_run(self, conversation, message):
        raise RuntimeError(f'failed to run: {message}')

    monkeypatch.setattr(
        ConversationRunner, 'create_orchestrator_conversation', fake_create_conversation
    )
    monkeypatch.setattr(ConversationRunner, 'send_and_run', fake_send_and_run)

    session = ExecutionSession.create(bootstrap, conversation_id=conversation_id)
    try:
        session.run('Run failing path')
    except RuntimeError as exc:
        assert 'failed to run' in str(exc)
    else:
        raise AssertionError('Expected session.run() to propagate the failure')

    payload = json.loads(session.session_summary_path.read_text(encoding='utf-8'))
    assert payload['conversation_summary'] is None
    assert payload['error']['type'] == 'RuntimeError'
    assert 'failed to run' in payload['error']['message']


def test_execution_session_failure_preserves_delegate_progress(
    monkeypatch, tmp_path: Path
):
    monkeypatch.setenv('CHATFIRE_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(persistence_dir=tmp_path / 'conversations')
    conversation_id = uuid4()

    class FakeConversation:
        def __init__(
            self, *, conversation_id, persistence_dir: Path, workspace_root: Path
        ) -> None:
            conversation_dir = persistence_dir / conversation_id.hex
            conversation_dir.mkdir(parents=True, exist_ok=True)
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
    ):
        return FakeConversation(
            conversation_id=conversation_id,
            persistence_dir=Path(persistence_dir),
            workspace_root=self.bootstrap.workspace_root,
        )

    class RichFakeVerilatorAdapter(FakeVerilatorAdapter):
        async def simulate(
            self,
            *,
            design: str,
            top_module: str,
            output_dir: str,
            extra_arguments: dict | None = None,
        ) -> str:
            self.calls.append(
                (
                    'simulate',
                    {
                        'design': design,
                        'top_module': top_module,
                        'output_dir': output_dir,
                        'extra_arguments': extra_arguments or {},
                    },
                )
            )
            out = Path(output_dir)
            out.mkdir(parents=True, exist_ok=True)
            checkpoints = ['CHK_SBOX_MATCH']
            if top_module == 'aes128_encrypt_core':
                checkpoints = [
                    'CHK_RESET_CLEAR',
                    'CHK_START_ACCEPTED',
                    'CHK_BUSY_ASSERTED',
                    'CHK_DONE_PULSE',
                    'CHK_CIPHERTEXT_MATCH',
                    'CHK_BUSY_DEASSERTED',
                ]
            elif top_module == 'aes_key_schedule_128':
                checkpoints = ['CHK_ROUNDKEY_MATCH']
            elif top_module == 'aes_round_transform':
                checkpoints = ['CHK_ROUND_STATE_MATCH']
            (out / 'simulation.log').write_text(
                '\n'.join(f'CHECKPOINT|{name}|PASS|ok' for name in checkpoints) + '\n',
                encoding='utf-8',
            )
            (out / 'simulation.vcd').write_text('wave', encoding='utf-8')
            return f'simulated:{top_module}'

    def fake_create_adapter(self, *, conversation_id='aes-mvp'):
        return RichFakeVerilatorAdapter(self.workspace_root)

    def fake_send_and_run(self, conversation, message):
        conversation_dir = Path(conversation.state.persistence_dir)
        events_dir = conversation_dir / 'events'
        events_dir.mkdir(parents=True, exist_ok=True)
        (events_dir / 'event-00001-delegate-action.json').write_text(
            json.dumps(
                {
                    'id': 'delegate-action',
                    'source': 'agent',
                    'tool_name': 'delegate',
                    'tool_call_id': 'call-delegate-1',
                    'tool_call': {
                        'arguments': '{"command":"spawn","ids":["module_review__aes_sbox"]}'
                    },
                }
            ),
            encoding='utf-8',
        )
        (events_dir / 'event-00002-delegate-observation.json').write_text(
            json.dumps(
                {
                    'id': 'delegate-observation',
                    'source': 'environment',
                    'tool_name': 'delegate',
                    'tool_call_id': 'call-delegate-1',
                    'observation': {
                        'is_error': False,
                        'content': [{'type': 'text', 'text': 'delegate ok'}],
                    },
                }
            ),
            encoding='utf-8',
        )
        raise RuntimeError('provider connection dropped')

    monkeypatch.setattr(
        RuntimeBootstrap,
        'create_verilator_adapter',
        fake_create_adapter,
    )
    monkeypatch.setattr(
        ConversationRunner, 'create_orchestrator_conversation', fake_create_conversation
    )
    monkeypatch.setattr(ConversationRunner, 'send_and_run', fake_send_and_run)

    session = ExecutionSession.create(bootstrap, conversation_id=conversation_id)
    try:
        session.run(
            'Run hybrid delegate path',
            execute_green_path=True,
            execution_mode='hybrid-delegate',
        )
    except RuntimeError as exc:
        assert 'provider connection dropped' in str(exc)
    else:
        raise AssertionError('Expected session.run() to propagate the failure')

    payload = json.loads(session.session_summary_path.read_text(encoding='utf-8'))
    assert payload['conversation_summary'] is None
    assert payload['deterministic_execution'] is not None
    assert payload['delegate_batch_count'] == 3
    assert payload['delegate_attempted'] == 1
    assert payload['delegate_completed'] == 1

    delegate_results = json.loads(
        session.delegate_results_path.read_text(encoding='utf-8')
    )
    assert delegate_results['attempted'] == 1
    assert delegate_results['completed'] == 1


def test_hybrid_build_provider_failure_synthesizes_acceptance_summary(
    monkeypatch, tmp_path: Path
):
    monkeypatch.setenv('CHATFIRE_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(persistence_dir=tmp_path / 'conversations')
    conversation_id = uuid4()

    class FakeConversation:
        def __init__(
            self, *, conversation_id, persistence_dir: Path, workspace_root: Path
        ) -> None:
            conversation_dir = persistence_dir / conversation_id.hex
            conversation_dir.mkdir(parents=True, exist_ok=True)
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
    ):
        return FakeConversation(
            conversation_id=conversation_id,
            persistence_dir=Path(persistence_dir),
            workspace_root=self.bootstrap.workspace_root,
        )

    def fake_send_and_run(self, conversation, message):
        conversation_dir = Path(conversation.state.persistence_dir)
        events_dir = conversation_dir / 'events'
        events_dir.mkdir(parents=True, exist_ok=True)
        (events_dir / 'event-00001-delegate-action.json').write_text(
            json.dumps(
                {
                    'id': 'delegate-action',
                    'source': 'agent',
                    'tool_name': 'delegate',
                    'tool_call_id': 'call-delegate-1',
                    'tool_call': {
                        'arguments': '{"command":"spawn","ids":["module_build__aes_sbox"]}'
                    },
                }
            ),
            encoding='utf-8',
        )
        (events_dir / 'event-00002-delegate-observation.json').write_text(
            json.dumps(
                {
                    'id': 'delegate-observation',
                    'source': 'environment',
                    'tool_name': 'delegate',
                    'tool_call_id': 'call-delegate-1',
                    'observation': {
                        'is_error': False,
                        'content': [{'type': 'text', 'text': 'delegate ok'}],
                    },
                }
            ),
            encoding='utf-8',
        )
        raise RuntimeError(
            'litellm.APIError: APIError: OpenAIException - insufficient_user_quota'
        )

    def fake_collect_existing(self):
        payload = {
            'conversation_id': str(self.conversation_id),
            'focus_module_id': self.focus_module_id,
            'module_results_dir': str(self.module_results_dir),
            'integration_summary_path': str(self.integration_summary_path),
            'modules': {
                'aes_sbox': {
                    'module_id': 'aes_sbox',
                    'l0_result_path': '/tmp/l0.json',
                    'l1_result_path': '/tmp/l1.json',
                    'l2_result_path': None,
                }
            },
            'integration': {'status': 'passed', 'campaign_count': 3},
        }
        self._write_json(self.deterministic_execution_path, payload)
        self._write_json(self.integration_summary_path, payload['integration'])
        return payload

    monkeypatch.setattr(
        ConversationRunner, 'create_orchestrator_conversation', fake_create_conversation
    )
    monkeypatch.setattr(ConversationRunner, 'send_and_run', fake_send_and_run)
    monkeypatch.setattr(
        ExecutionSession, '_collect_existing_execution_summary', fake_collect_existing
    )

    session = ExecutionSession.create(bootstrap, conversation_id=conversation_id)
    summary = session.run(
        'Run hybrid build path',
        execute_green_path=True,
        execution_mode='hybrid-build',
    )

    assert summary.conversation_summary.execution_status == 'finished_with_fallback'
    assert summary.delegate_attempted == 1
    assert summary.delegate_completed == 1
    payload = json.loads(session.session_summary_path.read_text(encoding='utf-8'))
    assert payload['conversation_summary']['execution_status'] == (
        'finished_with_fallback'
    )
    assert payload['fallback_error']['type'] == 'RuntimeError'
    final_acceptance = json.loads(
        session.final_acceptance_summary_path.read_text(encoding='utf-8')
    )
    assert final_acceptance['status'] == 'synthesized_from_fallback'
    assert final_acceptance['integration_status'] == 'passed'


def test_conversation_runner_creates_local_conversation(monkeypatch):
    monkeypatch.setenv('CHATFIRE_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build()
    factory = SdkAgentFactory(bootstrap)
    runner = ConversationRunner(bootstrap, factory)
    conversation = runner.create_orchestrator_conversation(delete_on_close=True)
    summary = runner.describe(conversation)

    assert summary.execution_status in {'IDLE', 'initialized', 'idle'}
    assert summary.workspace_root.endswith('MultiAgent_FPGA/aes_mvp')
    assert summary.persistence_dir.endswith(
        f'MultiAgent_FPGA/aes_mvp/reports/conversations/{conversation.state.id.hex}'
    )
    conversation.close()


def test_checkpoint_parser_extracts_stable_format():
    parser = CheckpointParser()
    parsed = parser.parse_text(
        'noise\nCHECKPOINT|CHK_A|PASS|detail a\nCHECKPOINT|CHK_B|FAIL|detail b\n'
    )
    assert parsed == {'CHK_A': 'PASS|detail a', 'CHK_B': 'FAIL|detail b'}


def test_executors_write_structured_reports(tmp_path):
    package_root = tmp_path
    rtl = package_root / 'rtl'
    tb = package_root / 'tb'
    rtl.mkdir()
    tb.mkdir()
    (rtl / 'aes_sbox.v').write_text('module aes_sbox; endmodule\n', encoding='utf-8')
    (tb / 'aes_sbox_tb.cpp').write_text('// tb\n', encoding='utf-8')

    node = (
        load_default_plan_dag()
        .nodes[0]
        .model_copy(
            update={
                'rtl_files': ['rtl/aes_sbox.v'],
                'tb_file': 'tb/aes_sbox_tb.cpp',
                'build_output_dir': 'reports/l0/aes_sbox/obj_dir',
                'sim_output_dir': 'reports/l1/aes_sbox',
            }
        )
    )
    adapter = FakeVerilatorAdapter(package_root)
    l0 = L0Executor(adapter=adapter, package_root=package_root)
    l1 = L1Executor(adapter=adapter, package_root=package_root)
    l2 = L2CampaignExecutor(adapter=adapter, package_root=package_root)

    l0_report = l0.run(node)
    l1_report = l1.run(node)
    l2_report = l2.run(node, profile='rand_small', cases=8, seed=7)

    assert l0_report.path.name == 'l0_result.json'
    assert l1_report.path.name == 'module_run_result.json'
    assert l2_report.path.name == 'l2_result.json'
    assert any(call[0] == 'compile' for call in adapter.calls)
    assert any(call[0] == 'simulate' for call in adapter.calls)
    assert adapter.calls[-1][1]['extra_arguments']['plusargs'] == {
        'profile': 'rand_small',
        'cases': 8,
        'seed': 7,
    }


def test_cli_parser_exposes_generate_node_and_hybrid_generate_mode():
    parser = build_parser()
    args = parser.parse_args(['run-aes-mvp', '--execution-mode', 'hybrid-generate'])
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
        ['run-node', 'aes_sbox', '--workspace-root', '/tmp/work', '--strict-validation']
    )

    assert args.execution_mode == 'hybrid-generate'
    assert node_args.command == 'generate-node'
    assert node_args.workspace_root == '/tmp/work'
    assert node_args.strict_validation is True
    assert run_node_args.strict_validation is True


def test_hybrid_generate_delegate_plan_materializes_workspace_contracts(
    monkeypatch, tmp_path: Path
):
    monkeypatch.setenv('CHATFIRE_API_KEY', 'test-secret')
    bootstrap = RuntimeBootstrap.build(persistence_dir=tmp_path / 'conversations')
    session = ExecutionSession.create(bootstrap, conversation_id=uuid4())

    delegate_plan = session._build_delegate_plan(  # type: ignore[attr-defined]
        None,
        execution_mode='hybrid-generate',
    )

    assert delegate_plan['execution_mode'] == 'hybrid-generate'
    assert Path(session.generation_plan_path).is_file()
    assert Path(session.brief_generation_summary_path).is_file()
    assert len(delegate_plan['batches']) == 3
    assert delegate_plan['batches'][0]['tasks'][0]['mode'] == 'generate'
    assert delegate_plan['batches'][2]['tasks'][0]['mode'] == 'l2_execute'

    first_task = delegate_plan['batches'][0]['tasks'][0]
    request = first_task['request']
    assert request['workspace_root'].startswith(str(session.report_root))
    assert request['contract_paths']['design_brief'].endswith('design_brief.json')
    assert request['result_paths']['generation_result'].endswith(
        'generation_result.json'
    )
    assert request['result_paths']['workspace_state'].endswith('workspace_state.json')
    assert 'generate-node' in request['executor_command']
    assert '--strict-validation' in request['executor_command']
    assert Path(first_task['request_path']).is_file()

    generation_plan = json.loads(session.generation_plan_path.read_text('utf-8'))
    assert generation_plan['nodes'][0]['module_id'] == 'aes_sbox'
    assert Path(
        generation_plan['nodes'][0]['contract_paths']['module_contract']
    ).is_file()

    session.conversation.close()
