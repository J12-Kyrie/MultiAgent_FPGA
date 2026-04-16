"""References to the repository skills that constrain the AES MVP runtime."""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path

from MultiAgent_FPGA.aes_mvp.paths import REPO_ROOT


@dataclass(frozen=True)
class SkillRef:
    name: str
    path: Path
    purpose: str


def _skills_root() -> Path:
    return REPO_ROOT / '.openhands' / 'skills'


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
    """Return the 6 doc-only skills (used by synthesis.py for ModuleDesignBrief hints)."""
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
        'openhands_sdk_bootstrap': SkillRef(
            name='openhands-sdk-bootstrap',
            path=skills_root / 'openhands_sdk_bootstrap.md',
            purpose='SDK bootstrap pattern for Agent, Conversation, Workspace, and LLM',
        ),
        'openhands_sdk_mcp_integration': SkillRef(
            name='openhands-sdk-mcp-integration',
            path=skills_root / 'openhands_sdk_mcp_integration.md',
            purpose='OpenHands SDK MCP integration patterns and tool discovery flow',
        ),
        'openhands_sdk_observability': SkillRef(
            name='openhands-sdk-observability',
            path=skills_root / 'openhands_sdk_observability.md',
            purpose='Tracing, event, and conversation-level debug guidance',
        ),
    }


def get_all_skill_refs() -> dict[str, SkillRef]:
    """Return union of all three registries (16 total) for backward-compat callers."""
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


# -- Orchestrator skill groups --
ORCHESTRATOR_CORE_SKILL_KEYS = ('aes_verilator_profile',)

SDK_DELEGATION_SKILL_KEYS = ('openhands_sdk_subagent_delegation',)

# The finalizer only reads finalizer_input.json and calls FinishTool.
# No delegation, no MCP tools, no Verilator, no spec synthesis, no skills.
FINALIZER_SKILL_KEYS: tuple[str, ...] = ()

# -- Worker skill groups --
WORKER_FPGA_CORE_SKILL_KEYS = (
    'aes_verilator_profile',
    'aes_module_patterns',
    'aes_tb_contracts',
)

REPAIR_CORE_SKILL_KEYS = ('aes_repair_heuristics',)

WORKER_SKILL_KEYS = (
    *WORKER_FPGA_CORE_SKILL_KEYS,
    *REPAIR_CORE_SKILL_KEYS,
)

# Validate mode is read-only: only needs checkpoint/vector interpretation.
VALIDATE_WORKER_SKILL_KEYS = ('aes_verilator_profile',)

# L2 campaigns only need the AES node taxonomy for checkpoint/vector knowledge.
L2_WORKER_SKILL_KEYS = ('aes_verilator_profile',)


def select_worker_skill_keys(
    active_mode: str | None = None,
) -> tuple[str, ...]:
    """Return only the skills relevant to the active work mode.

    Memory keys are no longer part of skill key selection — memory.py handles them.
    """
    if active_mode == 'repair':
        base = REPAIR_CORE_SKILL_KEYS
    elif active_mode == 'generate':
        base = WORKER_FPGA_CORE_SKILL_KEYS
    elif active_mode == 'validate':
        base = VALIDATE_WORKER_SKILL_KEYS
    elif active_mode == 'l2_execute':
        base = L2_WORKER_SKILL_KEYS
    elif active_mode is None:
        base = WORKER_SKILL_KEYS
    else:
        raise ValueError(f'unknown active_mode: {active_mode!r}')
    return base


def select_skill_refs(*keys: str) -> list[SkillRef]:
    """Select skill refs by key, searching all registries."""
    refs = get_all_skill_refs()
    selected = list(keys) or list(refs)
    return [refs[key] for key in selected]


def build_skill_reference_block(*keys: str) -> str:
    """Build constraint-line block for policy/pattern skills.

    Memory inlining is now handled by MemoryStore.build_prompt_block().
    """
    validate_skill_paths()
    refs_by_key = get_all_skill_refs()
    selected_keys = list(keys) or list(get_runtime_skill_refs())
    constraint_lines = ['Follow these repository skills as hard constraints:']
    seen_keys: set[str] = set()
    for key in selected_keys:
        if key in seen_keys:
            continue
        seen_keys.add(key)
        if key not in refs_by_key:
            continue
        ref = refs_by_key[key]
        constraint_lines.append(f'- {ref.name} ({ref.purpose})')
    return '\n'.join(constraint_lines)
