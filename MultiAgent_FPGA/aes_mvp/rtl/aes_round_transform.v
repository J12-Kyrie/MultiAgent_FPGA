module aes_round_transform (
    input [127:0] state_in,
    input [127:0] round_key,
    input final_round,
    output reg [127:0] sub_bytes_state,
    output reg [127:0] shift_rows_state,
    output reg [127:0] mix_columns_state,
    output reg [127:0] state_out
);
    function [7:0] aes_xtime;
        input [7:0] value;
        begin
            aes_xtime = value[7] ? {value[6:0], 1'b0} ^ 8'h1b : {value[6:0], 1'b0};
        end
    endfunction

    function [7:0] aes_gf_mul;
        input [7:0] lhs;
        input [7:0] rhs;
        integer i;
        reg [7:0] multiplicand;
        reg [7:0] multiplier;
        reg [7:0] result;
        begin
            multiplicand = lhs;
            multiplier = rhs;
            result = 8'h00;
            for (i = 0; i < 8; i = i + 1) begin
                if (multiplier[0]) begin
                    result = result ^ multiplicand;
                end
                multiplicand = aes_xtime(multiplicand);
                multiplier = multiplier >> 1;
            end
            aes_gf_mul = result;
        end
    endfunction

    function [7:0] aes_gf_pow;
        input [7:0] base;
        input [7:0] exponent;
        integer i;
        reg [7:0] factor;
        reg [7:0] result;
        begin
            factor = base;
            result = 8'h01;
            for (i = 0; i < 8; i = i + 1) begin
                if (exponent[i]) begin
                    result = aes_gf_mul(result, factor);
                end
                factor = aes_gf_mul(factor, factor);
            end
            aes_gf_pow = result;
        end
    endfunction

    function [7:0] aes_sbox_byte;
        input [7:0] value;
        reg [7:0] affine;
        reg [7:0] inverse;
        begin
            if (value == 8'h00) begin
                aes_sbox_byte = 8'h63;
            end else begin
                inverse = aes_gf_pow(value, 8'hfe);
                affine[0] = inverse[0] ^ inverse[4] ^ inverse[5] ^ inverse[6] ^ inverse[7] ^ 1'b1;
                affine[1] = inverse[1] ^ inverse[5] ^ inverse[6] ^ inverse[7] ^ inverse[0] ^ 1'b1;
                affine[2] = inverse[2] ^ inverse[6] ^ inverse[7] ^ inverse[0] ^ inverse[1];
                affine[3] = inverse[3] ^ inverse[7] ^ inverse[0] ^ inverse[1] ^ inverse[2];
                affine[4] = inverse[4] ^ inverse[0] ^ inverse[1] ^ inverse[2] ^ inverse[3];
                affine[5] = inverse[5] ^ inverse[1] ^ inverse[2] ^ inverse[3] ^ inverse[4] ^ 1'b1;
                affine[6] = inverse[6] ^ inverse[2] ^ inverse[3] ^ inverse[4] ^ inverse[5] ^ 1'b1;
                affine[7] = inverse[7] ^ inverse[3] ^ inverse[4] ^ inverse[5] ^ inverse[6];
                aes_sbox_byte = affine;
            end
        end
    endfunction

    function [127:0] sub_bytes;
        input [127:0] value;
        begin
            sub_bytes = {
                aes_sbox_byte(value[127:120]),
                aes_sbox_byte(value[119:112]),
                aes_sbox_byte(value[111:104]),
                aes_sbox_byte(value[103:96]),
                aes_sbox_byte(value[95:88]),
                aes_sbox_byte(value[87:80]),
                aes_sbox_byte(value[79:72]),
                aes_sbox_byte(value[71:64]),
                aes_sbox_byte(value[63:56]),
                aes_sbox_byte(value[55:48]),
                aes_sbox_byte(value[47:40]),
                aes_sbox_byte(value[39:32]),
                aes_sbox_byte(value[31:24]),
                aes_sbox_byte(value[23:16]),
                aes_sbox_byte(value[15:8]),
                aes_sbox_byte(value[7:0])
            };
        end
    endfunction

    function [127:0] shift_rows;
        input [127:0] value;
        begin
            shift_rows = {
                value[127:120],
                value[87:80],
                value[47:40],
                value[7:0],
                value[95:88],
                value[55:48],
                value[15:8],
                value[103:96],
                value[63:56],
                value[23:16],
                value[111:104],
                value[71:64],
                value[31:24],
                value[119:112],
                value[79:72],
                value[39:32]
            };
        end
    endfunction

    function [31:0] mix_column;
        input [31:0] column;
        reg [7:0] a0;
        reg [7:0] a1;
        reg [7:0] a2;
        reg [7:0] a3;
        begin
            a0 = column[31:24];
            a1 = column[23:16];
            a2 = column[15:8];
            a3 = column[7:0];
            mix_column = {
                aes_gf_mul(a0, 8'h02) ^ aes_gf_mul(a1, 8'h03) ^ a2 ^ a3,
                a0 ^ aes_gf_mul(a1, 8'h02) ^ aes_gf_mul(a2, 8'h03) ^ a3,
                a0 ^ a1 ^ aes_gf_mul(a2, 8'h02) ^ aes_gf_mul(a3, 8'h03),
                aes_gf_mul(a0, 8'h03) ^ a1 ^ a2 ^ aes_gf_mul(a3, 8'h02)
            };
        end
    endfunction

    function [127:0] mix_columns;
        input [127:0] value;
        begin
            mix_columns = {
                mix_column(value[127:96]),
                mix_column(value[95:64]),
                mix_column(value[63:32]),
                mix_column(value[31:0])
            };
        end
    endfunction

    always @* begin
        sub_bytes_state = sub_bytes(state_in);
        shift_rows_state = shift_rows(sub_bytes_state);
        if (final_round) begin
            mix_columns_state = shift_rows_state;
            state_out = shift_rows_state ^ round_key;
        end else begin
            mix_columns_state = mix_columns(shift_rows_state);
            state_out = mix_columns_state ^ round_key;
        end
    end
endmodule
