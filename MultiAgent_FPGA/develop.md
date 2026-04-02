# MultiAgent for FPGA Development Guide

## 1. Goal

This document defines a new implementation path for `MultiAgent for FPGA` that is more compatible with OpenHands.

The system should not be built as a loose network of chatty agents first. It should be built as an OpenHands-native engineering workflow centered on:

- one workflow orchestrator
- role-specific Skills
- stable tool adapters and MCP tools
- typed engineering memory
- measurable EDA feedback as the only source of truth

Current scope:

- focus on `Spec -> RTL -> verification -> physical closure`
- do not include on-board execution in the mainline
- keep L4 as a future extension, not a current dependency
- the current executable MVP is the Verilator-MCP inner loop:
  `Spec -> PlanDAG -> per-module RTL -> L0 -> L1 -> conditional L2 -> integration functional regression`

---

## 2. Core Principles

### 2.1 Toolchain is the judge

The system does not optimize for natural-language quality. It optimizes for FPGA closure signals:

- syntax and synthesizable-subset correctness
- lint quality
- unit simulation pass and assertion pass
- adversarial robustness
- synthesis and implementation timing/resource closure
- constraint consistency

### 2.2 Roles are implemented as capabilities, not only personas

In OpenHands terms, most "agents" in the pipeline should first be implemented as:

- Skills
- tools
- routing policies
- memory retrieval rules

Only use separate sub-agents when parallel exploration is truly necessary.

### 2.3 Separate fast correctness closure from slow physical closure

The main system must explicitly distinguish:

- inner loop: syntax, function, robustness
- outer loop: timing, resource, congestion, constraints

Any physical edit must be forced back through correctness regression.

### 2.4 Knowledge must be typed

Do not store FPGA experience as raw chat history only.

Store reusable engineering knowledge as typed cards:

- `ConstraintCard`
- `ToolFailureCard`
- `TimingCaseCard`
- `PatchPairCard`
- `CounterexampleCard`

---

## 3. New Mainline

The canonical mainline is:

1. `Spec -> Architect -> Planner -> PlanDAG`
2. each module runs `Designer -> L0 -> L1`
3. enter `L2` only when close to convergence or when a critical module changes
4. after module-level convergence, run unified integration and `L3`
5. if `L3` fails, classify the failure as `constraint issue` or `structural issue`, then route to different fix paths
6. all `L3` edits must regress through `L0-L2`

This replaces the earlier notion of a flat pipeline.

For the current implementation phase, freeze the executable sub-mainline to:

1. `Spec -> PlanDAG`
2. `per-module RTL -> L0 -> L1`
3. `conditional L2`
4. `integration functional regression`

`L3` remains part of the long-term architecture, but it is not part of the first runnable Verilator-MCP MVP.

---

## 4. OpenHands-Native Implementation Shape

### 4.1 Architecture

The preferred implementation shape is:

- `Workflow Orchestrator`
- `FPGA Skills`
- `EDA Tool Adapters`
- `Engineering Memory Store`

The system should look like:

```text
User Spec
-> Orchestrator
-> Architect Skill
-> Planner Skill
-> PlanDAG
-> Module Execution Loop
-> Integration Loop
-> Physical Closure Loop
```

### 4.2 OpenHands mapping

Map the FPGA system to OpenHands like this:

- Orchestrator:
  - owns the state machine
  - decides what stage runs next
  - decides which skill/tool/memory retrieval to invoke
- Skills:
  - hold role-specific reasoning policy and domain workflow
  - replace most static multi-agent prompting
- Tools or MCP:
  - execute lint, sim, synth, impl, log parsing, retrieval, artifact validation
- Memory:
  - built-in OpenHands memory for conversation/workspace context
  - external typed FPGA memory for reusable engineering cases

### 4.3 Why this is better than agent-to-agent RPC first

This shape is better because:

- it fits OpenHands V1 skill loading and agent context composition
- it reduces coordination overhead
- it keeps the workflow deterministic and auditable
- it makes DSPy optimization easier because each capability has cleaner I/O
- it avoids over-investing in transport complexity before the engineering loop is stable

---

## 5. Stage Design

## 5.1 Stage A: Spec -> Architect -> Planner -> PlanDAG

### Purpose

Convert natural language requirements into a stable, machine-checkable plan.

### Inputs

- user spec
- board and device constraints
- timing targets
- reset and clock assumptions
- forbidden interface changes

### Outputs

- `SpecIR.json`
- `PlanDAG.json`
- acceptance criteria
- module boundaries
- verification intent
- physical redlines

### Skills

- `fpga_architect`
- `fpga_planner`
- `spec_normalizer`

### Tool support

- `validate_spec_ir`
- `validate_plan_dag`
- `resolve_platform_profile`
- `search_fpga_memory`

### Notes

