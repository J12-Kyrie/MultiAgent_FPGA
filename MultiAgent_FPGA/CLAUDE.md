# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in the `MultiAgent_FPGA/` directory.

## Project Overview

A blueprint-driven multi-agent FPGA design automation framework built on the OpenHands SDK. It implements a generic hardware design pipeline — from spec intake through RTL generation, Verilator-based compile/simulate verification, robustness testing, and integration regression — using a framework-controlled (not prompt-controlled) architecture where batch progression and acceptance decisions are owned by the state machine, not the LLM. Designs are defined via YAML blueprints in `designs/`; the built-in AES-128 design is the reference implementation.

## Scope Constraints (Frozen for MVP)

- AES-128, encrypt only, block-level handshake, iterative 10-round microarchitecture
- 11-cycle latency target, single-cycle `done` pulse
- No L3 (synthesis/implementation), no decryption, no AES-192/256, no streaming interfaces
- Testbenches are `.cpp` self-checking only — no `.sv`, no auto-generated testbenches
- LLM backend: DeepSeek official API (`deepseek-chat` via `https://api.deepseek.com`)
- Env var: `DEEPSEEK_API_KEY`

## Commands

```bash
# Contract validation (no SDK or API key needed)
PYTHONPATH=. python -m MultiAgent_FPGA.fpga_flow validate

# SDK smoke test
PYTHONPATH=. python -m MultiAgent_FPGA.fpga_flow smoke-sdk

# DeepSeek API preflight
PYTHONPATH=. python -m MultiAgent_FPGA.fpga_flow smoke-provider

# Run a single node through L0+L1 (with workspace tracking)
PYTHONPATH=. python -m MultiAgent_FPGA.fpga_flow run-node aes_sbox --workspace-root /tmp/ws/aes_sbox

# Run a node with L2 robustness campaign
PYTHONPATH=. python -m MultiAgent_FPGA.fpga_flow run-node aes128_encrypt_core --l2-profile rand_small

# Record a repair edit after manual file changes
PYTHONPATH=. python -m MultiAgent_FPGA.fpga_flow record-repair-edit aes_sbox --workspace-root /tmp/ws/aes_sbox

# Generate a node (workspace-aware, memory-prepopulate + validate)
PYTHONPATH=. python -m MultiAgent_FPGA.fpga_flow generate-node aes_sbox

# Manifest-driven integration regression
PYTHONPATH=. python -m MultiAgent_FPGA.fpga_flow run-integration --promoted-root /tmp/ws/promoted

# Full autonomous end-to-end run (AES-128 hardcoded path)
PYTHONPATH=. python -m MultiAgent_FPGA.fpga_flow run-aes-mvp
PYTHONPATH=. python -m MultiAgent_FPGA.fpga_flow run-aes-mvp --dry-run

# Blueprint-driven design run (generic — any design)
PYTHONPATH=. python -m MultiAgent_FPGA.fpga_flow run-design --blueprint designs/aes128/blueprint.yaml --dry-run
PYTHONPATH=. python -m MultiAgent_FPGA.fpga_flow run-design --blueprint designs/led_chaser/blueprint.yaml --dry-run

# Unit tests
PYTHONPATH=. python -m pytest tests/unit/test_multiagent_fpga_aes_mvp.py -x
PYTHONPATH=. python -m pytest tests/unit/test_multiagent_fpga_executors.py -x
PYTHONPATH=. python -m pytest tests/unit/test_multiagent_fpga_runtime.py -x
```

All commands require `PYTHONPATH=.` from the repo root. The `run-node` and `run-integration` commands require Verilator (`/opt/homebrew/bin/verilator`) and the built `verilator-mcp` server (`mcp4eda/verilator-mcp/dist/index.js`).

## Orchestrator State Machine

```
SPEC_INTAKE → ARCHITECTING → PLANNING → MODULE_DESIGN → MODULE_L0 → MODULE_L1
  → [MODULE_L2_OPTIONAL] → INTEGRATION_READY → INTEGRATION_REGRESSION → DONE
```

Each state maps to exactly one LLM profile and one subagent policy via `AgentExecutionPolicy`:

| State | LLM Profile | Subagent Policy |
|-------|-------------|-----------------|
| SPEC_INTAKE, ARCHITECTING, PLANNING | thinking | forbidden |
| MODULE_DESIGN, MODULE_L0, MODULE_L1 | fast | module_worker_allowed |
| MODULE_L2_OPTIONAL | fast | l2_campaign_allowed |
| INTEGRATION_READY, INTEGRATION_REGRESSION | thinking | forbidden |

