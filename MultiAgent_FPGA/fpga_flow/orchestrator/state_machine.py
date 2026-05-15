"""State-machine helpers for the AES MVP workflow orchestrator."""

from __future__ import annotations

from dataclasses import dataclass

from MultiAgent_FPGA.fpga_flow.artifacts import (
    IntegrationRegressionManifest,
    PlanDAGNode,
    SpecIR,
)
from MultiAgent_FPGA.fpga_flow.policy import (
    AgentExecutionPolicy,
    OrchestratorState,
)
from MultiAgent_FPGA.fpga_flow.synthesis import (
    DEFAULT_AUTONOMOUS_GOAL,
    synthesize_agent_execution_policy,
    synthesize_integration_manifest,
    synthesize_plan_dag,
    synthesize_spec_ir,
)


@dataclass(frozen=True)
class ModuleWorkOrder:
    node: PlanDAGNode
    state: OrchestratorState
    repair_attempts: int = 0


@dataclass(frozen=True)
class L2CampaignRequest:
    node: PlanDAGNode
    profile: str
    vecfile: str
    cases: int | None = None
    seed: int | None = None


@dataclass(frozen=True)
class StateTraceEntry:
    state: str
    profile: str
    subagent_policy: str
    module_id: str | None
    next_state: str | None
    requires_l2: bool


class AESWorkflowOrchestrator:
    """Decision logic for the AES MVP state machine and task routing."""

    def __init__(
        self,
        *,
        spec_ir: SpecIR,
        plan_dag,
        policy: AgentExecutionPolicy,
        integration_manifest: IntegrationRegressionManifest,
    ) -> None:
        self.spec_ir = spec_ir
        self.plan_dag = plan_dag
        self.policy = policy
        self.integration_manifest = integration_manifest

    @classmethod
    def from_defaults(cls) -> 'AESWorkflowOrchestrator':
        spec_ir = synthesize_spec_ir(system_goal=DEFAULT_AUTONOMOUS_GOAL)
        plan_dag = synthesize_plan_dag(spec_ir)
        return cls(
            spec_ir=spec_ir,
            plan_dag=plan_dag,
            policy=synthesize_agent_execution_policy(),
            integration_manifest=synthesize_integration_manifest(spec_ir, plan_dag),
        )

    def get_node(self, module_id: str) -> PlanDAGNode:
        for node in self.plan_dag.nodes:
            if node.module_id == module_id:
                return node
        known = [n.module_id for n in self.plan_dag.nodes]
        raise KeyError(
            f'Unknown module: {module_id!r}. Known nodes in current design: {known}'
        )

    def profile_for_state(self, state: OrchestratorState):
        return self.policy.profile_for_state(state)

    def subagent_policy_for_state(self, state: OrchestratorState):
        return self.policy.subagent_policy_for_state(state)

    def should_escalate(
        self,
        repair_attempts: int,
        *,
        cross_module_issue: bool = False,
        state_machine_issue: bool = False,
        interface_issue: bool = False,
    ) -> bool:
        return self.policy.should_escalate(
            repair_attempts,
            cross_module_issue=cross_module_issue,
            state_machine_issue=state_machine_issue,
            interface_issue=interface_issue,
        )

    def build_module_work_order(
        self, module_id: str, state: OrchestratorState
    ) -> ModuleWorkOrder:
        if state not in {
            OrchestratorState.MODULE_DESIGN,
            OrchestratorState.MODULE_L0,
            OrchestratorState.MODULE_L1,
        }:
            raise ValueError(f'{state} is not a node-local module work state')
        return ModuleWorkOrder(node=self.get_node(module_id), state=state)

    def build_l2_campaign_request(
        self,
        module_id: str,
        *,
        profile: str,
        vecfile: str,
        cases: int | None = None,
        seed: int | None = None,
    ) -> L2CampaignRequest:
        node = self.get_node(module_id)
        return L2CampaignRequest(
            node=node,
            profile=profile,
            vecfile=vecfile,
            cases=cases,
            seed=seed,
        )

    def next_state_after_success(
        self,
        state: OrchestratorState,
        *,
        requires_l2: bool = False,
    ) -> OrchestratorState:
        transitions = {
            OrchestratorState.SPEC_INTAKE: OrchestratorState.ARCHITECTING,
            OrchestratorState.ARCHITECTING: OrchestratorState.PLANNING,
            OrchestratorState.PLANNING: OrchestratorState.MODULE_DESIGN,
            OrchestratorState.MODULE_DESIGN: OrchestratorState.MODULE_L0,
            OrchestratorState.MODULE_L0: OrchestratorState.MODULE_L1,
            OrchestratorState.MODULE_L1: (
                OrchestratorState.MODULE_L2_OPTIONAL
                if requires_l2
                else OrchestratorState.INTEGRATION_READY
            ),
            OrchestratorState.MODULE_L2_OPTIONAL: OrchestratorState.INTEGRATION_READY,
            OrchestratorState.INTEGRATION_READY: OrchestratorState.INTEGRATION_REGRESSION,
            OrchestratorState.INTEGRATION_REGRESSION: OrchestratorState.DONE,
        }
        if state not in transitions:
            raise ValueError(f'No success transition defined for {state}')
        return transitions[state]

    def describe_state_progression(
        self, *, focus_module_id: str | None = None
    ) -> list[StateTraceEntry]:
        focus_node = self.get_node(
            focus_module_id or self.integration_manifest.top_module
        )
        requires_l2 = focus_node.l2_policy != 'skip'
        progression = [
            OrchestratorState.SPEC_INTAKE,
            OrchestratorState.ARCHITECTING,
            OrchestratorState.PLANNING,
            OrchestratorState.MODULE_DESIGN,
            OrchestratorState.MODULE_L0,
            OrchestratorState.MODULE_L1,
        ]
        if requires_l2:
            progression.append(OrchestratorState.MODULE_L2_OPTIONAL)
        progression.extend(
            [
                OrchestratorState.INTEGRATION_READY,
                OrchestratorState.INTEGRATION_REGRESSION,
                OrchestratorState.DONE,
            ]
        )

        trace: list[StateTraceEntry] = []
        for state in progression:
            next_state: OrchestratorState | None = None
            policy_state = state
            if state == OrchestratorState.DONE:
                policy_state = OrchestratorState.INTEGRATION_REGRESSION
            else:
                next_state = self.next_state_after_success(
                    state,
                    requires_l2=requires_l2 and state == OrchestratorState.MODULE_L1,
                )
            trace.append(
                StateTraceEntry(
                    state=state.value,
                    profile=self.profile_for_state(policy_state).value,
                    subagent_policy=self.subagent_policy_for_state(policy_state).value,
                    module_id=focus_node.module_id,
                    next_state=next_state.value if next_state else None,
                    requires_l2=requires_l2 and state == OrchestratorState.MODULE_L1,
                )
            )
        return trace
