---
name: aes-memory-key-schedule
description: Verified reference RTL and testbench for aes_key_schedule_128 (combinational AES-128 key expansion).
type: knowledge
version: 1.0.0
agent: CodeActAgent
triggers:
  - aes_key_schedule_128 memory
  - key schedule reference
  - key expansion verified
---

# Purpose

Consult this memory when generating or repairing the `aes_key_schedule_128` module. This is the complete, Verilator-verified implementation that passes all checkpoints.

# Verified RTL: `aes_key_schedule_128.v`

```verilog
// Key schedule SubWord must use the same S-box as the data path (aes_sbox_lut.vh).
`include "aes_sbox_lut.vh"

module aes_key_schedule_128 (
    input [127:0] key,
    input [3:0] round_index,
    output reg [127:0] round_key
);
    function [31:0] rot_word;
        input [31:0] value;
        begin
            rot_word = {value[23:0], value[31:24]};
        end
    endfunction

    function [31:0] sub_word;
        input [31:0] value;
        begin
            sub_word = {
                aes_sbox_lut(value[31:24]),
                aes_sbox_lut(value[23:16]),
                aes_sbox_lut(value[15:8]),
                aes_sbox_lut(value[7:0])
            };
        end
    endfunction

    function [31:0] rcon_word;
        input [3:0] round;
        begin
            case (round)
                4'd1:  rcon_word = 32'h01000000;
                4'd2:  rcon_word = 32'h02000000;
                4'd3:  rcon_word = 32'h04000000;
                4'd4:  rcon_word = 32'h08000000;
                4'd5:  rcon_word = 32'h10000000;
                4'd6:  rcon_word = 32'h20000000;
                4'd7:  rcon_word = 32'h40000000;
                4'd8:  rcon_word = 32'h80000000;
                4'd9:  rcon_word = 32'h1b000000;
                4'd10: rcon_word = 32'h36000000;
                default: rcon_word = 32'h00000000;
            endcase
        end
    endfunction

    function [127:0] expand_round_key;
        input [127:0] key_in;
        input [3:0] round;
        integer i;
        reg [31:0] w0;
        reg [31:0] w1;
        reg [31:0] w2;
        reg [31:0] w3;
        reg [31:0] temp;
        reg [31:0] nw0;
        reg [31:0] nw1;
        reg [31:0] nw2;
        reg [31:0] nw3;
        reg [3:0] round_sel;
        begin
            w0 = key_in[127:96];
            w1 = key_in[95:64];
            w2 = key_in[63:32];
            w3 = key_in[31:0];

            for (i = 1; i <= 10 && i <= round; i = i + 1) begin
                round_sel = i[3:0];
                temp = sub_word(rot_word(w3)) ^ rcon_word(round_sel);
                nw0 = w0 ^ temp;
                nw1 = w1 ^ nw0;
                nw2 = w2 ^ nw1;
                nw3 = w3 ^ nw2;
                w0 = nw0;
                w1 = nw1;
                w2 = nw2;
                w3 = nw3;
            end

            expand_round_key = {w0, w1, w2, w3};
        end
    endfunction

    always @* begin
        round_key = expand_round_key(key, round_index);
    end
endmodule
```

# Verified Testbench: `aes_key_schedule_128_tb.cpp`

```cpp
#include <verilated.h>

#include <exception>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "Vaes_key_schedule_128.h"
#include "aes_tb_common.hpp"

namespace {

std::string resolve_vecfile(int argc, char** argv) {
    return aes_tb::resolve_path(
        argc,
        argv,
        aes_tb::get_plusarg_value(
            argc,
            argv,
            "vecfile",
            "vectors/aes128/aes_key_schedule_128_kat.txt"
        ),
        "../../../../vectors/aes128/aes_key_schedule_128_kat.txt"
    );
}

void check_round_key(
    Vaes_key_schedule_128& dut,
    const aes_tb::Block& key,
    int round_index,
    const aes_tb::Block& expected,
    const std::string& label
) {
    aes_tb::write_block_to_wide(key, dut.key);
    dut.round_index = round_index;
    dut.eval();

    const aes_tb::Block observed = aes_tb::read_block_from_wide(dut.round_key);
    if (observed != expected) {
        std::ostringstream message;
        message << "Round key mismatch for " << label
                << " round=" << round_index
                << " expected=" << aes_tb::block_to_hex(expected)
                << " observed=" << aes_tb::block_to_hex(observed);
        throw std::runtime_error(message.str());
    }
}

int run_known_answer_test(int argc, char** argv) {
    const std::map<std::string, std::string> values =
        aes_tb::read_key_value_file(resolve_vecfile(argc, argv));
    const aes_tb::Block key = aes_tb::parse_hex_block(values.at("key"));
    Vaes_key_schedule_128 dut;

    // Test round 0 (original key)
    check_round_key(
        dut,
        key,
        0,
        aes_tb::parse_hex_block(values.at("round_key_0")),
        "round_key_0"
    );

    for (int round = 1; round <= 10; ++round) {
        std::ostringstream name;
        name << "round_key_" << round;
        check_round_key(
            dut,
            key,
            round,
            aes_tb::parse_hex_block(values.at(name.str())),
            name.str()
        );
    }

    aes_tb::emit_checkpoint("CHK_ROUNDKEY_MATCH", "known_answer_vectors");
    aes_tb::write_placeholder_vcd("simulation.vcd", "aes_key_schedule_128");
    return 0;
}

int run_random_campaign(int argc, char** argv) {
    const uint64_t cases = aes_tb::get_plusarg_uint(argc, argv, "cases", 64);
    uint64_t seed = aes_tb::get_plusarg_uint(argc, argv, "seed", 1001);
    Vaes_key_schedule_128 dut;

    for (uint64_t index = 0; index < cases; ++index) {
        const aes_tb::Block key = aes_tb::random_block(seed);
        const aes_tb::RoundKeys round_keys = aes_tb::expand_round_keys(key);
        // Test round 0 every 11th case, rounds 1-10 otherwise
        const int round = (index % 11 == 0) ? 0 : static_cast<int>((index % 10) + 1);
        check_round_key(
            dut,
            key,
            round,
            round_keys[round],
            "random_campaign"
        );
    }

    aes_tb::emit_checkpoint("CHK_ROUNDKEY_MATCH", "random_campaign");
    aes_tb::write_placeholder_vcd("simulation.vcd", "aes_key_schedule_128");
    return 0;
}

}  // namespace

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    try {
        const std::string profile =
            aes_tb::get_plusarg_value(argc, argv, "profile", "");
        if (profile == "rand_small" || profile == "rand_medium") {
            return run_random_campaign(argc, argv);
        }
        return run_known_answer_test(argc, argv);
    } catch (const std::exception& exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }
}
```

# Key Implementation Notes

- Purely combinational: `expand_round_key` iteratively computes from round 1 to the target `round_index`
- When `round_index=0`, the loop body does not execute; original key is returned
- Uses `aes_sbox_lut.vh` for SubWord -- same S-box as the datapath (critical for consistency)
- RCON values match FIPS-197: `01, 02, 04, 08, 10, 20, 40, 80, 1B, 36`
- Key expansion XOR chain: `temp = sub_word(rot_word(w3)) ^ rcon; nw0=w0^temp; nw1=w1^nw0; nw2=w2^nw1; nw3=w3^nw2`
- TB uses `write_block_to_wide`/`read_block_from_wide` for 128-bit key/round_key bus packing
- Checkpoint: `CHK_ROUNDKEY_MATCH`
- Dependencies: `aes_sbox_lut.vh`, `aes_tb_common.hpp`
