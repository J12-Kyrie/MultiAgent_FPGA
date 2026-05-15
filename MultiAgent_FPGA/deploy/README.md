# FPGA Deploy — RTL & Testbench Code

Two FPGA designs ready for deployment to development boards.

## Directory Structure

```
deploy/
  aes128/
    rtl/                        # Verilog source (4 modules + 1 header)
      aes_sbox.v                # S-Box (combinational LUT)
      aes_sbox_lut.vh           # S-Box lookup table header
      aes_key_schedule_128.v    # Key expansion (128-bit)
      aes_round_transform.v     # Single AES round (SubBytes+ShiftRows+MixColumns+AddRoundKey)
      aes128_encrypt_core.v     # Top-level encrypt core (10-round iterative, block handshake)
    tb/                         # C++ self-checking testbenches (Verilator)
      aes_sbox_tb.cpp
      aes_key_schedule_128_tb.cpp
      aes_round_transform_tb.cpp
      aes128_encrypt_core_tb.cpp
      aes_tb_common.hpp         # Shared utilities (hex parsing, checkpoint emission)
    vectors/                    # Known-answer & campaign test vectors
      aes_sbox_kat.txt
      aes_key_schedule_128_kat.txt
      aes_round_transform_kat.txt
      aes128_encrypt_core_kat.txt
      aes128_encrypt_core_regress.txt
      aes128_encrypt_core_zero.txt
      aes128_encrypt_core_l2_rand_small.txt
      aes128_encrypt_core_l2_rand_medium.txt
      aes128_encrypt_core_l2_back_to_back.txt
      aes128_encrypt_core_l2_mid_reset.txt
    blueprint.yaml              # Design blueprint (source of truth)

  led_chaser/
    rtl/
      led_chaser.v              # 4-bit LED chaser with direction control (33 lines)
    tb/
      led_chaser_tb.cpp         # Verilator self-checking testbench (93 lines)
    vectors/
      led_chaser_kat.txt
```

## Source Provenance

| Design | Source | Verification |
|--------|--------|-------------|
| aes128 | Pre-built reference implementation | Manual (reference design) |
| led_chaser | MultiAgent system generated, session `2550b6b5` | All 4 checkpoints PASS (L0+L1+Integration) |

## AES-128 Ports

```verilog
module aes128_encrypt_core (
    input  wire        clk,
    input  wire        rst_n,
    input  wire        start,        // pulse to begin encryption
    input  wire [127:0] plaintext,   // 128-bit plaintext block
    input  wire [127:0] key,         // 128-bit cipher key
    output reg  [127:0] ciphertext,  // 128-bit ciphertext output
    output reg         busy,         // high while encrypting
    output reg         done          // single-cycle pulse on completion
);
```

- 11-cycle latency (1 load + 10 rounds)
- Block handshake: assert `start` when `busy=0`, wait for `done` pulse

## LED Chaser Ports

```verilog
module led_chaser (
    input  wire       clk,
    input  wire       rst_n,
    input  wire       dir,    // 0=shift right, 1=shift left
    output reg  [3:0] leds
);
```

- 4-bit circular shift register
- Async active-low reset to `0001`
