// LED Chaser Module
// 4-bit LED chaser with direction control and wrap-around
module led_chaser (
    input wire clk,
    input wire rst_n,
    input wire dir,          // 0 = shift right, 1 = shift left
    output reg [3:0] leds
);

    // Register for LED state
    reg [3:0] led_state;

    // Sequential logic
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            // Reset: set LSB to 1, others to 0
            led_state <= 4'b0001;
        end else begin
            // Shift based on direction
            if (dir) begin
                // Shift left (dir = 1)
                led_state <= {led_state[2:0], led_state[3]};
            end else begin
                // Shift right (dir = 0)
                led_state <= {led_state[0], led_state[3:1]};
            end
        end
    end

    // Continuous assignment
    assign leds = led_state;

endmodule
