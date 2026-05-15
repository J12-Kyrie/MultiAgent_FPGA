#pragma once

#include <array>
#include <cctype>
#include <cstdlib>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace aes_tb {

using Block = std::array<uint8_t, 16>;
using RoundKeys = std::array<Block, 11>;

struct CampaignCase {
    Block key;
    Block plaintext;
    Block ciphertext;
    std::string label;
};

inline std::string trim(const std::string& value) {
    std::size_t start = 0;
    while (start < value.size() && std::isspace(static_cast<unsigned char>(value[start]))) {
        ++start;
    }

    std::size_t end = value.size();
    while (end > start && std::isspace(static_cast<unsigned char>(value[end - 1]))) {
        --end;
    }

    return value.substr(start, end - start);
}

inline bool file_exists(const std::string& path) {
    std::ifstream file(path.c_str());
    return file.good();
}

inline std::string resolve_path(const std::string& requested, const std::string& fallback) {
    const std::vector<std::string> candidates = {
        requested,
        std::string("../../../../") + requested,
        std::string("../../../") + requested,
        std::string("../../") + requested,
        fallback,
    };

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

inline std::map<std::string, std::string> read_key_value_file(const std::string& path) {
    std::ifstream input(path.c_str());
    if (!input.is_open()) {
        throw std::runtime_error("Unable to open vector file: " + path);
    }

    std::map<std::string, std::string> values;
    std::string line;
    while (std::getline(input, line)) {
        const std::string stripped = trim(line);
        if (stripped.empty() || stripped[0] == '#') {
            continue;
        }

        const std::size_t equals = stripped.find('=');
        if (equals == std::string::npos) {
            continue;
        }

        const std::string key = trim(stripped.substr(0, equals));
        const std::string value = trim(stripped.substr(equals + 1));
        values[key] = value;
    }

    return values;
}

inline std::vector<std::pair<uint8_t, uint8_t> > read_sbox_kat(
    const std::string& path
) {
    std::ifstream input(path.c_str());
    if (!input.is_open()) {
        throw std::runtime_error("Unable to open vector file: " + path);
    }

    std::vector<std::pair<uint8_t, uint8_t> > entries;
    std::string line;
    while (std::getline(input, line)) {
        const std::string stripped = trim(line);
        if (stripped.empty() || stripped[0] == '#') {
            continue;
        }

        const std::size_t comma = stripped.find(',');
        if (comma == std::string::npos) {
            continue;
        }

        const std::string lhs = trim(stripped.substr(0, comma));
        const std::string rhs = trim(stripped.substr(comma + 1));
        const uint8_t in = static_cast<uint8_t>(std::stoul(lhs, 0, 16));
        const uint8_t out = static_cast<uint8_t>(std::stoul(rhs, 0, 16));
        entries.push_back(std::make_pair(in, out));
    }

    return entries;
}

inline std::vector<std::string> split_string(
    const std::string& value,
    char delimiter
) {
    std::vector<std::string> parts;
    std::string current;
    for (std::size_t index = 0; index < value.size(); ++index) {
        if (value[index] == delimiter) {
            parts.push_back(trim(current));
            current.clear();
        } else {
            current.push_back(value[index]);
        }
    }
    parts.push_back(trim(current));
    return parts;
}

inline Block parse_hex_block(const std::string& value);

inline std::vector<CampaignCase> read_campaign_case_file(
    const std::string& path
) {
    std::ifstream input(path.c_str());
    if (!input.is_open()) {
        throw std::runtime_error("Unable to open campaign vector file: " + path);
    }

    std::vector<CampaignCase> cases;
    std::string line;
    while (std::getline(input, line)) {
        const std::string stripped = trim(line);
        if (stripped.empty() || stripped[0] == '#') {
            continue;
        }

        std::map<std::string, std::string> fields;
        const std::vector<std::string> parts = split_string(stripped, '|');
        for (std::size_t index = 0; index < parts.size(); ++index) {
            const std::size_t equals = parts[index].find('=');
            if (equals == std::string::npos) {
                continue;
            }
            const std::string key = trim(parts[index].substr(0, equals));
            const std::string value = trim(parts[index].substr(equals + 1));
            fields[key] = value;
        }

        if (fields.find("key") == fields.end() ||
            fields.find("plaintext") == fields.end() ||
            fields.find("ciphertext") == fields.end()) {
            throw std::runtime_error(
                "Campaign vector file must include key/plaintext/ciphertext: " + path
            );
        }

        CampaignCase vec;
        vec.key = parse_hex_block(fields["key"]);
        vec.plaintext = parse_hex_block(fields["plaintext"]);
        vec.ciphertext = parse_hex_block(fields["ciphertext"]);
        vec.label = fields.find("label") == fields.end() ? path : fields["label"];
        cases.push_back(vec);
    }

    return cases;
}

inline int hex_value(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'a' && c <= 'f') {
        return 10 + (c - 'a');
    }
    if (c >= 'A' && c <= 'F') {
        return 10 + (c - 'A');
    }
    throw std::runtime_error(std::string("Invalid hex digit: ") + c);
}

