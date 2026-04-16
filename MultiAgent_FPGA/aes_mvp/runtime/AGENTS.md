<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-04-16 -->

# runtime

## Purpose

SDK integration layer that bridges the pure-Python contract/synthesis/generation layers with the OpenHands SDK conversation engine. Handles bootstrap, agent factory, conversation driving, session orchestration, and the `run_executor` custom tool.

## Key Files

| File | Description |
|------|-------------|
| `bootstrap.py` | `RuntimeBootstrap.build()` — frozen factory that validates skills, synthesizes artifacts, configures MCP+LLM. Single shared context for all components. |
| `factory.py` | `SdkAgentFactory` — creates SDK agents per role (orchestrator, worker, repair, L2, finalizer). Registers delegate factories, filters MCP tools, builds `AgentContext` with skill filtering. |
| `runner.py` | `ConversationRunner` — drives SDK conversations. `run_current_batch_until_gate()` runs conversation in daemon thread with gate-polling loop (200ms interval). |
| `session.py` | `ExecutionSession` — top-level orchestration driver (~3,300 lines). Plans batches via `DAGBatchPlanner`, runs gate-controlled execution loop, handles repair verification, promotion tracking, cascade blocking, integration regression, and finalizer. |
| `execution_tools.py` | `RunExecutor` tool — the **only** agent interface to Verilator. Loads task contracts, dispatches to L0/L1/L2/integration executors, returns structured observations with next-action hints. |
| `sdk_shim.py` | SDK import shim with `rich` and `protobuf` compatibility patches. |
| `context_assembler.py` | Builds structured batch messages (`BatchMessageEnvelope`) and task contract envelopes (`TaskContractEnvelope`) for conversation prompts. |

## For AI Agents

### Working In This Directory
- `session.py` is the most complex file (~3,300 lines) — read in chunks, understand the `while True` execution loop before modifying
- The exception handler in `run()` (line 3094+) has a provider-failure fallback that synthesizes results without the LLM — keep this path working
- Each batch gets a **fresh conversation** (new UUID) — conversations accumulate, not replace
- The `batch_gate` is a closure that checks artifact mtime/size changes — framework-controlled, not LLM-controlled
- `execution_tools.py` dispatches to `__main__` CLI functions — changes to CLI signatures must be reflected here

### Testing Requirements
```bash
PYTHONPATH=. python -m pytest tests/unit/test_multiagent_fpga_runtime.py -x
```

### Critical Invariants
- `register_execution_tools()` is called once (guarded by `_REGISTERED` flag)
- Delegate agents inherit parent LLM via `model_copy(update={'usage_id': ...})`
- `VERILATOR_ALLOWED_MCP_REGEX` blocks `testbenchgenerator` and `naturallanguage` tools
- Batch timeouts are phase-specific: generate=600s, repair=420s, l2=300s, integration=300s

<!-- MANUAL: -->
