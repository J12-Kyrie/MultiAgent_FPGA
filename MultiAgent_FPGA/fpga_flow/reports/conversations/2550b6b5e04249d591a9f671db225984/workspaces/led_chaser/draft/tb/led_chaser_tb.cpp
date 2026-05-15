#include <verilated.h>
#include <iostream>
#include <cassert>

#include "Vled_chaser.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    Vled_chaser* dut = new Vled_chaser;

    // Initialize
    dut->rst_n = 0;
    dut->clk = 0;
    dut->dir = 0;
    dut->eval();

    // Apply reset
    dut->clk = 1;
    dut->eval();
    dut->clk = 0;
    dut->eval();

    // Release reset
    dut->rst_n = 1;
    dut->eval();

    // Check reset state (CHK_RESET_CLEAR)
    if (dut->leds != 0x1) {
        std::cerr << "FAIL: Reset state incorrect. Expected 0001, got "
                  << std::hex << (int)dut->leds << std::endl;
        delete dut;
        return 1;
    }
    std::cout << "CHECKPOINT|CHK_RESET_CLEAR|PASS|Reset sets leds=0001" << std::endl;

    // Test shift left (CHK_SHIFT_LEFT)
    dut->dir = 1; // Shift left
    for (int i = 0; i < 3; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }

    if (dut->leds != 0x8) {
        std::cerr << "FAIL: Shift left incorrect. Expected 1000, got "
                  << std::hex << (int)dut->leds << std::endl;
        delete dut;
        return 1;
    }
    std::cout << "CHECKPOINT|CHK_SHIFT_LEFT|PASS|Shift left 3 times gives 1000" << std::endl;

    // Test shift right (CHK_SHIFT_RIGHT)
    dut->dir = 0; // Shift right
    for (int i = 0; i < 2; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }

    if (dut->leds != 0x2) {
        std::cerr << "FAIL: Shift right incorrect. Expected 0010, got "
                  << std::hex << (int)dut->leds << std::endl;
        delete dut;
        return 1;
    }
    std::cout << "CHECKPOINT|CHK_SHIFT_RIGHT|PASS|Shift right 2 times gives 0010" << std::endl;

    // Test wrap-around (CHK_WRAP_AROUND)
    // State is 0010 after CHK_SHIFT_RIGHT; shift left 3 times: 0100 → 1000 → 0001
    dut->dir = 1; // Shift left
    for (int i = 0; i < 3; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }

    if (dut->leds != 0x1) {
        std::cerr << "FAIL: Wrap-around incorrect. Expected 0001, got "
                  << std::hex << (int)dut->leds << std::endl;
        delete dut;
        return 1;
    }
    std::cout << "CHECKPOINT|CHK_WRAP_AROUND|PASS|Wrap-around from leftmost gives 0001" << std::endl;

    std::cout << "All tests passed!" << std::endl;
    dut->final();
    delete dut;
    return 0;
}
