---
name: aes-memory-encrypt-core
description: Verified reference RTL and L1 testbench for aes128_encrypt_core (top-level iterative 10-round AES-128 with handshake).
type: knowledge
version: 1.0.0
agent: CodeActAgent
triggers:
  - aes128_encrypt_core memory
  - encrypt core reference
  - top core verified
---

# Purpose

Consult this memory when generating or repairing the `aes128_encrypt_core` module. This is the complete, Verilator-verified implementation that passes all 6 checkpoints.

# Verified RTL: `aes128_encrypt_core.v`

```verilog
module aes128_encrypt_core (
    input clk,
    input rst_n,
    input start,
    input [127:0] key,
    input [127:0] plaintext,
    output reg busy,
    output reg done,
    output reg [127:0] ciphertext
);
    localparam [1:0] STATE_IDLE = 2'd0;
    localparam [1:0] STATE_ROUND = 2'd1;
    localparam [1:0] STATE_DONE = 2'd2;

    reg [1:0] fsm_state;
    reg [127:0] key_reg;
    reg [127:0] plaintext_reg;
    reg [127:0] state_reg;
    reg [3:0] round_index;

    wire [127:0] round_key;
    wire [127:0] sub_bytes_state;
    wire [127:0] shift_rows_state;
    wire [127:0] mix_columns_state;
    wire [127:0] round_state_out;
    wire final_round;

    assign final_round = (round_index == 4'd10);

    aes_key_schedule_128 u_key_schedule (
        .key(key_reg),
        .round_index(round_index),
        .round_key(round_key)
    );

    aes_round_transform u_round_transform (
        .state_in(state_reg),
        .round_key(round_key),
        .final_round(final_round),
        .sub_bytes_state(sub_bytes_state),
        .shift_rows_state(shift_rows_state),
        .mix_columns_state(mix_columns_state),
        .state_out(round_state_out)
    );

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            fsm_state <= STATE_IDLE;
            key_reg <= 128'h0;
            plaintext_reg <= 128'h0;
            state_reg <= 128'h0;
            round_index <= 4'd0;
            busy <= 1'b0;
            done <= 1'b0;
            ciphertext <= 128'h0;
        end else begin
            done <= 1'b0;
            case (fsm_state)
                STATE_IDLE: begin
                    busy <= 1'b0;
                    if (start) begin
                        key_reg <= key;
                        plaintext_reg <= plaintext;
                        state_reg <= plaintext ^ key;
                        round_index <= 4'd1;
                        busy <= 1'b1;
                        fsm_state <= STATE_ROUND;
                    end
                end

                STATE_ROUND: begin
                    busy <= 1'b1;
                    if (round_index >= 4'd1) begin
                        state_reg <= round_state_out;
                        if (round_index == 4'd10) begin
                            ciphertext <= round_state_out;
                            done <= 1'b1;
                            fsm_state <= STATE_DONE;
                            round_index <= 4'd0;
                        end else begin
                            round_index <= round_index + 4'd1;
                        end
                    end else begin
                        state_reg <= plaintext_reg ^ key_reg;
                        round_index <= 4'd1;
                    end
                end

                STATE_DONE: begin
                    busy <= 1'b0;
                    fsm_state <= STATE_IDLE;
                end

                default: begin
                    fsm_state <= STATE_IDLE;
                    busy <= 1'b0;
                end
            endcase
        end
    end
endmodule
```

# Verified Testbench (L1 Core): `aes128_encrypt_core_tb.cpp`

The complete TB includes L2 campaign functions. Below is the L1 core (KAT/functional) portion that covers all 6 checkpoints.

