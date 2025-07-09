module counter (
  input clk,
  input ce, // clock enable
  output [3:0] LEDS
);
    // Some initial code has been provided for you
    // You can change this code if needed
    reg [3:0] led_cnt_value;
    assign LEDS = led_cnt_value;

    reg [26:0] cycle_counter;
    localparam CYCLES_PER_SECOND = 27'd125_000_000;

    always @(posedge clk) begin
        // update the reg if clock is enabled (ce is 1).
        // Once the requisite number of cycles is reached, increment the count.
        if(ce) begin
            if (cycle_counter == CYCLES_PER_SECOND - 1) begin
                // Reset cycle counter and increment LED counter
                cycle_counter <= 27'd0;
                led_cnt_value <= led_cnt_value + 1; // 4-bit counter automatically wraps around
            end else begin
                // Increment cycle counter
                cycle_counter <= cycle_counter + 1;
            end
        end
    end
endmodule

