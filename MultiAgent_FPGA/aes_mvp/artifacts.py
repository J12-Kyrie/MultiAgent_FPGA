"""Artifact models and loaders for the AES MVP framework."""

from __future__ import annotations

import json
from enum import Enum
from pathlib import Path

from pydantic import BaseModel, ConfigDict, Field, model_validator

from MultiAgent_FPGA.aes_mvp.paths import (
    INTEGRATION_MANIFEST_PATH,
    PLAN_DAG_PATH,
    SPEC_IR_PATH,
)

FROZEN_AES_NODE_IDS = (
    'aes_sbox',
    'aes_key_schedule_128',
    'aes_round_transform',
    'aes128_encrypt_core',
)
FROZEN_AES_DEPENDENCIES = {
    'aes_sbox': [],
    'aes_key_schedule_128': ['aes_sbox'],
    'aes_round_transform': ['aes_sbox'],
    'aes128_encrypt_core': ['aes_key_schedule_128', 'aes_round_transform'],
}


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
        if set(self.module_candidates) != set(FROZEN_AES_NODE_IDS):
            raise ValueError(
                'SpecIR.module_candidates must match the frozen AES node taxonomy'
            )
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


class PlanDAG(BaseModel):
    model_config = ConfigDict(extra='forbid')

    nodes: list[PlanDAGNode]

    @model_validator(mode='after')
    def validate_frozen_aes_dag(self) -> 'PlanDAG':
        node_ids = [node.module_id for node in self.nodes]
        if node_ids != list(FROZEN_AES_NODE_IDS):
            raise ValueError('PlanDAG.nodes must follow the frozen AES node ordering')
        for node in self.nodes:
            if node.language != 'verilog':
                raise ValueError(f'{node.module_id} must use language=verilog')
            if node.depends_on != FROZEN_AES_DEPENDENCIES[node.module_id]:
                raise ValueError(
                    f'{node.module_id} dependencies do not match the frozen AES DAG'
                )
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
    skill_paths: list[str] = Field(default_factory=list)
    workspace_strategy: str


class NodeWorkspaceState(str, Enum):
    MISSING = 'missing'
    DRAFT_READY = 'draft_ready'
    GENERATED = 'generated'
    VALIDATED = 'validated'
    PROMOTED = 'promoted'
    REPAIRING = 'repairing'
    BLOCKED = 'blocked'


class NodeWorkspaceRecord(BaseModel):
    model_config = ConfigDict(extra='forbid')

    module_id: str
    workspace_root: str
    state: NodeWorkspaceState
    validation_runs: int = Field(default=0, ge=0)
    contract_paths: dict[str, str]
    draft_paths: dict[str, str]
    validation_paths: dict[str, str]
    canonical_targets: list[str]
    snapshot_paths: list[str] = Field(default_factory=list)


class PromotionRecord(BaseModel):
    model_config = ConfigDict(extra='forbid')

    module_id: str
    promoted_at: str
    draft_paths: list[str]
    canonical_targets: list[str]
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
        if self.top_module != 'aes128_encrypt_core':
            raise ValueError('Integration top module must be aes128_encrypt_core')
        if self.latency_target_cycles != 11:
            raise ValueError('Integration latency target must be 11 cycles')
        return self


def _load_json_model(path: Path, model_cls: type[BaseModel]) -> BaseModel:
    with path.open('r', encoding='utf-8') as handle:
        return model_cls.model_validate(json.load(handle))


def load_default_spec_ir() -> SpecIR:
    return _load_json_model(SPEC_IR_PATH, SpecIR)


def load_default_plan_dag() -> PlanDAG:
    return _load_json_model(PLAN_DAG_PATH, PlanDAG)


def load_default_integration_manifest() -> IntegrationRegressionManifest:
    return _load_json_model(INTEGRATION_MANIFEST_PATH, IntegrationRegressionManifest)