inline uint8_t parse_hex_byte(const std::string& value, std::size_t offset) {
    return static_cast<uint8_t>((hex_value(value[offset]) << 4) | hex_value(value[offset + 1]));
}

inline Block parse_hex_block(const std::string& value) {
    if (value.size() != 32) {
        throw std::runtime_error("Expected 32 hex characters, got: " + value);
    }

    Block block{};
    for (std::size_t i = 0; i < 16; ++i) {
        block[i] = parse_hex_byte(value, i * 2);
    }
    return block;
}

static const uint8_t AES_SBOX_TABLE[256] = {
    0x63U, 0x7cU, 0x77U, 0x7bU, 0xf2U, 0x6bU, 0x6fU, 0xc5U,
    0x30U, 0x01U, 0x67U, 0x2bU, 0xfeU, 0xd7U, 0xabU, 0x76U,
    0xcaU, 0x82U, 0xc9U, 0x7dU, 0xfaU, 0x59U, 0x47U, 0xf0U,
    0xadU, 0xd4U, 0xa2U, 0xafU, 0x9cU, 0xa4U, 0x72U, 0xc0U,
    0xb7U, 0xfdU, 0x93U, 0x26U, 0x36U, 0x3fU, 0xf7U, 0xccU,
    0x34U, 0xa5U, 0xe5U, 0xf1U, 0x71U, 0xd8U, 0x31U, 0x15U,
    0x04U, 0xc7U, 0x23U, 0xc3U, 0x18U, 0x96U, 0x05U, 0x9aU,
    0x07U, 0x12U, 0x80U, 0xe2U, 0xebU, 0x27U, 0xb2U, 0x75U,
    0x09U, 0x83U, 0x2cU, 0x1aU, 0x1bU, 0x6eU, 0x5aU, 0xa0U,
    0x52U, 0x3bU, 0xd6U, 0xb3U, 0x29U, 0xe3U, 0x2fU, 0x84U,
    0x53U, 0xd1U, 0x00U, 0xedU, 0x20U, 0xfcU, 0xb1U, 0x5bU,
    0x6aU, 0xcbU, 0xbeU, 0x39U, 0x4aU, 0x4cU, 0x58U, 0xcfU,
    0xd0U, 0xefU, 0xaaU, 0xfbU, 0x43U, 0x4dU, 0x33U, 0x85U,
    0x45U, 0xf9U, 0x02U, 0x7fU, 0x50U, 0x3cU, 0x9fU, 0xa8U,
    0x51U, 0xa3U, 0x40U, 0x8fU, 0x92U, 0x9dU, 0x38U, 0xf5U,
    0xbcU, 0xb6U, 0xdaU, 0x21U, 0x10U, 0xffU, 0xf3U, 0xd2U,
    0xcdU, 0x0cU, 0x13U, 0xecU, 0x5fU, 0x97U, 0x44U, 0x17U,
    0xc4U, 0xa7U, 0x7eU, 0x3dU, 0x64U, 0x5dU, 0x19U, 0x73U,
    0x60U, 0x81U, 0x4fU, 0xdcU, 0x22U, 0x2aU, 0x90U, 0x88U,
    0x46U, 0xeeU, 0xb8U, 0x14U, 0xdeU, 0x5eU, 0x0bU, 0xdbU,
    0xe0U, 0x32U, 0x3aU, 0x0aU, 0x49U, 0x06U, 0x24U, 0x5cU,
    0xc2U, 0xd3U, 0xacU, 0x62U, 0x91U, 0x95U, 0xe4U, 0x79U,
    0xe7U, 0xc8U, 0x37U, 0x6dU, 0x8dU, 0xd5U, 0x4eU, 0xa9U,
    0x6cU, 0x56U, 0xf4U, 0xeaU, 0x65U, 0x7aU, 0xaeU, 0x08U,
    0xbaU, 0x78U, 0x25U, 0x2eU, 0x1cU, 0xa6U, 0xb4U, 0xc6U,
    0xe8U, 0xddU, 0x74U, 0x1fU, 0x4bU, 0xbdU, 0x8bU, 0x8aU,
    0x70U, 0x3eU, 0xb5U, 0x66U, 0x48U, 0x03U, 0xf6U, 0x0eU,
    0x61U, 0x35U, 0x57U, 0xb9U, 0x86U, 0xc1U, 0x1dU, 0x9eU,
    0xe1U, 0xf8U, 0x98U, 0x11U, 0x69U, 0xd9U, 0x8eU, 0x94U,
    0x9bU, 0x1eU, 0x87U, 0xe9U, 0xceU, 0x55U, 0x28U, 0xdfU,
    0x8cU, 0xa1U, 0x89U, 0x0dU, 0xbfU, 0xe6U, 0x42U, 0x68U,
    0x41U, 0x99U, 0x2dU, 0x0fU, 0xb0U, 0x54U, 0xbbU, 0x16U,
};

