---
name: aes-spec-decomposition
description: Reference skill for decomposing an AES-128 encrypt-only block-handshake objective into SpecIR fields, node taxonomy, dependency graph, and integration sink selection.
type: knowledge
version: 1.0.0
agent: CodeActAgent
triggers:
  - aes decomposition
  - specir
  - plan dag
  - autonomous generate
---

# Purpose

Use this skill when an agent must synthesize `SpecIR` or `PlanDAG` for the AES-128 encrypt-only MVP.

Treat the repository RTL, testbench, and vectors as examples only. Do not assume they are the correct implementation for the current run.

# Stable AES MVP Scope

- `AES-128`
- `encrypt only`
- `block_handshake`
- `iterative_10_round`

Do not silently broaden the scope to decrypt, AES-192/256, streaming, or memory-mapped control.

# Decomposition Pattern

For the frozen node taxonomy (4 modules), dependency graph, criticality, and L2 policies, see skill **aes-verilator-profile** section "Fixed AES Node Taxonomy". That is the single source of truth for the AES MVP node structure.

# Integration Sink Selection

Choose the sink node by dependency closure, not by a hardcoded name.

For the AES MVP, the sink is the node that:

- consumes the round transform and key schedule outputs
- owns the block-level handshake
- owns the ciphertext output

That node is typically the top integration target.

# Verification Guardrails

- Keep RTL in Verilog, not SystemVerilog.
- Keep `.cpp` self-checking testbenches.
- Preserve stable checkpoint semantics.
- Use compile and simulation results from executors as the only truth source.
