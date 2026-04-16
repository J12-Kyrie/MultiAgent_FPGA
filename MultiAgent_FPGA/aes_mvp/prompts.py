"""Prompt builders that compose shared AES MVP prompt contracts."""

from __future__ import annotations

from MultiAgent_FPGA.aes_mvp.artifacts import PlanDAGNode
from MultiAgent_FPGA.aes_mvp.memory import MemoryStore
from MultiAgent_FPGA.aes_mvp.prompt_contracts import (
    AES_SCOPE_CONTRACT,
    FINALIZER_TERMINAL_PHASE,
    FRAMEWORK_OWNS_PROGRESS_CONTRACT,
    GENERATE_PHASE,
    L2_PHASE,
    MEMORY_CONSULTATION_DIRECTIVE,
    NO_RAW_VERILATOR_CONTRACT,
    ORCHESTRATOR_DELEGATION_PHASE,
    ORCHESTRATOR_NO_FINISH,
    ORCHESTRATOR_ONLY_CURRENT_BATCH,
    REPAIR_MEMORY_DIRECTIVE,
    REPAIR_PHASE_ROUND_1,
    REPAIR_PHASE_ROUND_2_PLUS,
    RUN_EXECUTOR_PHASE,
    SKILLS_AS_AUTHORITY_CONTRACT,
    STRUCTURED_IO_CONTRACT,
    VALIDATE_PHASE,
    WORKER_LOCAL_SCOPE,
    WORKER_REQUEST_AUTHORITY,
    InstancePayload,
    compose_prompt,
)
from MultiAgent_FPGA.aes_mvp.skill_refs import (
    FINALIZER_SKILL_KEYS,
    L2_WORKER_SKILL_KEYS,
    ORCHESTRATOR_CORE_SKILL_KEYS,
    SDK_DELEGATION_SKILL_KEYS,
    build_skill_reference_block,
    select_worker_skill_keys,
)


def build_execution_orchestrator_prompt() -> str:
    return compose_prompt(
        'You are the execution-phase Workflow Orchestrator for the AES MVP framework.',
        base_contracts=(
            AES_SCOPE_CONTRACT,
            STRUCTURED_IO_CONTRACT,
            NO_RAW_VERILATOR_CONTRACT,
            FRAMEWORK_OWNS_PROGRESS_CONTRACT,
            SKILLS_AS_AUTHORITY_CONTRACT,
        ),
        phase_mixins=(
            ORCHESTRATOR_ONLY_CURRENT_BATCH,
            ORCHESTRATOR_DELEGATION_PHASE,
            ORCHESTRATOR_NO_FINISH,
        ),
        instance_payload=InstancePayload(
            lines=(
                'Use thinking mode only for batch-local diagnosis, fallback decisions, and stalled repair analysis.',
                'Do not personally perform node-local generate/validate/L2 work unless delegate fallback is explicitly required.',
                'If a delegated module task turns green, promote only into session-scoped promoted artifacts.',
                'Never exceed the provided max_children limit.',
            )
        ),
        skill_block=build_skill_reference_block(
            *ORCHESTRATOR_CORE_SKILL_KEYS,
            *SDK_DELEGATION_SKILL_KEYS,
        ),
    )


def build_finalizer_orchestrator_prompt() -> str:
    return compose_prompt(
        'You are the finalizer Workflow Orchestrator for the AES MVP framework.',
        base_contracts=(
            AES_SCOPE_CONTRACT,
            STRUCTURED_IO_CONTRACT,
            FRAMEWORK_OWNS_PROGRESS_CONTRACT,
            SKILLS_AS_AUTHORITY_CONTRACT,
        ),
        phase_mixins=(FINALIZER_TERMINAL_PHASE,),
        instance_payload=InstancePayload(
            lines=(
                'Do not reopen planning questions or propose additional execution after the workflow gate is terminal.',
            )
        ),
        skill_block=build_skill_reference_block(*FINALIZER_SKILL_KEYS)
        if FINALIZER_SKILL_KEYS
        else None,
    )


def _select_phase_mixins(active_mode: str | None = None) -> tuple:
    """Return only the phase mixins relevant to the active work mode (B4)."""
    # Always include worker-local scope, request authority, and run_executor
    base = (WORKER_LOCAL_SCOPE, WORKER_REQUEST_AUTHORITY, RUN_EXECUTOR_PHASE)
    if active_mode == 'generate':
        return (*base, GENERATE_PHASE, MEMORY_CONSULTATION_DIRECTIVE)
    elif active_mode == 'repair':
        raise ValueError(
            'Use build_repair_worker_prompt() for repair mode, '
            "not build_module_worker_prompt(active_mode='repair')"
        )
    elif active_mode == 'validate':
        return (*base, VALIDATE_PHASE, MEMORY_CONSULTATION_DIRECTIVE)
    elif active_mode == 'l2_execute':
        return (*base, L2_PHASE)
    # Fallback: load all (backward compat for unqualified spawns)
    return (
        WORKER_LOCAL_SCOPE,
        WORKER_REQUEST_AUTHORITY,
        RUN_EXECUTOR_PHASE,
        GENERATE_PHASE,
        VALIDATE_PHASE,
        L2_PHASE,
    )