The planner must emit explicit module units. The rest of the system should not operate on one giant monolithic RTL target by default.

---

## 5.2 Stage B: Per-module Designer -> L0 -> L1

Each module in `PlanDAG` runs through the same local closure lane.

### Designer

Produces:

- synthesizable RTL
- module-level assumptions
- interface notes

### L0

Purpose:

- syntax check
- lint check
- synthesizable subset check

Hard gate:

- syntax must pass
- lint errors must be zero
- forbidden constructs must be zero

### L1

Purpose:

- unit simulation
- assertions
- basic coverage

Hard gate:

- sim must pass
- assertions must pass
- minimum coverage target must be satisfied

### Skills

- `rtl_designer`
- `vivado_lint_fix`
- `tb_assertions`
- `func_debugger`

### Tool support

- `run_l0_lint`
- `run_l1_sim`
- `extract_lint_features`
- `extract_sim_features`
- `apply_patch_to_rtl`

### Routing rules

- if `L0` fails, route to lint-oriented patch flow
- if `L1` fails, route to functional patch flow
- do not run `L2` yet by default

---

## 5.3 Stage C: Conditional L2

`L2` is not the default cost path for every module iteration.

Run `L2` only when:

- a module is close to convergence
- a module is critical to top-level correctness
- a module changed handshake, reset, CDC, buffering, or boundary behavior
- the orchestrator detects repeated L1 passes with fragile behavior

### Purpose

- adversarial simulation
- random and corner stress
- minimal counterexample extraction
- differential testing when a reference model exists

### Skills

- `counterexample_hunter`
- `random_stimulus_designer`
- `delta_debug_minimizer`

### Tool support

- `run_l2_adv_sim`
- `minimize_counterexample`
- `compare_against_reference_model`

### Gate

- no unstable failure under the configured adversarial budget
- critical robustness assertions remain green

### Write-back policy

L2 is the first stage where `CounterexampleCard` and high-value `PatchPairCard` entries become worth storing.

---

## 5.4 Stage D: Integration and L3

After module-level closure, the orchestrator performs integration and runs physical closure.

### Integration

Integration should create a top-level workset:

- integrated RTL
- top-level TB and sanity checks
- merged constraints
- module dependency manifest

### L3

Purpose:

- synthesis
- implementation
- timing and utilization closure
- constraint consistency checks

### Skills

- `integration_judge`
- `xdc_constraint_author`
- `timing_closure`
- `phys_analyst`

### Tool support

- `run_l3_synth_impl`
- `extract_phys_features`
- `classify_l3_failure`
- `estimate_regression_scope`

### Hard gate

- timing target satisfied, or explicitly accepted temporary target reached
- resources under budget
- no critical constraint inconsistency

---

## 5.5 L3 failure routing

When `L3` fails, the orchestrator must classify the failure before patching.

### Path 1: Constraint issue

Typical signals:

- missing or wrong clock definitions
- false-path or multicycle issue
- IO or pin conflict
- clock domain declaration mismatch
- board-specific constraint mismatch

Route to:

- `xdc_constraint_author`
- `constraint_debugger`

Expected edits:

- XDC updates
- timing exception updates
- top-level constraint alignment

### Path 2: Structural issue

Typical signals:

- deep combinational path
- high fanout
- poor pipelining
- architectural bottleneck
- excessive sharing or control complexity

Route to:

- `timing_closure`
- `rtl_designer`
- `phys_analyst`

Expected edits:

- pipeline insertion
- register duplication
- resource rebalance
- local architectural refactor

### Mandatory rule

Every `L3` edit, regardless of type, must re-enter:

- `L0`
- `L1`
- conditional `L2` depending on impact

No direct `L3 -> final` shortcut is allowed.

---

## 6. Orchestrator State Machine

The orchestrator should be implemented as an explicit state machine, not an implicit chain of prompt calls.

Suggested states:

- `SPEC_INTAKE`
- `ARCHITECTING`
- `PLANNING`
- `MODULE_DESIGN`
- `MODULE_L0`
- `MODULE_L1`
- `MODULE_L2_OPTIONAL`
- `INTEGRATION_READY`
- `L3_RUN`
- `L3_CONSTRAINT_FIX`
- `L3_STRUCTURAL_FIX`
- `REGRESSION`
- `DONE`
- `FAILED`

Suggested transition rules:

- `SPEC_INTAKE -> ARCHITECTING` once minimum user inputs exist
- `ARCHITECTING -> PLANNING` once `SpecIR` is valid
- `PLANNING -> MODULE_DESIGN` once `PlanDAG` is valid
- `MODULE_L1 -> MODULE_L2_OPTIONAL` only if trigger conditions are met
- `MODULE_* -> INTEGRATION_READY` only when all required modules are green
- `L3_RUN -> L3_CONSTRAINT_FIX` if classifier says constraint issue
- `L3_RUN -> L3_STRUCTURAL_FIX` if classifier says structural issue
- `L3_* -> REGRESSION` after patch application
- `REGRESSION -> L3_RUN` if physical closure still pending
- `REGRESSION -> DONE` only if all hard gates are satisfied

