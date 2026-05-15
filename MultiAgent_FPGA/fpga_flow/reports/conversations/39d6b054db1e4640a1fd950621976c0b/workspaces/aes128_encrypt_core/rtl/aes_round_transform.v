// SubBytes (16× aes_sbox), ShiftRows, MixColumns, AddRoundKey — FIPS-197 compatible.
module aes_round_transform (
    input [127:0] state_in,
    input [127:0] round_key,
    input final_round,
    output reg [127:0] sub_bytes_state,
    output reg [127:0] shift_rows_state,
    output reg [127:0] mix_columns_state,
    output reg [127:0] state_out
);
    function automatic [7:0] ot_xtime;
        input [7:0] b;
        ot_xtime = b[7] ? ({b[6:0], 1'b0} ^ 8'h1b) : {b[6:0], 1'b0};
    endfunction

    function automatic [7:0] ot_mul3;
        input [7:0] b;
        ot_mul3 = ot_xtime(b) ^ b;
    endfunction

    // TB maps C++ block[i] to Verilog [(15-i)*8 +: 8] (block[0]@[127:120], block[15]@[7:0]).
    // 16 SubBytes: byte index gi = block[gi]
    wire [7:0] sb_o [0:15];
    genvar gi;
    generate
        for (gi = 0; gi < 16; gi = gi + 1) begin : g_sbox
            aes_sbox u_sb (
                .in_byte(state_in[(15 - gi) * 8 +: 8]),
                .out_byte(sb_o[gi])
            );
        end
    endgenerate

    wire [127:0] sub_bytes_wire;
    assign sub_bytes_wire = {
        sb_o[0],  sb_o[1],  sb_o[2],  sb_o[3],
        sb_o[4],  sb_o[5],  sb_o[6],  sb_o[7],
        sb_o[8],  sb_o[9],  sb_o[10], sb_o[11],
        sb_o[12], sb_o[13], sb_o[14], sb_o[15]
    };

    // ShiftRows: match aes_tb_common.hpp (Block index j = bits [8*j+7:8*j])
    function automatic [3:0] sr_src;
        input [3:0] j;
        case (j)
            4'd0:  sr_src = 4'd0;
            4'd1:  sr_src = 4'd5;
            4'd2:  sr_src = 4'd10;
            4'd3:  sr_src = 4'd15;
            4'd4:  sr_src = 4'd4;
            4'd5:  sr_src = 4'd9;
            4'd6:  sr_src = 4'd14;
            4'd7:  sr_src = 4'd3;
            4'd8:  sr_src = 4'd8;
            4'd9:  sr_src = 4'd13;
            4'd10: sr_src = 4'd2;
            4'd11: sr_src = 4'd7;
            4'd12: sr_src = 4'd12;
            4'd13: sr_src = 4'd1;
            4'd14: sr_src = 4'd6;
            default: sr_src = 4'd11;  // j==15
        endcase
    endfunction

    wire [127:0] shift_rows_wire;
    genvar sj;
    generate
        for (sj = 0; sj < 16; sj = sj + 1) begin : g_sh
            assign shift_rows_wire[(15 - sj) * 8 +: 8] =
                sub_bytes_wire[(15 - sr_src(sj[3:0])) * 8 +: 8];
        end
    endgenerate

    // MixColumns: aes_tb column-major — column c uses block indices c*4 .. c*4+3
    wire [7:0] c0_0 = shift_rows_wire[(15 - 0) * 8 +: 8];
    wire [7:0] c0_1 = shift_rows_wire[(15 - 1) * 8 +: 8];
    wire [7:0] c0_2 = shift_rows_wire[(15 - 2) * 8 +: 8];
    wire [7:0] c0_3 = shift_rows_wire[(15 - 3) * 8 +: 8];
    wire [7:0] c1_0 = shift_rows_wire[(15 - 4) * 8 +: 8];
    wire [7:0] c1_1 = shift_rows_wire[(15 - 5) * 8 +: 8];
    wire [7:0] c1_2 = shift_rows_wire[(15 - 6) * 8 +: 8];
    wire [7:0] c1_3 = shift_rows_wire[(15 - 7) * 8 +: 8];
    wire [7:0] c2_0 = shift_rows_wire[(15 - 8) * 8 +: 8];
    wire [7:0] c2_1 = shift_rows_wire[(15 - 9) * 8 +: 8];
    wire [7:0] c2_2 = shift_rows_wire[(15 - 10) * 8 +: 8];
    wire [7:0] c2_3 = shift_rows_wire[(15 - 11) * 8 +: 8];
    wire [7:0] c3_0 = shift_rows_wire[(15 - 12) * 8 +: 8];
    wire [7:0] c3_1 = shift_rows_wire[(15 - 13) * 8 +: 8];
    wire [7:0] c3_2 = shift_rows_wire[(15 - 14) * 8 +: 8];
    wire [7:0] c3_3 = shift_rows_wire[(15 - 15) * 8 +: 8];

    wire [31:0] mix_w0;
    wire [31:0] mix_w1;
    wire [31:0] mix_w2;
    wire [31:0] mix_w3;

    // Per column: out[o+k] = s'k (k=0..3 top..bottom) at state bytes [8*(4*c+k)+:8]
    assign mix_w0[7:0]   = ot_xtime(c0_0) ^ ot_mul3(c0_1) ^ c0_2 ^ c0_3;
    assign mix_w0[15:8]  = c0_0 ^ ot_xtime(c0_1) ^ ot_mul3(c0_2) ^ c0_3;
    assign mix_w0[23:16] = c0_0 ^ c0_1 ^ ot_xtime(c0_2) ^ ot_mul3(c0_3);
    assign mix_w0[31:24] = ot_mul3(c0_0) ^ c0_1 ^ c0_2 ^ ot_xtime(c0_3);

    assign mix_w1[7:0]   = ot_xtime(c1_0) ^ ot_mul3(c1_1) ^ c1_2 ^ c1_3;
    assign mix_w1[15:8]  = c1_0 ^ ot_xtime(c1_1) ^ ot_mul3(c1_2) ^ c1_3;
    assign mix_w1[23:16] = c1_0 ^ c1_1 ^ ot_xtime(c1_2) ^ ot_mul3(c1_3);
    assign mix_w1[31:24] = ot_mul3(c1_0) ^ c1_1 ^ c1_2 ^ ot_xtime(c1_3);

    assign mix_w2[7:0]   = ot_xtime(c2_0) ^ ot_mul3(c2_1) ^ c2_2 ^ c2_3;
    assign mix_w2[15:8]  = c2_0 ^ ot_xtime(c2_1) ^ ot_mul3(c2_2) ^ c2_3;
    assign mix_w2[23:16] = c2_0 ^ c2_1 ^ ot_xtime(c2_2) ^ ot_mul3(c2_3);
    assign mix_w2[31:24] = ot_mul3(c2_0) ^ c2_1 ^ c2_2 ^ ot_xtime(c2_3);

    assign mix_w3[7:0]   = ot_xtime(c3_0) ^ ot_mul3(c3_1) ^ c3_2 ^ c3_3;
    assign mix_w3[15:8]  = c3_0 ^ ot_xtime(c3_1) ^ ot_mul3(c3_2) ^ c3_3;
    assign mix_w3[23:16] = c3_0 ^ c3_1 ^ ot_xtime(c3_2) ^ ot_mul3(c3_3);
    assign mix_w3[31:24] = ot_mul3(c3_0) ^ c3_1 ^ c3_2 ^ ot_xtime(c3_3);

    // Pack columns to TB order: block[0..3]@[127:96], ..., block[12..15]@[31:0]
    wire [127:0] mix_columns_wire;
    assign mix_columns_wire = {
        mix_w0[7:0], mix_w0[15:8], mix_w0[23:16], mix_w0[31:24],
        mix_w1[7:0], mix_w1[15:8], mix_w1[23:16], mix_w1[31:24],
        mix_w2[7:0], mix_w2[15:8], mix_w2[23:16], mix_w2[31:24],
        mix_w3[7:0], mix_w3[15:8], mix_w3[23:16], mix_w3[31:24]
    };

    wire [127:0] add_round_key_wire;
    wire [127:0] state_out_wire;
    genvar zi;
    generate
        for (zi = 0; zi < 16; zi = zi + 1) begin : g_ark
            assign add_round_key_wire[(15 - zi) * 8 +: 8] =
                mix_columns_wire[(15 - zi) * 8 +: 8] ^ round_key[(15 - zi) * 8 +: 8];
            assign state_out_wire[(15 - zi) * 8 +: 8] = final_round
                ? (shift_rows_wire[(15 - zi) * 8 +: 8] ^ round_key[(15 - zi) * 8 +: 8])
                : add_round_key_wire[(15 - zi) * 8 +: 8];
        end
    endgenerate

    always @* begin
        sub_bytes_state = sub_bytes_wire;
        shift_rows_state = shift_rows_wire;
        mix_columns_state = final_round ? shift_rows_wire : mix_columns_wire;
        state_out = state_out_wire;
    end
endmodule
