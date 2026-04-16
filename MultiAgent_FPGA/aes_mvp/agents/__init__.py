"""Agent specifications for the AES MVP framework."""

from MultiAgent_FPGA.aes_mvp.agents.specs import (
    AgentSpawnSpec,
    build_finalizer_orchestrator_spec,
    build_l2_campaign_spec,
    build_module_worker_spec,
    build_repair_worker_spec,
    build_workflow_orchestrator_spec,
)

__all__ = [
    'AgentSpawnSpec',
    'build_finalizer_orchestrator_spec',
    'build_l2_campaign_spec',
    'build_module_worker_spec',
    'build_repair_worker_spec',
    'build_workflow_orchestrator_spec',
]