---

## 7. Skill Design

## 7.1 Skill strategy

Most domain behavior should be encoded as skills, not embedded inside one giant system prompt.

Recommended skill set:

- `fpga_architect`
- `fpga_planner`
- `rtl_designer`
- `tb_assertions`
- `func_debugger`
- `counterexample_hunter`
- `vivado_lint_fix`
- `xdc_constraint_author`
- `timing_closure`
- `phys_analyst`
- `integration_judge`

## 7.2 Skill types

Use three layers:

- public reusable skills
- repository-private skills
- run-specific conversation instructions

### Public reusable skills

Use for generic FPGA workflows:

- synthesizable Verilog rules
- reset and clock discipline
- CDC patterns
- AXI-stream and FIFO patterns
- timing closure tactics

### Repository-private skills

Use for project-specific rules:

- board profile
- Vivado version assumptions
- preferred top module naming
- local directory conventions
- custom Tcl flow
- forbidden resource or interface changes

These should live in:

- `.openhands/skills/`

or for backward compatibility:

- `.openhands/microagents/`

### Run-specific conversation instructions

Use for transient constraints:

- current target Fmax
- current failing path group
- modules currently frozen
- this run's accepted redlines

Do not store long-term engineering memory here.

---

## 8. Memory Design

## 8.1 Use OpenHands memory for what it is good at

OpenHands built-in memory is good for:

- workspace context
- repository instructions
- runtime context
- triggered skill or microagent knowledge

It should continue to provide:

- repo instructions
- runtime info
- conversation instructions
- skill-triggered knowledge

## 8.2 Add a separate FPGA Engineering Memory

Do not overload the built-in conversation memory with long-term FPGA closure cases.

Create a dedicated engineering memory layer with typed entries:

- `ConstraintCard`
- `ToolFailureCard`
- `TimingCaseCard`
- `PatchPairCard`
- `CounterexampleCard`

This memory should be retrieved through tools, not blindly appended to every prompt.

## 8.3 Suggested card schemas

### ConstraintCard

- board
- device
- clock domains
- reset scheme
- io constraints
- forbidden combinations
- xdc snippets
- rationale

### ToolFailureCard

- tool
- symptom signature
- root cause
- fix actions
- validation steps
- risk

### TimingCaseCard

- wns
- tns
- utilization
- critical path features
- applied fix recipe
- before and after metrics
- patch diff
- do-not-change list

### PatchPairCard

- error fingerprint
- patch summary
- why it works
- regression scope
- rollback rule

### CounterexampleCard

- failure class
- failing seed or vector
- minimal reproducer
- affected module
- fix summary

## 8.4 Retrieval rules

Retrieval should be role-aware.

- Architect:
  - board constraints
  - interface rules
  - prior top-level patterns
- Designer:
  - module patterns
  - prior patch pairs
  - common lint failure fixes
- Verifier:
  - adversarial patterns
  - prior counterexamples
  - assertion templates
- Phys Analyst:
  - timing cases
  - constraint cards
  - prior implementation failures

## 8.5 Write-back rules

Only write back when gated success is achieved.

Minimum write-back rule:

- L1 must pass for functional cards
- L2 should pass before storing robustness-related patches
- L3 improvement must be visible before storing timing cases

Do not write raw noisy trial traces as memory cards.

---

## 9. Tool and MCP Layer

All engineering actions should be reachable through stable tools.

Recommended tool surface:

- `validate_spec_ir`
- `validate_plan_dag`
- `run_l0_lint`
- `run_l1_sim`
- `run_l2_adv_sim`
- `run_l3_synth_impl`
- `extract_lint_features`
- `extract_sim_features`
- `extract_phys_features`
- `classify_l3_failure`
- `search_fpga_memory`
- `record_memory_card`
- `apply_patch_to_rtl`
- `merge_constraints`
- `estimate_regression_scope`

If the flow expands, wrap remote EDA infrastructure through MCP or service adapters, but keep the orchestrator-facing API stable.

---

## 10. Artifact Model

The orchestrator should operate on explicit artifacts.

Required artifacts:

- `SpecIR.json`
- `PlanDAG.json`
- `rtl/<module>.sv`
- `tb/<module>_tb.sv`
- `assert/<module>.svh`
- `constraints/top.xdc`
- `reports/l0/*.json`
- `reports/l1/*.json`
- `reports/l2/*.json`
- `reports/l3/*.json`
- `trace/run.jsonl`

Recommended structured records:

- `MetricResult`
- `PhysFeatures`
- `RegressionScope`
- `FailureClassification`

