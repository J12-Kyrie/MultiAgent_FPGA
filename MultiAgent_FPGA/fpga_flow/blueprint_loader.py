"""Blueprint-driven design specification loader.

BlueprintLoader reads YAML blueprint files and converts them to the framework's
core artifacts (SpecIR, PlanDAG, IntegrationRegressionManifest).  This decouples
design-specific data (ports, checkpoints, vectors, repair hints) from framework
code, enabling the same pipeline to run arbitrary FPGA designs.
"""

from __future__ import annotations

from pathlib import Path
from typing import Any

import yaml
from pydantic import BaseModel, ConfigDict, Field

from MultiAgent_FPGA.fpga_flow.artifacts import (
    IntegrationRegressionManifest,
    L1PassCriteria,
    PassCriteria,
    PlanDAG,
    PlanDAGNode,
    SpecIR,
)

# ---------------------------------------------------------------------------
# Blueprint YAML schema models
# ---------------------------------------------------------------------------


class RepairHintsSpec(BaseModel):
    """Optional repair guidance for a module."""

    model_config = ConfigDict(extra='forbid')

    must_add_tokens: list[str] = Field(default_factory=list)
    guidance: str = ''


class MemorySpec(BaseModel):
    """Optional memory skill file references for a module."""

    model_config = ConfigDict(extra='forbid')

    rtl_skill: str | None = None
    tb_skill: str | None = None
    shared_skill: str | None = None


class DesignMeta(BaseModel):
    """Top-level design metadata, including SpecIR-level fields."""

    model_config = ConfigDict(extra='forbid')

    # Required
    name: str
    scope: str
    language: str = 'verilog'

    # SpecIR-level (optional — defaults allow simple designs like LED chaser)
    autonomous_goal: str = ''
    algorithm: str = ''
    variant: str = ''
    operation: str = ''
    interface_style: str = ''
    microarchitecture: str = ''
    block_width: int = 1
    key_width: int = 1
    clock_reset_assumptions: dict[str, str] = Field(default_factory=dict)
    timing_targets: dict[str, int | str] = Field(default_factory=dict)
    latency_target_cycles: int = 1
    accept_condition: str = ''
    output_valid_condition: str = ''
    frozen_interfaces: list[str] = Field(default_factory=list)
    verification_redlines: list[str] = Field(default_factory=list)


class ModuleSpec(BaseModel):
    """Per-module specification within a blueprint."""

    model_config = ConfigDict(extra='forbid')

    # Required
    id: str
    rtl: str | list[str]
    tb: str

    # Optional — with sensible defaults
    checkpoints: list[str] = Field(default_factory=list)
    depends_on: list[str] = Field(default_factory=list)
    integration_role: str = 'leaf'
    vectors: str | None = None
    repair_hints: RepairHintsSpec | None = None
    l2_profiles: list[str] = Field(default_factory=list)
    l2_defaults: dict[str, Any] = Field(default_factory=dict)
    memory: MemorySpec | None = None
    criticality: str = 'medium'
    l2_policy: str | None = None
    checkpoint_contract: str | None = None

    # ContractCompiler-consumed fields
    ports: list[dict[str, Any]] = Field(default_factory=list)
    design_goals: list[str] = Field(default_factory=list)
    summary: str = ''
    vector_format: str | None = None
    plusargs: list[str] = Field(default_factory=list)
    prohibited_constructs: list[str] = Field(default_factory=list)
    latency_expectation: str | None = None

    # Blueprint-driven hints consumed by prompt builders and generation.py
    vector_hint_style: str | None = None
    worker_prompt_hint: str | None = None

    # Free-form pass-through (integration fields, worker hints, etc.)
    design_context: dict[str, Any] = Field(default_factory=dict)


class VectorsSpec(BaseModel):
    """Optional vector base directory configuration."""

    model_config = ConfigDict(extra='forbid')

    base_dir: str = ''


class IntegrationSpec(BaseModel):
    """Optional integration regression configuration."""

    model_config = ConfigDict(extra='forbid')

    top_module: str
    vector_set: str
    regression_checkpoints: list[str] = Field(default_factory=list)
    back_to_back_required: bool = False
    mid_reset_scenarios: list[str] = Field(default_factory=list)
    checkpoint_contract: str = 'CHECKPOINT|<name>|PASS|<detail>'


class BlueprintSpec(BaseModel):
    """Root model for a design blueprint YAML file."""

    model_config = ConfigDict(extra='forbid')

    design: DesignMeta
    modules: list[ModuleSpec]
    vectors: VectorsSpec | None = None
    integration: IntegrationSpec | None = None
    memory_required: bool = False


