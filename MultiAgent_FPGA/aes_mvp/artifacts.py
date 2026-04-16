"""Artifact models and example loaders for the AES MVP framework."""

from __future__ import annotations

from enum import Enum

from pydantic import BaseModel, ConfigDict, Field, model_validator


class SpecIR(BaseModel):
    model_config = ConfigDict(extra='forbid')

    system_goal: str
    algorithm: str
    variant: str
    operation: str
    interface_style: str
    microarchitecture: str
    block_width: int = Field(ge=128)
    key_width: int = Field(ge=128)
    clock_reset_assumptions: dict[str, str]
    timing_targets: dict[str, int | str]
    latency_target_cycles: int = Field(ge=1)
    accept_condition: str
    output_valid_condition: str
    frozen_interfaces: list[str]
    module_candidates: list[str]
    verification_redlines: list[str]

    @model_validator(mode='after')
    def validate_aes_scope(self) -> 'SpecIR':
        if self.algorithm != 'AES':
            raise ValueError('SpecIR.algorithm must be AES for the current MVP')
        if self.variant != 'AES-128':
            raise ValueError('SpecIR.variant must be AES-128 for the current MVP')
        if self.operation != 'encrypt':
            raise ValueError('SpecIR.operation must be encrypt for the current MVP')
        if self.interface_style != 'block_handshake':
            raise ValueError('SpecIR.interface_style must be block_handshake')
        if self.microarchitecture != 'iterative_10_round':
            raise ValueError('SpecIR.microarchitecture must be iterative_10_round')
        if self.latency_target_cycles != 11:
            raise ValueError('SpecIR.latency_target_cycles must be 11 for the AES MVP')
        if not self.module_candidates:
            raise ValueError('SpecIR.module_candidates must not be empty')
        return self


class L1PassCriteria(BaseModel):
    model_config = ConfigDict(extra='forbid')

    sim_pass_required: bool = True
    assertion_pass_required: bool = True
    coverage_checkpoints: list[str] = Field(default_factory=list)
    vector_set: str
    latency_expectation: str
    checkpoint_contract: str


class PassCriteria(BaseModel):
    model_config = ConfigDict(extra='forbid')

    l1: L1PassCriteria


class PlanDAGNode(BaseModel):
    model_config = ConfigDict(extra='forbid')

    module_id: str
    depends_on: list[str] = Field(default_factory=list)
    top_module: str
    rtl_files: list[str]
    tb_file: str
    language: str
    build_output_dir: str
    sim_output_dir: str
    l2_policy: str
    criticality: str
    integration_role: str
    pass_criteria: PassCriteria
    design_context: dict[str, object] = Field(default_factory=dict)


class PlanDAG(BaseModel):
    model_config = ConfigDict(extra='forbid')

    nodes: list[PlanDAGNode]

    @model_validator(mode='after')
    def validate_frozen_aes_dag(self) -> 'PlanDAG':
        node_ids = [node.module_id for node in self.nodes]
        if len(node_ids) != len(set(node_ids)):
            raise ValueError('PlanDAG.node ids must be unique')
        known = set(node_ids)
        for node in self.nodes:
            if node.language != 'verilog':
                raise ValueError(f'{node.module_id} must use language=verilog')
            if node.module_id in node.depends_on:
                raise ValueError(f'{node.module_id} cannot depend on itself')
            unknown = [
                dependency for dependency in node.depends_on if dependency not in known
            ]
            if unknown:
                raise ValueError(
                    f'{node.module_id} depends on unknown nodes: {", ".join(unknown)}'
                )
        visiting: set[str] = set()
        visited: set[str] = set()
        by_id = {node.module_id: node for node in self.nodes}

        def visit(module_id: str) -> None:
            if module_id in visited:
                return
            if module_id in visiting:
                raise ValueError('PlanDAG dependencies must not contain cycles')
            visiting.add(module_id)
            for dependency in by_id[module_id].depends_on:
                visit(dependency)
            visiting.remove(module_id)
            visited.add(module_id)

        for module_id in node_ids:
            visit(module_id)
        return self


class ModuleRunResult(BaseModel):
    model_config = ConfigDict(extra='forbid')

    module_id: str
    compile_result: str
    sim_result: str
    log_path: str
    waveform_path: str
    checkpoint_summary: dict[str, str]


class PortSpec(BaseModel):
    model_config = ConfigDict(extra='forbid')

    name: str
    direction: str
    width: int = Field(ge=1, default=1)
    description: str


