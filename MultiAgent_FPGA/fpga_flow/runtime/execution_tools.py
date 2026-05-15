"""Custom SDK tools that execute FPGA flow framework actions structurally."""

from __future__ import annotations

import json
from pathlib import Path
from typing import Any, Sequence

from pydantic import Field

from MultiAgent_FPGA.fpga_flow.delegation import DelegateBatchTask, SubagentWorkMode
from MultiAgent_FPGA.fpga_flow.executor_contracts import (
    ExecutorKind,
    ExecutorObservation,
    ExecutorStatus,
    NextAction,
    NextReadHints,
)
from MultiAgent_FPGA.fpga_flow.runtime.sdk_shim import SDKUnavailableError

try:
    from openhands.sdk import Action, Observation, TextContent
    from openhands.sdk.tool import ToolDefinition, ToolExecutor, register_tool
except Exception as exc:  # pragma: no cover - exercised in environments without SDK
    raise SDKUnavailableError(
        f'OpenHands SDK tool package is unavailable: {exc}'
    ) from exc


RUN_EXECUTOR_TOOL_NAME = 'run_executor'


class RunExecutorAction(Action):
    request_path: str = Field(
        description='Absolute path to a delegate/integration task contract JSON.'
    )


class RunExecutorObservation(Observation):
    executor_kind: ExecutorKind
    status: ExecutorStatus
    phase: str
    request_path: str
    module_id: str | None = None
    summary: str
    result_paths: dict[str, str] = Field(default_factory=dict)
    next_read_paths: list[str] = Field(default_factory=list)
    next_read_hints: list[NextReadHints] = Field(default_factory=list)
    repair_request_path: str | None = None
    repair_verify_failure_path: str | None = None
    recommended_next_phase: str | None = None
    workflow_gate_hint: str | None = None
    payload: dict[str, object] = Field(default_factory=dict)

    @property
    def to_llm_content(self) -> Sequence[TextContent]:
        lines = [
            f'run_executor: {self.executor_kind.value}',
            f'status: {self.status.value}',
            f'phase: {self.phase}',
            f'request_path: {self.request_path}',
            f'summary: {self.summary}',
        ]
        if self.module_id:
            lines.append(f'module_id: {self.module_id}')
        if self.recommended_next_phase:
            lines.append(f'recommended_next_phase: {self.recommended_next_phase}')
        if self.workflow_gate_hint:
            lines.append(f'workflow_gate_hint: {self.workflow_gate_hint}')
        if self.result_paths:
            lines.extend(
                [
                    'result_paths:',
                    *[f'- {k}: {v}' for k, v in self.result_paths.items()],
                ]
            )
        if self.next_read_hints:
            for hint in self.next_read_hints:
                lines.append(f'next_action: {hint.action.value}')
                if hint.reason:
                    lines.append(f'  reason: {hint.reason}')
                if hint.paths:
                    lines.extend(f'  - {p}' for p in hint.paths[:5])
        if self.repair_request_path:
            lines.append(f'repair_request_path: {self.repair_request_path}')
        if self.payload:
            for key in ('validation_status', 'recommended_mode'):
                if key in self.payload:
                    lines.append(f'{key}: {self.payload[key]}')
        if self.next_read_paths:
            lines.extend(
                ['next_read_paths:', *[f'- {path}' for path in self.next_read_paths]]
            )
        return [TextContent(text='\n'.join(lines))]

    @classmethod
    def from_executor_observation(
        cls, observation: ExecutorObservation, *, is_error: bool = False
    ) -> 'RunExecutorObservation':
        instance = cls(
            content=[],
            is_error=is_error,
            executor_kind=observation.executor_kind,
            status=observation.status,
            phase=observation.phase,
            request_path=observation.request_path,
            module_id=observation.module_id,
            summary=observation.summary,
            result_paths=observation.result_paths,
            next_read_paths=observation.next_read_paths,
            next_read_hints=observation.next_read_hints,
            repair_request_path=observation.repair_request_path,
            repair_verify_failure_path=observation.repair_verify_failure_path,
            recommended_next_phase=observation.recommended_next_phase,
            workflow_gate_hint=observation.workflow_gate_hint,
            payload=observation.payload,
        )
        # Sync content with to_llm_content so both access paths agree
        return instance.model_copy(update={'content': list(instance.to_llm_content)})