---

## 11. Recommended Repository Layout

For an OpenHands-aligned implementation, a future FPGA workflow package can be organized as:

```text
MultiAgent_FPGA/
  develop.md
  docs/
  skills/
    fpga_architect.md
    fpga_planner.md
    rtl_designer.md
    tb_assertions.md
    timing_closure.md
  memory/
    schemas.py
    retriever.py
    writer.py
  tools/
    lint.py
    sim.py
    adv_sim.py
    synth_impl.py
    parse_reports.py
    classify.py
  orchestrator/
    state_machine.py
    routing.py
    policies.py
  models/
    spec_ir.py
    plan_dag.py
    metric_result.py
    phys_features.py
```

---

## 12. Current Development Priorities

Priority order should be:

1. land the Verilator-MCP MVP inner loop and freeze its interfaces
2. define the artifact schemas
3. implement stable tool adapters
4. encode FPGA workflow as skills
5. implement orchestrator state machine
6. add typed engineering memory retrieval and gated write-back
7. add DSPy optimization only after the above are stable

Do not start with:

- a complex agent RPC mesh
- end-to-end autonomous board deployment
- instruction optimization before tool signals are reliable

---

## 13. Current Verilator-MCP MVP Implementation Profile

The long-term architecture in this document still includes `L3` physical closure. However, the first executable implementation should now be treated as an AES-specific inner-loop profile built on OpenHands SDK, `verilator-mcp`, and the repository's existing Verilator skills.

This section is the implementation contract for the AES MVP.

### 13.1 Scope and boundaries

Freeze the executable case study to:

- `AES-128`
- `encrypt only`
- `block-level handshake`
- `iterative 10-round microarchitecture`

Freeze the executable mainline to:

1. `Spec -> PlanDAG`
2. `per-module RTL -> L0 -> L1`
3. `conditional L2`
4. `integration functional regression`

Explicitly out of scope for this MVP:

- `L3` synth and implementation closure
- AES decryption
- AES-192 and AES-256
- streaming and memory-mapped interfaces
- cipher modes such as ECB wrapper expansion, CBC, CTR, or GCM
- on-board execution
- agent-to-agent RPC meshes

Execution shape:

- one `Workflow Orchestrator`
- OpenHands SDK stdio MCP connection to `verilator-mcp`
- runtime use of `verilator_compile` and `verilator_simulate` only
- `verilator_mcp_setup` for setup and smoke tests only
- `verilog_verilator` as the generic runtime policy skill
- `aes_verilator_profile` as the AES overlay policy

Stable testbench standard for this AES MVP:

- existing `.cpp` self-checking testbench is the only stable path
- `.v` testbenches remain allowed by the generic skill but are not part of the stable AES MVP path
- `.sv` testbenches are not part of the MVP path

### 13.2 OpenHands SDK and skill contract

The MVP must follow the SDK and skill boundaries already established in this repository.

OpenHands SDK contract:

- use stdio `mcp_config["mcpServers"]["verilator"]`
- do not expose runtime behavior through ad hoc shell-only integrations
- keep the orchestrator-facing API stable even if MCP internals evolve
- use pinned Chatfire `LLMConfig` objects for the orchestrator and allowed sub-agents rather than ad hoc per-call model strings

Runtime skill contract:

- follow `.openhands/skills/verilator_mcp_setup.md` only for connection and smoke test steps
- follow `.openhands/skills/verilog_verilator.md` for all generic runtime execution rules
- follow `.openhands/skills/aes_verilator_profile.md` for AES-specific narrowing
- follow `.openhands/skills/chatfire_deepseek_sdk.md` for the stable Chatfire model, base URL, and thinking contract

Runtime restrictions inherited from `verilog_verilator` and narrowed by the AES overlay:

- require explicit `topModule`, `files`, and `outputDir`
- always use `language: "verilog"` for `.v` workflows
- require existing `.cpp` self-checking testbenches for all executable AES nodes
- do not use `verilator_testbenchgenerator`
- do not use `verilator_naturallanguage`
- do not rely on `simulation://...` MCP resources
- inspect `simulation.log` and `simulation.vcd` directly from the filesystem

Pinned Chatfire runtime rules:

- always use `model="deepseek-v3.2"` as the request model
- always record the resolved backend model, currently `deepseek-v3-2-251201`
- always use `base_url="https://api.chatfire.ai/v1"`
- always source the key from `CHATFIRE_API_KEY` or equivalent secret injection
- never assume the resolved backend model is also directly routable as a request model
- never use `https://api.chatfire.cn/token` as the runtime inference path
- never switch thinking through `reasoning_effort`
- parse normal answers from `choices[0].message.content`
- when thinking is enabled, allow `choices[0].message.reasoning_content` and `usage.completion_tokens_details.reasoning_tokens` as optional analysis artifacts

