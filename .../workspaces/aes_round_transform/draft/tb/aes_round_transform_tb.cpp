#include <verilated.h>

#include <iostream>

#include "Vaes_round_transform.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vaes_round_transform dut;
    dut.eval();
    // Required checkpoint contract is declared in testbench_contract.json.
    std::cout << "TODO: scaffold testbench, no checkpoints emitted yet." << std::endl;
    return 0;
}
