"""Structured delegation contracts for the AES MVP runtime."""

from __future__ import annotations

from enum import Enum

from pydantic import BaseModel, ConfigDict, Field, model_validator

from MultiAgent_FPGA.aes_mvp.executor_contracts import ExecutorKind
from MultiAgent_FPGA.aes_mvp.policy import OrchestratorState


class SubagentWorkMode(str, Enum):
    GENERATE = 'generate'
    VALIDATE = 'validate'
    REPAIR = 'repair'
    L2_EXECUTE = 'l2_execute'
    INTEGRATION = 'integration'


class NodeExecutionRequest(BaseModel):
    model_config = ConfigDict(extra='forbid')

    module_id: str
    stage: OrchestratorState
    repair_budget: int = Field(default=2, ge=0)
    writable_paths: list[str] = Field(default_factory=list)
    canonical_targets: list[str] = Field(default_factory=list)
    artifact_paths: list[str] = Field(default_factory=list)
    l2_profile: str | None = None
    vecfile: str | None = None
    cases: int | None = None
    seed: int | None = None
    executor_kind: ExecutorKind | None = None
    executor_inputs: dict[str, object] = Field(default_factory=dict)
    manual_executor_command: str | None = Field(
        default=None,
        description=(
            'Manual reproduction command only. Runtime dispatch must use '
            'executor_kind plus executor_inputs instead of parsing this string.'
        ),
    )
    manual_receipt_command: str | None = Field(
        default=None,
        description=(
            'Manual repair-receipt command only. Runtime dispatch must use '
            'preflight_record_repair_edit instead of this string.'
        ),
    )
    preflight_record_repair_edit: bool = False
    working_directory: str | None = None
    workspace_root: str | None = None
    contract_paths: dict[str, str] = Field(default_factory=dict)
    result_paths: dict[str, str] = Field(default_factory=dict)
    promoted_targets: list[str] = Field(default_factory=list)
    allowed_progress_actions: list[str] = Field(default_factory=list)
    next_read_paths: list[str] = Field(default_factory=list)
    workflow_gate_hint: str | None = None


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
        payload: dict[str, object] = {
            'command': 'delegate',
            'tasks': {task.worker_id: task.prompt for task in self.tasks},
        }
        # Expose request_paths as a separate structured field so the
        # orchestrator LLM cannot lose them by paraphrasing the prompt text.
        rp_map = {
            task.worker_id: task.request_path
            for task in self.tasks
            if task.request_path
        }
        if rp_map:
            payload['request_paths'] = rp_map
        return payload