Document-level `LLMConfig` profiles:

```python
import os

from pydantic import SecretStr

from openhands.core.config.llm_config import LLMConfig

chatfire_deepseek_thinking = LLMConfig(
    model="deepseek-v3.2",
    api_key=SecretStr(os.environ["CHATFIRE_API_KEY"]),
    base_url="https://api.chatfire.ai/v1",
    completion_kwargs={
        "thinking": {"type": "enabled"},
    },
)
```

```python
import os

from pydantic import SecretStr

from openhands.core.config.llm_config import LLMConfig

chatfire_deepseek_fast = LLMConfig(
    model="deepseek-v3.2",
    api_key=SecretStr(os.environ["CHATFIRE_API_KEY"]),
    base_url="https://api.chatfire.ai/v1",
)
```

### 13.3 Agent and SubAgent execution contract

The AES MVP uses one main orchestrator plus bounded helper agents. It does not allow free-form agent meshes.

Allowed runtime roles:

- `Workflow Orchestrator`
  - always uses `chatfire_deepseek_thinking`
  - owns `SpecIR`, `PlanDAG`, stage routing, repair routing, `L2` interpretation, and final acceptance
- `Module Worker SubAgent`
  - uses `chatfire_deepseek_fast`
  - allowed only in `MODULE_DESIGN`, bounded `L0/L1` repair loops, and node-local `.cpp` testbench work
- `L2 Campaign SubAgent`
  - uses `chatfire_deepseek_fast`
  - allowed only for multiple independent `+vecfile/+seed/+cases/+profile` campaigns

Execution rules:

- do not allow sub-agents in `SPEC_INTAKE`, `ARCHITECTING`, or `PLANNING`
- do not allow free-form agent-to-agent negotiation
- all sub-agent inputs and outputs must pass through the `Workflow Orchestrator` as explicit artifacts
- sub-agent write ownership must be derived from `rtl_files`, `tb_file`, `build_output_dir`, and `sim_output_dir`
- the orchestrator remains the only authority for cross-module edits, state transitions, and acceptance decisions

Stage-to-model routing policy:

- thinking-enabled on the main orchestrator:
  - `SPEC_INTAKE`
  - `ARCHITECTING`
  - `PLANNING`
  - repeated-failure diagnosis after module repair loops stall
  - `L2` result interpretation, counterexample analysis, and fragility triage
  - integration regression failure analysis and top-level acceptance review
- non-thinking by default:
  - first-pass per-module RTL implementation
  - `.cpp` testbench implementation and checkpoint wiring
  - `L0` compile-fix loops
  - straightforward `L1` simulation-fix loops
  - batch `L2` campaign execution

Escalation rule:

- if a module worker fails to close after `2` repair attempts, or the failure is clearly interface, state-machine, or cross-module in nature, control must return to the thinking orchestrator for analysis before another patch round begins

### 13.4 Subplan A: Spec intake and `SpecIR`

Goal:

- convert natural-language requirements into an AES-shaped execution contract

Required orchestrator states:

- `SPEC_INTAKE`
- `ARCHITECTING`

Execution profile:

- main `Workflow Orchestrator` only
- always use `chatfire_deepseek_thinking`
- do not spawn sub-agents in this stage

Required `SpecIR` fields:

- `system_goal`
- `algorithm="AES"`
- `variant="AES-128"`
- `operation="encrypt"`
- `interface_style="block_handshake"`
- `microarchitecture="iterative_10_round"`
- `block_width=128`
- `key_width=128`
- `clock_reset_assumptions`
- `timing_targets`
- `latency_target_cycles=11`
- `accept_condition="start && !busy"`
- `output_valid_condition="done pulse"`
- `frozen_interfaces=["clk","rst_n","start","key[127:0]","plaintext[127:0]","busy","done","ciphertext[127:0]"]`
- `module_candidates`
- `verification_redlines`

Frozen interface semantics:

- sample `key` and `plaintext` when `start && !busy`
- assert `busy` during encryption
- pulse `done` for one cycle when `ciphertext` is valid
- ignore `start` while `busy=1`

Rules:

- do not call Verilator MCP in this stage
- retrieve repo skill knowledge before module planning
- reject specs that ask for decrypt, multi-key-length, streaming, or memory-mapped behavior in the MVP
- reject incomplete specs that leave clock, reset, latency, or frozen interface semantics undefined

Exit gate:

- `SpecIR` is structurally valid
- the AES product contract is fully frozen for downstream planning

### 13.5 Subplan B: Planner and `PlanDAG`

Goal:

- translate `SpecIR` into a fixed AES execution DAG rather than a loose task list

Required orchestrator state:

- `PLANNING`

Execution profile:

- main `Workflow Orchestrator` only
- always use `chatfire_deepseek_thinking`
- do not delegate planning to sub-agents