def _load_task_contract(path: Path) -> DelegateBatchTask:
    payload = json.loads(path.read_text(encoding='utf-8'))
    if not isinstance(payload, dict):
        raise ValueError(f'Invalid task contract payload: {path}')
    task_payload = payload.get('task')
    if not isinstance(task_payload, dict):
        raise ValueError(f'Task contract missing task object: {path}')
    task = DelegateBatchTask.model_validate(task_payload)
    return task.model_copy(update={'request_path': str(path)})


def _infer_executor_kind(task: DelegateBatchTask) -> ExecutorKind:
    # Manual reproduction commands remain in the contract for operators, but
    # runtime dispatch is driven only by the structured request fields below.
    request = task.request
    if request.executor_kind is not None:
        return request.executor_kind
    if task.mode == SubagentWorkMode.GENERATE:
        return ExecutorKind.GENERATE_NODE
    if task.mode == SubagentWorkMode.L2_EXECUTE:
        return ExecutorKind.RUN_NODE
    if task.mode == SubagentWorkMode.VALIDATE:
        return ExecutorKind.RUN_NODE
    if task.mode == SubagentWorkMode.REPAIR:
        return ExecutorKind.RECORD_REPAIR_EDIT
    if task.mode == SubagentWorkMode.INTEGRATION:
        return ExecutorKind.RUN_NODE
    raise ValueError(f'Unsupported task mode for run_executor: {task.mode}')


def _collect_result_paths(
    task: DelegateBatchTask, payload: dict[str, Any]
) -> dict[str, str]:
    result_paths = {
        key: value
        for key, value in task.request.result_paths.items()
        if isinstance(value, str) and value
    }
    for key, value in payload.items():
        if key.endswith('_path') and isinstance(value, str) and value:
            result_paths[key] = value
    return result_paths


def _next_read_paths(task: DelegateBatchTask, payload: dict[str, Any]) -> list[str]:
    ordered: list[str] = []
    seen: set[str] = set()
    candidates = [
        *task.request.next_read_paths,
        *task.request.result_paths.values(),
        payload.get('generation_result_path'),
        payload.get('workspace_state_path'),
        payload.get('repair_request_path'),
        payload.get('edit_receipt_path'),
        payload.get('integration_result_path'),
        payload.get('l2_result_path'),
    ]
    for raw in candidates:
        if not isinstance(raw, str) or not raw.strip():
            continue
        if raw not in seen:
            seen.add(raw)
            ordered.append(raw)
    return ordered


def _recommended_next_phase(
    task: DelegateBatchTask, payload: dict[str, Any]
) -> str | None:
    if isinstance(payload.get('recommended_mode'), str):
        mode = str(payload['recommended_mode']).strip()
        if mode == 'repair':
            return 'repair_edit'
        if mode == 'validate':
            return 'revalidate'
    if task.mode == SubagentWorkMode.REPAIR:
        return 'revalidate'
    if task.mode == SubagentWorkMode.L2_EXECUTE:
        return 'wait_for_next_batch'
    if task.request.executor_kind == ExecutorKind.RUN_INTEGRATION:
        return None
    return 'wait_for_next_batch'


def _workflow_gate_hint(task: DelegateBatchTask, payload: dict[str, Any]) -> str | None:
    if task.request.executor_kind == ExecutorKind.RUN_INTEGRATION:
        return 'framework_will_evaluate_terminal_integration_status'
    if payload.get('validation_status') == 'failed':
        return 'framework_will_schedule_repair_or_block'
    if task.mode == SubagentWorkMode.REPAIR:
        return 'framework_will_materialize_revalidate_batch'
    return 'framework_will_select_next_eligible_batch'


def _status_from_payload(kind: ExecutorKind, payload: dict[str, Any]) -> ExecutorStatus:
    if kind == ExecutorKind.RECORD_REPAIR_EDIT:
        return (
            ExecutorStatus.RECORDED
            if payload.get('repair_status') == 'recorded'
            else ExecutorStatus.FAILED
        )
    if kind == ExecutorKind.RUN_INTEGRATION:
        return (
            ExecutorStatus.PASSED
            if payload.get('status') == 'passed'
            else ExecutorStatus.FAILED
        )
    validation_status = payload.get('validation_status')
    if validation_status == 'passed':
        return ExecutorStatus.PASSED
    if validation_status == 'failed':
        return ExecutorStatus.FAILED
    if 'error' in payload:
        return ExecutorStatus.FAILED
    return ExecutorStatus.PASSED


