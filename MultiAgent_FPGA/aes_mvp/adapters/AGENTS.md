<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-04-16 -->

# adapters

## Purpose

External tool adapters. Currently only wraps the Verilator MCP server for compile and simulate operations.

## Key Files

| File | Description |
|------|-------------|
| `verilator.py` | `VerilatorMCPAdapter` — wraps OpenHands MCP (`verilator_compile`, `verilator_simulate`). Builds `MCPStdioServerConfig` for the Node.js server. Auto-generates `-I` include flags, adds `-CFLAGS -std=c++17` for C++ TBs. `build_verilator_stdio_server()` and `default_verilator_mcp_entrypoint()` helpers. |

## For AI Agents

### Verilator MCP Entry Point
The Node.js server lives at `mcp4eda/verilator-mcp/dist/index.js`. Build with `npm run build` in that directory.

### Filtered Tools
`VERILATOR_ALLOWED_MCP_REGEX` in `runtime/factory.py` blocks `verilator_testbenchgenerator` and `verilator_naturallanguage` — agents should never see these.

<!-- MANUAL: -->
