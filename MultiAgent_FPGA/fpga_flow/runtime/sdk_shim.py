"""Import shim for the external OpenHands SDK runtime package."""

from __future__ import annotations

import os
import sys
import types
from contextlib import contextmanager, nullcontext
from dataclasses import dataclass
from importlib import import_module
from importlib.metadata import PackageNotFoundError, version
from pathlib import Path
from types import ModuleType
from typing import Any, Callable


class SDKUnavailableError(RuntimeError):
    """Raised when the external OpenHands SDK runtime package is unavailable."""


SDK_SITE_PACKAGES_ENV = 'OPENHANDS_SDK_SITE_PACKAGES'
_SDK_VALIDATION_MODULES = (
    'openhands.sdk.agent',
    'openhands.sdk.conversation',
    'openhands.sdk.context',
    'openhands.sdk.llm',
    'openhands.sdk.workspace',
    'openhands.sdk.tool',
    'openhands.sdk.subagent',
    'openhands.tools.preset.default',
    'openhands.tools.delegate',
)


def _optional_shim_site_packages() -> Path | None:
    """Return a site-packages dir to prepend, or None to use the active interpreter only.

    We **do not** auto-prepend a hardcoded Poetry path: if that directory exists on disk but
    contains a stale or partial ``openhands-sdk``, it shadows a healthy install in the
    current conda/venv and imports fail with errors such as
    ``'>=' not supported between instances of 'NoneType' and 'str'``.

    Set ``OPENHANDS_SDK_SITE_PACKAGES`` explicitly when you must load the SDK from a
    non-default location (e.g. a specific Poetry virtualenv).
    """
    override = os.environ.get(SDK_SITE_PACKAGES_ENV)
    if not (override and str(override).strip()):
        return None
    resolved = Path(override).expanduser().resolve()
    return resolved if resolved.is_dir() else None


@contextmanager
def _prepend_sys_path(path: Path):
    resolved = str(path)
    removed = False
    if sys.path[:1] != [resolved]:
        sys.path.insert(0, resolved)
        removed = True
    try:
        yield
    finally:
        if removed and sys.path[:1] == [resolved]:
            sys.path.pop(0)


def _ensure_sdk_compatibility() -> None:
    # --- rich compatibility (tracebacks_max_frames kwarg removal) ---
    try:
        from rich.logging import RichHandler
    except ImportError:
        RichHandler = None  # type: ignore[assignment,misc]

    if RichHandler is not None and not getattr(
        RichHandler.__init__, '_fpga_flow_compat', False
    ):
        original_init = RichHandler.__init__

        def _compat_init(self, *args, **kwargs):
            kwargs.pop('tracebacks_max_frames', None)
            return original_init(self, *args, **kwargs)

        _compat_init._fpga_flow_compat = True  # type: ignore[attr-defined]
        RichHandler.__init__ = _compat_init  # type: ignore[assignment]

    # --- protobuf stub (only when google.protobuf is unavailable) ---
    try:
        import google.protobuf  # type: ignore[import-not-found]
    except Exception:
        google = sys.modules.get('google')
        if google is None:
            google = types.ModuleType('google')
            google.__path__ = []  # type: ignore[attr-defined]
            sys.modules['google'] = google

        protobuf = types.ModuleType('google.protobuf')
        protobuf.__path__ = []  # type: ignore[attr-defined]
        protobuf_json_format = types.ModuleType('google.protobuf.json_format')

        def _message_to_dict(*args, **kwargs):
            return {}

        def _parse_dict(*args, **kwargs):
            return None

        protobuf_json_format.MessageToDict = _message_to_dict
        protobuf_json_format.ParseDict = _parse_dict
        protobuf.json_format = protobuf_json_format  # type: ignore[attr-defined]
        sys.modules['google.protobuf'] = protobuf
        sys.modules['google.protobuf.json_format'] = protobuf_json_format


@dataclass(frozen=True)
class SdkEnvironmentStatus:
    available: bool
    package_name: str | None
    version: str | None
    message: str


