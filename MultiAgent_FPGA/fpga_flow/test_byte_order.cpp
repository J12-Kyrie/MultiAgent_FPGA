#include <iostream>
#include <iomanip>
#include <cstdint>
#include "tb/aes_tb_common.hpp"

int main() {
    // Test with a simple pattern: 0x00, 0x11, 0x22, ..., 0xFF
    aes_tb::Block block;
    for (int i = 0; i < 16; i++) {
        block[i] = i * 0x11;  // 0x00, 0x11, 0x22, ..., 0xFF
    }

    std::cout << "Block bytes (C++ order):" << std::endl;
    for (int i = 0; i < 16; i++) {
        std::cout << "block[" << i << "] = 0x" << std::hex << std::setw(2) << std::setfill('0')
                  << (int)block[i] << std::endl;
    }

    // Convert to wide
    uint32_t wide[4] = {0};
    aes_tb::write_block_to_wide(block, wide);

    std::cout << "\nWide words after write_block_to_wide:" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << "wide[" << i << "] = 0x" << std::hex << std::setw(8) << std::setfill('0')
                  << wide[i] << std::endl;

        // Print bytes within each word
        std::cout << "  Bytes in wide[" << i << "]: ";
        for (int j = 0; j < 4; j++) {
            uint8_t byte = (wide[i] >> (8*j)) & 0xFF;
            std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0')
                      << (int)byte << " ";
        }
        std::cout << std::endl;
    }

    // Convert back
    aes_tb::Block block2 = aes_tb::read_block_from_wide(wide);

    std::cout << "\nBlock bytes after read_block_from_wide:" << std::endl;
    for (int i = 0; i < 16; i++) {
        std::cout << "block2[" << i << "] = 0x" << std::hex << std::setw(2) << std::setfill('0')
                  << (int)block2[i] << std::endl;
    }

    // Test with actual vector data
    std::cout << "\n\nTesting with actual vector data:" << std::endl;
    std::string hex_str = "00102030405060708090a0b0c0d0e0f0";
    aes_tb::Block vec_block = aes_tb::parse_hex_block(hex_str);

    std::cout << "Vector block bytes:" << std::endl;
    for (int i = 0; i < 16; i++) {
        std::cout << "vec[" << i << "] = 0x" << std::hex << std::setw(2) << std::setfill('0')
                  << (int)vec_block[i] << std::endl;
    }

    uint32_t vec_wide[4] = {0};
    aes_tb::write_block_to_wide(vec_block, vec_wide);

    std::cout << "\nVector wide words:" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << "vec_wide[" << i << "] = 0x" << std::hex << std::setw(8) << std::setfill('0')
                  << vec_wide[i] << std::endl;
    }

    return 0;
}
