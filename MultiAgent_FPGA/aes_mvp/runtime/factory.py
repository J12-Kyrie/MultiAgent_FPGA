"""Factories for creating SDK-backed AES MVP agents and delegate registrations."""

from __future__ import annotations

from dataclasses import dataclass

from MultiAgent_FPGA.aes_mvp.agents import (
    AgentSpawnSpec,
    build_l2_campaign_spec,
    build_module_worker_spec,
    build_workflow_orchestrator_spec,
)
from MultiAgent_FPGA.aes_mvp.artifacts import PlanDAGNode
from MultiAgent_FPGA.aes_mvp.executor_contracts import resolve_l2_campaign_inputs
from MultiAgent_FPGA.aes_mvp.policy import AgentRole, LLMProfileName
from MultiAgent_FPGA.aes_mvp.runtime.bootstrap import RuntimeBootstrap
from MultiAgent_FPGA.aes_mvp.skill_refs import WORKER_SKILL_KEYS, WORKFLOW_SKILL_KEYS

VERILATOR_ALLOWED_MCP_REGEX = r'^(?!verilator_(testbenchgenerator|naturallanguage)$).*'


def _sanitize_registry_name(text: str) -> str:
    return (
        text.lower()
        .replace(' ', '_')
        .replace('-', '_')
        .replace('.', '_')
        .replace('/', '_')
    )


@dataclass(frozen=True)
class RuntimeAgentHandle:
    role: AgentRole
    llm_profile: LLMProfileName
    spawn_spec: AgentSpawnSpec
    agent: object