@dataclass(frozen=True)
class SdkModules:
    sdk: ModuleType
    tools_preset: ModuleType
    delegate: ModuleType
    Agent: type
    Conversation: type
    AgentContext: type
    LLM: type
    LocalWorkspace: type
    Tool: type
    load_project_skills: Callable[..., Any]
    register_agent: Callable[..., Any]
    register_agent_if_absent: Callable[..., Any]
    get_default_tools: Callable[..., Any]
    DelegateTool: type


def discover_sdk_environment() -> SdkEnvironmentStatus:
    try:
        shim_root = _optional_shim_site_packages()
        ctx = _prepend_sys_path(shim_root) if shim_root is not None else nullcontext()
        with ctx:
            _ensure_sdk_compatibility()
            for module_name in _SDK_VALIDATION_MODULES:
                import_module(module_name)
    except Exception as exc:
        hint = (
            ' Use the same interpreter as `poetry run` (or run `poetry install` in '
            'the repo root) so `openhands-sdk` matches `pyproject.toml`. '
            'Do not set OPENHANDS_SDK_SITE_PACKAGES unless it points at a complete '
            'site-packages tree for that SDK.'
        )
        return SdkEnvironmentStatus(
            available=False,
            package_name=None,
            version=None,
            message=(
                'OpenHands SDK runtime package is unavailable. '
                f'{type(exc).__name__}: {exc}.' + hint
            ),
        )

    try:
        pkg_version = version('openhands-sdk')
    except PackageNotFoundError:
        pkg_version = None
    return SdkEnvironmentStatus(
        available=True,
        package_name='openhands.sdk',
        version=pkg_version,
        message='OpenHands SDK runtime package is available.',
    )


def load_sdk_modules() -> SdkModules:
    status = discover_sdk_environment()
    if not status.available:
        raise SDKUnavailableError(status.message)

    try:
        site_packages_root = _optional_shim_site_packages()
        ctx = (
            _prepend_sys_path(site_packages_root)
            if site_packages_root is not None
            else nullcontext()
        )
        with ctx:
            # _ensure_sdk_compatibility() already ran in discover_sdk_environment() above
            agent_mod = import_module('openhands.sdk.agent')
            conversation_mod = import_module('openhands.sdk.conversation')
            context_mod = import_module('openhands.sdk.context')
            llm_mod = import_module('openhands.sdk.llm')
            workspace_mod = import_module('openhands.sdk.workspace')
            tool_mod = import_module('openhands.sdk.tool')
            tools_preset = import_module('openhands.tools.preset.default')
            delegate = import_module('openhands.tools.delegate')
            subagent = import_module('openhands.sdk.subagent')
            sdk = types.ModuleType('openhands.sdk')
            sdk.Agent = agent_mod.Agent
            sdk.Conversation = conversation_mod.Conversation
            sdk.AgentContext = context_mod.AgentContext
            sdk.LLM = llm_mod.LLM
            sdk.LocalWorkspace = workspace_mod.LocalWorkspace
            sdk.Tool = tool_mod.Tool
            sdk.load_project_skills = context_mod.load_project_skills
            sdk.register_agent = subagent.register_agent
            sdk.register_agent_if_absent = subagent.register_agent_if_absent
    except Exception as exc:
        raise SDKUnavailableError(
            f'OpenHands SDK runtime package could not be loaded from site-packages: {exc}'
        ) from exc
    return SdkModules(
        sdk=sdk,
        tools_preset=tools_preset,
        delegate=delegate,
        Agent=sdk.Agent,
        Conversation=sdk.Conversation,
        AgentContext=sdk.AgentContext,
        LLM=sdk.LLM,
        LocalWorkspace=sdk.LocalWorkspace,
        Tool=sdk.Tool,
        load_project_skills=sdk.load_project_skills,
        register_agent=sdk.register_agent,
        register_agent_if_absent=subagent.register_agent_if_absent,
        get_default_tools=tools_preset.get_default_tools,
        DelegateTool=delegate.DelegateTool,
    )
