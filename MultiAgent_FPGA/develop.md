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

1. define the artifact schemas
2. implement stable tool adapters
3. encode FPGA workflow as skills
4. implement orchestrator state machine
5. add typed engineering memory retrieval and gated write-back
6. add DSPy optimization only after the above are stable

Do not start with:

- a complex agent RPC mesh
- end-to-end autonomous board deployment
- instruction optimization before tool signals are reliable

---

## 13. Future Extension

`L4 ON-BOARD` remains a future extension.

When it is added, it should be attached after `L3` and should never redefine the current mainline. It should consume the same artifacts, tool interfaces, and memory system rather than creating a second independent pipeline.