inline std::string block_to_hex(const Block& block) {
    std::ostringstream output;
    output << std::hex << std::setfill('0');
    for (std::size_t i = 0; i < block.size(); ++i) {
        output << std::setw(2) << static_cast<unsigned int>(block[i]);
    }
    return output.str();
}

inline uint8_t gf_xtime(uint8_t value) {
    return static_cast<uint8_t>((value << 1) ^ ((value & 0x80U) ? 0x1bU : 0x00U));
}

inline uint8_t gf_mul(uint8_t lhs, uint8_t rhs) {
    uint8_t result = 0;
    uint8_t multiplicand = lhs;
    uint8_t multiplier = rhs;

    for (int i = 0; i < 8; ++i) {
        if (multiplier & 1U) {
            result ^= multiplicand;
        }
        multiplicand = gf_xtime(multiplicand);
        multiplier >>= 1;
    }
    return result;
}

inline uint8_t gf_pow(uint8_t base, uint8_t exponent) {
    uint8_t result = 1;
    uint8_t factor = base;
    for (int i = 0; i < 8; ++i) {
        if (exponent & (1U << i)) {
            result = gf_mul(result, factor);
        }
        factor = gf_mul(factor, factor);
    }
    return result;
}

inline uint8_t aes_sbox_byte(uint8_t value) {
    return AES_SBOX_TABLE[value];
}

inline Block xor_blocks(const Block& lhs, const Block& rhs) {
    Block out{};
    for (std::size_t i = 0; i < 16; ++i) {
        out[i] = static_cast<uint8_t>(lhs[i] ^ rhs[i]);
    }
    return out;
}

inline Block sub_bytes(const Block& input) {
    Block out{};
    for (std::size_t i = 0; i < 16; ++i) {
        out[i] = aes_sbox_byte(input[i]);
    }
    return out;
}

inline Block shift_rows(const Block& input) {
    Block out{};
    out[0] = input[0];
    out[1] = input[5];
    out[2] = input[10];
    out[3] = input[15];
    out[4] = input[4];
    out[5] = input[9];
    out[6] = input[14];
    out[7] = input[3];
    out[8] = input[8];
    out[9] = input[13];
    out[10] = input[2];
    out[11] = input[7];
    out[12] = input[12];
    out[13] = input[1];
    out[14] = input[6];
    out[15] = input[11];
    return out;
}