```cpp
#include <verilated.h>

#include <exception>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "Vaes128_encrypt_core.h"
#include "aes_tb_common.hpp"

namespace {

vluint64_t sim_time = 0;

double sc_time_stamp() {
    return static_cast<double>(sim_time);
}

struct VectorCase {
    aes_tb::Block key;
    aes_tb::Block plaintext;
    aes_tb::Block ciphertext;
    std::string label;
};

std::string resolve_requested_path(
    int argc,
    char** argv,
    const std::string& requested,
    const std::string& fallback
) {
    return aes_tb::resolve_path(argc, argv, requested, fallback);
}

std::string resolve_named_vector_file(int argc, char** argv, const std::string& file_name) {
    const std::string requested = "vectors/aes128/" + file_name;
    const std::string fallback = "../../../../" + requested;
    return resolve_requested_path(argc, argv, requested, fallback);
}

std::string lookup_value(
    const std::map<std::string, std::string>& values,
    const std::string& key,
    const std::string& context
) {
    const std::map<std::string, std::string>::const_iterator it = values.find(key);
    if (it == values.end()) {
        std::ostringstream message;
        message << "Missing '" << key << "' in " << context;
        throw std::runtime_error(message.str());
    }
    return it->second;
}

VectorCase load_vector_case(const std::string& path, const std::string& label) {
    const std::map<std::string, std::string> values = aes_tb::read_key_value_file(path);
    VectorCase vec;
    vec.key = aes_tb::parse_hex_block(lookup_value(values, "key", path));
    vec.plaintext = aes_tb::parse_hex_block(lookup_value(values, "plaintext", path));
    vec.ciphertext = aes_tb::parse_hex_block(lookup_value(values, "ciphertext", path));
    vec.label = label;
    return vec;
}

std::vector<VectorCase> load_l1_vectors(int argc, char** argv) {
    const std::string explicit_vecfile =
        aes_tb::get_plusarg_value(argc, argv, "vecfile", "");
    if (!explicit_vecfile.empty()) {
        const std::string resolved = resolve_requested_path(
            argc,
            argv,
            explicit_vecfile,
            "../../../../" + explicit_vecfile
        );
        return std::vector<VectorCase>(1, load_vector_case(resolved, explicit_vecfile));
    }

    std::vector<VectorCase> vectors;
    vectors.push_back(load_vector_case(
        resolve_named_vector_file(argc, argv, "aes128_encrypt_core_kat.txt"),
        "kat"
    ));
    vectors.push_back(load_vector_case(
        resolve_named_vector_file(argc, argv, "aes128_encrypt_core_zero.txt"),
        "zero"
    ));
    vectors.push_back(load_vector_case(
        resolve_named_vector_file(argc, argv, "aes128_encrypt_core_regress.txt"),
        "regress"
    ));
    return vectors;
}

void eval_half_cycle(Vaes128_encrypt_core& dut, int clk_value) {
    dut.clk = clk_value;
    dut.eval();
    ++sim_time;
}

void tick(Vaes128_encrypt_core& dut) {
    eval_half_cycle(dut, 0);
    eval_half_cycle(dut, 1);
}

void reset_dut(Vaes128_encrypt_core& dut) {
    dut.rst_n = 0;
    dut.start = 0;
    aes_tb::Block zero = {};
    aes_tb::write_block_to_wide(zero, dut.key);
    aes_tb::write_block_to_wide(zero, dut.plaintext);
    for (int i = 0; i < 2; ++i) {
        tick(dut);
    }
    dut.rst_n = 1;
    tick(dut);
    if (static_cast<int>(dut.busy) != 0 || static_cast<int>(dut.done) != 0) {
        throw std::runtime_error("Reset failed to clear busy/done");
    }
    aes_tb::emit_checkpoint("CHK_RESET_CLEAR", "reset_release");
}

int run_transaction(
    Vaes128_encrypt_core& dut,
    const VectorCase& vec,
    bool emit_handshake_checkpoints
) {
    aes_tb::write_block_to_wide(vec.key, dut.key);
    aes_tb::write_block_to_wide(vec.plaintext, dut.plaintext);
    dut.start = 1;
    tick(dut);
    dut.start = 0;

    if (emit_handshake_checkpoints) {
        if (static_cast<int>(dut.busy) != 1) {
            throw std::runtime_error("busy did not assert after start");
        }
        aes_tb::emit_checkpoint("CHK_START_ACCEPTED", vec.label);
        aes_tb::emit_checkpoint("CHK_BUSY_ASSERTED", vec.label);
    }

    int latency_cycles = 1;
    while (static_cast<int>(dut.done) == 0) {
        tick(dut);
        ++latency_cycles;
        if (latency_cycles > 16) {
            throw std::runtime_error("AES core exceeded expected latency");
        }
    }

    const aes_tb::Block observed = aes_tb::read_block_from_wide(dut.ciphertext);
    if (observed != vec.ciphertext) {
        std::ostringstream message;
        message << "Ciphertext mismatch for " << vec.label
                << " expected=" << aes_tb::block_to_hex(vec.ciphertext)
                << " observed=" << aes_tb::block_to_hex(observed);
        throw std::runtime_error(message.str());
    }

    if (latency_cycles != 11) {
        std::ostringstream message;
        message << "Expected 11-cycle latency, observed " << latency_cycles;
        throw std::runtime_error(message.str());
    }

    if (emit_handshake_checkpoints) {
        aes_tb::emit_checkpoint("CHK_DONE_PULSE", vec.label);
        aes_tb::emit_checkpoint("CHK_CIPHERTEXT_MATCH", vec.label);
    }

    tick(dut);
    if (static_cast<int>(dut.busy) != 0 || static_cast<int>(dut.done) != 0) {
        throw std::runtime_error("busy/done did not clear after completion");
    }
    if (emit_handshake_checkpoints) {
        aes_tb::emit_checkpoint("CHK_BUSY_DEASSERTED", vec.label);
    }
    return latency_cycles;
}

void verify_ignore_while_busy(Vaes128_encrypt_core& dut, const VectorCase& vec) {
    aes_tb::write_block_to_wide(vec.key, dut.key);
    aes_tb::write_block_to_wide(vec.plaintext, dut.plaintext);
    dut.start = 1;
    tick(dut);
    dut.start = 0;

    aes_tb::Block bogus_key = aes_tb::random_block(sim_time);
    aes_tb::Block bogus_plaintext = aes_tb::random_block(sim_time);
    aes_tb::write_block_to_wide(bogus_key, dut.key);
    aes_tb::write_block_to_wide(bogus_plaintext, dut.plaintext);
    dut.start = 1;
    tick(dut);
    dut.start = 0;

    while (static_cast<int>(dut.done) == 0) {
        tick(dut);
    }

    const aes_tb::Block observed = aes_tb::read_block_from_wide(dut.ciphertext);
    if (observed != vec.ciphertext) {
        throw std::runtime_error("Core accepted a second start while busy");
    }
    tick(dut);
}

}  // namespace

// NOTE: Full TB also includes L2 campaign functions (run_random_profile,
// run_back_to_back_profile, run_mid_reset_profile, run_profile_campaign).
// Those are omitted here for token efficiency. See the full file at:
// MultiAgent_FPGA/aes_mvp/tb/aes128_encrypt_core_tb.cpp

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    try {
        Vaes128_encrypt_core dut;
        reset_dut(dut);

        const std::vector<VectorCase> vectors = load_l1_vectors(argc, argv);
        for (std::size_t index = 0; index < vectors.size(); ++index) {
            run_transaction(dut, vectors[index], index == 0);
        }
        verify_ignore_while_busy(dut, vectors.front());

        aes_tb::write_placeholder_vcd("simulation.vcd", "aes128_encrypt_core");
        return 0;
    } catch (const std::exception& exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }
}
```

