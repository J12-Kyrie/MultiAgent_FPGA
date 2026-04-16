---
name: aes-memory-sbox
description: Verified reference RTL and testbench for the aes_sbox module (combinational FIPS-197 S-box lookup).
type: knowledge
version: 1.0.0
agent: CodeActAgent
triggers:
  - aes_sbox memory
  - sbox reference implementation
  - sbox verified code
---

# Purpose

Consult this memory when generating or repairing the `aes_sbox` module. This is the complete, Verilator-verified implementation that passes all checkpoints.

# Verified RTL: `aes_sbox.v`

```verilog
// Combinational SubBytes using shared FIPS-197 lookup (aes_sbox_lut.vh).
`include "aes_sbox_lut.vh"

module aes_sbox (
    input [7:0] in_byte,
    output reg [7:0] out_byte
);
    always @* begin
        out_byte = aes_sbox_lut(in_byte);
    end
endmodule
```

# Verified Testbench: `aes_sbox_tb.cpp`

```cpp
#include <verilated.h>

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "Vaes_sbox.h"
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
            "vectors/aes128/aes_sbox_kat.txt"
        ),
        "../../../../vectors/aes128/aes_sbox_kat.txt"
    );
}

int run_known_answer_test(int argc, char** argv) {
    const std::string vecfile_path = resolve_vecfile(argc, argv);
    const std::vector<std::pair<uint8_t, uint8_t> > entries =
        aes_tb::read_sbox_kat(vecfile_path);

    if (entries.empty()) {
        std::cerr << "ERROR: No test vectors loaded from " << vecfile_path << std::endl;
        return 1;
    }

    Vaes_sbox dut;
    int test_count = 0;
    int fail_count = 0;

    for (std::size_t i = 0; i < entries.size(); ++i) {
        const uint8_t input_val = entries[i].first;
        const uint8_t expected_val = entries[i].second;

        dut.in_byte = input_val;
        dut.eval();

        const uint8_t actual_val = static_cast<uint8_t>(dut.out_byte);
        ++test_count;

        if (actual_val != expected_val) {
            ++fail_count;
            std::cerr << "FAIL: in_byte=0x" << std::hex
                      << static_cast<unsigned int>(input_val)
                      << " expected=0x" << static_cast<unsigned int>(expected_val)
                      << " observed=0x" << static_cast<unsigned int>(actual_val)
                      << std::dec << std::endl;
        }
    }

    if (fail_count == 0 && test_count > 0) {
        aes_tb::emit_checkpoint("CHK_SBOX_MATCH",
            std::to_string(test_count) + " vectors passed");
        return 0;
    }

    std::cerr << fail_count << "/" << test_count << " tests failed" << std::endl;
    return 1;
}

int run_exhaustive_test(int /* argc */, char** /* argv */) {
    Vaes_sbox dut;
    int fail_count = 0;

    for (unsigned int i = 0; i < 256; ++i) {
        dut.in_byte = static_cast<uint8_t>(i);
        dut.eval();
        const uint8_t expected = aes_tb::aes_sbox_byte(static_cast<uint8_t>(i));
        const uint8_t actual = static_cast<uint8_t>(dut.out_byte);
        if (actual != expected) {
            ++fail_count;
            std::cerr << "FAIL: in_byte=0x" << std::hex << i
                      << " expected=0x" << static_cast<unsigned int>(expected)
                      << " observed=0x" << static_cast<unsigned int>(actual)
                      << std::dec << std::endl;
        }
    }

    if (fail_count == 0) {
        aes_tb::emit_checkpoint("CHK_SBOX_MATCH", "exhaustive_256_entries");
        return 0;
    }

    std::cerr << fail_count << "/256 entries failed" << std::endl;
    return 1;
}

}  // namespace

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    try {
        const std::string profile =
            aes_tb::get_plusarg_value(argc, argv, "profile", "");
        if (profile == "exhaustive") {
            return run_exhaustive_test(argc, argv);
        }
        return run_known_answer_test(argc, argv);
    } catch (const std::exception& exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }
}
```

# Key Implementation Notes

- Pure combinational module: no clock, no reset, no sequential logic
- Wraps `aes_sbox_lut.vh` which defines `function automatic [7:0] aes_sbox_lut(input [7:0] b)` with all 256 FIPS-197 entries
- The LUT include file is shared with `aes_key_schedule_128` (SubWord uses the same S-box)
- TB has two modes: KAT (4 spot-check vectors from file) and exhaustive (all 256 entries vs C++ reference)
- Checkpoint: `CHK_SBOX_MATCH`
- Dependencies: `aes_sbox_lut.vh`, `aes_tb_common.hpp`
