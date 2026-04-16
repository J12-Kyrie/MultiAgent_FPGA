---
name: aes-repair-heuristics
description: Reference skill for AES node-local repair from compile logs, checkpoints, latency, handshake errors, and KAT or ciphertext mismatches.
type: knowledge
version: 1.0.1
agent: CodeActAgent
---

# Purpose

Use this skill after a generate or validate step fails and the worker must decide what to repair next.

# Repair Order

1. Compile or elaboration errors
2. Missing checkpoints
3. Failed checkpoints
4. Latency mismatch
5. Busy/done protocol mismatch

# Common Repair Patterns

Compile failures:

- fix port declarations and widths first
- remove SystemVerilog-only syntax
- keep module and file names aligned

Missing checkpoints:

- inspect whether the testbench reached the intended state
- add the checkpoint at the narrowest correct observation point

Failed checkpoints:

- compare expected contract intent against current data path
- avoid broad rewrites when a local transform is wrong

## Ciphertext Or KAT Mismatch (`CHK_CIPHERTEXT_MATCH` / similar)

When the simulator reports wrong ciphertext against a known-answer test, work **in this order**:

1. **128-bit port byte order** — most common cause. See skill **aes-tb-contracts** for the authoritative `write_block_to_wide` mapping and RIGHT/WRONG indexing rule.
2. **ShiftRows source indices** — see skill **aes-module-patterns** for the frozen permutation table.
3. **MixColumns** — see skill **aes-module-patterns** for `xtime`/`mul3` formulas and column byte grouping.
4. **AddRoundKey** — XOR must align byte-for-byte with `xor_blocks` after MixColumns / final-round ShiftRows.
5. **Key schedule** — ensure SubWord uses the **same** S-box as the datapath (skill **aes-module-patterns**).

A stable wrong 128-bit value almost always traces to 1–5 above. Only after ruling these out should you suspect handshake timing (which affects *when* ciphertext is sampled, not *what* it is).

Compile failures mentioning **missing `.vh`** or **`Cannot find file containing module`**: treat as include-path hygiene (see skill **verilog-verilator**), not as AES math bugs.

Latency failures:

- prefer explicit cycle counters or clear control-state sequencing
- do not “fix” latency by weakening the checker

Handshake failures:

- check reset defaults
- check `start && !busy` acceptance
- check `busy` hold window
- check single-cycle `done`

# Escalation Rule

Escalate back to the orchestrator when the issue is clearly:

- cross-module
- interface-wide
- state-machine-wide
- outside the local repair budget
