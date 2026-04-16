"""Conversation helpers for the SDK-backed AES MVP runtime."""

from __future__ import annotations

import logging
import threading
import time
from collections.abc import Callable
from dataclasses import dataclass
from pathlib import Path
from typing import Any
from uuid import UUID

from MultiAgent_FPGA.aes_mvp.runtime.bootstrap import RuntimeBootstrap
from MultiAgent_FPGA.aes_mvp.runtime.factory import SdkAgentFactory

logger = logging.getLogger(__name__)

# Terminal status values matching ConversationExecutionStatus enum members.
# Using string values instead of importing the enum directly keeps this module
# importable without the SDK and compatible with test fakes.
_TERMINAL_STATUS_VALUES = frozenset(
    {
        'finished',
        'error',
        'stuck',
        'waiting_for_confirmation',
    }
)


def _status_value(status: Any) -> str:
    """Extract the string value from a ConversationExecutionStatus enum or plain string."""
    return status.value if hasattr(status, 'value') else str(status)


@dataclass(frozen=True)
class ConversationSummary:
    conversation_id: str
    execution_status: str
    event_count: int
    workspace_root: str
    persistence_dir: str | None


@dataclass(frozen=True)
class BatchRunSummary:
    conversation_summary: ConversationSummary
    gate_satisfied: bool
    pause_reason: str | None
    timed_out: bool


class ConversationRunner:
    """Create and drive local SDK conversations for the AES MVP."""

    def __init__(
        self, bootstrap: RuntimeBootstrap, agent_factory: SdkAgentFactory
    ) -> None:
        self.bootstrap = bootstrap
        self.agent_factory = agent_factory

    def create_execution_conversation(
        self,
        *,
        conversation_id: UUID | None = None,
        persistence_dir: str | Path | None = None,
        delete_on_close: bool = True,
        max_iteration_per_run: int = 100,
    ):
        orchestrator = self.agent_factory.create_execution_orchestrator()
        return self.bootstrap.sdk.Conversation(
            orchestrator,
            workspace=self.bootstrap.sdk.LocalWorkspace(
                working_dir=self.bootstrap.workspace_root
            ),
            persistence_dir=persistence_dir or self.bootstrap.persistence_dir,
            conversation_id=conversation_id,
            delete_on_close=delete_on_close,
            max_iteration_per_run=max_iteration_per_run,
        )

    def create_finalizer_conversation(
        self,
        *,
        conversation_id: UUID | None = None,
        persistence_dir: str | Path | None = None,
        delete_on_close: bool = True,
        max_iteration_per_run: int = 50,
    ):
        orchestrator = self.agent_factory.create_finalizer_orchestrator()
        return self.bootstrap.sdk.Conversation(
            orchestrator,
            workspace=self.bootstrap.sdk.LocalWorkspace(
                working_dir=self.bootstrap.workspace_root
            ),
            persistence_dir=persistence_dir or self.bootstrap.persistence_dir,
            conversation_id=conversation_id,
            delete_on_close=delete_on_close,
            max_iteration_per_run=max_iteration_per_run,
        )

    def send_and_run(self, conversation, message: str) -> ConversationSummary:
        conversation.send_message(message)
        conversation.run()
        return self.describe(conversation)

    def run_current_batch_until_gate(
        self,
        conversation,
        message: str,
        *,
        batch_gate: Callable[[], bool],
        timeout_s: float = 180.0,
        poll_interval_s: float = 0.2,
    ) -> BatchRunSummary:
        conversation.send_message(message)
        run_errors: list[BaseException] = []
        completed = threading.Event()

        def _run() -> None:
            try:
                conversation.run()
            except BaseException as exc:  # noqa: BLE001
                run_errors.append(exc)
            finally:
                completed.set()

        runner_thread = threading.Thread(target=_run, daemon=True)
        runner_thread.start()

        deadline = time.monotonic() + timeout_s
        pause_reason: str | None = None
        gate_satisfied = False
        timed_out = False

        while not completed.wait(timeout=poll_interval_s):
            if batch_gate():
                gate_satisfied = True
                pause_reason = 'batch_gate_satisfied'
                conversation.pause()
                break

            status = _status_value(conversation.state.execution_status)
            if status in _TERMINAL_STATUS_VALUES:
                if status == 'finished':
                    pause_reason = 'conversation_finished_before_gate'
                else:
                    pause_reason = f'conversation_{status}'
                try:
                    conversation.pause()
                except Exception:  # noqa: BLE001
                    logger.warning('Failed to pause conversation', exc_info=True)
                break

            if time.monotonic() >= deadline:
                timed_out = True
                pause_reason = 'timeout'
                conversation.pause()
                break

        # If ``run()`` finishes before the first ``wait`` timeout, ``completed`` is
        # already set and the while-loop body never runs; recover terminal status.
        if pause_reason is None and completed.is_set() and not gate_satisfied:
            if batch_gate():
                gate_satisfied = True
                pause_reason = 'batch_gate_satisfied'
                try:
                    conversation.pause()
                except Exception:  # noqa: BLE001
                    logger.warning('Failed to pause conversation', exc_info=True)
            else:
                status = _status_value(conversation.state.execution_status)
                if status in _TERMINAL_STATUS_VALUES:
                    if status == 'finished':
                        pause_reason = 'conversation_finished_before_gate'
                    else:
                        pause_reason = f'conversation_{status}'
                    try:
                        conversation.pause()
                    except Exception:  # noqa: BLE001
                        pass

        if not completed.is_set():
            runner_thread.join(timeout=max(1.0, poll_interval_s * 5))
        if runner_thread.is_alive():
            raise TimeoutError('Conversation run thread did not stop after pause')
        if run_errors:
            raise run_errors[0]

        return BatchRunSummary(
            conversation_summary=self.describe(conversation),
            gate_satisfied=gate_satisfied,
            pause_reason=pause_reason,
            timed_out=timed_out,
        )

    def describe(self, conversation) -> ConversationSummary:
        state = conversation.state
        status = _status_value(state.execution_status)
        return ConversationSummary(
            conversation_id=str(state.id),
            execution_status=status,
            event_count=len(state.events),
            workspace_root=str(conversation.workspace.working_dir),
            persistence_dir=str(state.persistence_dir)
            if state.persistence_dir
            else None,
        )
