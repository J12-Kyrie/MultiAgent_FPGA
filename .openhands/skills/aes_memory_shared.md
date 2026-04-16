---
name: aes-memory-shared
description: Verified reference for shared AES utilities — aes_sbox_lut.vh interface and critical aes_tb_common.hpp functions (byte-order packing, path resolution, checkpoint emission).
type: knowledge
version: 1.0.0
agent: CodeActAgent
triggers:
  - aes_tb_common memory
  - shared utilities reference
  - sbox lut reference
  - block packing reference
  - write_block_to_wide reference
---

# Purpose

Consult this memory for the shared utility interfaces that all AES modules and testbenches depend on.

# `aes_sbox_lut.vh` — S-box Lookup Function

The full file defines a 256-entry case statement. Interface and representative entries:

```verilog
`ifndef AES_SBOX_LUT_VH
`define AES_SBOX_LUT_VH

function automatic [7:0] aes_sbox_lut;
    input [7:0] in_byte;
    begin
        case (in_byte)
            8'h00: aes_sbox_lut = 8'h63;
            8'h01: aes_sbox_lut = 8'h7c;
            8'h02: aes_sbox_lut = 8'h77;
            // ... 250 more entries matching FIPS-197 Table 4 ...
            8'hfd: aes_sbox_lut = 8'h54;
            8'hfe: aes_sbox_lut = 8'hbb;
            8'hff: aes_sbox_lut = 8'h16;
            default: aes_sbox_lut = 8'h00;
        endcase
    end
endfunction

`endif
```

The full 268-line file lives at `MultiAgent_FPGA/aes_mvp/rtl/aes_sbox_lut.vh`. Both `aes_sbox.v` and `aes_key_schedule_128.v` include it via `` `include "aes_sbox_lut.vh" ``.

# `aes_tb_common.hpp` — Critical Functions

## Data Types

```cpp
namespace aes_tb {

using Block = std::array<uint8_t, 16>;
using RoundKeys = std::array<Block, 11>;

struct CampaignCase {
    Block key;
    Block plaintext;
    Block ciphertext;
    std::string label;
};
```

(The `aes_tb` namespace continues for ~600 more lines — do not close it here.)

## Byte-Order Packing (RTL <-> C++ Bridge)

This is the most critical function for RTL/TB alignment. It maps between C++ `Block` (byte array) and Verilator's wide signal (4 x uint32_t).

```cpp
template <typename WideT>
inline void write_block_to_wide(const Block& block, WideT& wide) {
    for (std::size_t word = 0; word < 4; ++word) {
        const std::size_t byte_index = 12 - (word * 4);
        wide[word] = word_from_bytes(
            block[byte_index + 0],
            block[byte_index + 1],
            block[byte_index + 2],
            block[byte_index + 3]
        );
    }
}

template <typename WideT>
inline Block read_block_from_wide(const WideT& wide) {
    Block block{};
    for (std::size_t word = 0; word < 4; ++word) {
        const uint32_t value = wide[word];
        const std::size_t byte_index = 12 - (word * 4);
        block[byte_index + 0] = static_cast<uint8_t>(value >> 24);
        block[byte_index + 1] = static_cast<uint8_t>(value >> 16);
        block[byte_index + 2] = static_cast<uint8_t>(value >> 8);
        block[byte_index + 3] = static_cast<uint8_t>(value);
    }
    return block;
}
```

Mapping result: `Block[0]` -> Verilog `[127:120]` (MSB), `Block[15]` -> Verilog `[7:0]` (LSB).

## Vector Path Resolution

Required 4-argument form that uses `+aes_mvp_package_root` plusarg:

```cpp
inline std::string resolve_path(
    int argc,
    char** argv,
    const std::string& requested,
    const std::string& fallback
) {
    std::vector<std::string> candidates;
    const std::string package_root =
        get_plusarg_value(argc, argv, "aes_mvp_package_root", "");
    if (!package_root.empty() && !requested.empty()) {
        const bool absolute_unix = requested[0] == '/';
        const bool absolute_windows =
            requested.size() > 2
            && std::isalpha(static_cast<unsigned char>(requested[0]))
            && (requested[1] == ':' || requested[1] == '\\');
        if (!absolute_unix && !absolute_windows) {
            const std::string joined = join_under_package_root(package_root, requested);
            if (!joined.empty()) {
                candidates.push_back(joined);
            }
        }
    }
    candidates.push_back(requested);
    candidates.push_back(std::string("../../../../") + requested);
    candidates.push_back(std::string("../../../") + requested);
    candidates.push_back(std::string("../../") + requested);
    candidates.push_back(fallback);

    for (std::size_t i = 0; i < candidates.size(); ++i) {
        if (!candidates[i].empty() && file_exists(candidates[i])) {
            return candidates[i];
        }
    }

    std::ostringstream message;
    message << "Unable to resolve vector file. Requested='" << requested
            << "' fallback='" << fallback << "'";
    throw std::runtime_error(message.str());
}
```

## Checkpoint Emission

```cpp
inline void emit_checkpoint(
    const std::string& checkpoint,
    const std::string& detail
) {
    std::cout << "CHECKPOINT|" << checkpoint << "|PASS|" << detail << std::endl;
}
```

## Gold Reference AES Functions

```cpp
inline Block encrypt_block(const Block& key, const Block& plaintext) {
    const RoundKeys round_keys = expand_round_keys(key);
    Block state = xor_blocks(plaintext, round_keys[0]);
    for (int round = 1; round < 10; ++round) {
        state = xor_blocks(mix_columns(shift_rows(sub_bytes(state))), round_keys[round]);
    }
    state = xor_blocks(shift_rows(sub_bytes(state)), round_keys[10]);
    return state;
}
```

Also available: `sub_bytes()`, `shift_rows()`, `mix_columns()`, `expand_round_keys()`, `apply_round_transform()`, `xor_blocks()`, `random_block()`, `block_to_hex()`, `parse_hex_block()`, `read_key_value_file()`, `read_sbox_kat()`.

## Plusarg Helpers

```cpp
inline std::string get_plusarg_value(int argc, char** argv, const std::string& name, const std::string& fallback);
inline uint64_t get_plusarg_uint(int argc, char** argv, const std::string& name, uint64_t fallback);
inline bool plusarg_enabled(int argc, char** argv, const std::string& flag_name);
```

# Key Notes

- The full `aes_tb_common.hpp` is 629 lines at `MultiAgent_FPGA/aes_mvp/tb/aes_tb_common.hpp`
- All testbenches must `#include "aes_tb_common.hpp"` and thread `argc`/`argv` through to `resolve_path`
- The 2-argument `resolve_path(requested, fallback)` overload is legacy — always use the 4-argument form
- `word_from_bytes(b0,b1,b2,b3)` packs bytes big-endian into a uint32_t: `(b0<<24)|(b1<<16)|(b2<<8)|b3`
