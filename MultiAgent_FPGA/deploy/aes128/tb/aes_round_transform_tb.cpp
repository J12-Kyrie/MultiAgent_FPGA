#include <verilated.h>

#include <exception>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "Vaes_round_transform.h"
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
            "vectors/aes128/aes_round_transform_kat.txt"
        ),
        "../../../../vectors/aes128/aes_round_transform_kat.txt"
    );
}

void check_block(
    const std::string& label,
    const aes_tb::Block& expected,
    const aes_tb::Block& observed
) {
    if (observed != expected) {
        std::ostringstream message;
        message << label
                << " expected=" << aes_tb::block_to_hex(expected)
                << " observed=" << aes_tb::block_to_hex(observed);
        throw std::runtime_error(message.str());
    }
}

int run_known_answer_test(int argc, char** argv) {
    const std::map<std::string, std::string> values =
        aes_tb::read_key_value_file(resolve_vecfile(argc, argv));
    Vaes_round_transform dut;

    // Load the state after initial AddRoundKey (input to round 1)
    const aes_tb::Block state_in =
        aes_tb::parse_hex_block(values.at("state_after_add_round_key"));
    const aes_tb::Block round_key_1 =
        aes_tb::parse_hex_block(values.at("round_key_1"));

    // Expected intermediate and final states from the vector file
    const aes_tb::Block expected_sub_bytes =
        aes_tb::parse_hex_block(values.at("state_after_sub_bytes"));
    const aes_tb::Block expected_shift_rows =
        aes_tb::parse_hex_block(values.at("state_after_shift_rows"));
    const aes_tb::Block expected_mix_columns =
        aes_tb::parse_hex_block(values.at("state_after_mix_columns"));
    const aes_tb::Block expected_round_1 =
        aes_tb::parse_hex_block(values.at("state_after_round_1"));

    // --- Test normal round (final_round=0) ---
    aes_tb::write_block_to_wide(state_in, dut.state_in);
    aes_tb::write_block_to_wide(round_key_1, dut.round_key);
    dut.final_round = 0;
    dut.eval();

    // Check intermediate outputs
    check_block(
        "SubBytes mismatch",
        expected_sub_bytes,
        aes_tb::read_block_from_wide(dut.sub_bytes_state)
    );
    check_block(
        "ShiftRows mismatch",
        expected_shift_rows,
        aes_tb::read_block_from_wide(dut.shift_rows_state)
    );
    check_block(
        "MixColumns mismatch",
        expected_mix_columns,
        aes_tb::read_block_from_wide(dut.mix_columns_state)
    );
    check_block(
        "Round 1 output mismatch",
        expected_round_1,
        aes_tb::read_block_from_wide(dut.state_out)
    );

    // --- Test final round (final_round=1): MixColumns bypassed ---
    dut.final_round = 1;
    dut.eval();

    // In final round, state_out = ShiftRows(SubBytes(state_in)) XOR round_key
    const aes_tb::Block expected_final_out =
        aes_tb::xor_blocks(expected_shift_rows, round_key_1);
    check_block(
        "Final-round output mismatch",
        expected_final_out,
        aes_tb::read_block_from_wide(dut.state_out)
    );

    // In final round, mix_columns_state should equal shift_rows_state (bypass)
    check_block(
        "Final-round mix_columns_state should equal shift_rows_state",
        expected_shift_rows,
        aes_tb::read_block_from_wide(dut.mix_columns_state)
    );

    aes_tb::emit_checkpoint("CHK_ROUND_STATE_MATCH", "known_answer_vectors");
    aes_tb::write_placeholder_vcd("simulation.vcd", "aes_round_transform");
    return 0;
}

int run_random_campaign(int argc, char** argv) {
    const uint64_t cases = aes_tb::get_plusarg_uint(argc, argv, "cases", 64);
    uint64_t seed = aes_tb::get_plusarg_uint(argc, argv, "seed", 1001);
    Vaes_round_transform dut;

    for (uint64_t index = 0; index < cases; ++index) {
        const aes_tb::Block state_in = aes_tb::random_block(seed);
        const aes_tb::Block round_key = aes_tb::random_block(seed);
        const bool final_round = (index % 3 == 0);

        // Compute expected output using gold C++ reference
        aes_tb::Block expected_sub, expected_shift, expected_mix;
        const aes_tb::Block expected_out = aes_tb::apply_round_transform(
            state_in, round_key, final_round,
            &expected_sub, &expected_shift, &expected_mix
        );

        // Drive DUT
        aes_tb::write_block_to_wide(state_in, dut.state_in);
        aes_tb::write_block_to_wide(round_key, dut.round_key);
        dut.final_round = final_round ? 1 : 0;
        dut.eval();

        // Check all outputs
        check_block(
            "Random SubBytes mismatch",
            expected_sub,
            aes_tb::read_block_from_wide(dut.sub_bytes_state)
        );
        check_block(
            "Random ShiftRows mismatch",
            expected_shift,
            aes_tb::read_block_from_wide(dut.shift_rows_state)
        );
        check_block(
            "Random MixColumns mismatch",
            expected_mix,
            aes_tb::read_block_from_wide(dut.mix_columns_state)
        );
        check_block(
            "Random round output mismatch",
            expected_out,
            aes_tb::read_block_from_wide(dut.state_out)
        );
    }

    aes_tb::emit_checkpoint("CHK_ROUND_STATE_MATCH", "random_campaign");
    aes_tb::write_placeholder_vcd("simulation.vcd", "aes_round_transform");
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
