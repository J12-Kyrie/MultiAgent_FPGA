"""Conversation helpers for the SDK-backed AES MVP runtime."""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from uuid import UUID

from MultiAgent_FPGA.aes_mvp.runtime.bootstrap import RuntimeBootstrap
from MultiAgent_FPGA.aes_mvp.runtime.factory import SdkAgentFactory


@dataclass(frozen=True)
class ConversationSummary:
    conversation_id: str
    execution_status: str
    event_count: int
    workspace_root: str
    persistence_dir: str | None


class ConversationRunner:
    """Create and drive local SDK conversations for the AES MVP."""

    def __init__(
        self, bootstrap: RuntimeBootstrap, agent_factory: SdkAgentFactory
    ) -> None:
        self.bootstrap = bootstrap
        self.agent_factory = agent_factory

    def create_orchestrator_conversation(
        self,
        *,
        conversation_id: UUID | None = None,
        persistence_dir: str | Path | None = None,
        delete_on_close: bool = True,
    ):
        orchestrator = self.agent_factory.create_workflow_orchestrator()
        return self.bootstrap.sdk.Conversation(
            orchestrator,
            workspace=self.bootstrap.sdk.LocalWorkspace(
                working_dir=self.bootstrap.workspace_root
            ),
            persistence_dir=persistence_dir or self.bootstrap.persistence_dir,
            conversation_id=conversation_id,
            delete_on_close=delete_on_close,
        )

    def send_and_run(self, conversation, message: str) -> ConversationSummary:
        conversation.send_message(message)
        conversation.run()
        return self.describe(conversation)

    def describe(self, conversation) -> ConversationSummary:
        status = getattr(conversation, 'execution_status', None)
        if status is None:
            status = conversation.state.execution_status
        if hasattr(status, 'value'):
            status = status.value
        events = getattr(conversation, 'events', None)
        if events is None:
            events = conversation.state.events
        persistence_dir = getattr(conversation.state, 'persistence_dir', None)
        if persistence_dir is None:
            persistence_dir = getattr(conversation, 'persistence_dir', None)
        return ConversationSummary(
            conversation_id=str(conversation.state.id),
            execution_status=str(status),
            event_count=len(events),
            workspace_root=str(conversation.workspace.working_dir),
            persistence_dir=str(persistence_dir) if persistence_dir else None,
        )
