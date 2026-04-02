"""Verilator MCP adapter for the AES MVP framework."""

from __future__ import annotations

import json
import os
import shutil
from pathlib import Path
from typing import Any

from MultiAgent_FPGA.aes_mvp.paths import REPO_ROOT
from openhands.core.config.mcp_config import MCPStdioServerConfig
from openhands.events.action.mcp import MCPAction
from openhands.events.observation.mcp import MCPObservation
from openhands.mcp.utils import call_tool_mcp, create_mcp_clients

VERILATOR_MCP_ENTRYPOINT_ENV = 'VERILATOR_MCP_ENTRYPOINT'
VERILATOR_BIN = Path('/opt/homebrew/bin/verilator')
_PASSTHROUGH_ENV_KEYS = ('TMPDIR', 'LANG', 'LC_ALL', 'LC_CTYPE')


def default_verilator_mcp_entrypoint() -> Path:
    env_value = os.environ.get(VERILATOR_MCP_ENTRYPOINT_ENV)
    if env_value:
        return Path(env_value)
    return REPO_ROOT / 'mcp4eda' / 'verilator-mcp' / 'dist' / 'index.js'


def build_verilator_stdio_server(
    *,
    name: str = 'verilator',
    entrypoint: Path | None = None,
) -> MCPStdioServerConfig:
    node = shutil.which('node')
    if node is None:
        raise RuntimeError('node is required to launch verilator-mcp')
    if not VERILATOR_BIN.is_file():
        raise RuntimeError(f'Expected Verilator at {VERILATOR_BIN}')

    resolved_entrypoint = (entrypoint or default_verilator_mcp_entrypoint()).resolve()
    if not resolved_entrypoint.is_file():
        raise RuntimeError(f'Missing verilator-mcp entrypoint: {resolved_entrypoint}')

    inherited_path = os.environ.get('PATH', '')
    env = {
        'PATH': f'{VERILATOR_BIN.parent}:{inherited_path}'.rstrip(':'),
        'HOME': str(Path.home()),
        'LOG_LEVEL': 'info',
        'VERILATOR_PATH': str(VERILATOR_BIN),
    }
    for key in _PASSTHROUGH_ENV_KEYS:
        value = os.environ.get(key)
        if value:
            env[key] = value
    return MCPStdioServerConfig(
        name=name,
        command=node,
        args=[str(resolved_entrypoint)],
        env=env,
    )


def _extract_text(observation: MCPObservation) -> str:
    payload = json.loads(observation.content)
    if payload.get('isError', False):
        raise RuntimeError(json.dumps(payload, indent=2))
    content = payload.get('content', [])
    if not content or content[0].get('type') != 'text':
        raise RuntimeError(f'Unexpected MCP payload: {payload}')
    return content[0]['text']


class VerilatorMCPAdapter:
    """Thin async adapter over the repo's Verilator MCP integration."""

    def __init__(self, *, conversation_id: str = 'aes-mvp') -> None:
        self._conversation_id = conversation_id

    async def _create_clients(self):
        server = build_verilator_stdio_server()
        mcp_clients = await create_mcp_clients(
            sse_servers=[],
            shttp_servers=[],
            conversation_id=self._conversation_id,
            stdio_servers=[server],
        )
        if not mcp_clients:
            raise RuntimeError('Failed to connect to verilator-mcp')
        return mcp_clients

    async def verify_required_tools(self) -> list[str]:
        mcp_clients = await self._create_clients()
        tool_names = [tool.name for client in mcp_clients for tool in client.tools]
        missing = {'verilator_compile', 'verilator_simulate'}.difference(tool_names)
        if missing:
            raise RuntimeError(
                f'verilator-mcp is missing expected tools: {sorted(missing)}; got {tool_names}'
            )
        return tool_names

    async def compile(
        self,
        *,
        files: list[str],
        top_module: str,
        output_dir: str,
        extra_arguments: dict[str, Any] | None = None,
    ) -> str:
        mcp_clients = await self._create_clients()
        default_verilator_flags: list[str] = []
        if any(path.endswith(('.cpp', '.cc', '.cxx')) for path in files):
            default_verilator_flags.extend(['-CFLAGS', '-std=c++17'])
        arguments = {
            'files': files,
            'topModule': top_module,
            'outputDir': output_dir,
            'language': 'verilog',
        }
        if extra_arguments:
            arguments.update(extra_arguments)
        existing_flags = list(arguments.get('verilatorFlags', []))
        if default_verilator_flags:
            arguments['verilatorFlags'] = [
                *default_verilator_flags,
                *existing_flags,
            ]
        observation = await call_tool_mcp(
            mcp_clients,
            MCPAction(name='verilator_compile', arguments=arguments),
        )
        return _extract_text(observation)

    async def simulate(
        self,
        *,
        design: str,
        top_module: str,
        output_dir: str,
        extra_arguments: dict[str, Any] | None = None,
    ) -> str:
        mcp_clients = await self._create_clients()
        arguments = {
            'design': design,
            'topModule': top_module,
            'outputDir': output_dir,
            'useExistingBuild': True,
            'autoGenerateTestbench': False,
            'enableWaveform': True,
        }
        if extra_arguments:
            arguments.update(extra_arguments)
        observation = await call_tool_mcp(
            mcp_clients,
            MCPAction(name='verilator_simulate', arguments=arguments),
        )
        return _extract_text(observation)
