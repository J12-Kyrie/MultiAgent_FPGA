"""Helpers that assemble thin per-batch and per-task runtime context."""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True)
class TaskContractEnvelope:
    request_path: Path
    working_directory: str | None
    phase: str


@dataclass(frozen=True)
class BatchMessageEnvelope:
    batch_id: str
    phase: str
    snapshot_path: Path
    workflow_gate_path: Path
    delegate_requests_dir: Path
    report_root: Path
    expected_artifacts: tuple[str, ...]
    handoff_digest_path: Path | None = None
    integration_request_path: Path | None = None


class ContextAssembler:
    """Build terse prompts/messages from structured runtime artifacts."""

    def build_delegate_transport_shell(self, *, envelope: TaskContractEnvelope) -> str:
        lines = [
            f'REQUIRED request_path: {envelope.request_path}',
            f'Task contract file: {envelope.request_path}',
            f'Phase: {envelope.phase}',
        ]
        if envelope.phase == 'repair_edit':
            lines.append(
                'Repair phase: use repair_request.primary_target_file as the first and only initial edit target.'
            )
        else:
            lines.append("Advance this phase only through 'run_executor'.")
        if envelope.working_directory:
            lines.append(f'Working directory: {envelope.working_directory}')
        lines.append('Do not inspect unrelated paths before reading the task contract.')
        return '\n'.join(lines)

    def attach_task_contract_hint(
        self, prompt: str, envelope: TaskContractEnvelope
    ) -> str:
        transport = self.build_delegate_transport_shell(envelope=envelope)
        if not prompt or not prompt.strip():
            return transport
        return f'{transport}\n\n{prompt}'

    def build_batch_message(
        self,
        *,
        base_message: str,
        envelope: BatchMessageEnvelope,
    ) -> str:
        lines = [
            'Framework-controlled execution batch.',
            f'batch_id: {envelope.batch_id}',
            f'phase: {envelope.phase}',
            f'current_batch_snapshot: {envelope.snapshot_path}',
            f'workflow_gate: {envelope.workflow_gate_path}',
            f'delegate_requests_dir: {envelope.delegate_requests_dir}',
            f'report_root: {envelope.report_root}',
        ]
        if envelope.expected_artifacts:
            lines.extend(
                [
                    'expected_artifacts:',
                    *[f'- {path}' for path in envelope.expected_artifacts],
                ]
            )
        if envelope.handoff_digest_path is not None:
            lines.append(f'autonomous_handoff_digest: {envelope.handoff_digest_path}')
        if envelope.integration_request_path is not None:
            lines.append(f'integration_request: {envelope.integration_request_path}')
        lines.append(
            'Complete only this batch. Structured artifacts are the source of truth.'
        )
        lines.append(
            'ACTION SEQUENCE: 1) Read current_batch_snapshot (one cat command). '
            '2) Immediately spawn the registered worker. '
            '3) Delegate with the VERBATIM task prompt from delegate.tasks. '
            'Do NOT read design briefs, contracts, workspace directories, or any '
            'other files before delegating — the worker receives all paths it needs '
            'in the task prompt. Minimize orchestrator iterations.'
        )
        lines.append(
            'CRITICAL: When delegating tasks, pass the delegate.tasks prompt text '
            'VERBATIM to each sub-agent. Do NOT paraphrase, summarize, or drop any '
            'file paths from the prompt. The request_path in each task prompt is the '
            'exact filesystem path the sub-agent needs. If delegate.request_paths is '
            'present, include "request_path: <path>" in the delegation for each worker.'
        )
        lines.append(f'Original request: {base_message}')
        return '\n'.join(lines)
