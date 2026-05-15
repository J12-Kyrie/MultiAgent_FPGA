"""Composable prompt contracts for the AES MVP runtime."""

from __future__ import annotations

from dataclasses import dataclass
from typing import Iterable


@dataclass(frozen=True)
class BaseContract:
    """Hard constraints shared across prompt variants."""

    name: str
    lines: tuple[str, ...]


@dataclass(frozen=True)
class PhaseMixin:
    """Small, phase-specific constraints layered on top of the base contract."""

    name: str
    lines: tuple[str, ...]


@dataclass(frozen=True)
class InstancePayload:
    """Per-task or per-batch payload that should stay terse and structured."""

    lines: tuple[str, ...] = tuple()


def compose_prompt(
    role_intro: str,
    *,
    base_contracts: Iterable[BaseContract],
    phase_mixins: Iterable[PhaseMixin] = (),
    instance_payload: InstancePayload | None = None,
    skill_block: str | None = None,
) -> str:
    lines: list[str] = [role_intro]
    for contract in base_contracts:
        lines.extend(contract.lines)
    for mixin in phase_mixins:
        lines.extend(mixin.lines)
    if instance_payload is not None:
        lines.extend(instance_payload.lines)
    if skill_block:
        lines.append(skill_block)
    return '\n'.join(line for line in lines if line.strip())


def build_scope_contract(scope_text: str) -> BaseContract:
    """Build a scope contract from a design's scope description."""
    return BaseContract(
        name='design_scope',
        lines=(f'Stay within the {scope_text}.',),
    )


AES_SCOPE_CONTRACT = build_scope_contract(
    'AES-128 encrypt-only block-handshake iterative-10-round MVP'
)

STRUCTURED_IO_CONTRACT = BaseContract(
    name='structured_io',
    lines=(
        'Prefer the provided task contract, workflow_gate, manifest, and report JSON as the source of truth.',
        'Never cat whole large JSON files; use bounded reads only.',
    ),
)

NO_RAW_VERILATOR_CONTRACT = BaseContract(
    name='no_raw_verilator',
    lines=('Never call raw verilator_compile or verilator_simulate directly.',),
)

SKILLS_AS_AUTHORITY_CONTRACT = BaseContract(
    name='skills_as_authority',
    lines=(
        'Repository skills are the authority for FPGA, Verilator, and SDK policy; do not paraphrase or restate them.',
    ),
)

FRAMEWORK_OWNS_PROGRESS_CONTRACT = BaseContract(
    name='framework_owns_progress',
    lines=('The framework, not you, owns batch progression and workflow completion.',),
)

ORCHESTRATOR_ONLY_CURRENT_BATCH = PhaseMixin(
    name='orchestrator_current_batch',
    lines=(
        'Execute only the current batch handed to this conversation.',
        'Do not infer future batches, merge batches, or summarize the whole workflow as complete.',
    ),
)

ORCHESTRATOR_DELEGATION_PHASE = PhaseMixin(
    name='orchestrator_delegation',
    lines=(
        'Delegate bounded node-local work; keep planning, architecture, and cross-module reasoning on the orchestrator.',
        'Use structured batch artifacts to decide delegate, escalate, or integration dispatch.',
    ),
)

ORCHESTRATOR_NO_FINISH = PhaseMixin(
    name='orchestrator_no_finish',
    lines=('Do not call finish in the execution conversation.',),
)

FINALIZER_TERMINAL_PHASE = PhaseMixin(
    name='finalizer_terminal',
    lines=(
        'Use the supplied finalizer_input artifacts as the source of truth.',
        'Do not spawn subagents or execute module, L2, or integration work.',
        'Call finish exactly once after summarizing the terminal workflow outcome.',
    ),
)

WORKER_LOCAL_SCOPE = PhaseMixin(
    name='worker_local_scope',
    lines=(
        'You own only one node-local draft scope at a time.',
        'Do not change cross-module architecture, frozen interfaces, or integration policy.',
    ),
)

