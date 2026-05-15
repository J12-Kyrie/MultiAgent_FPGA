"""Bootstrap helpers that turn AES MVP contracts into a runnable SDK context."""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Any

from MultiAgent_FPGA.fpga_flow.adapters.verilator import (
    VerilatorMCPAdapter,
    build_verilator_stdio_server,
)
from MultiAgent_FPGA.fpga_flow.artifacts import (
    IntegrationRegressionManifest,
    PlanDAG,
    SpecIR,
)
from MultiAgent_FPGA.fpga_flow.llm_profiles import (
    build_sdk_deepseek_official_fast_kwargs,
    build_sdk_deepseek_official_thinking_kwargs,
)
from MultiAgent_FPGA.fpga_flow.paths import DESIGNS_DIR, REPO_ROOT, REPORTS_DIR
from MultiAgent_FPGA.fpga_flow.policy import (
    AgentExecutionPolicy,
)
from MultiAgent_FPGA.fpga_flow.runtime.sdk_shim import SdkModules, load_sdk_modules
from MultiAgent_FPGA.fpga_flow.skill_refs import (
    _is_aes_design,
    get_runtime_skill_refs,
    validate_skill_paths,
)
from MultiAgent_FPGA.fpga_flow.synthesis import (
    DEFAULT_AUTONOMOUS_GOAL,
    synthesize_agent_execution_policy,
    synthesize_integration_manifest,
    synthesize_plan_dag,
    synthesize_spec_ir,
    validate_plan_dag_l1_vector_paths,
)


@dataclass(frozen=True)
class RuntimeBootstrap:
    sdk: SdkModules
    workspace_root: Path
    repo_root: Path
    persistence_dir: Path
    runtime_skills: list[Any]
    runtime_skills_by_name: dict[str, Any]
    runtime_skill_names: tuple[str, ...]
    llm_profile_kwargs: dict[str, dict[str, Any]]
    policy: AgentExecutionPolicy
    spec_ir: SpecIR
    plan_dag: PlanDAG
    integration_manifest: IntegrationRegressionManifest
    mcp_config: dict[str, Any]
    system_goal: str
    synthesis_source: str

    @classmethod
    def build(
        cls,
        *,
        workspace_root: Path | None = None,
        repo_root: Path | None = None,
        persistence_dir: Path | None = None,
        allow_placeholder_api_key: bool = False,
        system_goal: str | None = None,
        blueprint_path: str | Path | None = None,
    ) -> 'RuntimeBootstrap':
        sdk = load_sdk_modules()
        if blueprint_path is not None:
            bp = Path(blueprint_path)
            default_workspace = bp.parent
        else:
            default_workspace = DESIGNS_DIR / 'aes128'
        resolved_workspace = (workspace_root or default_workspace).resolve()
        resolved_repo = (repo_root or REPO_ROOT).resolve()
        resolved_persistence = (
            persistence_dir or REPORTS_DIR / 'conversations'
        ).resolve()

        # Detect design name from blueprint to decide which skills to load.
        _design_name: str | None = None
        if blueprint_path is not None:
            import yaml

            _bp_text = Path(blueprint_path).read_text(encoding='utf-8')
            _bp_data = yaml.safe_load(_bp_text)
            _design_name = (_bp_data.get('design', {}) or {}).get('name', '')

        is_aes = _is_aes_design(_design_name)

        if is_aes:
            validate_skill_paths()
        skill_refs = get_runtime_skill_refs()
        loaded_skills = sdk.load_project_skills(str(resolved_repo))
        loaded_by_name = {skill.name: skill for skill in loaded_skills}
        if is_aes:
            missing = [
                ref.name
                for ref in skill_refs.values()
                if ref.name not in loaded_by_name
            ]
            if missing:
                missing_names = ', '.join(missing)
                raise FileNotFoundError(
                    f'Failed to load required runtime skills through the OpenHands SDK: '
                    f'{missing_names}'
                )
        runtime_skills = [
            loaded_by_name[ref.name]
            for ref in skill_refs.values()
            if ref.name in loaded_by_name
        ]

        thinking_kwargs = build_sdk_deepseek_official_thinking_kwargs(
            allow_placeholder_api_key=allow_placeholder_api_key
        )
        fast_kwargs = build_sdk_deepseek_official_fast_kwargs(
            allow_placeholder_api_key=allow_placeholder_api_key
        )
        if blueprint_path is not None:
            resolved_goal = system_goal.strip() if system_goal else None
        else:
            resolved_goal = (system_goal or DEFAULT_AUTONOMOUS_GOAL).strip()
        spec_ir = synthesize_spec_ir(
            system_goal=resolved_goal, blueprint_path=blueprint_path
        )
        plan_dag = synthesize_plan_dag(spec_ir, blueprint_path=blueprint_path)
        missing_vectors = validate_plan_dag_l1_vector_paths(plan_dag)
        if missing_vectors:
            raise FileNotFoundError(
                'Missing L1 vector files required for AES MVP synthesis:\n'
                + '\n'.join(missing_vectors)
            )
        integration_manifest = synthesize_integration_manifest(spec_ir, plan_dag)
        mcp_server = build_verilator_stdio_server()
        mcp_config = {
            'mcpServers': {
                mcp_server.name: {
                    'command': mcp_server.command,
                    'args': list(mcp_server.args),
                    'env': dict(mcp_server.env),
                }
            }
        }
        return cls(
            sdk=sdk,
            workspace_root=resolved_workspace,
            repo_root=resolved_repo,
            persistence_dir=resolved_persistence,
            runtime_skills=runtime_skills,
            runtime_skills_by_name=loaded_by_name,
            runtime_skill_names=tuple(skill.name for skill in runtime_skills),
            llm_profile_kwargs={
                'deepseek_official_thinking': thinking_kwargs,
                'deepseek_official_fast': fast_kwargs,
            },
            policy=synthesize_agent_execution_policy(),
            spec_ir=spec_ir,
            plan_dag=plan_dag,
            integration_manifest=integration_manifest,
            mcp_config=mcp_config,
            system_goal=resolved_goal or spec_ir.system_goal,
            synthesis_source='autonomous',
        )

    def create_verilator_adapter(
        self, *, conversation_id: str = 'aes-mvp'
    ) -> VerilatorMCPAdapter:
        return VerilatorMCPAdapter(conversation_id=conversation_id)

    def to_summary(self) -> dict[str, object]:
        return {
            'algorithm': self.spec_ir.algorithm,
            'variant': self.spec_ir.variant,
            'runtime_skill_names': list(self.runtime_skill_names),
            'workspace_root': str(self.workspace_root),
            'repo_root': str(self.repo_root),
            'persistence_dir': str(self.persistence_dir),
            'nodes': [node.module_id for node in self.plan_dag.nodes],
            'integration_top': self.integration_manifest.top_module,
            'mcp_servers': sorted(self.mcp_config.get('mcpServers', {}).keys()),
            'sdk_package': self.sdk.sdk.__name__,
            'system_goal': self.system_goal,
            'synthesis_source': self.synthesis_source,
        }

    def orchestrator(self):
        from MultiAgent_FPGA.fpga_flow.orchestrator import AESWorkflowOrchestrator

        return AESWorkflowOrchestrator(
            spec_ir=self.spec_ir,
            plan_dag=self.plan_dag,
            policy=self.policy,
            integration_manifest=self.integration_manifest,
        )