class ModuleContract(BaseModel):
    model_config = ConfigDict(extra='forbid')

    module_id: str
    summary: str
    ports: list[PortSpec]
    dependencies: list[str] = Field(default_factory=list)
    dependency_interfaces: list[str] = Field(default_factory=list)
    required_checkpoints: list[str] = Field(default_factory=list)
    prohibited_constructs: list[str] = Field(default_factory=list)
    writable_targets: list[str] = Field(default_factory=list)
    canonical_rtl_targets: list[str] = Field(default_factory=list)
    canonical_tb_target: str


class TestbenchContract(BaseModel):
    model_config = ConfigDict(extra='forbid')

    module_id: str
    tb_language: str
    vector_format: str
    checkpoint_names: list[str] = Field(default_factory=list)
    checkpoint_contract: str | None = None
    plusargs: list[str] = Field(default_factory=list)
    success_rules: list[str] = Field(default_factory=list)
    writable_target: str


class ModuleDesignBrief(BaseModel):
    model_config = ConfigDict(extra='forbid')

    module_id: str
    summary: str
    design_goals: list[str] = Field(default_factory=list)
    dependency_notes: list[str] = Field(default_factory=list)
    vectors: list[str] = Field(default_factory=list)
    checkpoints: list[str] = Field(default_factory=list)
    implementation_hints: list[str] = Field(default_factory=list)
    repair_hints: list[str] = Field(default_factory=list)
    skill_paths: list[str] = Field(default_factory=list)
    workspace_strategy: str


class NodeWorkspaceState(str, Enum):
    MISSING = 'missing'
    DRAFT_READY = 'draft_ready'
    VALIDATED = 'validated'
    PROMOTED = 'promoted'
    REPAIRING = 'repairing'
    BLOCKED = 'blocked'
    FAILED = 'failed'


class ValidationFailurePhase(str, Enum):
    L0_COMPILE = 'l0_compile'
    L1_SIM = 'l1_sim'
    CHECKPOINT_MISSING = 'checkpoint_missing'
    CHECKPOINT_FAILED = 'checkpoint_failed'


class NodeWorkspaceRecord(BaseModel):
    model_config = ConfigDict(extra='forbid')

    module_id: str
    workspace_root: str
    state: NodeWorkspaceState
    validation_runs: int = Field(default=0, ge=0)
    repair_edit_count: int = Field(default=0, ge=0)
    contract_paths: dict[str, str]
    draft_paths: dict[str, str]
    promoted_paths: dict[str, str]
    validation_paths: dict[str, str]
    canonical_targets: list[str]
    snapshot_paths: list[str] = Field(default_factory=list)


class RepairContract(BaseModel):
    model_config = ConfigDict(extra='forbid')

    module_id: str
    workspace_root: str
    generation_result_path: str
    workspace_state_path: str
    validation_summary_path: str
    validation_error_path: str
    failure_phase: ValidationFailurePhase | None = None
    primary_target_file: str
    primary_target_reason: str | None = None
    primary_file_excerpt: str | None = None
    secondary_target_files: list[str] = Field(default_factory=list)
    required_first_edit: str
    first_edit_steps: list[str] = Field(default_factory=list)
    must_add_tokens: list[str] = Field(default_factory=list)
    expected_checkpoint: str | None = None
    error_excerpt: str | None = None
    simulation_log_excerpt: str | None = None
    rerun_command: str
    edit_verification: dict[str, object] = Field(default_factory=dict)


class EditReceipt(BaseModel):
    model_config = ConfigDict(extra='forbid')

    module_id: str
    workspace_root: str
    repair_request_path: str
    edited_files: list[str] = Field(default_factory=list)
    first_edit_summary: str
    rerun_command: str


class PromotionRecord(BaseModel):
    model_config = ConfigDict(extra='forbid')

    module_id: str
    promoted_at: str
    draft_paths: list[str]
    promoted_targets: list[str]
    snapshot_paths: list[str] = Field(default_factory=list)
    validation_paths: list[str] = Field(default_factory=list)
    checkpoint_summary: dict[str, str] = Field(default_factory=dict)


class IntegrationRegressionManifest(BaseModel):
    model_config = ConfigDict(extra='forbid')

    top_module: str
    rtl_files: list[str]
    tb_file: str
    build_output_dir: str
    sim_output_dir: str
    required_modules: list[str]
    interface_freeze_hash: str
    regression_checkpoints: list[str]
    vector_set: str
    latency_target_cycles: int
    back_to_back_required: bool
    mid_reset_scenarios: list[str]
    checkpoint_contract: str

    @model_validator(mode='after')
    def validate_manifest(self) -> 'IntegrationRegressionManifest':
        if self.top_module not in self.required_modules:
            raise ValueError('Integration top module must appear in required_modules')
        if self.latency_target_cycles < 1:
            raise ValueError('Integration latency target must be positive')
        return self