def _next_read_hints(
    *,
    task: DelegateBatchTask,
    payload: dict[str, Any],
    next_read_paths: list[str],
    status: ExecutorStatus,
) -> list[NextReadHints]:
    if task.mode == SubagentWorkMode.REPAIR:
        return [
            NextReadHints(
                action=NextAction.WAIT_FOR_NEXT_BATCH,
                paths=next_read_paths,
                reason='Repair phase stops after the first concrete edit.',
            )
        ]
    if status == ExecutorStatus.FAILED:
        action = (
            NextAction.EDIT_PRIMARY_TARGET
            if payload.get('recommended_mode') == 'repair'
            else NextAction.ESCALATE_TO_ORCHESTRATOR
        )
        return [
            NextReadHints(
                action=action,
                paths=next_read_paths,
                reason='Execution failed; inspect only the named artifacts before deciding the next step.',
            )
        ]
    return [
        NextReadHints(
            action=NextAction.WAIT_FOR_NEXT_BATCH,
            paths=next_read_paths,
            reason='Framework-owned workflow progression continues after this observation.',
        )
    ]


def _to_executor_observation(
    *,
    task: DelegateBatchTask,
    request_path: Path,
    executor_kind: ExecutorKind,
    payload: dict[str, Any],
) -> ExecutorObservation:
    status = _status_from_payload(executor_kind, payload)
    next_paths = _next_read_paths(task, payload)
    payload_summary = {
        key: value
        for key, value in payload.items()
        if key in {'validation_status', 'repair_status', 'status', 'recommended_mode'}
        or key.endswith('_path')
        or key == 'module_id'
    }
    return ExecutorObservation(
        executor_kind=executor_kind,
        status=status,
        phase=task.mode.value,
        request_path=str(request_path),
        module_id=task.request.module_id,
        summary=(
            f'{task.request.module_id}: {executor_kind.value} -> {status.value}'
            if task.request.module_id
            else f'{executor_kind.value} -> {status.value}'
        ),
        result_paths=_collect_result_paths(task, payload),
        next_read_paths=next_paths,
        next_read_hints=_next_read_hints(
            task=task,
            payload=payload,
            next_read_paths=next_paths,
            status=status,
        ),
        repair_request_path=(
            payload.get('repair_request_path')
            if isinstance(payload.get('repair_request_path'), str)
            else task.request.result_paths.get('repair_request')
        ),
        repair_verify_failure_path=(
            str(
                Path(task.request.workspace_root).resolve()
                / 'repair_verify_failure.json'
            )
            if task.request.workspace_root
            else None
        ),
        recommended_next_phase=_recommended_next_phase(task, payload),
        workflow_gate_hint=_workflow_gate_hint(task, payload),
        payload=payload_summary,
    )


def _dispatch_executor(
    task: DelegateBatchTask, executor_kind: ExecutorKind
) -> dict[str, Any]:
    from MultiAgent_FPGA.fpga_flow.__main__ import (
        _generate_node,
        _record_repair_edit,
        _run_integration,
        _run_node,
    )

    request = task.request
    if executor_kind == ExecutorKind.GENERATE_NODE:
        return _generate_node(request.module_id, workspace_root=request.workspace_root)
    if executor_kind == ExecutorKind.RUN_NODE:
        if request.preflight_record_repair_edit and request.workspace_root:
            edit_receipt = request.result_paths.get('edit_receipt')
            if edit_receipt and not Path(edit_receipt).is_file():
                _record_repair_edit(request.module_id, request.workspace_root)
        return _run_node(
            request.module_id,
            request.l2_profile,
            vecfile=request.vecfile,
            cases=request.cases,
            seed=request.seed,
            workspace_root=request.workspace_root,
            promoted_root=request.executor_inputs.get('promoted_root')
            if isinstance(request.executor_inputs.get('promoted_root'), str)
            else None,
            increment_workspace_validation=bool(
                request.executor_inputs.get('increment_workspace_validation', True)
            ),
        )
    if executor_kind == ExecutorKind.RECORD_REPAIR_EDIT:
        if request.workspace_root is None:
            raise ValueError('record_repair_edit requires workspace_root')
        return _record_repair_edit(request.module_id, request.workspace_root)
    if executor_kind == ExecutorKind.RUN_INTEGRATION:
        promoted_root = request.executor_inputs.get('promoted_root')
        output_root = request.executor_inputs.get('output_root')
        return _run_integration(
            promoted_root=promoted_root if isinstance(promoted_root, str) else None,
            output_root=output_root if isinstance(output_root, str) else None,
        )
    raise ValueError(f'Unsupported executor kind: {executor_kind}')


