"""SDK-ready agent role specifications for the AES MVP runtime."""

from __future__ import annotations

from dataclasses import dataclass

from MultiAgent_FPGA.aes_mvp.artifacts import PlanDAGNode
from MultiAgent_FPGA.aes_mvp.policy import AgentRole, LLMProfileName, OrchestratorState
from MultiAgent_FPGA.aes_mvp.prompts import (
    build_l2_campaign_prompt,
    build_module_worker_prompt,
    build_workflow_orchestrator_prompt,
)
from MultiAgent_FPGA.aes_mvp.runtime.sdk_shim import (
    SDKUnavailableError,
    discover_sdk_environment,
)


class SoftwareAgentSDKUnavailableError(SDKUnavailableError):
    """Raised when the external OpenHands Software Agent SDK is not installed."""


@dataclass(frozen=True)
class AgentSpawnSpec:
    role: AgentRole
    llm_profile: LLMProfileName
    system_prompt: str
    allowed_states: tuple[OrchestratorState, ...]
    writable_paths: tuple[str, ...]


def ensure_sdk_available() -> None:
    status = discover_sdk_environment()
    if not status.available:
        raise SoftwareAgentSDKUnavailableError(status.message)


def build_workflow_orchestrator_spec() -> AgentSpawnSpec:
    return AgentSpawnSpec(
        role=AgentRole.WORKFLOW_ORCHESTRATOR,
        llm_profile=LLMProfileName.DEEPSEEK_OFFICIAL_THINKING,
        system_prompt=build_workflow_orchestrator_prompt(),
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
    )


def build_module_worker_spec(node: PlanDAGNode) -> AgentSpawnSpec:
    return AgentSpawnSpec(
        role=AgentRole.MODULE_WORKER_SUBAGENT,
        llm_profile=LLMProfileName.DEEPSEEK_OFFICIAL_FAST,
        system_prompt=build_module_worker_prompt(node),
        allowed_states=(
            OrchestratorState.MODULE_DESIGN,
            OrchestratorState.MODULE_L0,
            OrchestratorState.MODULE_L1,
        ),
        writable_paths=tuple([*node.rtl_files, node.tb_file]),
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
        allowed_states=(OrchestratorState.MODULE_L2_OPTIONAL,),
        writable_paths=tuple(),
    )
