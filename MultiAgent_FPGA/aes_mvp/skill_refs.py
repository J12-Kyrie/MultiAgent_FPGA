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


def get_runtime_skill_refs() -> dict[str, SkillRef]:
    skills_root = REPO_ROOT / '.openhands' / 'skills'
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
        'aes_verilator_profile': SkillRef(
            name='aes-verilator-profile',
            path=skills_root / 'aes_verilator_profile.md',
            purpose='AES node taxonomy, vectors, checkpoints, and L2 conventions',
        ),
        'deepseek_official_sdk': SkillRef(
            name='deepseek-official-sdk',
            path=skills_root / 'chatfire_deepseek_sdk.md',
            purpose='Pinned DeepSeek official OpenAI-compatible model and runtime rules',
        ),
        'openhands_sdk_bootstrap': SkillRef(
            name='openhands-sdk-bootstrap',
            path=skills_root / 'openhands_sdk_bootstrap.md',
            purpose='SDK bootstrap pattern for Agent, Conversation, Workspace, and LLM',
        ),
        'openhands_sdk_skill_authoring': SkillRef(
            name='openhands-sdk-skill-authoring',
            path=skills_root / 'openhands_sdk_skill_authoring.md',
            purpose='Skill authoring rules for repo and knowledge skills',
        ),
        'openhands_sdk_mcp_integration': SkillRef(
            name='openhands-sdk-mcp-integration',
            path=skills_root / 'openhands_sdk_mcp_integration.md',
            purpose='OpenHands SDK MCP integration patterns and tool discovery flow',
        ),
        'openhands_sdk_subagent_delegation': SkillRef(
            name='openhands-sdk-subagent-delegation',
            path=skills_root / 'openhands_sdk_subagent_delegation.md',
            purpose='Subagent registration, spawn, delegate, and task-boundary rules',
        ),
        'openhands_sdk_observability': SkillRef(
            name='openhands-sdk-observability',
            path=skills_root / 'openhands_sdk_observability.md',
            purpose='Tracing, event, and conversation-level debug guidance',
        ),
    }


def validate_skill_paths() -> None:
    missing = [
        ref.path for ref in get_runtime_skill_refs().values() if not ref.path.is_file()
    ]
    if missing:
        missing_paths = ', '.join(str(path) for path in missing)
        raise FileNotFoundError(
            f'Missing required AES MVP skill files: {missing_paths}'
        )


WORKFLOW_SKILL_KEYS = (
    'verilator_mcp_setup',
    'verilog_verilator',
    'aes_verilator_profile',
    'deepseek_official_sdk',
    'openhands_sdk_bootstrap',
    'openhands_sdk_mcp_integration',
    'openhands_sdk_subagent_delegation',
    'openhands_sdk_observability',
)

WORKER_SKILL_KEYS = (
    'verilator_mcp_setup',
    'verilog_verilator',
    'aes_verilator_profile',
    'deepseek_official_sdk',
    'openhands_sdk_mcp_integration',
)


def select_skill_refs(*keys: str) -> list[SkillRef]:
    refs = get_runtime_skill_refs()
    selected = list(keys) or list(refs)
    return [refs[key] for key in selected]


def build_skill_reference_block(*keys: str) -> str:
    validate_skill_paths()
    lines = ['Follow these repository skills as hard constraints:']
    for ref in select_skill_refs(*keys):
        lines.append(f'- {ref.name}: {ref.path} ({ref.purpose})')
    return '\n'.join(lines)
