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
