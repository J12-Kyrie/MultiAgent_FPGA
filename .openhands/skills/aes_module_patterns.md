---
name: aes-module-patterns
description: Reference skill for AES module roles, interfaces, alignment with aes_tb_common.hpp, and design patterns for node-local RTL.
type: knowledge
version: 1.0.1
agent: CodeActAgent
---

# Purpose

Use this skill when a module worker must generate or repair a node-local AES implementation from a contract.

These are patterns and expectations. For exact implementations, consult the per-module memory skills listed in Verified Implementations below.

# Module Roles

`aes_sbox`

- pure combinational byte substitution
- no sequential state
- ideal for exhaustive byte-level checking

`aes_key_schedule_128`

- derives round keys for rounds `0..10`
- deterministic combinational or lightweight helper logic
- must remain compatible with the S-box transform semantics

`aes_round_transform`

- composes `SubBytes`, `ShiftRows`, `MixColumns`, and `AddRoundKey`
- final-round path must bypass `MixColumns`
- intermediate observability can be useful for checkpoints

`aes128_encrypt_core`

- owns `clk/rst_n/start/key/plaintext/busy/done/ciphertext`
- samples inputs on `start && !busy`
- ignores new `start` while busy
- targets `11` cycles latency for the MVP

# Design Heuristics

- Prefer simple, explicit state/control over clever compact code.
- Preserve frozen port names from the contract.
- Avoid cross-module rewrites inside a node-local task.
- When repairing, fix the smallest contract violation first:
  - compile failure
  - missing checkpoint
  - wrong latency
  - handshake mismatch

# Alignment With C++ Reference (`aes_tb_common.hpp`)

Treat `MultiAgent_FPGA/aes_mvp/tb/aes_tb_common.hpp` as the behavioral contract for the datapath and key schedule when the TB uses `write_block_to_wide` / `read_block_from_wide`.

For byte-order packing, port layout, and 128-bit block indexing rules, see the **aes-tb-contracts** skill (the single source of truth for RTL/TB interface alignment).

- **S-box consistency**: Key-schedule SubWord must use the **same** substitution table semantics as the datapath (for example a shared include header such as `aes_sbox_lut.vh`), not an independent mathematical S-box derivation, or round keys and data-path SubBytes will disagree.

# Verified Implementations (Cross-References)

Complete, Verilator-verified RTL and testbench code lives in the per-module memory skills. Consult them instead of writing code from scratch:

- **`aes-memory-sbox`** — S-box combinational lookup RTL + exhaustive/KAT testbench
- **`aes-memory-key-schedule`** — RCON values, RotWord/SubWord/XOR chain, key expansion RTL + KAT testbench
- **`aes-memory-round-transform`** — SubBytes (16× parallel S-box), ShiftRows permutation, MixColumns GF(2⁸), final-round bypass RTL + KAT testbench
- **`aes-memory-encrypt-core`** — 3-state FSM (IDLE/ROUND/DONE), 11-cycle iterative datapath, handshake RTL + L1 testbench
- **`aes-memory-shared`** — `aes_sbox_lut.vh` interface, `write_block_to_wide`/`read_block_from_wide` byte-order packing, `resolve_path` vector resolution, `emit_checkpoint` protocol

If a memory skill and this patterns skill disagree, the memory skill is authoritative (it contains the exact code that passes Verilator).
