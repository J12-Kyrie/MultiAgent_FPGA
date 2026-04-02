"""Execution policy for the AES MVP orchestrator and subagents."""

from __future__ import annotations

import json
from enum import Enum

from pydantic import BaseModel, ConfigDict, Field, model_validator

from MultiAgent_FPGA.aes_mvp.paths import AGENT_EXECUTION_POLICY_PATH


class OrchestratorState(str, Enum):
    SPEC_INTAKE = 'SPEC_INTAKE'
    ARCHITECTING = 'ARCHITECTING'
    PLANNING = 'PLANNING'
    MODULE_DESIGN = 'MODULE_DESIGN'
    MODULE_L0 = 'MODULE_L0'
    MODULE_L1 = 'MODULE_L1'
    MODULE_L2_OPTIONAL = 'MODULE_L2_OPTIONAL'
    INTEGRATION_READY = 'INTEGRATION_READY'
    INTEGRATION_REGRESSION = 'INTEGRATION_REGRESSION'
    DONE = 'DONE'
    FAILED = 'FAILED'


class LLMProfileName(str, Enum):
    DEEPSEEK_OFFICIAL_THINKING = 'deepseek_official_thinking'
    DEEPSEEK_OFFICIAL_FAST = 'deepseek_official_fast'


class SubagentPolicy(str, Enum):
    FORBIDDEN = 'forbidden'
    MODULE_WORKER_ALLOWED = 'module_worker_allowed'
    L2_CAMPAIGN_ALLOWED = 'l2_campaign_allowed'


class AgentRole(str, Enum):
    WORKFLOW_ORCHESTRATOR = 'Workflow Orchestrator'
    MODULE_WORKER_SUBAGENT = 'Module Worker SubAgent'
    L2_CAMPAIGN_SUBAGENT = 'L2 Campaign SubAgent'


class AgentExecutionPolicy(BaseModel):
    model_config = ConfigDict(extra='forbid')

    state_profiles: dict[OrchestratorState, LLMProfileName]
    state_subagents: dict[OrchestratorState, SubagentPolicy]
    repair_attempt_threshold: int = Field(default=2, ge=1)

    @model_validator(mode='after')
    def validate_complete_state_mapping(self) -> 'AgentExecutionPolicy':
        required_states = {
            OrchestratorState.SPEC_INTAKE,
            OrchestratorState.ARCHITECTING,
            OrchestratorState.PLANNING,
            OrchestratorState.MODULE_DESIGN,
            OrchestratorState.MODULE_L0,
            OrchestratorState.MODULE_L1,
            OrchestratorState.MODULE_L2_OPTIONAL,
            OrchestratorState.INTEGRATION_READY,
            OrchestratorState.INTEGRATION_REGRESSION,
        }
        missing_profiles = required_states.difference(self.state_profiles.keys())
        missing_subagents = required_states.difference(self.state_subagents.keys())
        if missing_profiles or missing_subagents:
            raise ValueError(
                'AgentExecutionPolicy must map all active AES MVP states to both an '
                'LLM profile and a subagent policy'
            )
        return self

    def profile_for_state(self, state: OrchestratorState) -> LLMProfileName:
        return self.state_profiles[state]

    def subagent_policy_for_state(self, state: OrchestratorState) -> SubagentPolicy:
        return self.state_subagents[state]

    def should_escalate(
        self,
        repair_attempts: int,
        *,
        cross_module_issue: bool = False,
        state_machine_issue: bool = False,
        interface_issue: bool = False,
    ) -> bool:
        return (
            repair_attempts >= self.repair_attempt_threshold
            or cross_module_issue
            or state_machine_issue
            or interface_issue
        )


def load_default_agent_execution_policy() -> AgentExecutionPolicy:
    with AGENT_EXECUTION_POLICY_PATH.open('r', encoding='utf-8') as handle:
        return AgentExecutionPolicy.model_validate(json.load(handle))