Each `PlanDAGNode` must carry:

- `module_id`
- `depends_on`
- `top_module`
- `rtl_files`
- `tb_file`
- `language`
- `build_output_dir`
- `sim_output_dir`
- `l2_policy`
- `criticality`
- `integration_role`
- `pass_criteria`

Freeze the AES node taxonomy to:

- `aes_sbox`
- `aes_key_schedule_128`
- `aes_round_transform`
- `aes128_encrypt_core`

Freeze dependencies to:

- `aes_key_schedule_128 -> aes_sbox`
- `aes_round_transform -> aes_sbox`
- `aes128_encrypt_core -> aes_key_schedule_128, aes_round_transform`

Freeze node roles and defaults:

- `aes_sbox`: `criticality=medium`, `l2_policy=skip`
- `aes_key_schedule_128`: `criticality=high`, `l2_policy=conditional`
- `aes_round_transform`: `criticality=high`, `l2_policy=conditional`
- `aes128_encrypt_core`: `criticality=high`, `l2_policy=required`, `integration_role=top`

Fixed field defaults:

- `language="verilog"`
- `pass_criteria.l1.sim_pass_required=true`
- `pass_criteria.l1.assertion_pass_required=true`
- `pass_criteria.l1.coverage_checkpoints=[]`
- `pass_criteria.l1.vector_set`
- `pass_criteria.l1.latency_expectation`
- `pass_criteria.l1.checkpoint_contract`

Planner rules:

- every executable node must have an existing `.cpp` self-checking testbench
- nodes without an existing `.cpp` testbench must be marked `blocked_by_missing_tb`
- do not call `verilator_testbenchgenerator`
- do not allow runtime inference of `top_module`, `tb_file`, `build_output_dir`, or `sim_output_dir`
- set the integration top to `aes128_encrypt_core`
- do not add a separate top wrapper in the MVP

### 13.6 Subplan C: Per-module RTL delivery

Goal:

- ensure each AES node reaches the minimum runnable unit required by the Verilator lane

Required orchestrator state:

- `MODULE_DESIGN`

Execution profile:

- the orchestrator stays responsible for node selection and artifact ownership
- `Module Worker SubAgent` is allowed for bounded node-local RTL and `.cpp` testbench work
- default model profile for implementation is `chatfire_deepseek_fast`
- return control to the orchestrator when the work becomes cross-module or architectural

Per-node deliverables:

- synthesizable RTL `.v`
- existing `.cpp` self-checking testbench
- `module_contract`

`module_contract` must include:

- `ports`
- `clock_reset_semantics`
- `input_sampling_rule`
- `output_valid_rule`
- `latency_expectation`
- `testbench_vector_source`
- `checkpoint_contract`

Frozen checkpoint expectations by node:

- `aes_sbox`: lookup output matches the expected S-box substitution table
- `aes_key_schedule_128`: round keys match the AES-128 known-answer schedule
- `aes_round_transform`: round state matches expected intermediate vectors
- `aes128_encrypt_core`: block-level handshake and ciphertext behavior match the frozen interface contract

Design rules:

- `tb_assertions` owns the testbench-level assertion and checkpoint convention
- testbenches must emit machine-parsable checkpoint lines in the format `CHECKPOINT|<name>|PASS|<detail>`
- independent DAG branches may be parallelized, but the default remains one orchestrator and deterministic routing

### 13.7 Subplan D: L0 adapter layer

Goal:

- use Verilator as the fast syntax and elaboration gate for the frozen AES nodes

Required orchestrator state:

- `MODULE_L0`

Execution profile:

- use `chatfire_deepseek_fast` for deterministic compile-fix work
- keep the loop bounded to node-local RTL and testbench fixes
- escalate back to the thinking orchestrator if the `2`-attempt repair threshold is hit

Tool mapping:

- `run_l0_lint` is a thin wrapper around `verilator_compile`

Fixed call contract:

- `files=[rtl_files..., tb_file]`
- `topModule=<PlanDAGNode.top_module>`
- `outputDir=<PlanDAGNode.build_output_dir>`
- `language="verilog"`

L0 gate:

- `verilator_compile.success=true`
- compile `errors=[]`
- forbidden-construct policy check passes

Implementation note:

- do not treat Verilator as the only forbidden-construct checker
- add a repo-side static policy checker and combine its result with compile status

### 13.8 Subplan E: L1 module simulation loop

Goal:

- close module-level AES correctness before robustness work

Required orchestrator state:

- `MODULE_L1`

Execution profile:

- use `chatfire_deepseek_fast` by default for straightforward simulation-fix loops
- allow `Module Worker SubAgent` for bounded node-local repair
- return to the thinking orchestrator when the `2`-attempt threshold is hit or when the issue is interface, state-machine, or cross-module in nature

Tool mapping:

