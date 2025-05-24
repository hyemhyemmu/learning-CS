module dac #(
    parameter CYCLES_PER_WINDOW = 1024,
    parameter CODE_WIDTH = $clog2(CYCLES_PER_WINDOW)
)(
    input clk,
    input rst,
    input [CODE_WIDTH-1:0] code,
    output next_sample,
    output reg pwm
);

    // Counter for tracking cycles within the window
    reg [CODE_WIDTH-1:0] counter;
    
    always @(posedge clk) begin
        if (rst) begin
            // reset everything
            counter <= {CODE_WIDTH{1'b0}};
            pwm <= 1'b0;
        end else begin
            // Increment counter, wrap around at CYCLES_PER_WINDOW
            if (counter == CYCLES_PER_WINDOW - 1) begin
                counter <= {CODE_WIDTH{1'b0}}; // reset
            end else begin
                counter <= counter + 1'b1; // regular plus 1
            end
            
            // PWM logic
            pwm <= (code == {CODE_WIDTH{1'b0}}) ? 1'b0 : (counter < code);
        end
    end
    
    // next_sample is high on the final cycle of the pulse window
    assign next_sample = (counter == CYCLES_PER_WINDOW - 1);

endmodule
