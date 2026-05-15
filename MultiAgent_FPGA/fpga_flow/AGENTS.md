<!-- Parent: ../../AGENTS.md -->
<!-- Generated: 2026-04-16 -->

# aes_mvp

## Purpose

The core Python package implementing a multi-agent FPGA design automation framework for AES-128 encrypt-only hardware. Orchestrates the full pipeline — from spec synthesis through RTL generation, Verilator-based verification, repair cycles, and integration regression — using a **framework-controlled** (not prompt-controlled) architecture where batch progression and acceptance decisions are owned by the state machine, not the LLM.

## Key Files

| File | Description |
|------|-------------|
| `__main__.py` | CLI entry: `validate`, `smoke-sdk`, `smoke-provider`, `run-node`, `run-aes-mvp`, etc. |
| `artifacts.py` | All Pydantic models: `SpecIR`, `PlanDAG`, `PlanDAGNode`, `ModuleRunResult`, `RepairContract`, `EditReceipt`, `PromotionRecord`, etc. All use `extra='forbid'`. |
| `synthesis.py` | `_aes_blueprints()` (single source of truth), `synthesize_spec_ir/plan_dag/integration_manifest()`, `ContractCompiler`, `NodePolicyEngine`, `DAGBatchPlanner`, `L2AdaptivePlanner`, `IntegrationReadinessResolver` |
| `generation.py` | Workspace lifecycle: `initialize_node_workspace()`, repair cycle (`write_repair_request` → `verify_repair_edit` → `write_edit_receipt`), `promote_workspace()`, `evaluate_validation_result()` |
| `memory.py` | `MemoryStore` — centralized RTL/TB pre-population from skill markdown files. Maps `module_id` → memory key via `_MEMORY_REGISTRY`. |
| `executors.py` | `L0Executor` (compile), `L1Executor` (compile+sim), `L2CampaignExecutor` (robustness), `IntegrationRegressionExecutor` (multi-campaign). All use `VerilatorMCPAdapter`. |
| `executor_contracts.py` | Resolved input dataclasses, checkpoint rollup via `summarize_required_checkpoints()` |
| `delegation.py` | `NodeExecutionRequest`, `DelegateBatchTask`, `DelegateBatchPlan`, `SubagentWorkMode` enum |
| `policy.py` | `AgentExecutionPolicy` — maps `OrchestratorState` → `LLMProfileName` + `SubagentPolicy`. Escalation threshold = 2 repair attempts. |
| `prompts.py` | Prompt builders: `build_execution_orchestrator_prompt()`, `build_module_worker_prompt()`, `build_repair_worker_prompt()`, `build_l2_campaign_prompt()` |
| `prompt_contracts.py` | Composable `BaseContract` and `PhaseMixin` constants, `compose_prompt()` |
| `skill_refs.py` | 16 `SkillRef` entries (5 runtime + 5 memory + 6 doc-only), skill key groupings |
| `llm_profiles.py` | DeepSeek API profiles, preflight checks, response parsing |
| `paths.py` | Canonical path constants: `PACKAGE_ROOT`, `REPO_ROOT`, `RTL_DIR`, `TB_DIR`, `VECTORS_DIR` |
| `ARCHITECTURE_DIAGRAMS.md` | 14 Mermaid diagrams covering all system flows |

## Subdirectories

| Directory | Purpose |
|-----------|---------|
| `runtime/` | SDK integration: bootstrap, factory, runner, session, tools (see `runtime/AGENTS.md`) |
| `orchestrator/` | State machine: `AESWorkflowOrchestrator` (see `orchestrator/AGENTS.md`) |
| `agents/` | Agent spawn specs per role (see `agents/AGENTS.md`) |
| `adapters/` | Verilator MCP adapter (see `adapters/AGENTS.md`) |
| `rtl/` | Canonical Verilog source files (4 modules) |
| `tb/` | C++ testbenches + `aes_tb_common.hpp` shared utilities |
| `vectors/` | KAT vectors, L2 campaign vectors |
| `reports/` | Runtime output: conversation artifacts, workspace states |

## For AI Agents

### Working In This Directory
- `_aes_blueprints()` in `synthesis.py` is the **single source of truth** for all AES node definitions
- All Pydantic models use `extra='forbid'` — never add unknown fields
- The `run_executor` tool is the **only** allowed way to trigger compile/simulate — never call raw Verilator MCP
- Workspace state transitions follow: MISSING → DRAFT_READY → GENERATED → VALIDATED → PROMOTED (or BLOCKED)
- Memory extraction failure is a hard error — all 4 modules require verified memory skill files

### Testing Requirements
```bash
PYTHONPATH=. python -m pytest tests/unit/test_multiagent_fpga_aes_mvp.py -x
PYTHONPATH=. python -m pytest tests/unit/test_multiagent_fpga_executors.py -x
PYTHONPATH=. python -m pytest tests/unit/test_multiagent_fpga_runtime.py -x
PYTHONPATH=. python -m MultiAgent_FPGA.aes_mvp validate  # contract validation
```

### Common Patterns
- Framework owns progression: batch gate callbacks check artifact existence, not LLM signals
- Checkpoint protocol: `CHECKPOINT|<name>|PASS|<detail>` parsed from `simulation.log`
- Repair contract: SHA-256 baseline hashes + `must_add_tokens` for verification
- Two LLM profiles: `thinking` (orchestrator/integration) and `fast` (workers)

## Dependencies

### Internal
- `openhands.sdk` — Agent, Conversation, Tool, Workspace, DelegateTool
- `.openhands/skills/` — 16 skill markdown files
- `mcp4eda/verilator-mcp/` — Node.js MCP server for Verilator

### External
- `pydantic` — All contract models
- `litellm` — LLM abstraction (via OpenHands SDK)
- `requests` — DeepSeek API preflight

<!-- MANUAL: -->
