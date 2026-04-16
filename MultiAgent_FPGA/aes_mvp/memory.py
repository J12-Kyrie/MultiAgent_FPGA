"""Centralized memory retrieval, prompt injection, and workspace pre-population.

MemoryStore is the single source of truth for AES reference memory artifacts.
It replaces the scattered memory logic previously in skill_refs.py, generation.py,
and prompt_contracts.py.
"""

from __future__ import annotations

import re
from dataclasses import dataclass
from pathlib import Path

_MEMORY_CODE_PATTERN = re.compile(r'```(\w+)\s*\n(.*?)```', re.DOTALL)

# Registry: module_id -> memory skill key
# Add task_type dimension when a second task type materializes.
_MEMORY_REGISTRY: dict[str, str] = {
    'aes_sbox': 'aes_memory_sbox',
    'aes_key_schedule_128': 'aes_memory_key_schedule',
    'aes_round_transform': 'aes_memory_round_transform',
    'aes128_encrypt_core': 'aes_memory_encrypt_core',
}

_SHARED_MEMORY_KEY = 'aes_memory_shared'


@dataclass(frozen=True)
class MemoryArtifact:
    """A single memory artifact extracted from a skill file."""

    key: str
    module_id: str
    content_rtl: str | None
    content_tb: str | None
    source_path: Path


def _extract_code_block(text: str, language: str) -> str | None:
    """Extract the first code block of the given language from markdown."""
    for match in _MEMORY_CODE_PATTERN.finditer(text):
        if match.group(1) == language:
            return match.group(2).rstrip('\n') + '\n'
    return None


def _strip_yaml_frontmatter(text: str) -> str:
    """Remove YAML frontmatter (between --- delimiters) from a skill file."""
    if not text.startswith('---'):
        return text
    end = text.find('---', 3)
    if end == -1:
        return text
    return text[end + 3 :].lstrip('\n')


class MemoryStore:
    """Single source of truth for AES reference memory retrieval."""

    def __init__(self) -> None:
        from MultiAgent_FPGA.aes_mvp.skill_refs import get_memory_skill_refs

        self._refs = get_memory_skill_refs()

    def select(self, module_id: str) -> list[MemoryArtifact]:
        """Return memory artifacts relevant to a module.

        Always includes the shared memory artifact plus the module-specific one.
        """
        artifacts: list[MemoryArtifact] = []
        # Shared memory (aes_sbox_lut.vh + aes_tb_common.hpp context)
        shared = self._load_artifact(_SHARED_MEMORY_KEY, module_id)
        if shared is not None:
            artifacts.append(shared)
        # Module-specific memory
        module_key = _MEMORY_REGISTRY.get(module_id)
        if module_key:
            art = self._load_artifact(module_key, module_id)
            if art is not None:
                artifacts.append(art)
        return artifacts

    def retrieve(self, key: str) -> MemoryArtifact:
        """Return a single artifact by key. Raises KeyError if not found."""
        ref = self._refs.get(key)
        if ref is None or not ref.path.is_file():
            raise KeyError(f'Memory artifact not found: {key!r}')
        content = ref.path.read_text(encoding='utf-8')
        return MemoryArtifact(
            key=key,
            module_id='',
            content_rtl=_extract_code_block(content, 'verilog'),
            content_tb=_extract_code_block(content, 'cpp'),
            source_path=ref.path,
        )

    def build_prompt_block(self, module_id: str) -> str:
        """Return prompt-injectable text with full RTL+TB code for a module."""
        artifacts = self.select(module_id)
        if not artifacts:
            return ''
        blocks: list[str] = []
        for art in artifacts:
            ref = self._refs.get(art.key)
            if ref is None:
                continue
            content = ref.path.read_text(encoding='utf-8')
            body = _strip_yaml_frontmatter(content)
            blocks.append(f'=== MEMORY: {ref.name} ===\n{body}\n=== END MEMORY ===')
        return '\n\n'.join(blocks)

    def populate_workspace(
        self,
        module_id: str,
        workspace_root: Path,
    ) -> dict[str, Path]:
        """Write memory content to workspace draft dirs.

        Returns dict of written file paths keyed by type ('rtl', 'tb').
        Raises RuntimeError if memory extraction fails.
        """
        module_key = _MEMORY_REGISTRY.get(module_id)
        if not module_key:
            raise RuntimeError(
                f'No memory registered for module {module_id!r}. '
                f'Known modules: {sorted(_MEMORY_REGISTRY)}'
            )
        ref = self._refs.get(module_key)
        if ref is None or not ref.path.is_file():
            raise RuntimeError(
                f'Memory skill file not found for {module_id!r}: key={module_key!r}'
            )
        content = ref.path.read_text(encoding='utf-8')
        rtl = _extract_code_block(content, 'verilog')
        tb = _extract_code_block(content, 'cpp')
        if rtl is None or tb is None:
            raise RuntimeError(
                f'Memory extraction failed for {module_id}: '
                f'rtl={"ok" if rtl else "MISSING"}, '
                f'tb={"ok" if tb else "MISSING"}. '
                f'All modules require verified memory skill files.'
            )
        written: dict[str, Path] = {}
        draft_rtl_dir = workspace_root / 'draft' / 'rtl'
        draft_rtl_dir.mkdir(parents=True, exist_ok=True)
        rtl_path = draft_rtl_dir / f'{module_id}.v'
        if not rtl_path.exists():
            rtl_path.write_text(rtl, encoding='utf-8')
        written['rtl'] = rtl_path

        draft_tb_dir = workspace_root / 'draft' / 'tb'
        draft_tb_dir.mkdir(parents=True, exist_ok=True)
        tb_path = draft_tb_dir / f'{module_id}_tb.cpp'
        if not tb_path.exists():
            tb_path.write_text(tb, encoding='utf-8')
        written['tb'] = tb_path

        return written

    def _load_artifact(
        self,
        key: str,
        module_id: str,
    ) -> MemoryArtifact | None:
        ref = self._refs.get(key)
        if ref is None or not ref.path.is_file():
            return None
        content = ref.path.read_text(encoding='utf-8')
        return MemoryArtifact(
            key=key,
            module_id=module_id,
            content_rtl=_extract_code_block(content, 'verilog'),
            content_tb=_extract_code_block(content, 'cpp'),
            source_path=ref.path,
        )