Escalation rule: if a module worker fails after 2 repair attempts, or the failure is cross-module/interface/state-machine in nature, control returns to the thinking orchestrator.

## AES Node DAG (Frozen)

```
aes_sbox  ←─────────────── aes_key_schedule_128
    │                              │
    └──── aes_round_transform      │
                    │              │
                    └──── aes128_encrypt_core (top/sink)
```

| Node | Checkpoint | L2 Policy | Criticality |
|------|-----------|-----------|-------------|
| `aes_sbox` | `CHK_SBOX_MATCH` | skip | medium |
| `aes_key_schedule_128` | `CHK_ROUNDKEY_MATCH` | conditional | high |
| `aes_round_transform` | `CHK_ROUND_STATE_MATCH` | conditional | high |
| `aes128_encrypt_core` | `CHK_RESET_CLEAR`, `CHK_START_ACCEPTED`, `CHK_BUSY_ASSERTED`, `CHK_DONE_PULSE`, `CHK_CIPHERTEXT_MATCH`, `CHK_BUSY_DEASSERTED` | required | high |

## Layer Architecture

### Contract Layer — data models and validation

- `artifacts.py` — Pydantic models: `SpecIR`, `PlanDAG`/`PlanDAGNode`, `ModuleRunResult`, `IntegrationRegressionManifest`, `NodeWorkspaceRecord`, `RepairContract`, `EditReceipt`, `PromotionRecord`, `ModuleContract`, `TestbenchContract`, `ModuleDesignBrief`. All use `extra='forbid'`.
- `policy.py` — `AgentExecutionPolicy` maps every `OrchestratorState` to an `LLMProfileName` and `SubagentPolicy`. Validates completeness. Provides `should_escalate()` with the 2-attempt threshold.
- `executor_contracts.py` — Resolved input dataclasses (`ResolvedNodeCompileInputs`, `ResolvedL2CampaignInputs`, `ResolvedIntegrationRegressionInputs`), path resolution from `package_root`, checkpoint rollup via `summarize_required_checkpoints()`, L2 vector corpus validation.
- `paths.py` — Canonical path constants: `PACKAGE_ROOT`, `REPO_ROOT`, `RTL_DIR`, `TB_DIR`, `VECTORS_DIR`.

### Synthesis Layer — goal-driven artifact generation

- `synthesis.py` — `synthesize_spec_ir()`, `synthesize_plan_dag()`, `synthesize_integration_manifest()` produce all core artifacts from either a YAML blueprint (via `BlueprintLoader`) or the hardcoded AES fallback in `_aes_blueprints()`.
- `blueprint_loader.py` — `BlueprintLoader` reads YAML blueprint files and converts them to `SpecIR`, `PlanDAG`, and `IntegrationRegressionManifest`. Decouples design-specific data from framework code. `ContractCompiler` generates per-node `ModuleContract`, `TestbenchContract`, `ModuleDesignBrief`. `NodePolicyEngine` decides workspace state transitions (generate/repair/blocked). `DAGBatchPlanner` produces topological-layer batches. `L2AdaptivePlanner` selects L2 profiles from fragility history. `IntegrationReadinessResolver` computes dependency closures and selects the integration sink.

### Execution Layer — Verilator compile/simulate

- `executors.py` — `L0Executor` (compile gate), `L1Executor` (compile+simulate+checkpoint parsing, passes `+fpga_flow_package_root` and `+vecfile` plusargs), `L2CampaignExecutor` (robustness with `+profile/+vecfile/+seed/+cases` plusargs, writes `counterexample.json` and `fragility_summary.json`), `IntegrationRegressionExecutor` (baseline + back_to_back + mid_reset campaigns, passes `+fpga_flow_package_root` and `+vecfile` plusargs). All inherit `_BaseExecutor` which owns `CheckpointParser` and `RunReportWriter`. Uses `asyncio.run()` to call the async adapter synchronously.
- `adapters/verilator.py` — `VerilatorMCPAdapter` wraps OpenHands MCP (`verilator_compile`, `verilator_simulate`). Builds `MCPStdioServerConfig` for the Node.js verilator-mcp server. Filters input files, auto-generates `-I` include flags, adds `-CFLAGS -std=c++17` for C++ TBs.
- Checkpoint protocol: testbenches emit `CHECKPOINT|<name>|PASS|<detail>` to stdout, parsed from `simulation.log`.

### Runtime Layer — SDK integration and session orchestration

