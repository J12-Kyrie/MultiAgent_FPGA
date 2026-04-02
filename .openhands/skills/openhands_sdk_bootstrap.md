---
name: openhands-sdk-bootstrap
description: Guidance for creating and running a minimal OpenHands Software Agent SDK runtime, including LLM, Agent, Conversation, and Workspace setup.
type: knowledge
version: 1.0.0
agent: CodeActAgent
triggers:
  - sdk bootstrap
  - openhands sdk bootstrap
  - conversation
  - workspace
  - agent runtime
  - llmconfig
---

# Purpose And Scope

Use this skill when you need the shortest path from SDK concepts to a runnable agent runtime.

This skill covers:

- `LLM`
- `AgentContext`
- `Agent`
- `Workspace`
- `Conversation`

It does not cover MCP integration, sub-agent delegation, skill authoring, or repository-specific workflows.

# Minimal Startup Order

Follow this order when bootstrapping an SDK runtime:

1. Choose the SDK `LLM` configuration and keep secrets external.
2. Load or define the agent skills / context.
3. Create the `Agent`.
4. Create the `Workspace`.
5. Create the `Conversation`.
6. Send the first message and run the conversation loop.

If the project pins a provider-specific model, reuse the pinned profile instead of hardcoding a second model path.

# Stable Rules

- Keep configuration provider-agnostic unless the project explicitly pins a provider.
- Store API keys in environment variables or a secrets store.
- Use `SecretStr` for sensitive values when the SDK expects it.
- If the runtime cannot import the SDK package, treat that as an integration gap rather than a workflow failure.
- Prefer the official SDK abstraction over direct app-specific plumbing.
- For the external SDK runtime package, prefer `import openhands.sdk` and verify the package in the active Poetry environment.
- If the task is about Chatfire, Verilator, or a repository-specific runtime policy, hand off to a dedicated skill for that topic.

# References

- Local architecture notes: [OpenHands.md](/Users/kyrie/Downloads/OpenHands-1.5.0/OpenHands.md)
- SDK architecture: [SDK Package](https://docs.openhands.dev/sdk/arch/sdk)
- Conversation lifecycle: [Conversation](https://docs.openhands.dev/sdk/arch/conversation)
- Example startup patterns: [OpenHands software-agent-sdk](https://github.com/OpenHands/software-agent-sdk)
