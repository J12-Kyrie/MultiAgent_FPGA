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

struct ProfileConfig {
    std::string profile;
    uint64_t cases;
    uint64_t seed;
};

std::string resolve_requested_path(
    const std::string& requested,
    const std::string& fallback
) {
    return aes_tb::resolve_path(requested, fallback);
}

std::string resolve_named_vector_file(const std::string& file_name) {
    const std::string requested = "vectors/aes128/" + file_name;
    const std::string fallback = "../../../../" + requested;
    return resolve_requested_path(requested, fallback);
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

bool has_value(
    const std::map<std::string, std::string>& values,
    const std::string& key
) {
    return values.find(key) != values.end();
}

uint64_t parse_uint_or_default(
    const std::map<std::string, std::string>& values,
    const std::string& key,
    uint64_t fallback
) {
    const std::map<std::string, std::string>::const_iterator it = values.find(key);
    if (it == values.end()) {
        return fallback;
    }
    return static_cast<uint64_t>(std::strtoull(it->second.c_str(), 0, 0));
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
            explicit_vecfile,
            "../../../../" + explicit_vecfile
        );
        return std::vector<VectorCase>(1, load_vector_case(resolved, explicit_vecfile));
    }

    std::vector<VectorCase> vectors;
    vectors.push_back(load_vector_case(
        resolve_named_vector_file("aes128_encrypt_core_kat.txt"),
        "kat"
    ));
    vectors.push_back(load_vector_case(
        resolve_named_vector_file("aes128_encrypt_core_zero.txt"),
        "zero"
    ));
    vectors.push_back(load_vector_case(
        resolve_named_vector_file("aes128_encrypt_core_regress.txt"),
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

ProfileConfig load_profile_config(
    int argc,
    char** argv,
    const std::map<std::string, std::string>& values,
    const std::string& requested_profile
) {
    ProfileConfig config;
    config.profile = requested_profile.empty()
        ? lookup_value(values, "profile", "profile descriptor")
        : requested_profile;
    config.cases = parse_uint_or_default(values, "cases", 32);
    config.seed = parse_uint_or_default(values, "seed", 1001);

    config.cases = aes_tb::get_plusarg_uint(argc, argv, "cases", config.cases);
    config.seed = aes_tb::get_plusarg_uint(argc, argv, "seed", config.seed);

    if (config.cases == 0) {
        throw std::runtime_error("cases must be nonzero");
    }
    if (config.seed == 0) {
        throw std::runtime_error("seed must be nonzero");
    }
    return config;
}

void run_random_profile(
    Vaes128_encrypt_core& dut,
    uint64_t cases,
    uint64_t seed,
    const std::string& profile_name
) {
    for (uint64_t index = 0; index < cases; ++index) {
        VectorCase vec;
        vec.key = aes_tb::random_block(seed);
        vec.plaintext = aes_tb::random_block(seed);
        vec.ciphertext = aes_tb::encrypt_block(vec.key, vec.plaintext);
        vec.label = profile_name + "_case_" + std::to_string(index);
        run_transaction(dut, vec, index == 0);
    }
}

void run_explicit_campaign_profile(
    Vaes128_encrypt_core& dut,
    const std::string& vecfile
) {
    const std::vector<aes_tb::CampaignCase> cases =
        aes_tb::read_campaign_case_file(vecfile);
    for (std::size_t index = 0; index < cases.size(); ++index) {
        VectorCase vec;
        vec.key = cases[index].key;
        vec.plaintext = cases[index].plaintext;
        vec.ciphertext = cases[index].ciphertext;
        vec.label = cases[index].label;
        run_transaction(dut, vec, index == 0);
    }
}

void run_back_to_back_profile(
    Vaes128_encrypt_core& dut,
    uint64_t cases,
    uint64_t seed
) {
    for (uint64_t index = 0; index < cases; ++index) {
        VectorCase vec;
        vec.key = aes_tb::random_block(seed);
        vec.plaintext = aes_tb::random_block(seed);
        vec.ciphertext = aes_tb::encrypt_block(vec.key, vec.plaintext);
        vec.label = "back_to_back_case_" + std::to_string(index);
        run_transaction(dut, vec, index == 0);
    }
}

void run_mid_reset_profile(
    Vaes128_encrypt_core& dut,
    uint64_t cases,
    uint64_t seed
) {
    for (uint64_t index = 0; index < cases; ++index) {
        VectorCase vec;
        vec.key = aes_tb::random_block(seed);
        vec.plaintext = aes_tb::random_block(seed);
        vec.ciphertext = aes_tb::encrypt_block(vec.key, vec.plaintext);
        vec.label = "mid_reset_case_" + std::to_string(index);

        if ((index % 2U) == 0U) {
            aes_tb::write_block_to_wide(vec.key, dut.key);
            aes_tb::write_block_to_wide(vec.plaintext, dut.plaintext);
            dut.start = 1;
            tick(dut);
            dut.start = 0;
            tick(dut);

            dut.rst_n = 0;
            tick(dut);
            dut.rst_n = 1;
            tick(dut);
            if (static_cast<int>(dut.busy) != 0 || static_cast<int>(dut.done) != 0) {
                throw std::runtime_error("Reset did not clear busy during mid_reset");
            }
            aes_tb::emit_checkpoint("CHK_RESET_CLEAR", vec.label + ":reset_during_busy");
            run_transaction(dut, vec, index == 0);
        } else {
            run_transaction(dut, vec, index == 0);
            dut.rst_n = 0;
            tick(dut);
            dut.rst_n = 1;
            tick(dut);
            if (static_cast<int>(dut.busy) != 0 || static_cast<int>(dut.done) != 0) {
                throw std::runtime_error("Reset did not clear busy after completion");
            }
            aes_tb::emit_checkpoint("CHK_RESET_CLEAR", vec.label + ":reset_after_done");
        }
    }
}

void run_profile_campaign(
    Vaes128_encrypt_core& dut,
    int argc,
    char** argv,
    const std::string& profile,
    const std::map<std::string, std::string>& values
) {
    const std::string campaign_vecfile =
        aes_tb::get_plusarg_value(argc, argv, "campaignVecfile", "");
    if (!campaign_vecfile.empty()) {
        const std::string resolved_campaign_vecfile = resolve_requested_path(
            campaign_vecfile,
            "../../../../" + campaign_vecfile
        );
        run_explicit_campaign_profile(dut, resolved_campaign_vecfile);
        return;
    }

    const ProfileConfig config = load_profile_config(argc, argv, values, profile);

    if (profile == "rand_small") {
        run_random_profile(dut, config.cases, config.seed, profile);
    } else if (profile == "rand_medium") {
        run_random_profile(dut, config.cases, config.seed, profile);
    } else if (profile == "back_to_back") {
        run_back_to_back_profile(dut, config.cases, config.seed);
    } else if (profile == "mid_reset") {
        run_mid_reset_profile(dut, config.cases, config.seed);
    } else {
        std::ostringstream message;
        message << "Unsupported AES profile: " << profile;
        throw std::runtime_error(message.str());
    }
}

bool is_profile_descriptor(const std::map<std::string, std::string>& values) {
    return has_value(values, "profile");
}

}  // namespace

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    try {
        Vaes128_encrypt_core dut;
        reset_dut(dut);

        const std::string explicit_vecfile =
            aes_tb::get_plusarg_value(argc, argv, "vecfile", "");
        const std::string requested_profile =
            aes_tb::get_plusarg_value(argc, argv, "profile", "");

        if (!explicit_vecfile.empty()) {
            const std::string resolved_vecfile = resolve_requested_path(
                explicit_vecfile,
                "../../../../" + explicit_vecfile
            );
            const std::map<std::string, std::string> values =
                aes_tb::read_key_value_file(resolved_vecfile);

            if (is_profile_descriptor(values) || !requested_profile.empty()) {
                const std::string profile = requested_profile.empty()
                    ? lookup_value(values, "profile", resolved_vecfile)
                    : requested_profile;
                if (has_value(values, "profile") && requested_profile.empty() == false) {
                    const std::string file_profile = lookup_value(
                        values,
                        "profile",
                        resolved_vecfile
                    );
                    if (file_profile != requested_profile) {
                        std::ostringstream message;
                        message << "Requested profile " << requested_profile
                                << " does not match vecfile profile " << file_profile;
                        throw std::runtime_error(message.str());
                    }
                }
                run_profile_campaign(dut, argc, argv, profile, values);
            } else {
                const VectorCase vec = load_vector_case(resolved_vecfile, explicit_vecfile);
                run_transaction(dut, vec, true);
                verify_ignore_while_busy(dut, vec);
            }
        } else if (!requested_profile.empty()) {
            const std::string resolved_vecfile = resolve_named_vector_file(
                "aes128_encrypt_core_l2_" + requested_profile + ".txt"
            );
            const std::map<std::string, std::string> values =
                aes_tb::read_key_value_file(resolved_vecfile);
            run_profile_campaign(dut, argc, argv, requested_profile, values);
        } else {
            const std::vector<VectorCase> vectors = load_l1_vectors(argc, argv);
            for (std::size_t index = 0; index < vectors.size(); ++index) {
                run_transaction(dut, vectors[index], index == 0);
            }
            verify_ignore_while_busy(dut, vectors.front());
        }

        aes_tb::write_placeholder_vcd("simulation.vcd", "aes128_encrypt_core");
        return 0;
    } catch (const std::exception& exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }
}
