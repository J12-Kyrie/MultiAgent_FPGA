"""References to the repository skills that constrain the FPGA runtime."""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path

from MultiAgent_FPGA.fpga_flow.paths import REPO_ROOT


@dataclass(frozen=True)
class SkillRef:
    name: str
    path: Path
    purpose: str


def _skills_root() -> Path:
    return REPO_ROOT / '.openhands' / 'skills'


class SkillRegistry:
    """Dynamic skill registry that can load from a design directory or defaults."""

    def __init__(
        self,
        runtime: dict[str, SkillRef] | None = None,
        memory: dict[str, SkillRef] | None = None,
        documentation: dict[str, SkillRef] | None = None,
    ) -> None:
        self._runtime = runtime or {}
        self._memory = memory or {}
        self._documentation = documentation or {}

    @classmethod
    def default(cls) -> 'SkillRegistry':
        """Return the default registry with hardcoded AES skills."""
        return cls(
            runtime=get_runtime_skill_refs(),
            memory=get_memory_skill_refs(),
            documentation=get_documentation_skill_refs(),
        )

    @classmethod
    def from_design_dir(cls, design_dir: Path) -> 'SkillRegistry':
        """Build a registry by scanning a design directory for skill files."""
        skills_dir = design_dir / 'skills'
        memory_dir = design_dir / 'memory'
        runtime: dict[str, SkillRef] = {}
        memory: dict[str, SkillRef] = {}
        # Scan skills/ for runtime + documentation skills
        if skills_dir.is_dir():
            for md_file in sorted(skills_dir.glob('*.md')):
                key = md_file.stem
                runtime[key] = SkillRef(
                    name=key.replace('_', '-'),
                    path=md_file,
                    purpose=f'Design skill: {key}',
                )
        # Scan memory/ for memory skills
        if memory_dir.is_dir():
            for md_file in sorted(memory_dir.glob('*.md')):
                key = md_file.stem
                memory[key] = SkillRef(
                    name=key.replace('_', '-'),
                    path=md_file,
                    purpose=f'Memory skill: {key}',
                )
        # Always include framework-level docs from default
        return cls(
            runtime=runtime,
            memory=memory,
            documentation=get_documentation_skill_refs(),
        )

    @property
    def runtime_refs(self) -> dict[str, SkillRef]:
        return dict(self._runtime)

    @property
    def memory_refs(self) -> dict[str, SkillRef]:
        return dict(self._memory)

    @property
    def documentation_refs(self) -> dict[str, SkillRef]:
        return dict(self._documentation)

    @property
    def all_refs(self) -> dict[str, SkillRef]:
        return {**self._runtime, **self._memory, **self._documentation}

    def worker_skill_keys(self) -> tuple[str, ...]:
        """Return available worker skill keys from runtime registry."""
        return tuple(self._runtime.keys())

    def memory_skill_keys(self) -> tuple[str, ...]:
        """Return available memory skill keys."""
        return tuple(self._memory.keys())

    def validate_paths(self) -> None:
        """Validate that registered skill files exist on disk."""
        refs = {**self._runtime, **self._memory}
        missing = [ref.path for ref in refs.values() if not ref.path.is_file()]
        if missing:
            missing_paths = ', '.join(str(p) for p in missing)
            raise FileNotFoundError(f'Missing required skill files: {missing_paths}')


def get_runtime_skill_refs() -> dict[str, SkillRef]:
    """Return the 5 agent-injected skills (used in *_SKILL_KEYS tuples)."""
    skills_root = _skills_root()
    return {
        'aes_verilator_profile': SkillRef(
            name='aes-verilator-profile',
            path=skills_root / 'aes_verilator_profile.md',
            purpose='AES node taxonomy, vectors, checkpoints, and L2 conventions',
        ),
        'aes_module_patterns': SkillRef(
            name='aes-module-patterns',
            path=skills_root / 'aes_module_patterns.md',
            purpose='Reference module patterns for S-box, key schedule, round transform, and top integration',
        ),
        'aes_tb_contracts': SkillRef(
            name='aes-tb-contracts',
            path=skills_root / 'aes_tb_contracts.md',
            purpose='Self-checking .cpp testbench contracts, vectors, and checkpoint semantics',
        ),
        'aes_repair_heuristics': SkillRef(
            name='aes-repair-heuristics',
            path=skills_root / 'aes_repair_heuristics.md',
            purpose='Common AES repair heuristics for compile, checkpoint, latency, and handshake failures',
        ),
        'openhands_sdk_subagent_delegation': SkillRef(
            name='openhands-sdk-subagent-delegation',
            path=skills_root / 'openhands_sdk_subagent_delegation.md',
            purpose='Subagent registration, spawn, delegate, and task-boundary rules',
        ),
    }


