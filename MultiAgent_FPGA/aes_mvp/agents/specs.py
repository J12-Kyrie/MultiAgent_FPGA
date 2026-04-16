"""SDK-ready agent role specifications for the AES MVP runtime."""

from __future__ import annotations

from dataclasses import dataclass

from MultiAgent_FPGA.aes_mvp.artifacts import PlanDAGNode
from MultiAgent_FPGA.aes_mvp.policy import AgentRole, LLMProfileName, OrchestratorState
from MultiAgent_FPGA.aes_mvp.prompts import (
    build_execution_orchestrator_prompt,
    build_finalizer_orchestrator_prompt,
    build_l2_campaign_prompt,
    build_module_worker_prompt,
    build_repair_worker_prompt,
)
from MultiAgent_FPGA.aes_mvp.skill_refs import (
    FINALIZER_SKILL_KEYS,
    ORCHESTRATOR_CORE_SKILL_KEYS,
    SDK_DELEGATION_SKILL_KEYS,
    select_worker_skill_keys,
)


@dataclass(frozen=True)
class AgentSpawnSpec:
    role: AgentRole
    llm_profile: LLMProfileName
    system_prompt: str
    skill_keys: tuple[str, ...]
    allowed_states: tuple[OrchestratorState, ...]
    writable_paths: tuple[str, ...]
    custom_tools: tuple[str, ...] = tuple()


def build_workflow_orchestrator_spec() -> AgentSpawnSpec:
    return AgentSpawnSpec(
        role=AgentRole.WORKFLOW_ORCHESTRATOR,
        llm_profile=LLMProfileName.DEEPSEEK_OFFICIAL_FAST,
        system_prompt=build_execution_orchestrator_prompt(),
        skill_keys=(
            *ORCHESTRATOR_CORE_SKILL_KEYS,
            *SDK_DELEGATION_SKILL_KEYS,
        ),
        allowed_states=(
            OrchestratorState.SPEC_INTAKE,
            OrchestratorState.ARCHITECTING,
            OrchestratorState.PLANNING,
            OrchestratorState.MODULE_DESIGN,
            OrchestratorState.MODULE_L0,
            OrchestratorState.MODULE_L1,
            OrchestratorState.MODULE_L2_OPTIONAL,
            OrchestratorState.INTEGRATION_READY,
            OrchestratorState.INTEGRATION_REGRESSION,
        ),
        writable_paths=tuple(),
        custom_tools=('run_executor',),
    )


def build_finalizer_orchestrator_spec() -> AgentSpawnSpec:
    return AgentSpawnSpec(
        role=AgentRole.WORKFLOW_ORCHESTRATOR,
        llm_profile=LLMProfileName.DEEPSEEK_OFFICIAL_THINKING,
        system_prompt=build_finalizer_orchestrator_prompt(),
        skill_keys=FINALIZER_SKILL_KEYS,
        allowed_states=(
            OrchestratorState.INTEGRATION_READY,
            OrchestratorState.INTEGRATION_REGRESSION,
            OrchestratorState.DONE,
        ),
        writable_paths=tuple(),
    )


def build_module_worker_spec(
    node: PlanDAGNode, *, active_mode: str | None = None
) -> AgentSpawnSpec:
    return AgentSpawnSpec(
        role=AgentRole.MODULE_WORKER_SUBAGENT,
        llm_profile=LLMProfileName.DEEPSEEK_OFFICIAL_FAST,
        system_prompt=build_module_worker_prompt(node, active_mode=active_mode),
        skill_keys=select_worker_skill_keys(active_mode),
        allowed_states=(
            OrchestratorState.MODULE_DESIGN,
            OrchestratorState.MODULE_L0,
            OrchestratorState.MODULE_L1,
        ),
        writable_paths=tuple([*node.rtl_files, node.tb_file]),
        custom_tools=('run_executor',),
    )


def build_repair_worker_spec(*, module_id: str | None = None) -> AgentSpawnSpec:
    return AgentSpawnSpec(
        role=AgentRole.MODULE_WORKER_SUBAGENT,
        llm_profile=LLMProfileName.DEEPSEEK_OFFICIAL_FAST,
        system_prompt=build_repair_worker_prompt(module_id=module_id),
        skill_keys=select_worker_skill_keys('repair'),
        allowed_states=(
            OrchestratorState.MODULE_DESIGN,
            OrchestratorState.MODULE_L0,
            OrchestratorState.MODULE_L1,
        ),
        writable_paths=tuple(),
    )


def build_l2_campaign_spec(
    node: PlanDAGNode,
    *,
    profile: str,
    vecfile: str,
    cases: int | None = None,
    seed: int | None = None,
) -> AgentSpawnSpec:
    return AgentSpawnSpec(
        role=AgentRole.L2_CAMPAIGN_SUBAGENT,
        llm_profile=LLMProfileName.DEEPSEEK_OFFICIAL_FAST,
        system_prompt=build_l2_campaign_prompt(
            node,
            profile=profile,
            vecfile=vecfile,
            cases=cases,
            seed=seed,
        ),
        skill_keys=select_worker_skill_keys('l2_execute'),
        allowed_states=(OrchestratorState.MODULE_L2_OPTIONAL,),
        writable_paths=tuple(),
        custom_tools=('run_executor',),
    )