- `runtime/bootstrap.py` — `RuntimeBootstrap.build()` loads SDK modules, detects design name from blueprint YAML, conditionally validates AES skill files (skipped for non-AES designs), builds LLM profile kwargs, synthesizes SpecIR/PlanDAG/IntegrationManifest, configures Verilator MCP. Immutable frozen dataclass.
- `runtime/factory.py` — `SdkAgentFactory` creates agents per role: execution orchestrator (with LLM condenser), finalizer orchestrator, module workers, repair workers, L2 campaign agents. Registers subagent factories for delegation. Filters MCP tools to exclude `verilator_testbenchgenerator` and `verilator_naturallanguage`.
- `runtime/runner.py` — `ConversationRunner` drives SDK conversations. `run_current_batch_until_gate()` polls a gate callback with configurable timeout, pausing the conversation when the gate is satisfied or terminal status is reached. All `pause()` calls use `_safe_pause()` — a daemon-thread wrapper with a 10s timeout that prevents SDK deadlock when the runner thread is stuck in `os.waitpid()`.
- `runtime/session.py` — `ExecutionSession` is the top-level orchestration driver. Plans batches via `DAGBatchPlanner`, runs each batch through a gate-controlled conversation, writes report trees, tracks promotion events, handles integration regression, and produces a finalizer conversation for terminal summary. `_autonomous_batch_timeout_s()` is memory-aware: non-memory designs (from-scratch generation) get 600s; memory-pre-populated designs get 420s (600s for top modules). `_has_memory_populated_drafts()` checks via `MemoryStore.has_module_memory()`.
- `runtime/sdk_shim.py` — Import shim for `openhands-sdk` with compatibility patching for `rich` and `google.protobuf`. Set `OPENHANDS_SDK_SITE_PACKAGES` to load SDK from a non-default location.
- `runtime/context_assembler.py` — Builds structured batch messages and task contract envelopes for conversation prompts.
- `runtime/execution_tools.py` — Registers the `run_executor` custom tool that agents use instead of calling Verilator directly.

### Generation/Workspace Layer — memory pre-population, repair, promotion lifecycle

- `memory.py` — `MemoryStore` is the single source of truth for reference memory retrieval. Maps `module_id` → memory skill keys via `MemoryRegistry`. Provides `has_module_memory(module_id)` (bool check), `select(module_id)` (returns `MemoryArtifact` list), `retrieve(key)` (single skill lookup), `build_prompt_block(module_id)` (prompt-injectable text with full RTL+TB code), and `populate_workspace(module_id, workspace_root)` (writes draft files from memory). When `memory_required=False`, gracefully returns empty results for unregistered modules (enables non-AES designs without memory).
- `generation.py` — `initialize_node_workspace()` creates workspace directory structure with contracts JSON, pre-populates draft RTL and TB via `MemoryStore.populate_workspace()`, and stages support headers (`.hpp`/`.h` from TB source dir). TB support header staging and repair hints (must_add_tokens, first_edit_steps, extra_vector_files) are design-agnostic — driven by `design_context` rather than hardcoded to AES. The repair cycle: `write_repair_request()` → external edit → `verify_repair_edit()` (checks file hash changes and required token addition) → `write_edit_receipt()` → revalidation via `run-node`. `promote_workspace()` copies validated drafts to `promoted/<module_id>/` with snapshots. `evaluate_validation_result()` computes pass/fail from checkpoint rollup.

### Agent/Prompt Layer — role specifications and prompt composition

- `agents/specs.py` — `AgentSpawnSpec` per role: `build_workflow_orchestrator_spec(design_name=...)`, `build_module_worker_spec(node)`, `build_repair_worker_spec(design_name=...)`, `build_l2_campaign_spec(node, ...)`, `build_finalizer_orchestrator_spec()`. Each spec declares role, LLM profile, system prompt, skill keys, allowed states, writable paths, and custom tools. Skill keys are design-aware — derived from `node.design_context['algorithm']` via `_design_name_from_node()`.
- `prompts.py` — Prompt builders that compose contracts + phase mixins + instance payloads + skill reference blocks. Scope contracts and memory directives are derived dynamically from `node.design_context` — non-AES designs get their own scope text and skip AES memory directives. `_scope_from_node()` builds scope from `design_context['scope']`; `_design_name_from_node()` extracts the algorithm for memory directive parameterization.
- `prompt_contracts.py` — Reusable `BaseContract` and `PhaseMixin` constants: `AES_SCOPE_CONTRACT`, `NO_RAW_VERILATOR_CONTRACT`, `FRAMEWORK_OWNS_PROGRESS_CONTRACT`, `REPAIR_PHASE_ROUND_1`/`REPAIR_PHASE_ROUND_2_PLUS` (edit-first protocol), `WORKER_LOCAL_SCOPE`, etc. `build_scope_contract()`, `build_memory_directive()`, and `build_repair_memory_directive()` produce design-parameterized contracts. Composed via `compose_prompt()`.
- `skill_refs.py` — 16 `SkillRef` entries pointing to `.openhands/skills/` markdown files, split into 3 registries: `get_runtime_skill_refs()` (5 agent-injected), `get_memory_skill_refs()` (5, owned by `memory.py`), `get_documentation_skill_refs()` (6, doc-only for synthesis hints). `get_all_skill_refs()` returns the union. **Design-aware skill routing**: `select_worker_skill_keys(active_mode, design_name=...)` and `orchestrator_skill_keys(design_name)` return AES-specific skill keys only for AES designs; non-AES designs get empty tuples so no AES context pollutes the agent prompt. `_is_aes_design()` is the routing predicate. `build_skill_reference_block()` returns empty string when no keys are provided.

