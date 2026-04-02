---
name: openhands-sdk-subagent-delegation
description: Guidance for spawning and delegating OpenHands SDK sub-agents, including registry setup, DelegateTool wiring, task boundaries, and result consolidation.
type: knowledge
version: 1.0.0
agent: CodeActAgent
triggers:
  - subagent
  - agent delegation
  - delegate tool
  - spawn delegate
  - parallel subagent
---

# Purpose And Scope

Use this skill when a task can be split into independent subtasks that should run in parallel or with isolated context.

This skill covers:

- `register_agent`
- `DelegateTool`
- `spawn`
- `delegate`
- sub-agent task boundaries
- result consolidation

It does not cover MCP setup, observability, or repository microagents.

# Stable Delegation Flow

1. Identify independent work that does not require shared reasoning.
2. Spawn the sub-agents with explicit names.
3. Delegate bounded tasks to each sub-agent.
4. Wait for all results.
5. Consolidate the outputs in the main agent.

Sub-agents should have a clear ownership boundary. Do not delegate planning, architecture, or cross-agent negotiation to a sub-agent.

# Stable Rules

- Spawn first, delegate second.
- Keep sub-agent tasks independent and measurable.
- Each sub-agent should have its own context and a single responsibility.
- Use the same workspace, but do not let sub-agents rewrite each other's scope.
- If a task needs global reasoning, keep it on the main agent.
- In this repository, use sub-agents only for bounded module work or independent L2 campaigns.
- If the work is architectural, cross-cutting, or shared-state heavy, do not delegate it.

# DelegateTool Setup Pattern

Register the delegate agent factories first, then add the delegate tool to the main agent's tool list:

```python
from openhands.sdk import register_agent

register_agent(
    name="module_worker",
    factory_func=create_module_worker_agent,
    description="Node-local RTL and testbench worker",
)
```

```python
from openhands.tools.delegate import DelegateTool
```

```python
from openhands.sdk import Tool

tools = [Tool(name=DelegateTool.name)]
```

# References

- Sub-agent guide: [Sub-Agent Delegation](https://docs.openhands.dev/sdk/guides/agent-delegation)
- Local architecture notes: [OpenHands.md](/Users/kyrie/Downloads/OpenHands-1.5.0/OpenHands.md)
- Repository policy example: [MultiAgent_FPGA/develop.md](/Users/kyrie/Downloads/OpenHands-1.5.0/MultiAgent_FPGA/develop.md)
