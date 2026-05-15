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
