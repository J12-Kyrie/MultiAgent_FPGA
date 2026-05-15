"""Centralized memory retrieval, prompt injection, and workspace pre-population.

MemoryStore is the single source of truth for reference memory artifacts.
It replaces the scattered memory logic previously in skill_refs.py, generation.py,
and prompt_contracts.py.
"""

from __future__ import annotations

import logging
import re
from dataclasses import dataclass
from pathlib import Path

_MEMORY_CODE_PATTERN = re.compile(r'```(\w+)\s*\n(.*?)```', re.DOTALL)

logger = logging.getLogger(__name__)

# Default AES registry: module_id -> memory skill key
_MEMORY_REGISTRY: dict[str, str] = {
    'aes_sbox': 'aes_memory_sbox',
    'aes_key_schedule_128': 'aes_memory_key_schedule',
    'aes_round_transform': 'aes_memory_round_transform',
    'aes128_encrypt_core': 'aes_memory_encrypt_core',
}

_SHARED_MEMORY_KEY = 'aes_memory_shared'


class MemoryRegistry:
    """Dynamic module_id -> skill_key mapping, built from blueprint or defaults."""

    def __init__(
        self,
        registry: dict[str, str] | None = None,
        shared_key: str = _SHARED_MEMORY_KEY,
    ) -> None:
        self._registry = dict(registry) if registry else dict(_MEMORY_REGISTRY)
        self._shared_key = shared_key

    @classmethod
    def default(cls) -> 'MemoryRegistry':
        """Return the default AES memory registry."""
        return cls()

    @classmethod
    def from_blueprint(cls, blueprint: object) -> 'MemoryRegistry':
        """Build a registry from a BlueprintSpec's module memory sections."""
        registry: dict[str, str] = {}
        shared_key = _SHARED_MEMORY_KEY
        for module in getattr(blueprint, 'modules', []):
            mem = getattr(module, 'memory', None)
            if mem is None:
                continue
            module_id = getattr(module, 'id', '')
            rtl_skill = getattr(mem, 'rtl_skill', None)
            if rtl_skill:
                registry[module_id] = rtl_skill
            shared = getattr(mem, 'shared_skill', None)
            if shared:
                shared_key = shared
        return cls(registry=registry, shared_key=shared_key)

    def get_module_key(self, module_id: str) -> str | None:
        return self._registry.get(module_id)

    @property
    def shared_key(self) -> str:
        return self._shared_key

    @property
    def known_modules(self) -> list[str]:
        return sorted(self._registry)


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


_MODULE_INTERFACE_RE = re.compile(r'module\s+(\w+)\s*\((.*?)\);', re.DOTALL)


def _build_summary(content: str) -> str:
    """Extract structured summary from a memory skill file.

    Returns: interface, design constraints, checkpoints, pitfalls, and
    strategy hints — without the actual Verilog/C++ code.
    """
    verilog = _extract_code_block(content, 'verilog')
    lines: list[str] = []

    # 1. Module interface from Verilog code block
    if verilog:
        iface_match = _MODULE_INTERFACE_RE.search(verilog)
        if iface_match:
            module_name = iface_match.group(1)
            ports_raw = iface_match.group(2).strip()
            port_list = [p.strip() for p in ports_raw.split(',') if p.strip()]
            lines.append('## Interface')
            lines.append(f'Module: {module_name}')
            if port_list:
                lines.append('Ports:')
                for p in port_list:
                    lines.append(f'  {p}')
            lines.append('')

    # 2. Key Implementation Notes / Key Notes section
    key_notes = _extract_section(content, 'Key Implementation Notes')
    if key_notes is None:
        key_notes = _extract_section(content, 'Key Notes')
    if key_notes:
        lines.append('## Design Guidance')
        lines.append(key_notes)

    return '\n'.join(lines) if lines else '(no memory summary available)'


def _extract_section(content: str, heading: str) -> str | None:
    """Extract body text of a markdown h1 section by heading name."""
    pattern = rf'^# {re.escape(heading)}\s*\n(.*?)(?=^# |\Z)'
    match = re.search(pattern, content, re.MULTILINE | re.DOTALL)
    if match:
        return match.group(1).rstrip()
    return None


class MemoryStore:
    """Single source of truth for reference memory retrieval."""

    def __init__(
        self,
        *,
        registry: MemoryRegistry | None = None,
        memory_required: bool = True,
    ) -> None:
        from MultiAgent_FPGA.fpga_flow.skill_refs import get_memory_skill_refs

        self._refs = get_memory_skill_refs()
        self._registry = registry or MemoryRegistry.default()
        self._memory_required = memory_required

    def has_module_memory(self, module_id: str) -> bool:
        """Return True if module-specific memory is registered."""
        return self._registry.get_module_key(module_id) is not None

    def select(self, module_id: str) -> list[MemoryArtifact]:
        """Return memory artifacts relevant to a module.

        Always includes the shared memory artifact plus the module-specific one.
        """
        artifacts: list[MemoryArtifact] = []
        # Shared memory
        shared = self._load_artifact(self._registry.shared_key, module_id)
        if shared is not None:
            artifacts.append(shared)
        # Module-specific memory
        module_key = self._registry.get_module_key(module_id)
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
        """Return prompt-injectable text with summary guidance for a module.

        Injects only interface description, design constraints, checkpoints,
        pitfalls, and strategy hints — NOT the full RTL/TB code.
        """
        artifacts = self.select(module_id)
        if not artifacts:
            return ''
        blocks: list[str] = []
        for art in artifacts:
            ref = self._refs.get(art.key)
            if ref is None:
                continue
            content = ref.path.read_text(encoding='utf-8')
            summary = _build_summary(content)
            blocks.append(f'=== MEMORY: {ref.name} ===\n{summary}\n=== END MEMORY ===')
        return '\n\n'.join(blocks)

    def populate_workspace(
        self,
        module_id: str,
        workspace_root: Path,
    ) -> dict[str, Path]:
        """Write memory content to workspace draft dirs.

        Returns dict of written file paths keyed by type ('rtl', 'tb').
        Returns empty dict if no memory is registered and memory is optional.
        Raises RuntimeError if memory extraction fails and memory_required is True.
        """
        module_key = self._registry.get_module_key(module_id)
        if not module_key:
            if self._memory_required:
                raise RuntimeError(
                    f'No memory registered for module {module_id!r}. '
                    f'Known modules: {self._registry.known_modules}'
                )
            logger.warning(
                'No memory registered for module %r — agents will generate from scratch.',
                module_id,
            )
            return {}
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
