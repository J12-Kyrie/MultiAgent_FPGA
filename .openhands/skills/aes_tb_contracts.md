---
name: aes-tb-contracts
description: Reference skill for AES `.cpp` self-checking testbenches, vector conventions, checkpoints, and 128-bit wide bus packing vs C++ Block.
type: knowledge
version: 1.0.2
agent: CodeActAgent
---

# Purpose

Use this skill when a worker must generate or repair an AES `.cpp` testbench from a testbench contract.

# Stable Testbench Rules

- Use `.cpp` self-checking testbenches on the stable path.
- Do not use generated `.v` or `.sv` testbenches.
- Emit `CHECKPOINT|<name>|PASS|<detail>` lines to `simulation.log`.
- Prefer deterministic vectors and deterministic pass/fail conditions.

# Vector Conventions

Typical vector families:

- `aes_sbox_kat`
- `aes_key_schedule_128_kat`
- `aes_round_transform_kat`
- `aes128_encrypt_core_kat`
- `aes128_encrypt_core_zero`
- `aes128_encrypt_core_regress`
- `aes128_encrypt_core_l2_<profile>`

When a node contract specifies `vecfile`, `cases`, or `seed`, treat those as frozen inputs for that run.

# Vector path resolution (package root / plusargs)

L1 validation may run Verilator with cwd under `workspace/.../validation/sim`. Vector files still live under the package tree (`vectors/aes128/...`). The executor passes `+aes_mvp_package_root=<abs path>` so `aes_tb_common.hpp` can resolve paths.

- **Required:** thread `argc` / `argv` from `main` into helpers that open vector files, and call `aes_tb::resolve_path(argc, argv, requested, fallback)` (four logical inputs: argc, argv, requested relative path, repo-relative fallback).
- **Forbidden:** calling the overload `aes_tb::resolve_path(requested, fallback)` only from `main`, which ignores plusargs and yields `Unable to resolve vector file` under validation cwd.

Canonical reference: `MultiAgent_FPGA/aes_mvp/tb/aes128_encrypt_core_tb.cpp` (`resolve_named_vector_file(argc, argv, ...)`). Python constant `AES_CPP_TB_VECTOR_PATH_CONTRACT` in `executor_contracts.py` restates this for codegen and reviews.

# Checkpoint Intent

Leaf nodes:

- one or a few semantic checkpoints proving the node output matches the expected transform

Top node:

- reset behavior
- start acceptance
- busy assertion
- done pulse
- ciphertext match
- busy deassertion

# Runtime Rule

The testbench should help the executor decide pass/fail quickly. It is not the place to reinterpret architecture decisions.

# 128-bit Wide Bus Packing (`write_block_to_wide` / `read_block_from_wide`)

The C++ harness uses `aes_tb::Block` (`std::array<uint8_t, 16>`) and maps it to Verilator's `WideT` (4 × `uint32_t`) in `aes_tb_common.hpp`:

```
write_block_to_wide:
  wide[0] = word_from_bytes(block[12], block[13], block[14], block[15])  → Verilog [31:0]
  wide[1] = word_from_bytes(block[8],  block[9],  block[10], block[11]) → Verilog [63:32]
  wide[2] = word_from_bytes(block[4],  block[5],  block[6],  block[7])  → Verilog [95:64]
  wide[3] = word_from_bytes(block[0],  block[1],  block[2],  block[3])  → Verilog [127:96]
```

Result: `Block[0]` → Verilog `[127:120]` (MSB), `Block[15]` → Verilog `[7:0]` (LSB).

For RTL byte-indexing rules that must match this mapping, see skill **aes-module-patterns** (section “Critical Byte-Indexing Convention”).

# Checkpoint Emission Contract

The C++ helper `aes_tb::emit_checkpoint(name, detail)` writes to stdout:

```
CHECKPOINT|<name>|PASS|<detail>
```

The executor's `CheckpointParser` splits on `|` and checks that `status == “PASS”`. The testbench must:

1. Only emit `PASS` when the check actually passed
2. Use the exact checkpoint name from `pass_criteria.l1.coverage_checkpoints`
3. Throw `std::runtime_error` on mismatch (which gives exit code 1 and clear diagnostics)
4. Never unconditionally emit `PASS` — this defeats the verification gate
