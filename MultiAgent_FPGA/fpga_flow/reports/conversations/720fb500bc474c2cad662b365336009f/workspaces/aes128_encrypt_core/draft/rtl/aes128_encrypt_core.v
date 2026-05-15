module aes128_encrypt_core (
    input clk,
    input rst_n,
    input start,
    input [127:0] key,
    input [127:0] plaintext,
    output reg busy,
    output reg done,
    output reg [127:0] ciphertext
);
    localparam [1:0] STATE_IDLE = 2'd0;
    localparam [1:0] STATE_ROUND = 2'd1;
    localparam [1:0] STATE_DONE = 2'd2;

    reg [1:0] fsm_state;
    reg [127:0] key_reg;
    reg [127:0] plaintext_reg;
    reg [127:0] state_reg;
    reg [3:0] round_index;

    wire [127:0] round_key;
    wire [127:0] sub_bytes_state;
    wire [127:0] shift_rows_state;
    wire [127:0] mix_columns_state;
    wire [127:0] round_state_out;
    wire final_round;

    assign final_round = (round_index == 4'd10);

    aes_key_schedule_128 u_key_schedule (
        .key(key_reg),
        .round_index(round_index),
        .round_key(round_key)
    );

    aes_round_transform u_round_transform (
        .state_in(state_reg),
        .round_key(round_key),
        .final_round(final_round),
        .sub_bytes_state(sub_bytes_state),
        .shift_rows_state(shift_rows_state),
        .mix_columns_state(mix_columns_state),
        .state_out(round_state_out)
    );

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            fsm_state <= STATE_IDLE;
            key_reg <= 128'h0;
            plaintext_reg <= 128'h0;
            state_reg <= 128'h0;
            round_index <= 4'd0;
            busy <= 1'b0;
            done <= 1'b0;
            ciphertext <= 128'h0;
        end else begin
            done <= 1'b0;
            case (fsm_state)
                STATE_IDLE: begin
                    busy <= 1'b0;
                    if (start) begin
                        key_reg <= key;
                        plaintext_reg <= plaintext;
                        state_reg <= plaintext ^ key;
                        round_index <= 4'd1;
                        busy <= 1'b1;
                        fsm_state <= STATE_ROUND;
                    end
                end

                STATE_ROUND: begin
                    busy <= 1'b1;
                    if (round_index >= 4'd1) begin
                        state_reg <= round_state_out;
                        if (round_index == 4'd10) begin
                            ciphertext <= round_state_out;
                            done <= 1'b1;
                            fsm_state <= STATE_DONE;
                            round_index <= 4'd0;
                        end else begin
                            round_index <= round_index + 4'd1;
                        end
                    end else begin
                        state_reg <= plaintext_reg ^ key_reg;
                        round_index <= 4'd1;
                    end
                end

                STATE_DONE: begin
                    busy <= 1'b0;
                    fsm_state <= STATE_IDLE;
                end

                default: begin
                    fsm_state <= STATE_IDLE;
                    busy <= 1'b0;
                end
            endcase
        end
    end
endmodule
