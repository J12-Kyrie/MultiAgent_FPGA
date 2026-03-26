# Verilator MCP Example

This example shows the current OpenHands-compatible way to call a local `verilator-mcp` stdio server and run a real Verilator simulation.

It uses the same MCP server model that OpenHands runtime and the V1 agent path consume:

- define an `MCPStdioServerConfig`
- connect through OpenHands MCP client utilities
- call `verilator_compile`
- call `verilator_simulate` with `useExistingBuild=true`

## Files

- [counter.v](/Users/kyrie/Downloads/OpenHands-1.5.0/examples/verilator_mcp/rtl/counter.v)
- [counter_main.cpp](/Users/kyrie/Downloads/OpenHands-1.5.0/examples/verilator_mcp/tb/counter_main.cpp)
- [run_direct_mcp.py](/Users/kyrie/Downloads/OpenHands-1.5.0/examples/verilator_mcp/run_direct_mcp.py)

## Prerequisites

- `VERILATOR_MCP_ENTRYPOINT` points to a built `verilator-mcp` entrypoint
- Homebrew Verilator exists at `/opt/homebrew/bin/verilator`
- run from the Python environment that can import OpenHands

Example:

```bash
export VERILATOR_MCP_ENTRYPOINT=/Users/kyrie/Downloads/OpenHands-1.5.0/mcp4eda/verilator-mcp/dist/index.js
cd /Users/kyrie/Downloads/OpenHands-1.5.0
/opt/anaconda3/envs/openhands/bin/python examples/verilator_mcp/run_direct_mcp.py
```

## Expected flow

1. `run_direct_mcp.py` builds a stdio MCP config for `verilator-mcp`
2. OpenHands MCP client connects and discovers tools
3. `verilator_compile` builds `build/obj_dir/Vcounter`
4. `verilator_simulate` runs the executable and writes:
   - `sim_output/simulation.log`
   - `sim_output/simulation.vcd`

The example keeps the RTL in `rtl/` on purpose because the current `verilator-mcp`
`useExistingBuild=true` path heuristically looks for `../../rtl/<top>.v` relative to
the compiled `obj_dir`.

## Mapping to V1 SDK MCP config

The current repository uses runtime-side MCP config classes, but the server shape maps directly to the V1 SDK `mcp_config` dictionary:

```python
mcp_config = {
    "mcpServers": {
        "verilator": {
            "command": "/opt/homebrew/bin/node",
            "args": ["/abs/path/to/verilator-mcp/dist/index.js"],
            "env": {
                "PATH": "/opt/homebrew/bin:...",
                "HOME": "/Users/kyrie",
                "LOG_LEVEL": "info",
            },
        }
    }
}
```

The important part is the stdio server contract:

- `command`: executable only
- `args`: argument list
- `env`: explicit environment, especially `PATH`