WORKER_REQUEST_AUTHORITY = PhaseMixin(
    name='worker_request_authority',
    lines=(
        'The task contract file is the source of truth for writable scope, artifacts, and executor inputs.',
        'Do not broad-scan unrelated paths before consulting the task contract.',
    ),
)

RUN_EXECUTOR_PHASE = PhaseMixin(
    name='run_executor_phase',
    lines=(
        "Use the 'run_executor' tool as the only allowed way to advance generate, validate, l2_execute, or integration phases.",
        "After 'run_executor' returns, read only the observation.next_read_paths or result_paths that it names.",
    ),
)

GENERATE_PHASE = PhaseMixin(
    name='generate',
    lines=(
        'Generate mode works only inside the provided workspace_root and session-scoped promoted targets.',
        'The first failed validation is a handoff signal, not a terminal outcome.',
    ),
)

VALIDATE_PHASE = PhaseMixin(
    name='validate',
    lines=(
        'Validate mode is read-mostly; do not edit files unless the task contract is clearly inconsistent.',
    ),
)

REPAIR_PHASE_ROUND_1 = PhaseMixin(
    name='repair_round_1',
    lines=(
        'Repair mode is edit-only. Do not run compile, simulation, or receipt-recording commands.',
        'Your first tool call MUST be a file_editor edit on repair_request.primary_target_file.',
        'Use repair_request.primary_file_excerpt, error_excerpt, simulation_log_excerpt, and first_edit_steps as the source of truth for the first edit.',
        'Do not inspect secondary_target_files before the primary edit is saved.',
        'Revalidation happens in a later validate phase.',
    ),
)

REPAIR_PHASE_ROUND_2_PLUS = PhaseMixin(
    name='repair_round_2_plus',
    lines=(
        'Repair mode is edit-only. Do not run compile, simulation, or receipt-recording commands.',
        'This is a SUBSEQUENT repair round. A prior repair attempt already modified the file.',
        'You MAY call file_editor view on the primary_target_file to see its current state before editing.',
        'Read the error_excerpt and simulation_log_excerpt carefully and locate the specific error in the file before editing.',
        'Make targeted, minimal edits to fix the specific compile or checkpoint error.',
        'Do not inspect secondary_target_files before the primary edit is saved.',
        'Revalidation happens in a later validate phase.',
    ),
)

L2_PHASE = PhaseMixin(
    name='l2_execute',
    lines=(
        'L2 execute mode does not allow RTL or testbench edits.',
        "Progress the campaign only through 'run_executor'.",
    ),
)


def build_memory_directive(design_name: str = 'AES') -> PhaseMixin:
    """Build a memory consultation directive parameterized by design name."""
    return PhaseMixin(
        name='memory_consultation',
        lines=(
            f'Your workspace draft files are pre-populated from verified {design_name} reference memory.',
            'The === MEMORY === blocks in your system prompt contain the same code that was written to your draft files.',
            'The draft RTL and TB in your workspace are verified reference implementations.',
            'The reference code passes all Verilator checkpoints. You may reproduce it verbatim or adapt it.',
            'If the reference and the patterns skill disagree, the reference memory is authoritative.',
        ),
    )


def build_repair_memory_directive(design_name: str = 'AES') -> PhaseMixin:
    """Build a repair memory directive parameterized by design name."""
    return PhaseMixin(
        name='repair_memory_consultation',
        lines=(
            f'Your workspace draft files were originally pre-populated from verified {design_name} reference memory.',
            'The on-disk draft files are the current truth — they may have been modified by prior repair rounds.',
            'Do not assume the original reference memory matches the current file state.',
            'Always read the actual file before editing. Base your repair on what is on disk, not on any recalled reference.',
        ),
    )


MEMORY_CONSULTATION_DIRECTIVE = build_memory_directive('AES')
"""Backward-compatible alias; prefer ``build_memory_directive(design_name)``."""

REPAIR_MEMORY_DIRECTIVE = build_repair_memory_directive('AES')
"""Backward-compatible alias; prefer ``build_repair_memory_directive(design_name)``."""