inline Block mix_columns(const Block& input) {
    Block out{};
    for (std::size_t column = 0; column < 4; ++column) {
        const std::size_t offset = column * 4;
        const uint8_t a0 = input[offset + 0];
        const uint8_t a1 = input[offset + 1];
        const uint8_t a2 = input[offset + 2];
        const uint8_t a3 = input[offset + 3];

        out[offset + 0] = static_cast<uint8_t>(gf_mul(a0, 0x02U) ^ gf_mul(a1, 0x03U) ^ a2 ^ a3);
        out[offset + 1] = static_cast<uint8_t>(a0 ^ gf_mul(a1, 0x02U) ^ gf_mul(a2, 0x03U) ^ a3);
        out[offset + 2] = static_cast<uint8_t>(a0 ^ a1 ^ gf_mul(a2, 0x02U) ^ gf_mul(a3, 0x03U));
        out[offset + 3] = static_cast<uint8_t>(gf_mul(a0, 0x03U) ^ a1 ^ a2 ^ gf_mul(a3, 0x02U));
    }
    return out;
}

inline uint32_t word_from_bytes(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3) {
    return (static_cast<uint32_t>(b0) << 24)
        | (static_cast<uint32_t>(b1) << 16)
        | (static_cast<uint32_t>(b2) << 8)
        | static_cast<uint32_t>(b3);
}

inline uint32_t rot_word(uint32_t word) {
    return (word << 8) | (word >> 24);
}

inline uint32_t sub_word(uint32_t word) {
    const uint8_t b0 = aes_sbox_byte(static_cast<uint8_t>(word >> 24));
    const uint8_t b1 = aes_sbox_byte(static_cast<uint8_t>(word >> 16));
    const uint8_t b2 = aes_sbox_byte(static_cast<uint8_t>(word >> 8));
    const uint8_t b3 = aes_sbox_byte(static_cast<uint8_t>(word));
    return word_from_bytes(b0, b1, b2, b3);
}

inline uint32_t rcon_word(int round) {
    switch (round) {
    case 1: return 0x01000000U;
    case 2: return 0x02000000U;
    case 3: return 0x04000000U;
    case 4: return 0x08000000U;
    case 5: return 0x10000000U;
    case 6: return 0x20000000U;
    case 7: return 0x40000000U;
    case 8: return 0x80000000U;
    case 9: return 0x1b000000U;
    case 10: return 0x36000000U;
    default: return 0x00000000U;
    }
}

inline RoundKeys expand_round_keys(const Block& key) {
    std::array<uint32_t, 44> words{};
    for (std::size_t i = 0; i < 4; ++i) {
        words[i] = word_from_bytes(
            key[i * 4 + 0],
            key[i * 4 + 1],
            key[i * 4 + 2],
            key[i * 4 + 3]
        );
    }

    for (std::size_t i = 4; i < 44; ++i) {
        uint32_t temp = words[i - 1];
        if (i % 4 == 0) {
            temp = sub_word(rot_word(temp)) ^ rcon_word(static_cast<int>(i / 4));
        }
        words[i] = words[i - 4] ^ temp;
    }

    RoundKeys round_keys{};
    for (std::size_t round = 0; round < 11; ++round) {
        for (std::size_t word = 0; word < 4; ++word) {
            const uint32_t value = words[round * 4 + word];
            round_keys[round][word * 4 + 0] = static_cast<uint8_t>(value >> 24);
            round_keys[round][word * 4 + 1] = static_cast<uint8_t>(value >> 16);
            round_keys[round][word * 4 + 2] = static_cast<uint8_t>(value >> 8);
            round_keys[round][word * 4 + 3] = static_cast<uint8_t>(value);
        }
    }
    return round_keys;
}

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

inline Block add_round_key(const Block& state, const Block& round_key) {
    return xor_blocks(state, round_key);
}

