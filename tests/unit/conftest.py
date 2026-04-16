"""Shared V0 module stubs for MultiAgent FPGA tests.

These stubs register fake ``openhands.*`` modules so that the AES MVP code
(which imports from those packages at module load time) can be imported in
test environments where the full OpenHands SDK is not installed.

pytest loads conftest.py before any test modules in the same directory,
so these stubs are available before any test file imports project code.
"""

from __future__ import annotations

import logging
import sys
import types

# -- pythonjsonlogger --------------------------------------------------------
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

# -- google.api_core / google.cloud.storage ----------------------------------
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

# -- openhands.core.config ---------------------------------------------------
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

# -- openhands.core.config.mcp_config ----------------------------------------
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

# -- openhands.events.action.mcp ---------------------------------------------
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

# -- openhands.events.observation.mcp ----------------------------------------
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

# -- openhands.mcp.utils -----------------------------------------------------
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
