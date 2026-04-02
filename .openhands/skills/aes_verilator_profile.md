---
name: aes-verilator-profile
description: AES-specific overlay skill for the repository's Verilator MCP workflow. Use when working on the AES-128 encrypt-only FPGA MVP with block-level handshake, iterative 10-round microarchitecture, and existing .cpp self-checking testbenches.
type: knowledge
version: 1.0.0
agent: CodeActAgent
triggers:
  - aes
  - aes-128
  - aes encrypt
  - aes core
  - fpga aes
---

# Purpose And Scope

Use this skill only for the repository's AES case study.

This skill narrows the generic runtime rules from [verilog_verilator.md](verilog_verilator.md) to the fixed AES MVP profile. It does not replace [verilator_mcp_setup.md](verilator_mcp_setup.md) and it does not broaden the generic Verilator workflow.

Fixed AES MVP scope:

- `AES-128`
- `encrypt only`
- `block-level handshake`
- `iterative 10-round microarchitecture`

If the task asks for decrypt, AES-192/256, streaming, memory-mapped behavior, or a pipelined core, stop and treat that as outside the MVP.

# Stable Runtime Rules

- Keep using only `verilator_compile` and `verilator_simulate`.
- Keep using `language: "verilog"` for RTL.
- Require an existing `.cpp` self-checking testbench for every executable AES node.
- Do not use `.v` testbenches on the stable AES path, even though the generic skill allows them.
- Do not use `verilator_testbenchgenerator`.
- Do not use `verilator_naturallanguage`.
- Do not rely on `simulation://...` resources.
- Read `simulation.log` and `simulation.vcd` directly from the filesystem.

# Fixed AES Node Taxonomy

Use only these executable nodes in the AES MVP:

- `aes_sbox`
- `aes_key_schedule_128`
- `aes_round_transform`
- `aes128_encrypt_core`

Frozen dependencies:

- `aes_key_schedule_128 -> aes_sbox`
- `aes_round_transform -> aes_sbox`
- `aes128_encrypt_core -> aes_key_schedule_128, aes_round_transform`

Frozen node defaults:

- `aes_sbox`: `criticality=medium`, `l2_policy=skip`
- `aes_key_schedule_128`: `criticality=high`, `l2_policy=conditional`
- `aes_round_transform`: `criticality=high`, `l2_policy=conditional`
- `aes128_encrypt_core`: `criticality=high`, `l2_policy=required`, `integration_role=top`

Do not add a separate top wrapper in the MVP.

# Interface, Vectors, And Checkpoints

Frozen top-level interface:

- `clk`
- `rst_n`
- `start`
- `key[127:0]`
- `plaintext[127:0]`
- `busy`
- `done`
- `ciphertext[127:0]`

Frozen handshake semantics:

- sample `key` and `plaintext` when `start && !busy`
- keep `busy=1` during encryption
- pulse `done` for one cycle when `ciphertext` is valid
- ignore `start` while `busy=1`
- target latency is `11` cycles

Vector naming convention:

- `vectors/aes128/<module>_<suite>.txt`
- required suites:
  - `aes_sbox_kat`
  - `aes_key_schedule_128_kat`
  - `aes_round_transform_kat`
  - `aes128_encrypt_core_kat`
  - `aes128_encrypt_core_zero`
  - `aes128_encrypt_core_regress`
  - `aes128_encrypt_core_l2_<profile>`

Checkpoint line format:

- `CHECKPOINT|<name>|PASS|<detail>`

Frozen checkpoint names:

- `aes_sbox`: `CHK_SBOX_MATCH`
- `aes_key_schedule_128`: `CHK_ROUNDKEY_MATCH`
- `aes_round_transform`: `CHK_ROUND_STATE_MATCH`
- `aes128_encrypt_core`:
  - `CHK_RESET_CLEAR`
  - `CHK_START_ACCEPTED`
  - `CHK_BUSY_ASSERTED`
  - `CHK_DONE_PULSE`
  - `CHK_CIPHERTEXT_MATCH`
  - `CHK_BUSY_DEASSERTED`

# L1, L2, And Integration Conventions

L1 rules:

- use curated known-answer vectors only
- include NIST AES-128 known-answer vectors
- include the all-zero key/plaintext case for the top core
- include one nontrivial regression vector set per node

L2 rules:

- keep using `verilator_simulate`
- vary campaigns only through:
  - `+vecfile=<path>`
  - `+seed=<n>`
  - `+cases=<n>`
  - `+profile=rand_small|rand_medium|back_to_back|mid_reset`
- allow `back_to_back` and `mid_reset` only for `aes128_encrypt_core`
- require outputs:
  - `counterexample.json`
  - `fragility_summary.json`

Integration rules:

- integration top is `aes128_encrypt_core`
- require the full top-level vector corpus
- prove deterministic `11`-cycle latency
- prove ignore-while-busy behavior
- prove back-to-back behavior
- prove reset recovery