inline Block apply_round_transform(
    const Block& state_in,
    const Block& round_key,
    bool final_round,
    Block* sub_bytes_state = 0,
    Block* shift_rows_state = 0,
    Block* mix_columns_state = 0
) {
    const Block sub = sub_bytes(state_in);
    const Block shifted = shift_rows(sub);
    const Block mixed = final_round ? shifted : mix_columns(shifted);

    if (sub_bytes_state) {
        *sub_bytes_state = sub;
    }
    if (shift_rows_state) {
        *shift_rows_state = shifted;
    }
    if (mix_columns_state) {
        *mix_columns_state = mixed;
    }
    return xor_blocks(mixed, round_key);
}

inline Block encrypt_block(const Block& key, const Block& plaintext) {
    const RoundKeys round_keys = expand_round_keys(key);
    Block state = xor_blocks(plaintext, round_keys[0]);
    for (int round = 1; round < 10; ++round) {
        state = xor_blocks(mix_columns(shift_rows(sub_bytes(state))), round_keys[round]);
    }
    state = xor_blocks(shift_rows(sub_bytes(state)), round_keys[10]);
    return state;
}

inline uint64_t next_rng(uint64_t& state) {
    state ^= state << 13;
    state ^= state >> 7;
    state ^= state << 17;
    return state;
}

inline Block random_block(uint64_t& state) {
    Block out{};
    for (std::size_t i = 0; i < 16; ++i) {
        out[i] = static_cast<uint8_t>(next_rng(state) >> 56);
    }
    return out;
}

inline std::string get_plusarg_value(
    int argc,
    char** argv,
    const std::string& name,
    const std::string& fallback
) {
    const std::string prefix = "+" + name + "=";
    for (int i = 1; i < argc; ++i) {
        const std::string argument(argv[i]);
        if (argument.compare(0, prefix.size(), prefix) == 0) {
            return argument.substr(prefix.size());
        }
    }
    return fallback;
}

inline std::string join_under_package_root(
    const std::string& root,
    const std::string& relative_path
) {
    if (root.empty()) {
        return {};
    }
    std::string r = root;
    while (!r.empty() && (r.back() == '/' || r.back() == '\\')) {
        r.pop_back();
    }
    std::string p = relative_path;
    while (!p.empty() && (p.front() == '/' || p.front() == '\\')) {
        p.erase(0, 1);
    }
    if (r.empty()) {
        return p;
    }
    return r + '/' + p;
}

inline std::string resolve_path(
    int argc,
    char** argv,
    const std::string& requested,
    const std::string& fallback
) {
    std::vector<std::string> candidates;
    const std::string package_root =
        get_plusarg_value(argc, argv, "fpga_flow_package_root", "");
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

inline uint64_t get_plusarg_uint(
    int argc,
    char** argv,
    const std::string& name,
    uint64_t fallback
) {
    const std::string value = get_plusarg_value(argc, argv, name, "");
    if (value.empty()) {
        return fallback;
    }
    return static_cast<uint64_t>(std::strtoull(value.c_str(), 0, 0));
}

inline bool plusarg_enabled(int argc, char** argv, const std::string& flag_name) {
    const std::string flag = "+" + flag_name;
    for (int i = 1; i < argc; ++i) {
        if (flag == argv[i]) {
            return true;
        }
    }
    return false;
}

inline void emit_checkpoint(
    const std::string& checkpoint,
    const std::string& detail
) {
    std::cout << "CHECKPOINT|" << checkpoint << "|PASS|" << detail << std::endl;
}

inline void write_placeholder_vcd(
    const std::string& path,
    const std::string& scope_name
) {
    std::ofstream out(path.c_str());
    out << "$date\n";
    out << "    generated by aes_mvp\n";
    out << "$end\n";
    out << "$version\n";
    out << "    placeholder waveform\n";
    out << "$end\n";
    out << "$timescale 1ns $end\n";
    out << "$scope module " << scope_name << " $end\n";
    out << "$upscope $end\n";
    out << "$enddefinitions $end\n";
    out << "$dumpvars\n";
    out << "$end\n";
}

}  // namespace aes_tb