def _build_default_module_worker_prompt(
    node: PlanDAGNode, *, active_mode: str | None = None
) -> str:
    writable_files = ', '.join([*node.rtl_files, node.tb_file])
    extra_lines: tuple[str, ...] = ()
    if node.module_id == 'aes_round_transform':
        extra_lines = (
            'MixColumns byte-packing uses a deliberate double-reversal. Do not simplify the concatenation order.',
        )
    # Only inject full memory content for generate mode.  In other modes
    # the draft files on disk are the current truth and prompt-inlining
    # the original reference would be stale / waste tokens.
    memory_block = (
        MemoryStore().build_prompt_block(node.module_id)
        if active_mode == 'generate'
        else ''
    )
    skill_block = build_skill_reference_block(*select_worker_skill_keys(active_mode))
    combined_block = '\n\n'.join(b for b in (skill_block, memory_block) if b)
    return compose_prompt(
        f'You are the Module Worker SubAgent for {node.module_id}.',
        base_contracts=(
            AES_SCOPE_CONTRACT,
            STRUCTURED_IO_CONTRACT,
            SKILLS_AS_AUTHORITY_CONTRACT,
        ),
        phase_mixins=_select_phase_mixins(active_mode),
        instance_payload=InstancePayload(
            lines=(
                f'Canonical filenames from plan (you will edit draft workspace copies, not these originals): {writable_files}',
                *extra_lines,
                'Use non-thinking mode.',
                'The delegate task defines the active mode: generate, validate, repair, or l2_execute.',
                'Do not edit repository canonical RTL/TB files directly — only edit draft copies in the workspace.',
                'Read generation_result.json, workspace_state.json, validation_summary.json, and validation_error.json when execution fails.',
                'If repair_request.json is present, it is the sole source of truth for repair mode.',
                'If an issue is clearly cross-module, interface-level, or state-machine-wide, stop and escalate back to the Workflow Orchestrator.',
            )
        ),
        skill_block=combined_block,
    )


def _build_aes128_encrypt_core_worker_prompt(
    node: PlanDAGNode, *, active_mode: str | None = None
) -> str:
    writable_files = ', '.join([*node.rtl_files, node.tb_file])
    memory_block = (
        MemoryStore().build_prompt_block(node.module_id)
        if active_mode == 'generate'
        else ''
    )
    skill_block = build_skill_reference_block(*select_worker_skill_keys(active_mode))
    combined_block = '\n\n'.join(b for b in (skill_block, memory_block) if b)
    return compose_prompt(
        'You are the Module Worker SubAgent for aes128_encrypt_core (AES-128 encrypt-only top: block handshake, 11-cycle latency MVP).',
        base_contracts=(
            AES_SCOPE_CONTRACT,
            STRUCTURED_IO_CONTRACT,
            SKILLS_AS_AUTHORITY_CONTRACT,
        ),
        phase_mixins=_select_phase_mixins(active_mode),
        instance_payload=InstancePayload(
            lines=(
                f'Canonical filenames from plan (you will edit draft workspace copies, not these originals): {writable_files}.',
                'Use non-thinking mode.',
                'Gold C++ reference for behavior and bus packing: MultiAgent_FPGA/aes_mvp/tb/aes_tb_common.hpp.',
            )
        ),
        skill_block=combined_block,
    )


def build_module_worker_prompt(
    node: PlanDAGNode, *, active_mode: str | None = None
) -> str:
    if node.module_id == 'aes128_encrypt_core':
        return _build_aes128_encrypt_core_worker_prompt(node, active_mode=active_mode)
    return _build_default_module_worker_prompt(node, active_mode=active_mode)


def build_repair_worker_prompt(
    *, repair_round: int = 1, module_id: str | None = None
) -> str:
    if repair_round <= 1:
        repair_mixin = REPAIR_PHASE_ROUND_1
    else:
        repair_mixin = REPAIR_PHASE_ROUND_2_PLUS
    skill_block = build_skill_reference_block(*select_worker_skill_keys('repair'))
    # No memory block for repair workers — the draft files on disk are the
    # current truth and may have been modified by prior repair rounds.
    return compose_prompt(
        'You are the Module Repair SubAgent for the AES MVP framework.',
        base_contracts=(
            AES_SCOPE_CONTRACT,
            STRUCTURED_IO_CONTRACT,
            SKILLS_AS_AUTHORITY_CONTRACT,
        ),
        phase_mixins=(WORKER_LOCAL_SCOPE, repair_mixin, REPAIR_MEMORY_DIRECTIVE),
        instance_payload=InstancePayload(
            lines=(
                'Use non-thinking mode.',
                'You handle exactly one draft repair task at a time.',
                'Your only writable scope is repair_request.primary_target_file.',
                'Do not edit repository canonical RTL/TB files.',
                'Stop immediately after the first concrete draft edit and return a compact repair summary.',
            )
        ),
        skill_block=skill_block,
    )


def build_l2_campaign_prompt(
    node: PlanDAGNode,
    *,
    profile: str,
    vecfile: str,
    cases: int | None = None,
    seed: int | None = None,
) -> str:
    campaign_parts = [f'profile={profile}', f'vecfile={vecfile}']
    if cases is not None:
        campaign_parts.append(f'cases={cases}')
    if seed is not None:
        campaign_parts.append(f'seed={seed}')
    campaign = ', '.join(campaign_parts)
    return compose_prompt(
        f'You are the L2 Campaign SubAgent for {node.module_id}.',
        base_contracts=(
            AES_SCOPE_CONTRACT,
            STRUCTURED_IO_CONTRACT,
            SKILLS_AS_AUTHORITY_CONTRACT,
        ),
        phase_mixins=(
            WORKER_REQUEST_AUTHORITY,
            RUN_EXECUTOR_PHASE,
            L2_PHASE,
        ),
        instance_payload=InstancePayload(
            lines=(
                'You own one independent robustness campaign only.',
                f'Campaign: {campaign}',
                'Use non-thinking mode for execution. Do not reinterpret results at the architecture level.',
                'Emit inputs and summaries that the Workflow Orchestrator can interpret.',
            )
        ),
        skill_block=build_skill_reference_block(*L2_WORKER_SKILL_KEYS),
    )