class SdkAgentFactory:
    """Create role-specific agents and register subagent factories."""

    def __init__(self, bootstrap: RuntimeBootstrap) -> None:
        self.bootstrap = bootstrap

    def _build_llm(self, profile_name: LLMProfileName, *, usage_id: str):
        kwargs = dict(self.bootstrap.llm_profile_kwargs[profile_name.value])
        kwargs['usage_id'] = usage_id
        return self.bootstrap.sdk.LLM(**kwargs)

    def _build_agent_context(self, system_prompt: str, *, role: AgentRole):
        if role == AgentRole.WORKFLOW_ORCHESTRATOR:
            skill_names = WORKFLOW_SKILL_KEYS
        else:
            skill_names = WORKER_SKILL_KEYS
        return self.bootstrap.sdk.AgentContext(
            skills=[
                self.bootstrap.runtime_skills_by_name[name]
                for name in skill_names
                if name in self.bootstrap.runtime_skills_by_name
            ],
            system_message_suffix=system_prompt,
            load_user_skills=False,
            load_public_skills=False,
        )

    def _default_tools(self, *, enable_delegate: bool) -> list[object]:
        tools = list(self.bootstrap.sdk.get_default_tools(enable_browser=False))
        if enable_delegate:
            tools.append(
                self.bootstrap.sdk.Tool(name=self.bootstrap.sdk.DelegateTool.name)
            )
        return tools

    def _create_agent_from_spec(
        self,
        spec: AgentSpawnSpec,
        *,
        usage_id: str,
        enable_delegate: bool,
    ) -> RuntimeAgentHandle:
        agent = self.bootstrap.sdk.Agent(
            llm=self._build_llm(spec.llm_profile, usage_id=usage_id),
            tools=self._default_tools(enable_delegate=enable_delegate),
            mcp_config=self.bootstrap.mcp_config,
            agent_context=self._build_agent_context(spec.system_prompt, role=spec.role),
            filter_tools_regex=VERILATOR_ALLOWED_MCP_REGEX,
        )
        return RuntimeAgentHandle(
            role=spec.role,
            llm_profile=spec.llm_profile,
            spawn_spec=spec,
            agent=agent,
        )

    def create_workflow_orchestrator(self) -> object:
        self.register_delegate_agents()
        spec = build_workflow_orchestrator_spec()
        return self._create_agent_from_spec(
            spec,
            usage_id='aes_mvp.orchestrator',
            enable_delegate=True,
        ).agent

    def create_module_worker(self, node: PlanDAGNode) -> object:
        spec = build_module_worker_spec(node)
        usage_id = f'aes_mvp.module_worker.{_sanitize_registry_name(node.module_id)}'
        return self._create_agent_from_spec(
            spec,
            usage_id=usage_id,
            enable_delegate=False,
        ).agent

    def create_l2_campaign(
        self,
        node: PlanDAGNode,
        *,
        profile: str,
        vecfile: str,
        cases: int | None = None,
        seed: int | None = None,
    ) -> object:
        spec = build_l2_campaign_spec(
            node,
            profile=profile,
            vecfile=vecfile,
            cases=cases,
            seed=seed,
        )
        usage_id = (
            f'aes_mvp.l2_campaign.{_sanitize_registry_name(node.module_id)}.'
            f'{_sanitize_registry_name(profile)}'
        )
        return self._create_agent_from_spec(
            spec,
            usage_id=usage_id,
            enable_delegate=False,
        ).agent

    def module_worker_registry_name(self, node: PlanDAGNode) -> str:
        return f'module_worker__{_sanitize_registry_name(node.module_id)}'

    def l2_campaign_registry_name(self, node: PlanDAGNode, *, profile: str) -> str:
        return (
            f'l2_campaign__{_sanitize_registry_name(node.module_id)}__'
            f'{_sanitize_registry_name(profile)}'
        )

    def default_l2_registration_kwargs(self, node: PlanDAGNode) -> dict[str, object]:
        kwargs: dict[str, object] = {'profile': 'rand_small'}
        if node.module_id != self.bootstrap.integration_manifest.top_module:
            kwargs.update({'cases': 8, 'seed': 7})
        resolved = resolve_l2_campaign_inputs(
            package_root=self.bootstrap.workspace_root,
            node=node,
            profile=str(kwargs['profile']),
            cases=kwargs.get('cases'),  # type: ignore[arg-type]
            seed=kwargs.get('seed'),  # type: ignore[arg-type]
        )
        kwargs['vecfile'] = str(resolved.vecfile)
        kwargs['cases'] = resolved.cases
        kwargs['seed'] = resolved.seed
        return kwargs

    def register_module_worker(self, node: PlanDAGNode) -> str:
        spec = build_module_worker_spec(node)
        registry_name = self.module_worker_registry_name(node)
        self.bootstrap.sdk.register_agent_if_absent(
            name=registry_name,
            factory_func=lambda _llm, node=node: self.create_module_worker(node),
            description=spec.system_prompt,
        )
        return registry_name

    def register_l2_campaign(
        self,
        node: PlanDAGNode,
        *,
        profile: str,
        vecfile: str,
        cases: int | None = None,
        seed: int | None = None,
    ) -> str:
        spec = build_l2_campaign_spec(
            node,
            profile=profile,
            vecfile=vecfile,
            cases=cases,
            seed=seed,
        )
        registry_name = self.l2_campaign_registry_name(node, profile=profile)
        self.bootstrap.sdk.register_agent_if_absent(
            name=registry_name,
            factory_func=lambda _llm,
            node=node,
            profile=profile,
            vecfile=vecfile,
            cases=cases,
            seed=seed: self.create_l2_campaign(
                node,
                profile=profile,
                vecfile=vecfile,
                cases=cases,
                seed=seed,
            ),
            description=spec.system_prompt,
        )
        return registry_name

    def register_delegate_agents(self) -> list[str]:
        registrations: list[str] = []
        for node in self.bootstrap.plan_dag.nodes:
            registrations.append(self.register_module_worker(node))
            if node.l2_policy == 'skip':
                continue
            l2_kwargs = self.default_l2_registration_kwargs(node)
            registrations.append(
                self.register_l2_campaign(
                    node,
                    profile=str(l2_kwargs['profile']),
                    vecfile=str(l2_kwargs['vecfile']),
                    cases=int(l2_kwargs['cases']),
                    seed=int(l2_kwargs['seed']),
                )
            )
        return registrations

    def delegate_factory_summary(self) -> dict[str, list[str]]:
        return {
            'module_workers': [
                self.module_worker_registry_name(node)
                for node in self.bootstrap.plan_dag.nodes
            ],
            'l2_campaigns': [
                self.l2_campaign_registry_name(node, profile='rand_small')
                for node in self.bootstrap.plan_dag.nodes
                if node.l2_policy != 'skip'
            ],
        }