class RunExecutor(ToolExecutor[RunExecutorAction, RunExecutorObservation]):
    def __call__(
        self, action: RunExecutorAction, conversation=None
    ) -> RunExecutorObservation:  # noqa: ARG002
        request_path = Path(action.request_path).resolve()
        try:
            task = _load_task_contract(request_path)
            executor_kind = _infer_executor_kind(task)
            payload = _dispatch_executor(task, executor_kind)
            observation = _to_executor_observation(
                task=task,
                request_path=request_path,
                executor_kind=executor_kind,
                payload=payload,
            )
            is_error = observation.status == ExecutorStatus.FAILED
            return RunExecutorObservation.from_executor_observation(
                observation, is_error=is_error
            )
        except Exception as exc:  # noqa: BLE001
            # If the task contract could not be loaded (e.g. FileNotFoundError),
            # return a minimal error observation instead of crashing the
            # sub-agent conversation.
            task_loaded = 'task' in dir() and task is not None  # type: ignore[has-type]
            executor_kind_val = (
                executor_kind  # type: ignore[has-type]
                if 'executor_kind' in dir()
                else ExecutorKind.GENERATE_NODE
            )
            if task_loaded:
                observation = ExecutorObservation(
                    executor_kind=executor_kind_val,
                    status=ExecutorStatus.FAILED,
                    phase=task.mode.value,  # type: ignore[union-attr]
                    request_path=str(request_path),
                    module_id=task.request.module_id,  # type: ignore[union-attr]
                    summary=f'{task.request.module_id}: {executor_kind_val.value} failed',  # type: ignore[union-attr]
                    result_paths=dict(task.request.result_paths),  # type: ignore[union-attr]
                    next_read_paths=[
                        path
                        for path in task.request.result_paths.values()  # type: ignore[union-attr]
                        if isinstance(path, str)
                    ],
                    next_read_hints=[
                        NextReadHints(
                            action=NextAction.ESCALATE_TO_ORCHESTRATOR,
                            paths=[
                                path
                                for path in task.request.result_paths.values()  # type: ignore[union-attr]
                                if isinstance(path, str)
                            ],
                            reason=str(exc),
                        )
                    ],
                    repair_request_path=task.request.result_paths.get('repair_request'),  # type: ignore[union-attr]
                    repair_verify_failure_path=(
                        str(
                            Path(task.request.workspace_root).resolve()  # type: ignore[union-attr]
                            / 'repair_verify_failure.json'
                        )
                        if task.request.workspace_root  # type: ignore[union-attr]
                        else None
                    ),
                    recommended_next_phase=_recommended_next_phase(task, {}),  # type: ignore[arg-type]
                    workflow_gate_hint='framework_will_treat_tool_failure_as_protocol_or_execution_failure',
                    payload={
                        'error_type': type(exc).__name__,
                        'error_message': str(exc),
                    },
                )
            else:
                # Task contract could not be loaded — return a minimal error.
                observation = ExecutorObservation(
                    executor_kind=ExecutorKind.GENERATE_NODE,
                    status=ExecutorStatus.FAILED,
                    phase='unknown',
                    request_path=str(request_path),
                    module_id=None,
                    summary=f'run_executor failed: cannot load task contract at {request_path}',
                    result_paths={},
                    next_read_paths=[],
                    next_read_hints=[
                        NextReadHints(
                            action=NextAction.ESCALATE_TO_ORCHESTRATOR,
                            paths=[],
                            reason=str(exc),
                        )
                    ],
                    repair_request_path=None,
                    repair_verify_failure_path=None,
                    recommended_next_phase=None,
                    workflow_gate_hint='framework_will_treat_tool_failure_as_protocol_or_execution_failure',
                    payload={
                        'error_type': type(exc).__name__,
                        'error_message': str(exc),
                    },
                )
            return RunExecutorObservation.from_executor_observation(
                observation, is_error=True
            )


class RunExecutorTool(ToolDefinition[RunExecutorAction, RunExecutorObservation]):
    name = RUN_EXECUTOR_TOOL_NAME

    @classmethod
    def create(cls, conv_state=None, **params) -> Sequence['RunExecutorTool']:  # noqa: ARG003
        return [
            cls(
                description=(
                    'Run the framework-owned executor for one task contract. '
                    'Use this tool instead of raw terminal execution for generate, '
                    'validate, L2, and integration phases.'
                ),
                action_type=RunExecutorAction,
                observation_type=RunExecutorObservation,
                executor=RunExecutor(),
            )
        ]


_REGISTERED = False


def register_execution_tools() -> None:
    global _REGISTERED
    if _REGISTERED:
        return
    register_tool(RUN_EXECUTOR_TOOL_NAME, RunExecutorTool)
    _REGISTERED = True
