"""Factories for creating SDK-backed AES MVP agents and delegate registrations."""

from __future__ import annotations

import os
from dataclasses import dataclass
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from typing import Any

from MultiAgent_FPGA.fpga_flow.agents import (
    AgentSpawnSpec,
    build_finalizer_orchestrator_spec,
    build_l2_campaign_spec,
    build_module_worker_spec,
    build_repair_worker_spec,
    build_workflow_orchestrator_spec,
)
from MultiAgent_FPGA.fpga_flow.artifacts import PlanDAGNode
from MultiAgent_FPGA.fpga_flow.executor_contracts import resolve_l2_campaign_inputs
from MultiAgent_FPGA.fpga_flow.policy import AgentRole, LLMProfileName
from MultiAgent_FPGA.fpga_flow.runtime.bootstrap import RuntimeBootstrap
from MultiAgent_FPGA.fpga_flow.runtime.execution_tools import register_execution_tools
from MultiAgent_FPGA.fpga_flow.synthesis import FragilityMemory, L2AdaptivePlanner

VERILATOR_ALLOWED_MCP_REGEX = r'^(?!verilator_(testbenchgenerator|naturallanguage)$).*'


def _l2_enabled() -> bool:
    """Return True only when L2 campaigns are explicitly enabled."""
    return os.environ.get('FPGA_FLOW_ENABLE_L2', '').lower() in ('1', 'true', 'yes')


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
    agent: Any