- `run_l1_sim` wraps `verilator_simulate`

Fixed call contract:

- `design=<build_output_dir>`
- `topModule=<top_module>`
- `outputDir=<sim_output_dir>`
- `useExistingBuild=true`
- `autoGenerateTestbench=false`
- `enableWaveform=true`

Allowed artifacts:

- `simulation.log`
- `simulation.vcd`

L1 vector policy:

- use curated known-answer vectors only
- include NIST AES-128 known-answer vectors
- include the all-zero key/plaintext case
- include one nontrivial regression vector set for each node

Frozen top-core checkpoint names:

- `CHK_RESET_CLEAR`
- `CHK_START_ACCEPTED`
- `CHK_BUSY_ASSERTED`
- `CHK_DONE_PULSE`
- `CHK_CIPHERTEXT_MATCH`
- `CHK_BUSY_DEASSERTED`

Frozen submodule checkpoint names:

- `aes_sbox`: `CHK_SBOX_MATCH`
- `aes_key_schedule_128`: `CHK_ROUNDKEY_MATCH`
- `aes_round_transform`: `CHK_ROUND_STATE_MATCH`

L1 gate:

- `simulation.passed=true`
- all assertions pass
- all required checkpoints are observed

MVP definition of `coverage_checkpoints`:

- not an EDA coverage database
- a required set of checkpoint markers emitted by the testbench and validated from `simulation.log`

Repair rule:

- `func_debugger` may patch RTL or the existing `.cpp` testbench
- any L1 repair must rerun `L0 -> L1`

### 13.9 Subplan F: Conditional L2

Goal:

- add bounded robustness pressure only where it materially improves confidence

Required orchestrator state:

- `MODULE_L2_OPTIONAL`

Execution profile:

- `L2 Campaign SubAgent` may run multiple independent campaigns with `chatfire_deepseek_fast`
- the main orchestrator must use `chatfire_deepseek_thinking` for result interpretation, counterexample analysis, and fragility triage
- do not allow free-form sub-agent coordination inside `L2`

Enter L2 only if at least one of the following is true:

- `PlanDAGNode.l2_policy=required`
- repeated L1 passes still look fragile
- a high-criticality node changed handshake or state sequencing behavior

Tool mapping:

- `run_l2_adv_sim` remains a wrapper around `verilator_simulate`

Allowed variability mechanisms:

- `+vecfile=<path>`
- `+seed=<n>`
- `+cases=<n>`
- `+profile=rand_small|rand_medium|back_to_back|mid_reset`

L2 profile rules:

- `back_to_back` and `mid_reset` are supported only for `aes128_encrypt_core`
- `aes_sbox` remains `l2_policy=skip`

Required L2 outputs:

- `counterexample.json`
- `fragility_summary.json`

L2 gate:

- no unstable failure under the configured budget
- critical assertions remain green

Memory rule:

- `CounterexampleCard` and high-value `PatchPairCard` may be written back only from L2 onward

Parallelism rule:

- use sub-agents only for multiple independent L2 campaigns
- do not allow free-form multi-agent negotiation

### 13.10 Subplan G: Integration functional regression

Goal:

- prove top-level AES functional integration without entering physical closure

Required orchestrator states:

- `INTEGRATION_READY`
- `INTEGRATION_REGRESSION`

Execution profile:

- compile and simulate steps remain non-thinking execution work
- use `chatfire_deepseek_fast` for bounded top-level build and run actions
- keep integration triage, failure analysis, and final signoff on the thinking orchestrator

Before running integration, generate `IntegrationRegressionManifest`.

Manifest fields:

- `top_module`
- `rtl_files`
- `tb_file`
- `build_output_dir`
- `sim_output_dir`
- `required_modules`
- `interface_freeze_hash`
- `regression_checkpoints`
- `vector_set`
- `latency_target_cycles`
- `back_to_back_required`
- `mid_reset_scenarios`
- `checkpoint_contract`

Tool mapping:

- run `verilator_compile`
- then run `verilator_simulate(useExistingBuild=true)`

Integration runtime rules:

- require an existing `.cpp` integration testbench
- do not introduce a separate top wrapper
- read only `simulation.log` and `simulation.vcd` for artifact inspection

Exit gate:

- top-level regression passes on the full vector corpus
- top-level latency is deterministically 11 cycles
- `start` is ignored while `busy=1`
- back-to-back transaction behavior is correct
- reset recovery behavior is correct
- all required modules are green
- all `regression_checkpoints` are satisfied

This stage ends at functional integration. It does not enter synth, impl, or XDC work.

### 13.11 MVP interfaces and artifacts

The generic artifact model in Section 10 remains the long-term target. The current AES MVP narrows it to the following required artifacts and interface contracts.

Core interfaces:

