---
name: verilator-mcp-setup
description: Guidance for connecting mcp4eda's verilator-mcp to OpenHands SDK through stdio MCP, validating the local setup, and handing off to the repo's strict Verilator workflow.
type: knowledge
version: 1.0.0
agent: CodeActAgent
triggers:
  - verilator mcp
  - verilator-mcp
  - mcp4eda
  - verilator mcp server
---

# Purpose And When To Use

Use this skill when the task is about connecting `mcp4eda/verilator-mcp` to OpenHands through stdio MCP, validating that the MCP server is discoverable, or explaining the SDK-facing setup shape.

This skill is for MCP server setup and integration, not day-to-day Verilator execution policy. After the MCP server is connected and validated, follow [verilog_verilator.md](verilog_verilator.md) for the strict compile-then-simulate runtime workflow.

# Local Prerequisites

Use these validated local paths for this machine:

- Node: `/opt/homebrew/bin/node`
- Verilator: `/opt/homebrew/bin/verilator`
- MCP entrypoint: `/Users/kyrie/Downloads/OpenHands-1.5.0/mcp4eda/verilator-mcp/dist/index.js`
- Python environment: `/opt/anaconda3/envs/openhands/bin/python`
- Workspace root: `/Users/kyrie/Downloads/OpenHands-1.5.0`

Before treating setup as complete, confirm:

- `/opt/homebrew/bin/node` exists
- `/opt/homebrew/bin/verilator` exists
- `/Users/kyrie/Downloads/OpenHands-1.5.0/mcp4eda/verilator-mcp/dist/index.js` exists
- the Python environment can import `openhands`

# OpenHands SDK MCP Contract

Use the SDK MCP shape below. For this repo, the stable integration path is stdio only.

- `mcp_config` must be shaped as `{"mcpServers": {"verilator": {...}}}`
- `command` must be the executable only
- `args` must contain the `dist/index.js` entrypoint
- `env` must set at least `PATH`, `HOME`, and `LOG_LEVEL`
- include `VERILATOR_PATH=/opt/homebrew/bin/verilator`

```python
mcp_config = {
    "mcpServers": {
        "verilator": {
            "command": "/opt/homebrew/bin/node",
            "args": [
                "/Users/kyrie/Downloads/OpenHands-1.5.0/mcp4eda/verilator-mcp/dist/index.js"
            ],
            "env": {
                "PATH": "/opt/homebrew/bin:/usr/bin:/bin",
                "HOME": "/Users/kyrie",
                "LOG_LEVEL": "info",
                "VERILATOR_PATH": "/opt/homebrew/bin/verilator",
            },
        }
    }
}
```

Repository mapping for the current OpenHands codebase:

- `openhands/app_server/app_conversation/live_status_app_conversation_service.py` builds `mcp_config` in SDK format
- `openhands/mcp/client.py` connects to stdio MCP servers and lists tools
- `openhands/mcp/utils.py` converts discovered MCP tools into agent-usable tool definitions

# Verified Local Setup And Smoke Test

Use the validated local smoke test when you need to prove setup end to end:

```bash
export VERILATOR_MCP_ENTRYPOINT=/Users/kyrie/Downloads/OpenHands-1.5.0/mcp4eda/verilator-mcp/dist/index.js
cd /Users/kyrie/Downloads/OpenHands-1.5.0
PYTHONPATH=. /opt/anaconda3/envs/openhands/bin/python examples/verilator_mcp/run_direct_mcp.py
```

Expected discovered tools:

- `verilator_compile`
- `verilator_simulate`
- `verilator_testbenchgenerator`
- `verilator_naturallanguage`

Expected stable success artifacts:

- `build/obj_dir/Vcounter`
- `sim_output/simulation.log`
- `sim_output/simulation.vcd`

If the smoke test fails before tool discovery, treat that as a setup problem. If it discovers tools but fails later, treat that as a workflow or design problem.

# Stable Tool Boundaries

Setup validation may confirm that four Verilator MCP tools are discoverable, but stable production use in this repository should rely only on:

- `verilator_compile`
- `verilator_simulate`

Do not treat these as part of the stable repo workflow:

- `verilator_testbenchgenerator`
- `verilator_naturallanguage`

Do not rely on `simulation://...` MCP resources for the stable path. The stable path reads generated filesystem artifacts directly.

# Handoff To `verilog_verilator`

Once setup passes, use [verilog_verilator.md](verilog_verilator.md) for actual Verilog test execution policy.

That skill governs:

- required `topModule`, `files`, and `outputDir`
- the requirement for an existing testbench
- fixed `.v` workflow with `language: "verilog"`
- the strict two-step flow: `verilator_compile` then `verilator_simulate`
- direct inspection of `simulation.log` and `simulation.vcd`
