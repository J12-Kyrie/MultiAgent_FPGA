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