class SdkAgentFactory:
    """Create role-specific agents and register subagent factories."""

    def __init__(self, bootstrap: RuntimeBootstrap) -> None:
        self.bootstrap = bootstrap
        register_execution_tools()

    def _build_llm(self, profile_name: LLMProfileName, *, usage_id: str):
        kwargs = dict(self.bootstrap.llm_profile_kwargs[profile_name.value])
        kwargs['usage_id'] = usage_id
        return self.bootstrap.sdk.LLM(**kwargs)

    def _resolve_skill_key(self, key: str) -> str:
        """Resolve an underscore skill key to the hyphenated SDK skill name."""
        from MultiAgent_FPGA.fpga_flow.skill_refs import get_runtime_skill_refs

        refs = get_runtime_skill_refs()
        if key in refs:
            return refs[key].name
        return key

    def _build_agent_context(self, spec: AgentSpawnSpec):
        from MultiAgent_FPGA.fpga_flow.skill_refs import get_memory_skill_refs

        memory_keys = set(get_memory_skill_refs())
        return self.bootstrap.sdk.AgentContext(
            skills=[
                self.bootstrap.runtime_skills_by_name[resolved]
                for name in spec.skill_keys
                if name not in memory_keys
                for resolved in (self._resolve_skill_key(name),)
                if resolved in self.bootstrap.runtime_skills_by_name
            ],
            system_message_suffix=spec.system_prompt,
            load_user_skills=False,
            load_public_skills=False,
        )

    def _default_tools(
        self,
        *,
        enable_delegate: bool,
        allowed_default_tool_names: set[str] | None = None,
        custom_tool_names: tuple[str, ...] = tuple(),
    ) -> list[Any]:
        tools = list(self.bootstrap.sdk.get_default_tools(enable_browser=False))
        if allowed_default_tool_names is not None:
            tools = [
                tool
                for tool in tools
                if getattr(tool, 'name', None) in allowed_default_tool_names
            ]
        if enable_delegate:
            tools.append(
                self.bootstrap.sdk.Tool(name=self.bootstrap.sdk.DelegateTool.name)
            )
        for tool_name in custom_tool_names:
            tools.append(self.bootstrap.sdk.Tool(name=tool_name))
        return tools

    def _create_agent_from_spec(
        self,
        spec: AgentSpawnSpec,
        *,
        usage_id: str,
        enable_delegate: bool,
        enable_mcp: bool = False,
        include_default_tools: list[str] | None = None,
        allowed_default_tool_names: set[str] | None = None,
        llm: Any | None = None,
        condenser: Any | None = None,
    ) -> RuntimeAgentHandle:
        agent_kwargs = {
            'llm': llm or self._build_llm(spec.llm_profile, usage_id=usage_id),
            'tools': self._default_tools(
                enable_delegate=enable_delegate,
                allowed_default_tool_names=allowed_default_tool_names,
                custom_tool_names=spec.custom_tools,
            ),
            'agent_context': self._build_agent_context(spec),
        }
        if include_default_tools is not None:
            agent_kwargs['include_default_tools'] = include_default_tools
        if enable_mcp:
            agent_kwargs['mcp_config'] = self.bootstrap.mcp_config
            agent_kwargs['filter_tools_regex'] = VERILATOR_ALLOWED_MCP_REGEX
        if condenser is not None:
            agent_kwargs['condenser'] = condenser
        agent = self.bootstrap.sdk.Agent(**agent_kwargs)
        return RuntimeAgentHandle(
            role=spec.role,
            llm_profile=spec.llm_profile,
            spawn_spec=spec,
            agent=agent,
        )

    def _design_name(self) -> str | None:
        """Extract design name from the first node's design_context, or None."""
        nodes = self.bootstrap.plan_dag.nodes
        if nodes:
            name = str(nodes[0].design_context.get('algorithm', ''))
            return name if name else None
        return None

    def create_execution_orchestrator(self, *, enable_l2: bool | None = None) -> Any:
        self.register_delegate_agents(
            enable_l2=enable_l2 if enable_l2 is not None else _l2_enabled()
        )
        spec = build_workflow_orchestrator_spec(design_name=self._design_name())
        # Execution batches use fresh Conversations per batch; keep tools minimal so the
        # model cannot call finish() (FinishTool is only on the finalizer agent).
        llm = self._build_llm(
            spec.llm_profile, usage_id='fpga_flow.orchestrator.execution'
        )
        condenser: Any | None = None
        disable = os.environ.get('FPGA_FLOW_DISABLE_EXECUTION_CONDENSER', '').lower()
        if disable not in ('1', 'true', 'yes'):
            from openhands.sdk.context.condenser import LLMSummarizingCondenser

            max_size = int(
                os.environ.get('FPGA_FLOW_EXECUTION_CONDENSER_MAX_SIZE', '12')
            )
            keep_first = int(
                os.environ.get('FPGA_FLOW_EXECUTION_CONDENSER_KEEP_FIRST', '2')
            )
            condenser = LLMSummarizingCondenser(
                llm=llm.model_copy(
                    update={'usage_id': 'fpga_flow.orchestrator.execution.condenser'}
                ),
                max_size=max_size,
                keep_first=keep_first,
            )
        return self._create_agent_from_spec(
            spec,
            usage_id='fpga_flow.orchestrator.execution',
            enable_delegate=True,
            enable_mcp=True,
            include_default_tools=['ThinkTool'],
            allowed_default_tool_names={'terminal'},
            llm=llm,
            condenser=condenser,
        ).agent

    def create_finalizer_orchestrator(self) -> Any:
        spec = build_finalizer_orchestrator_spec()
        return self._create_agent_from_spec(
            spec,
            usage_id='fpga_flow.orchestrator.finalizer',
            enable_delegate=False,
            include_default_tools=['FinishTool', 'ThinkTool'],
        ).agent

    def _build_worker_condenser(
        self, llm: Any, *, usage_id: str, max_size: int = 10
    ) -> Any:
        disable = os.environ.get('FPGA_FLOW_DISABLE_WORKER_CONDENSER', '').lower()
        if disable in ('1', 'true', 'yes'):
            return None
        from openhands.sdk.context.condenser import LLMSummarizingCondenser

        return LLMSummarizingCondenser(
            llm=llm.model_copy(update={'usage_id': f'{usage_id}.condenser'}),
            max_size=max_size,
            keep_first=2,
        )

    def create_module_worker(
        self, node: PlanDAGNode, *, active_mode: str | None = 'generate'
    ) -> Any:
        spec = build_module_worker_spec(node, active_mode=active_mode)
        usage_id = f'fpga_flow.module_worker.{_sanitize_registry_name(node.module_id)}'
        llm = self._build_llm(spec.llm_profile, usage_id=usage_id)
        return self._create_agent_from_spec(
            spec,
            usage_id=usage_id,
            enable_delegate=False,
            allowed_default_tool_names={'terminal', 'file_editor', 'task_tracker'},
            llm=llm,
            condenser=self._build_worker_condenser(llm, usage_id=usage_id, max_size=10),
        ).agent

    def create_module_repair_worker(self, node: PlanDAGNode) -> Any:
        design_name = str(node.design_context.get('algorithm', '')) or 'AES'
        spec = build_repair_worker_spec(
            module_id=node.module_id, design_name=design_name
        )
        usage_id = (
            f'fpga_flow.module_repair_worker.{_sanitize_registry_name(node.module_id)}'
        )
        llm = self._build_llm(spec.llm_profile, usage_id=usage_id)
        return self._create_agent_from_spec(
            spec,
            usage_id=usage_id,
            enable_delegate=False,
            allowed_default_tool_names={'file_editor', 'task_tracker'},
            llm=llm,
            condenser=self._build_worker_condenser(llm, usage_id=usage_id, max_size=8),
        ).agent

    def create_l2_campaign(
        self,
        node: PlanDAGNode,
        *,
        profile: str,
        vecfile: str,
        cases: int | None = None,
        seed: int | None = None,
    ) -> Any:
        spec = build_l2_campaign_spec(
            node,
            profile=profile,
            vecfile=vecfile,
            cases=cases,
            seed=seed,
        )
        usage_id = (
            f'fpga_flow.l2_campaign.{_sanitize_registry_name(node.module_id)}.'
            f'{_sanitize_registry_name(profile)}'
        )
        return self._create_agent_from_spec(
            spec,
            usage_id=usage_id,
            enable_delegate=False,
            allowed_default_tool_names={'file_editor', 'task_tracker'},
        ).agent

    def module_worker_registry_name(self, node: PlanDAGNode) -> str:
        return f'module_worker__{_sanitize_registry_name(node.module_id)}'

    def repair_worker_registry_name(self, node: PlanDAGNode) -> str:
        return f'module_repair__{_sanitize_registry_name(node.module_id)}'

    def l2_campaign_registry_name(self, node: PlanDAGNode, *, profile: str) -> str:
        return (
            f'l2_campaign__{_sanitize_registry_name(node.module_id)}__'
            f'{_sanitize_registry_name(profile)}'
        )

    def default_l2_registration_kwargs(self, node: PlanDAGNode) -> dict[str, object]:
        planner = L2AdaptivePlanner()
        planned = planner.plan(
            node=node,
            fragility_memory=FragilityMemory(),
            integration_manifest=self.bootstrap.integration_manifest,
        )
        if planned is None:
            raise ValueError(f'{node.module_id} does not require L2 registration')
        kwargs: dict[str, object] = {
            'profile': planned.profile,
            'vecfile': planned.vecfile,
        }
        if planned.cases is not None:
            kwargs['cases'] = planned.cases
        if planned.seed is not None:
            kwargs['seed'] = planned.seed
        resolved = resolve_l2_campaign_inputs(
            package_root=self.bootstrap.workspace_root,
            node=node,
            profile=str(kwargs['profile']),
            vecfile=str(kwargs['vecfile']),
            cases=kwargs.get('cases'),  # type: ignore[arg-type]
            seed=kwargs.get('seed'),  # type: ignore[arg-type]
        )
        kwargs['vecfile'] = str(resolved.vecfile)
        kwargs['cases'] = resolved.cases
        kwargs['seed'] = resolved.seed
        return kwargs

    def _create_from_parent_llm(
        self,
        parent_llm: Any,
        *,
        spec: AgentSpawnSpec,
        usage_id: str,
        allowed_tools: set[str],
        condenser_max_size: int | None = None,
    ) -> Any:
        """Create a delegate agent inheriting the parent orchestrator's LLM."""
        worker_llm = parent_llm.model_copy(update={'usage_id': usage_id})
        condenser = (
            self._build_worker_condenser(
                worker_llm, usage_id=usage_id, max_size=condenser_max_size
            )
            if condenser_max_size is not None
            else None
        )
        return self._create_agent_from_spec(
            spec,
            usage_id=usage_id,
            enable_delegate=False,
            allowed_default_tool_names=allowed_tools,
            llm=worker_llm,
            condenser=condenser,
        ).agent

    def register_module_worker(self, node: PlanDAGNode) -> str:
        spec = build_module_worker_spec(node, active_mode='generate')
        registry_name = self.module_worker_registry_name(node)
        usage_id = f'fpga_flow.module_worker.{_sanitize_registry_name(node.module_id)}'
        self.bootstrap.sdk.register_agent_if_absent(
            name=registry_name,
            factory_func=lambda parent_llm,
            node=node,
            spec=spec,
            usage_id=usage_id: self._create_from_parent_llm(
                parent_llm,
                spec=spec,
                usage_id=usage_id,
                allowed_tools={'file_editor', 'task_tracker'},
                condenser_max_size=10,
            ),
            description=spec.system_prompt,
        )
        return registry_name

    def register_repair_worker(self, node: PlanDAGNode) -> str:
        design_name = str(node.design_context.get('algorithm', '')) or 'AES'
        spec = build_repair_worker_spec(
            module_id=node.module_id, design_name=design_name
        )
        registry_name = self.repair_worker_registry_name(node)
        usage_id = (
            f'fpga_flow.module_repair_worker.{_sanitize_registry_name(node.module_id)}'
        )
        self.bootstrap.sdk.register_agent_if_absent(
            name=registry_name,
            factory_func=lambda parent_llm,
            spec=spec,
            usage_id=usage_id: self._create_from_parent_llm(
                parent_llm,
                spec=spec,
                usage_id=usage_id,
                allowed_tools={'file_editor', 'task_tracker'},
                condenser_max_size=8,
            ),
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
        usage_id = (
            f'fpga_flow.l2_campaign.{_sanitize_registry_name(node.module_id)}.'
            f'{_sanitize_registry_name(profile)}'
        )
        self.bootstrap.sdk.register_agent_if_absent(
            name=registry_name,
            factory_func=lambda parent_llm,
            spec=spec,
            usage_id=usage_id: self._create_from_parent_llm(
                parent_llm,
                spec=spec,
                usage_id=usage_id,
                allowed_tools={'file_editor', 'task_tracker'},
                condenser_max_size=8,
            ),
            description=spec.system_prompt,
        )
        return registry_name

    def register_delegate_agents(self, *, enable_l2: bool = False) -> list[str]:
        registrations: list[str] = []
        for node in self.bootstrap.plan_dag.nodes:
            registrations.append(self.register_module_worker(node))
            registrations.append(self.register_repair_worker(node))
            if not enable_l2 or node.l2_policy == 'skip':
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