def get_memory_skill_refs() -> dict[str, SkillRef]:
    """Return the 5 AES reference memory skills (owned by memory.py)."""
    skills_root = _skills_root()
    return {
        'aes_memory_sbox': SkillRef(
            name='aes-memory-sbox',
            path=skills_root / 'aes_memory_sbox.md',
            purpose='Verified reference RTL+TB for aes_sbox',
        ),
        'aes_memory_key_schedule': SkillRef(
            name='aes-memory-key-schedule',
            path=skills_root / 'aes_memory_key_schedule.md',
            purpose='Verified reference RTL+TB for aes_key_schedule_128',
        ),
        'aes_memory_round_transform': SkillRef(
            name='aes-memory-round-transform',
            path=skills_root / 'aes_memory_round_transform.md',
            purpose='Verified reference RTL+TB for aes_round_transform',
        ),
        'aes_memory_encrypt_core': SkillRef(
            name='aes-memory-encrypt-core',
            path=skills_root / 'aes_memory_encrypt_core.md',
            purpose='Verified reference RTL+TB for aes128_encrypt_core',
        ),
        'aes_memory_shared': SkillRef(
            name='aes-memory-shared',
            path=skills_root / 'aes_memory_shared.md',
            purpose='Verified reference for shared AES utilities (aes_sbox_lut.vh + aes_tb_common.hpp)',
        ),
    }


def get_documentation_skill_refs() -> dict[str, SkillRef]:
    """Return the 3 doc-only skills (used by synthesis.py for ModuleDesignBrief hints)."""
    skills_root = _skills_root()
    return {
        'verilator_mcp_setup': SkillRef(
            name='verilator-mcp-setup',
            path=skills_root / 'verilator_mcp_setup.md',
            purpose='MCP setup and smoke-test logic only',
        ),
        'verilog_verilator': SkillRef(
            name='verilog-verilator',
            path=skills_root / 'verilog_verilator.md',
            purpose='Strict compile-then-simulate Verilator runtime policy',
        ),
        'aes_spec_decomposition': SkillRef(
            name='aes-spec-decomposition',
            path=skills_root / 'aes_spec_decomposition.md',
            purpose='AES spec decomposition patterns for autonomous SpecIR and PlanDAG synthesis',
        ),
    }


def get_all_skill_refs() -> dict[str, SkillRef]:
    """Return union of all three registries (13 total) for backward-compat callers."""
    return {
        **get_runtime_skill_refs(),
        **get_memory_skill_refs(),
        **get_documentation_skill_refs(),
    }


def validate_skill_paths() -> None:
    """Validate that runtime + memory skill files exist on disk.

    Doc-only skills are validated lazily when accessed via select_skill_refs().
    """
    refs = {**get_runtime_skill_refs(), **get_memory_skill_refs()}
    missing = [ref.path for ref in refs.values() if not ref.path.is_file()]
    if missing:
        missing_paths = ', '.join(str(path) for path in missing)
        raise FileNotFoundError(
            f'Missing required AES MVP skill files: {missing_paths}'
        )


# -- Design-aware skill groups --
# AES-specific skills (only injected for AES designs)
_AES_ORCHESTRATOR_SKILL_KEYS = ('aes_verilator_profile',)
_AES_WORKER_FPGA_CORE_SKILL_KEYS = (
    'aes_verilator_profile',
    'aes_module_patterns',
    'aes_tb_contracts',
)
_AES_REPAIR_SKILL_KEYS = ('aes_repair_heuristics',)
_AES_VALIDATE_SKILL_KEYS = ('aes_verilator_profile',)
_AES_L2_SKILL_KEYS = ('aes_verilator_profile',)

