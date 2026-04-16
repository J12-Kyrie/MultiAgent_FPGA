<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-04-16 -->

# agents

## Purpose

Agent spawn specifications — frozen dataclasses that declare each agent role's LLM profile, system prompt, skill keys, allowed tools, writable paths, and custom tools.

## Key Files

| File | Description |
|------|-------------|
| `specs.py` | `AgentSpawnSpec` dataclass + 5 builder functions: `build_workflow_orchestrator_spec()`, `build_module_worker_spec(node)`, `build_repair_worker_spec()`, `build_l2_campaign_spec(node, ...)`, `build_finalizer_orchestrator_spec()` |

## For AI Agents

### Agent Roles and Their Tools

| Role | LLM Profile | Tools | Delegate | MCP |
|------|------------|-------|----------|-----|
| Execution Orchestrator | thinking | terminal, ThinkTool, DelegateTool, run_executor | Yes | verilator |
| Module Worker | fast | terminal, file_editor, task_tracker, run_executor | No | No |
| Repair Worker | fast | file_editor, task_tracker | No | No |
| L2 Campaign | fast | file_editor, task_tracker, run_executor | No | No |
| Finalizer | thinking | FinishTool, ThinkTool | No | No |

<!-- MANUAL: -->
