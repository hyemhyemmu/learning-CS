module sq_wave_gen (
    input clk,
    input next_sample,
    output reg [9:0] code
);

    reg [7:0] window_counter = 8'd0;
    reg wave_state = 1'b0;
    
    localparam HALF_PERIOD_WINDOWS = 8'd139;

    always @(posedge clk) begin
        if(next_sample) begin
            if(window_counter >= HALF_PERIOD_WINDOWS - 1) begin
                // switch wave state
                window_counter <= 8'd0;
                wave_state <= ~wave_state;
            end else begin
                window_counter <= window_counter + 1'b1;
            end
            
            // output code per wave state
            code <= wave_state ? 10'd562 : 10'd462;
        end 
    end

endmodule
