"""Runtime composition root for the AES MVP framework."""

from MultiAgent_FPGA.aes_mvp.runtime.bootstrap import RuntimeBootstrap
from MultiAgent_FPGA.aes_mvp.runtime.factory import SdkAgentFactory
from MultiAgent_FPGA.aes_mvp.runtime.runner import (
    ConversationRunner,
    ConversationSummary,
)
from MultiAgent_FPGA.aes_mvp.runtime.sdk_shim import (
    SdkEnvironmentStatus,
    SdkModules,
    SDKUnavailableError,
    discover_sdk_environment,
    load_sdk_modules,
)
from MultiAgent_FPGA.aes_mvp.runtime.session import (
    ExecutionSession,
    ExecutionSessionSummary,
)

__all__ = [
    'ConversationRunner',
    'ConversationSummary',
    'ExecutionSession',
    'ExecutionSessionSummary',
    'RuntimeBootstrap',
    'SDKUnavailableError',
    'SdkAgentFactory',
    'SdkEnvironmentStatus',
    'SdkModules',
    'discover_sdk_environment',
    'load_sdk_modules',
]