# ---------------------------------------------------------------------------
# Loader
# ---------------------------------------------------------------------------


class BlueprintLoader:
    """Load design blueprints from YAML and convert to framework artifacts."""

    @staticmethod
    def load(path: Path) -> BlueprintSpec:
        """Parse YAML blueprint file and return validated BlueprintSpec."""
        content = path.read_text(encoding='utf-8')
        data = yaml.safe_load(content)
        if not isinstance(data, dict):
            raise ValueError(
                f'Blueprint must be a YAML mapping, got {type(data).__name__}'
            )
        return BlueprintSpec(**data)

    @staticmethod
    def to_spec_ir(
        blueprint: BlueprintSpec,
        *,
        system_goal: str | None = None,
    ) -> SpecIR:
        """Convert BlueprintSpec to SpecIR artifact."""
        design = blueprint.design
        goal = (system_goal or design.autonomous_goal or design.scope).strip()
        if not goal:
            goal = f'Design and validate {design.name}.'
        module_candidates = [m.id for m in blueprint.modules]
        redlines = (
            list(design.verification_redlines)
            if design.verification_redlines
            else [
                'do not use SystemVerilog-only syntax',
                'do not use generated testbenches on the stable path',
                'do not bypass executor-based compile and simulation validation',
            ]
        )
        return SpecIR(
            system_goal=goal,
            algorithm=design.algorithm or design.name,
            variant=design.variant or design.name,
            operation=design.operation or 'default',
            interface_style=design.interface_style or 'generic',
            microarchitecture=design.microarchitecture or 'generic',
            block_width=design.block_width,
            key_width=design.key_width,
            clock_reset_assumptions=dict(design.clock_reset_assumptions),
            timing_targets=dict(design.timing_targets),
            latency_target_cycles=design.latency_target_cycles,
            accept_condition=design.accept_condition or 'design-specific',
            output_valid_condition=design.output_valid_condition or 'design-specific',
            frozen_interfaces=list(design.frozen_interfaces),
            module_candidates=module_candidates,
            verification_redlines=redlines,
        )

    @classmethod
    def _build_design_context(
        cls,
        module: ModuleSpec,
        spec_ir: SpecIR,
        *,
        scope: str = '',
    ) -> dict[str, Any]:
        """Construct the design_context dict for a PlanDAGNode."""
        ctx: dict[str, Any] = {}
        if scope:
            ctx['scope'] = scope
        ctx['summary'] = module.summary or f'Implement {module.id}.'
        if module.ports:
            ctx['ports'] = list(module.ports)
        if module.design_goals:
            ctx['design_goals'] = list(module.design_goals)
        if module.vector_format is not None:
            ctx['vector_format'] = module.vector_format
        if module.plusargs:
            ctx['plusargs'] = list(module.plusargs)
        if module.prohibited_constructs:
            ctx['prohibited_constructs'] = list(module.prohibited_constructs)
        ctx['l2_profiles'] = list(module.l2_profiles)
        ctx['l2_defaults'] = dict(module.l2_defaults)
        ctx['sink_role'] = module.integration_role in ('top', 'sink')
        if module.vector_hint_style:
            ctx['vector_hint_style'] = module.vector_hint_style
        if module.worker_prompt_hint:
            ctx['worker_prompt_hint'] = module.worker_prompt_hint
        # Merge free-form pass-through design_context from blueprint
        for key, value in module.design_context.items():
            ctx[key] = value
        # System-level fields from SpecIR
        ctx['system_goal'] = spec_ir.system_goal
        ctx['algorithm'] = spec_ir.algorithm
        ctx['variant'] = spec_ir.variant
        ctx['operation'] = spec_ir.operation
        ctx['interface_style'] = spec_ir.interface_style
        ctx['microarchitecture'] = spec_ir.microarchitecture
        return ctx

    @classmethod
    def _derive_checkpoint_contract(cls, module: ModuleSpec) -> str:
        """Derive checkpoint contract string from checkpoints list."""
        if module.checkpoint_contract:
            return module.checkpoint_contract
        if len(module.checkpoints) == 1:
            return f'CHECKPOINT|{module.checkpoints[0]}|PASS|<detail>'
        if len(module.checkpoints) > 1:
            return 'CHECKPOINT|CHK_*|PASS|<detail>'
        return 'CHECKPOINT|<name>|PASS|<detail>'

    @classmethod
    def _derive_l2_policy(cls, module: ModuleSpec) -> str:
        """Derive L2 policy from module configuration."""
        if module.l2_policy:
            return module.l2_policy
        if not module.l2_profiles:
            return 'skip'
        if module.integration_role in ('top', 'sink'):
            return 'required'
        return 'conditional'

    @classmethod
    def to_plan_dag(
        cls,
        blueprint: BlueprintSpec,
        spec_ir: SpecIR,
        *,
        design_root: Path | None = None,
    ) -> PlanDAG:
        """Convert BlueprintSpec to PlanDAG artifact."""
        nodes: list[PlanDAGNode] = []
        for module in blueprint.modules:
            raw_rtl = module.rtl if isinstance(module.rtl, list) else [module.rtl]
            if design_root is not None:
                rtl_files = [str((design_root / f).resolve()) for f in raw_rtl]
                tb_file = str((design_root / module.tb).resolve())
                vectors = (
                    str((design_root / module.vectors).resolve())
                    if module.vectors
                    else ''
                )
            else:
                rtl_files = list(raw_rtl)
                tb_file = module.tb
                vectors = module.vectors or ''
            design_context = cls._build_design_context(
                module,
                spec_ir,
                scope=blueprint.design.scope,
            )
            if design_root is not None:
                design_context['design_root'] = str(design_root)
            checkpoint_contract = cls._derive_checkpoint_contract(module)
            l2_policy = cls._derive_l2_policy(module)
            nodes.append(
                PlanDAGNode(
                    module_id=module.id,
                    depends_on=list(module.depends_on),
                    top_module=module.id,
                    rtl_files=rtl_files,
                    tb_file=tb_file,
                    language=blueprint.design.language,
                    build_output_dir=f'reports/l0/{module.id}/obj_dir',
                    sim_output_dir=f'reports/l1/{module.id}',
                    l2_policy=l2_policy,
                    criticality=module.criticality,
                    integration_role=module.integration_role,
                    pass_criteria=PassCriteria(
                        l1=L1PassCriteria(
                            sim_pass_required=True,
                            assertion_pass_required=True,
                            coverage_checkpoints=list(module.checkpoints),
                            vector_set=vectors,
                            latency_expectation=(
                                module.latency_expectation or 'unspecified'
                            ),
                            checkpoint_contract=checkpoint_contract,
                        )
                    ),
                    design_context=design_context,
                )
            )
        return PlanDAG(nodes=nodes)

    @classmethod
    def to_integration_manifest(
        cls,
        blueprint: BlueprintSpec,
        spec_ir: SpecIR,
        plan_dag: PlanDAG,
    ) -> IntegrationRegressionManifest | None:
        """Convert BlueprintSpec to IntegrationRegressionManifest.

        Returns None if no module has integration_role 'top'/'sink' and no
        integration section is present in the blueprint.
        """
        has_top = any(m.integration_role in ('top', 'sink') for m in blueprint.modules)
        if not has_top and blueprint.integration is None:
            return None

        # Lazy import to avoid circular dependency with synthesis.py
        from MultiAgent_FPGA.fpga_flow.synthesis import IntegrationReadinessResolver

        resolver = IntegrationReadinessResolver()
        sink = resolver.select_primary_sink(plan_dag)
        required_modules = resolver.dependency_closure(plan_dag, sink.module_id)

        nodes_by_id = {n.module_id: n for n in plan_dag.nodes}
        rtl_files: list[str] = []
        for module_id in required_modules:
            rtl_files.extend(nodes_by_id[module_id].rtl_files)

        integration_vector_set = str(
            sink.design_context.get(
                'integration_vector_set', sink.pass_criteria.l1.vector_set
            )
        )
        regression_checkpoints = list(
            sink.design_context.get(
                'integration_checkpoints',
                sink.pass_criteria.l1.coverage_checkpoints,
            )
        )

        return IntegrationRegressionManifest(
            top_module=sink.module_id,
            rtl_files=rtl_files,
            tb_file=sink.tb_file,
            build_output_dir='reports/integration/obj_dir',
            sim_output_dir='reports/integration',
            required_modules=required_modules,
            interface_freeze_hash=(
                f'{spec_ir.variant.lower()}-'
                f'{spec_ir.interface_style}-'
                f'{spec_ir.microarchitecture}-autonomous-v1'
            ),
            regression_checkpoints=regression_checkpoints,
            vector_set=integration_vector_set,
            latency_target_cycles=spec_ir.latency_target_cycles,
            back_to_back_required='back_to_back'
            in sink.design_context.get('l2_profiles', []),
            mid_reset_scenarios=list(
                sink.design_context.get('mid_reset_scenarios', [])
            ),
            checkpoint_contract=str(
                sink.design_context.get(
                    'integration_checkpoint_contract',
                    'CHECKPOINT|<name>|PASS|<detail>',
                )
            ),
        )
