---
name: openhands-sdk-mcp-integration
description: Guidance for connecting OpenHands SDK agents to MCP servers, including mcp_config, stdio/SSE/SHTTP setup, tool discovery, filtering, and tool calls.
type: knowledge
version: 1.0.0
agent: CodeActAgent
triggers:
  - openhands mcp
  - mcp_config
  - mcp servers
  - tool discovery
  - stdio server
  - sse server
  - shttp server
---

# Purpose And Scope

Use this skill when the task is about adding external tools to an OpenHands SDK agent through MCP.

This skill covers:

- `mcp_config`
- stdio / SSE / SHTTP servers
- tool discovery
- tool filtering
- tool invocation

It does not cover general agent bootstrapping, sub-agent delegation, observability, or generic MCP clients outside OpenHands.

# Stable MCP Flow

1. Build the MCP configuration.
2. Connect to the server(s).
3. Fetch the discovered tools.
4. Filter the tool surface if needed.
5. Expose the tools to the agent.
6. Call the tool and inspect the returned observation.

Prefer stdio for local command-line servers and SSE/SHTTP for remote servers.

# Stable Rules

- Shape MCP config as `{"mcpServers": {...}}` when following the SDK guide.
- Keep `command` to a single executable for stdio servers.
- Put the server entrypoint in `args`.
- Filter tools when the server exposes more than the workflow should use.
- Treat discovery failures as setup issues first, then workflow issues.
- In this repository, hand off Verilator-specific setup and execution policy to the Verilator skills.
- If a provider has its own stable workflow, layer that provider skill on top of this one instead of expanding this skill.

# Implementation Notes

The local OpenHands codebase already follows this pattern:

- `openhands/core/config/mcp_config.py` defines MCP server configs
- `openhands/mcp/utils.py` discovers clients, converts tools, and executes tool calls
- `openhands/mcp/client.py` connects to MCP servers

Use those patterns instead of inventing a separate ad hoc tool bridge.

# References

- MCP guide: [Model Context Protocol](https://docs.openhands.dev/sdk/guides/mcp)
- Local config model: [openhands/core/config/mcp_config.py](/Users/kyrie/Downloads/OpenHands-1.5.0/openhands/core/config/mcp_config.py)
- Local MCP helpers: [openhands/mcp/utils.py](/Users/kyrie/Downloads/OpenHands-1.5.0/openhands/mcp/utils.py)
- Verilator setup skill: [verilator_mcp_setup.md](/Users/kyrie/Downloads/OpenHands-1.5.0/.openhands/skills/verilator_mcp_setup.md)
