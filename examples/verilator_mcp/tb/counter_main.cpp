#include <verilated.h>
#include <verilated_vcd_c.h>
#include <iostream>

#include "Vcounter.h"

vluint64_t sim_time = 0;

double sc_time_stamp() {
    return sim_time;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    Vcounter dut;
    VerilatedVcdC trace;
    dut.trace(&trace, 5);
    trace.open("simulation.vcd");

    dut.clk = 0;
    dut.rst_n = 0;
    dut.enable = 0;
    dut.clear = 0;

    std::cout << "[phase] reset_asserted"
              << " sim_time=" << sim_time
              << " count=" << static_cast<int>(dut.count)
              << " overflow=" << static_cast<int>(dut.overflow) << std::endl;

    for (int i = 0; i < 6; ++i) {
        dut.clk = !dut.clk;
        dut.eval();
        trace.dump(sim_time++);
    }

    dut.rst_n = 1;
    dut.enable = 1;

    std::cout << "[phase] reset_released_enable_on"
              << " sim_time=" << sim_time
              << " count=" << static_cast<int>(dut.count)
              << " overflow=" << static_cast<int>(dut.overflow) << std::endl;

    for (int i = 0; i < 24; ++i) {
        dut.clk = !dut.clk;
        if (i == 10) {
            dut.clear = 1;
            std::cout << "[phase] clear_asserted"
                      << " sim_time=" << sim_time
                      << " count=" << static_cast<int>(dut.count)
                      << " overflow=" << static_cast<int>(dut.overflow) << std::endl;
        }
        if (i == 12) {
            dut.clear = 0;
            std::cout << "[phase] clear_released"
                      << " sim_time=" << sim_time
                      << " count=" << static_cast<int>(dut.count)
                      << " overflow=" << static_cast<int>(dut.overflow) << std::endl;
        }
        dut.eval();
        trace.dump(sim_time++);
    }

    std::cout << "[phase] simulation_complete"
              << " sim_time=" << sim_time
              << " count=" << static_cast<int>(dut.count)
              << " overflow=" << static_cast<int>(dut.overflow) << std::endl;

    dut.final();
    trace.close();
    return 0;
}
