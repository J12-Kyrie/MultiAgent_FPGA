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
        aes_tb::get_plusarg_value(
            argc,
            argv,
            "vecfile",
            "vectors/aes128/aes_round_transform_kat.txt"
        ),
        "../../../../vectors/aes128/aes_round_transform_kat.txt"
    );
}

void check_round_transform(
    Vaes_round_transform& dut,
    const aes_tb::Block& state_in,
    const aes_tb::Block& round_key,
    bool final_round,
    const aes_tb::Block& expected_sub_bytes,
    const aes_tb::Block& expected_shift_rows,
    const aes_tb::Block& expected_mix_columns,
    const aes_tb::Block& expected_state_out,
    const std::string& label
) {
    aes_tb::write_block_to_wide(state_in, dut.state_in);
    aes_tb::write_block_to_wide(round_key, dut.round_key);
    dut.final_round = final_round ? 1 : 0;
    dut.eval();

    const aes_tb::Block observed_sub = aes_tb::read_block_from_wide(dut.sub_bytes_state);
    const aes_tb::Block observed_shift = aes_tb::read_block_from_wide(dut.shift_rows_state);
    const aes_tb::Block observed_mix = aes_tb::read_block_from_wide(dut.mix_columns_state);
    const aes_tb::Block observed_out = aes_tb::read_block_from_wide(dut.state_out);

    if (observed_sub != expected_sub_bytes ||
        observed_shift != expected_shift_rows ||
        observed_mix != expected_mix_columns ||
        observed_out != expected_state_out) {
        std::ostringstream message;
        message << "Round transform mismatch for " << label;
        throw std::runtime_error(message.str());
    }
}

int run_known_answer_test(int argc, char** argv) {
    const std::map<std::string, std::string> values =
        aes_tb::read_key_value_file(resolve_vecfile(argc, argv));
    const aes_tb::Block state_in = aes_tb::parse_hex_block(
        values.at("state_after_add_round_key")
    );
    const aes_tb::Block round_key = aes_tb::parse_hex_block(values.at("round_key_1"));
    Vaes_round_transform dut;

    check_round_transform(
        dut,
        state_in,
        round_key,
        false,
        aes_tb::parse_hex_block(values.at("state_after_sub_bytes")),
        aes_tb::parse_hex_block(values.at("state_after_shift_rows")),
        aes_tb::parse_hex_block(values.at("state_after_mix_columns")),
        aes_tb::parse_hex_block(values.at("state_after_round_1")),
        "known_answer_vectors"
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
        // Test both final_round = false and final_round = true cases
        bool final_round = (index % 2 == 0); // Alternate between false and true

        aes_tb::Block expected_sub;
        aes_tb::Block expected_shift;
        aes_tb::Block expected_mix;
        const aes_tb::Block expected_out = aes_tb::apply_round_transform(
            state_in,
            round_key,
            final_round,
            &expected_sub,
            &expected_shift,
            &expected_mix
        );
        check_round_transform(
            dut,
            state_in,
            round_key,
            final_round,
            expected_sub,
            expected_shift,
            expected_mix,
            expected_out,
            "random_campaign"
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
