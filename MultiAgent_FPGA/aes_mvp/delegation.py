"""Structured delegation contracts for the AES MVP runtime."""

from __future__ import annotations

from enum import Enum

from pydantic import BaseModel, ConfigDict, Field, model_validator

from MultiAgent_FPGA.aes_mvp.policy import OrchestratorState


class SubagentWorkMode(str, Enum):
    GENERATE = 'generate'
    BUILD = 'build'
    VALIDATE = 'validate'
    REPAIR = 'repair'
    ARTIFACT_REVIEW = 'artifact_review'
    L2_EXECUTE = 'l2_execute'


class NodeExecutionRequest(BaseModel):
    model_config = ConfigDict(extra='forbid')

    module_id: str
    stage: OrchestratorState
    repair_budget: int = Field(default=2, ge=0)
    writable_paths: list[str] = Field(default_factory=list)
    artifact_paths: list[str] = Field(default_factory=list)
    l2_profile: str | None = None
    vecfile: str | None = None
    cases: int | None = None
    seed: int | None = None
    executor_command: str | None = None
    working_directory: str | None = None
    workspace_root: str | None = None
    contract_paths: dict[str, str] = Field(default_factory=dict)
    result_paths: dict[str, str] = Field(default_factory=dict)
    canonical_targets: list[str] = Field(default_factory=list)


class DelegateBatchTask(BaseModel):
    model_config = ConfigDict(extra='forbid')

    worker_id: str
    agent_type: str
    mode: SubagentWorkMode
    request: NodeExecutionRequest
    prompt: str
    request_path: str | None = None


class DelegateBatchPlan(BaseModel):
    model_config = ConfigDict(extra='forbid')

    batch_id: str
    stage: OrchestratorState
    max_children: int = Field(default=5, ge=1)
    fallback_policy: str
    tasks: list[DelegateBatchTask]

    @model_validator(mode='after')
    def validate_max_children(self) -> 'DelegateBatchPlan':
        if len(self.tasks) > self.max_children:
            raise ValueError(
                f'Batch {self.batch_id} exceeds max_children={self.max_children}'
            )
        return self

    def spawn_payload(self) -> dict[str, object]:
        return {
            'command': 'spawn',
            'ids': [task.worker_id for task in self.tasks],
            'agent_types': [task.agent_type for task in self.tasks],
        }

    def delegate_payload(self) -> dict[str, object]:
        return {
            'command': 'delegate',
            'tasks': {task.worker_id: task.prompt for task in self.tasks},
        }