# Key Implementation Notes

- **3-state FSM**: `STATE_IDLE` -> `STATE_ROUND` -> `STATE_DONE` -> `STATE_IDLE`
- **AddRoundKey-0 on start**: `state_reg <= plaintext ^ key` in IDLE (not a separate round cycle)
- **Iterative rounds 1-10**: Each clock in STATE_ROUND processes one round via instantiated `aes_round_transform` and `aes_key_schedule_128`
- **11-cycle latency**: 1 cycle for start/latch + 10 cycles for rounds 1-10 = 11 total (measured from tick after `start` to tick where `done=1`)
- **Handshake**: `busy` asserts on start acceptance, clears in STATE_DONE. `done` pulses for exactly one cycle. New `start` during busy is ignored.
- **Asynchronous reset**: Active-low `rst_n` clears all registers to zero
- **6 Checkpoints**: `CHK_RESET_CLEAR`, `CHK_START_ACCEPTED`, `CHK_BUSY_ASSERTED`, `CHK_DONE_PULSE`, `CHK_CIPHERTEXT_MATCH`, `CHK_BUSY_DEASSERTED`
- **L1 vectors**: kat (FIPS-197), zero (all-zero), regress (NIST SP 800-38A)
- Dependencies: `aes_key_schedule_128.v`, `aes_round_transform.v`, `aes_sbox.v`, `aes_sbox_lut.vh`, `aes_tb_common.hpp`