# Generic skills (for non-AES designs — no design-specific skills injected)
_GENERIC_ORCHESTRATOR_SKILL_KEYS: tuple[str, ...] = ()
_GENERIC_WORKER_SKILL_KEYS: tuple[str, ...] = ()
_GENERIC_REPAIR_SKILL_KEYS: tuple[str, ...] = ()
_GENERIC_VALIDATE_SKILL_KEYS: tuple[str, ...] = ()
_GENERIC_L2_SKILL_KEYS: tuple[str, ...] = ()


def _is_aes_design(design_name: str | None) -> bool:
    if not design_name:
        return True
    return design_name.upper().startswith('AES')


def orchestrator_skill_keys(design_name: str | None = None) -> tuple[str, ...]:
    if _is_aes_design(design_name):
        return _AES_ORCHESTRATOR_SKILL_KEYS
    return _GENERIC_ORCHESTRATOR_SKILL_KEYS


# Backward-compat aliases (default to AES)
ORCHESTRATOR_CORE_SKILL_KEYS = _AES_ORCHESTRATOR_SKILL_KEYS

SDK_DELEGATION_SKILL_KEYS = ('openhands_sdk_subagent_delegation',)

FINALIZER_SKILL_KEYS: tuple[str, ...] = ()

# Backward-compat aliases
WORKER_FPGA_CORE_SKILL_KEYS = _AES_WORKER_FPGA_CORE_SKILL_KEYS
REPAIR_CORE_SKILL_KEYS = _AES_REPAIR_SKILL_KEYS
WORKER_SKILL_KEYS = (*_AES_WORKER_FPGA_CORE_SKILL_KEYS, *_AES_REPAIR_SKILL_KEYS)
VALIDATE_WORKER_SKILL_KEYS = _AES_VALIDATE_SKILL_KEYS
L2_WORKER_SKILL_KEYS = _AES_L2_SKILL_KEYS


def select_worker_skill_keys(
    active_mode: str | None = None,
    *,
    design_name: str | None = None,
) -> tuple[str, ...]:
    """Return only the skills relevant to the active work mode and design.

    For non-AES designs, returns empty tuples so no AES-specific context
    pollutes the agent prompt.
    """
    is_aes = _is_aes_design(design_name)
    if active_mode == 'repair':
        return _AES_REPAIR_SKILL_KEYS if is_aes else _GENERIC_REPAIR_SKILL_KEYS
    elif active_mode == 'generate':
        return (
            _AES_WORKER_FPGA_CORE_SKILL_KEYS if is_aes else _GENERIC_WORKER_SKILL_KEYS
        )
    elif active_mode == 'validate':
        return _AES_VALIDATE_SKILL_KEYS if is_aes else _GENERIC_VALIDATE_SKILL_KEYS
    elif active_mode == 'l2_execute':
        return _AES_L2_SKILL_KEYS if is_aes else _GENERIC_L2_SKILL_KEYS
    elif active_mode is None:
        return WORKER_SKILL_KEYS if is_aes else _GENERIC_WORKER_SKILL_KEYS
    else:
        raise ValueError(f'unknown active_mode: {active_mode!r}')


def select_skill_refs(*keys: str) -> list[SkillRef]:
    """Select skill refs by key, searching all registries."""
    refs = get_all_skill_refs()
    selected = list(keys) or list(refs)
    return [refs[key] for key in selected]


def build_skill_reference_block(*keys: str) -> str:
    """Build constraint-line block for policy/pattern skills.

    Memory inlining is now handled by MemoryStore.build_prompt_block().
    Returns empty string when no keys are provided (non-AES designs).
    """
    if not keys:
        return ''
    refs_by_key = get_all_skill_refs()
    resolved_keys = [k for k in keys if k in refs_by_key]
    if not resolved_keys:
        return ''
    constraint_lines = ['Follow these repository skills as hard constraints:']
    seen_keys: set[str] = set()
    for key in resolved_keys:
        if key in seen_keys:
            continue
        seen_keys.add(key)
        ref = refs_by_key[key]
        constraint_lines.append(f'- {ref.name} ({ref.purpose})')
    return '\n'.join(constraint_lines)