- `AgentLLMProfiles`
- `SpecIR`
- `PlanDAGNode`
- `ModuleRunResult`
- `IntegrationRegressionManifest`

`AgentLLMProfiles` must include:

- `chatfire_deepseek_thinking`
- `chatfire_deepseek_fast`

`AgentExecutionPolicy` must define:

- which orchestrator states use the thinking profile
- which orchestrator states use the non-thinking profile
- whether sub-agents are forbidden, allowed, or preferred in each state
- the `2`-attempt escalation threshold for handing control back to the orchestrator

Minimum `ModuleRunResult` fields:

- `compile_result`
- `sim_result`
- `log_path`
- `waveform_path`
- `checkpoint_summary`

Current MVP artifact set:

- `SpecIR.json`
- `PlanDAG.json`
- `rtl/aes_sbox.v`
- `rtl/aes_key_schedule_128.v`
- `rtl/aes_round_transform.v`
- `rtl/aes128_encrypt_core.v`
- `tb/aes_sbox_tb.cpp`
- `tb/aes_key_schedule_128_tb.cpp`
- `tb/aes_round_transform_tb.cpp`
- `tb/aes128_encrypt_core_tb.cpp`
- `vectors/aes128/aes_sbox_kat.txt`
- `vectors/aes128/aes_key_schedule_128_kat.txt`
- `vectors/aes128/aes_round_transform_kat.txt`
- `vectors/aes128/aes128_encrypt_core_kat.txt`
- `vectors/aes128/aes128_encrypt_core_zero.txt`
- `vectors/aes128/aes128_encrypt_core_regress.txt`
- `vectors/aes128/aes128_encrypt_core_l2_<profile>.txt`
- `reports/l0/*.json`
- `reports/l1/*.json`
- `reports/l2/*.json`
- `reports/integration/*.json`
- `trace/run.jsonl`

Compatibility note:

- generic `.v` testbench support still exists at the repository skill level
- `.v` and `.sv` testbenches are not part of the stable AES MVP contract

### 13.12 MVP acceptance tests

Setup smoke tests:

- `verilator_mcp_setup` can discover the MCP tools
- `verilator_compile` and `verilator_simulate` are callable

Documentation review tests:

- Section 13 references `verilator_mcp_setup`, `verilog_verilator`, `aes_verilator_profile`, and `chatfire_deepseek_sdk`
- both pinned `LLMConfig` examples are present
- no alias fallback is described as part of the stable Chatfire path
- `reasoning_effort` is explicitly forbidden for this model
- thinking mode is expressed only through `completion_kwargs={"thinking": {"type": "enabled"}}`
- every orchestrator state in the MVP has an explicit thinking or non-thinking owner
- sub-agent policy allows module work and `L2` campaigns but not `SPEC_INTAKE`, `ARCHITECTING`, or `PLANNING`
- the `2`-attempt escalation rule is explicit

`SpecIR` tests:

- reject any spec missing AES variant, interface style, or latency target
- reject any spec that asks for decrypt, multi-key-length, streaming, or memory-mapped behavior in the MVP

Planner tests:

- only `aes_sbox`, `aes_key_schedule_128`, `aes_round_transform`, and `aes128_encrypt_core` are emitted
- dependencies and `l2_policy` values match the frozen AES taxonomy
- missing `.cpp` testbench marks a node `blocked_by_missing_tb`

L0 tests:

- each AES node compiles with explicit `topModule`, `files`, and `outputDir`
- compile errors or forbidden constructs fail the gate

L1 tests:

- `aes_sbox` passes lookup vectors
- `aes_key_schedule_128` passes round-key vectors
- `aes_round_transform` passes intermediate-state vectors
- `aes128_encrypt_core` passes NIST vectors, the all-zero case, and busy/done handshake checks
- missing checkpoint lines fail the gate

L2 tests:

- random vector profiles produce stable pass results under fixed seeds
- a forced mismatch generates `counterexample.json`
- `mid_reset` and `back_to_back` are supported only for `aes128_encrypt_core`

Integration tests:

- the full top-level vector corpus passes on `aes128_encrypt_core`
- top-level latency is always 11 cycles
- only `simulation.log` and `simulation.vcd` are used as inspection artifacts
- no `simulation://...` resource dependency exists

State-machine tests:

- `SPEC_INTAKE -> PLANNING -> MODULE_DESIGN -> MODULE_L0 -> MODULE_L1 -> MODULE_L2_OPTIONAL -> INTEGRATION_REGRESSION -> DONE`
- failed nodes do not skip intermediate gates
- failed node-local repair loops escalate back to the thinking orchestrator rather than silently continuing

---

## 14. Future Extension

`L4 ON-BOARD` remains a future extension.

When it is added, it should be attached after `L3` and should never redefine the current mainline. It should consume the same artifacts, tool interfaces, and memory system rather than creating a second independent pipeline.
