---
name: openhands-sdk-observability
description: Guidance for tracing, logging, and debugging OpenHands SDK conversations, agents, tool calls, and event streams.
type: knowledge
version: 1.0.0
agent: CodeActAgent
triggers:
  - openhands trace
  - observability
  - event stream
  - replay
  - debug
  - otel
---

# Purpose And Scope

Use this skill when you need to inspect, debug, or reason about the behavior of an OpenHands SDK agent runtime.

This skill covers:

- OpenTelemetry tracing
- conversation lifecycle events
- agent step traces
- tool call traces
- replay and debug workflows

It does not cover runtime setup, MCP wiring, sub-agent delegation mechanics, or model-selection policy.

# What To Inspect First

When debugging a failed run, inspect in this order:

1. Conversation lifecycle and state transitions.
2. Agent step history.
3. Tool call inputs and outputs.
4. LLM request / response metadata.
5. Workspace or runtime logs.

If the problem is tool-specific, inspect the tool span and the returned observation. If the problem is planning or reasoning, inspect the agent step trace first.

# Stable Tracing Rules

- Use trace IDs or conversation IDs to correlate spans.
- Treat the event stream as the source of truth for runtime behavior.
- Use direct runtime logs for file-system or command-execution issues.
- Keep provider-specific metadata separate from user-visible output.
- Do not debug tool failures only from summaries; inspect the raw observation when possible.
- If the failure is a workflow-design issue rather than a runtime issue, hand off to the appropriate planning or skill-specific guide.

# What OpenHands Traces

The SDK documentation describes tracing for:

- agent execution steps
- tool calls and executions
- LLM API calls
- conversation lifecycle events
- browser sessions when applicable

For FPGA workflows in this repository, combine SDK traces with direct inspection of generated artifacts such as `simulation.log` and `simulation.vcd` when a Verilator run fails.

# References

- Observability guide: [Observability & Tracing](https://docs.openhands.dev/sdk/guides/observability)
- SDK overview: [SDK Package](https://docs.openhands.dev/sdk/arch/sdk)
- Local architecture notes: [OpenHands.md](/Users/kyrie/Downloads/OpenHands-1.5.0/OpenHands.md)
