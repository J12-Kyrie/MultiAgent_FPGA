// Key schedule SubWord must use the same S-box as the data path (aes_sbox_lut.vh).
`include "aes_sbox_lut.vh"

module aes_key_schedule_128 (
    input [127:0] key,
    input [3:0] round_index,
    output reg [127:0] round_key
);
    function [31:0] rot_word;
        input [31:0] value;
        begin
            rot_word = {value[23:0], value[31:24]};
        end
    endfunction

    function [31:0] sub_word;
        input [31:0] value;
        begin
            sub_word = {
                aes_sbox_lut(value[31:24]),
                aes_sbox_lut(value[23:16]),
                aes_sbox_lut(value[15:8]),
                aes_sbox_lut(value[7:0])
            };
        end
    endfunction

    function [31:0] rcon_word;
        input [3:0] round;
        begin
            case (round)
                4'd1:  rcon_word = 32'h01000000;
                4'd2:  rcon_word = 32'h02000000;
                4'd3:  rcon_word = 32'h04000000;
                4'd4:  rcon_word = 32'h08000000;
                4'd5:  rcon_word = 32'h10000000;
                4'd6:  rcon_word = 32'h20000000;
                4'd7:  rcon_word = 32'h40000000;
                4'd8:  rcon_word = 32'h80000000;
                4'd9:  rcon_word = 32'h1b000000;
                4'd10: rcon_word = 32'h36000000;
                default: rcon_word = 32'h00000000;
            endcase
        end
    endfunction

    function [127:0] expand_round_key;
        input [127:0] key_in;
        input [3:0] round;
        integer i;
        reg [31:0] w0;
        reg [31:0] w1;
        reg [31:0] w2;
        reg [31:0] w3;
        reg [31:0] temp;
        reg [31:0] nw0;
        reg [31:0] nw1;
        reg [31:0] nw2;
        reg [31:0] nw3;
        reg [3:0] round_sel;
        begin
            w0 = key_in[127:96];
            w1 = key_in[95:64];
            w2 = key_in[63:32];
            w3 = key_in[31:0];

            for (i = 1; i <= 10 && i <= round; i = i + 1) begin
                round_sel = i[3:0];
                temp = sub_word(rot_word(w3)) ^ rcon_word(round_sel);
                nw0 = w0 ^ temp;
                nw1 = w1 ^ nw0;
                nw2 = w2 ^ nw1;
                nw3 = w3 ^ nw2;
                w0 = nw0;
                w1 = nw1;
                w2 = nw2;
                w3 = nw3;
            end

            expand_round_key = {w0, w1, w2, w3};
        end
    endfunction

    always @* begin
        round_key = expand_round_key(key, round_index);
    end
endmodule