### Orchestrator State Machine

- `orchestrator/state_machine.py` — `AESWorkflowOrchestrator` wraps `SpecIR`, `PlanDAG`, `AgentExecutionPolicy`, `IntegrationRegressionManifest`. Provides `next_state_after_success()` transitions, `build_module_work_order()`, `build_l2_campaign_request()`, `describe_state_progression()` for tracing.

### Delegation Layer

- `delegation.py` — `NodeExecutionRequest` (per-node task with executor_kind, workspace paths, manual commands), `DelegateBatchTask` (worker assignment), `DelegateBatchPlan` (batch with max_children enforcement). `SubagentWorkMode` enum: GENERATE, VALIDATE, REPAIR, L2_EXECUTE, INTEGRATION.

## Design Directory Structure

Each design lives under `designs/<name>/` with a standard layout:

```
designs/
  aes128/                        # Reference AES-128 design
    blueprint.yaml               # Design blueprint (SpecIR + PlanDAG source)
    rtl/                         # Verilog source files
    tb/                          # C++ self-checking testbenches
    vectors/                     # KAT, L2 campaign, regression vectors
  led_chaser/                    # Minimal validation design
    blueprint.yaml
    rtl/
    tb/
    vectors/
```

The `blueprint.yaml` file is the single source of truth for a design's module DAG, ports, checkpoints, vectors, and L2 profiles. The `BlueprintLoader` in `blueprint_loader.py` parses it into `SpecIR`, `PlanDAG`, and `IntegrationRegressionManifest`.

For the built-in AES-128 design, the hardcoded `_aes_blueprints()` function in `synthesis.py` provides an equivalent fallback when no blueprint path is given.

## Key Files Outside `fpga_flow/`

- `designs/aes128/rtl/` — Verilog source: `aes_sbox.v`, `aes_key_schedule_128.v`, `aes_round_transform.v`, `aes128_encrypt_core.v`
- `designs/aes128/tb/` — C++ testbenches and `aes_tb_common.hpp` (shared utilities: hex parsing, block packing, checkpoint emission, path resolution via `+fpga_flow_package_root` and `+vecfile` plusargs)
- `designs/aes128/vectors/` — KAT vectors, zero/regress vectors, L2 campaign vectors per profile
- `.openhands/skills/` — 16 skill markdown files referenced by `skill_refs.py` (5 runtime + 5 memory + 6 doc-only)
- `mcp4eda/verilator-mcp/` — TypeScript MCP server for Verilator (build with `npm run build` in that directory)
- `develop.md` — Full architecture and design specification

## Critical Invariants

- All contracts use Pydantic `extra='forbid'` — unknown fields are rejected
- Checkpoint validation uses the `CHECKPOINT|<name>|PASS|<detail>` protocol parsed from `simulation.log`
- The `run_executor` custom tool is the only allowed way for agents to trigger compile/simulate — agents never call raw Verilator MCP tools directly
- Workspace lifecycle: MISSING → DRAFT_READY → VALIDATED → PROMOTED (or REPAIRING → BLOCKED after budget exhaustion)
- Repair edit verification checks file hash changes against baselines and required token presence before allowing revalidation
- Design blueprints (`designs/<name>/blueprint.yaml`) are the single source of truth for a design's node taxonomy, ports, vectors, checkpoints, and L2 profiles; the hardcoded `_aes_blueprints()` in `synthesis.py` is the fallback for the built-in AES-128 design
- `aes_tb_common.hpp` `resolve_path(argc, argv, requested, fallback)` is the required vector path resolution method — the legacy two-argument form must not be used
