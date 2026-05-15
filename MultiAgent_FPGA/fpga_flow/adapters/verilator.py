"""Verilator MCP adapter for the AES MVP framework.

Uses the standalone ``mcp`` Python package for stdio-based MCP communication,
decoupled from the OpenHands SDK's internal MCP implementation.
"""

from __future__ import annotations

import os
import shutil
from contextlib import asynccontextmanager
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, AsyncIterator

from mcp import ClientSession, StdioServerParameters
from mcp.client.stdio import stdio_client

from MultiAgent_FPGA.fpga_flow.paths import REPO_ROOT

VERILATOR_MCP_ENTRYPOINT_ENV = 'VERILATOR_MCP_ENTRYPOINT'
VERILATOR_BIN = Path('/opt/homebrew/bin/verilator')
_PASSTHROUGH_ENV_KEYS = ('TMPDIR', 'LANG', 'LC_ALL', 'LC_CTYPE')


def default_verilator_mcp_entrypoint() -> Path:
    env_value = os.environ.get(VERILATOR_MCP_ENTRYPOINT_ENV)
    if env_value:
        return Path(env_value)
    return REPO_ROOT / 'mcp4eda' / 'verilator-mcp' / 'dist' / 'index.js'


@dataclass(frozen=True)
class VerilatorServerConfig:
    """MCP server config for the Verilator stdio server."""

    name: str
    command: str
    args: list[str] = field(default_factory=list)
    env: dict[str, str] = field(default_factory=dict)


def build_verilator_stdio_server(
    *,
    name: str = 'verilator',
    entrypoint: Path | None = None,
) -> VerilatorServerConfig:
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
    return VerilatorServerConfig(
        name=name,
        command=node,
        args=[str(resolved_entrypoint)],
        env=env,
    )


_VERILOG_SOURCE_SUFFIXES = frozenset({'.v', '.sv'})
_CPP_TB_SUFFIXES = frozenset({'.cpp', '.cc', '.cxx'})


def _filter_verilator_input_files(files: list[str]) -> list[str]:
    """Drop directories and unknown extensions (Verilator treats stray paths as source files)."""
    out: list[str] = []
    for raw in files:
        path = Path(raw)
        if not path.is_file():
            continue
        suf = path.suffix.lower()
        if suf in _VERILOG_SOURCE_SUFFIXES or suf in _CPP_TB_SUFFIXES:
            out.append(str(path.resolve()))
    return out


def _verilog_include_directories(files: list[str]) -> list[str]:
    """Parent dirs of Verilog sources so `` `include "*.vh" `` resolves (e.g. rtl/)."""
    ordered: list[str] = []
    seen: set[str] = set()
    for raw in files:
        path = Path(raw)
        if path.suffix.lower() not in _VERILOG_SOURCE_SUFFIXES:
            continue
        if not path.is_file():
            continue
        key = str(path.parent.resolve())
        if key not in seen:
            seen.add(key)
            ordered.append(key)
    return ordered


def _extract_text_from_result(result: Any) -> str:
    """Extract text from a CallToolResult, raising on error."""
    if result.isError:
        texts = [c.text for c in result.content if hasattr(c, 'text')]
        raise RuntimeError('\n'.join(texts) if texts else 'MCP tool returned an error')
    for block in result.content:
        if hasattr(block, 'text'):
            return block.text
    raise RuntimeError(f'Unexpected MCP result content: {result.content}')


class VerilatorMCPAdapter:
    """Thin async adapter over the repo's Verilator MCP integration."""

    def __init__(self, *, conversation_id: str = 'aes-mvp') -> None:
        self._conversation_id = conversation_id

    @asynccontextmanager
    async def _session(self) -> AsyncIterator[ClientSession]:
        """Create an MCP stdio session to the verilator-mcp server."""
        cfg = build_verilator_stdio_server()
        params = StdioServerParameters(
            command=cfg.command,
            args=cfg.args,
            env=cfg.env or None,
        )
        async with stdio_client(params) as (read, write):
            async with ClientSession(read, write) as session:
                try:
                    await session.initialize()
                except Exception as exc:
                    raise RuntimeError(
                        f'Failed to initialize verilator-mcp session: {exc}'
                    ) from exc
                yield session

    async def compile(
        self,
        *,
        files: list[str],
        top_module: str,
        output_dir: str,
        extra_arguments: dict[str, Any] | None = None,
    ) -> str:
        default_verilator_flags: list[str] = []
        filtered_files = _filter_verilator_input_files(files)
        if any(Path(p).suffix.lower() in _CPP_TB_SUFFIXES for p in filtered_files):
            default_verilator_flags.extend(['-CFLAGS', '-std=c++17'])
        arguments: dict[str, Any] = {
            'files': filtered_files,
            'topModule': top_module,
            'outputDir': output_dir,
            'language': 'verilog',
            'trace': True,
        }
        if extra_arguments:
            arguments.update(extra_arguments)
        # Always re-filter files after merge (callers may pass extra_arguments['files']).
        arguments['files'] = _filter_verilator_input_files(list(arguments['files']))
        explicit_includes = list(arguments.pop('includes', None) or [])
        auto_includes = _verilog_include_directories(arguments['files'])
        merged_includes: list[str] = []
        inc_seen: set[str] = set()
        for directory in [*auto_includes, *explicit_includes]:
            if directory not in inc_seen:
                inc_seen.add(directory)
                merged_includes.append(directory)
        # Use single-arg -I/path in verilatorFlags only. Some MCP clients mishandle a
        # separate "includes" list and append directory paths as Verilog sources.
        include_flags = [f'-I{directory}' for directory in merged_includes]
        existing_flags = list(arguments.get('verilatorFlags', []))
        arguments['verilatorFlags'] = [
            *include_flags,
            *default_verilator_flags,
            *existing_flags,
        ]
        if not arguments['files']:
            raise ValueError(
                'verilator_compile: no .v/.sv/.cpp inputs after path filtering; '
                'check package_root and compile file list.'
            )
        async with self._session() as session:
            result = await session.call_tool('verilator_compile', arguments=arguments)
            return _extract_text_from_result(result)

    async def simulate(
        self,
        *,
        design: str,
        top_module: str,
        output_dir: str,
        extra_arguments: dict[str, Any] | None = None,
    ) -> str:
        arguments: dict[str, Any] = {
            'design': design,
            'topModule': top_module,
            'outputDir': output_dir,
            'useExistingBuild': True,
            'autoGenerateTestbench': False,
            'enableWaveform': True,
        }
        if extra_arguments:
            arguments.update(extra_arguments)
        async with self._session() as session:
            result = await session.call_tool('verilator_simulate', arguments=arguments)
            return _extract_text_from_result(result)
