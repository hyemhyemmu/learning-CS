module sq_wave_gen #(
    parameter STEP = 10
)(
    input clk,
    input rst,
    input next_sample,
    input [2:0] buttons,
    output reg [9:0] code,
    output reg [3:0] leds
);

    // Registers for wave generation
    reg [11:0] window_counter;  // Increased to support wider range
    reg wave_state;
    reg [11:0] half_period_windows;  // Dynamic half period
    reg adjustment_mode;  // 0 = linear, 1 = exponential
    
    // Constants for frequency range
    // For 125MHz clock with 1024 cycles per window:
    // Sampling rate ≈ 122.07 kHz
    // 440Hz -> half_period = 139 windows
    // 20Hz -> half_period = 3051 windows  
    // 10kHz -> half_period = 6 windows
    localparam DEFAULT_HALF_PERIOD = 12'd139;  // 440Hz
    localparam MIN_HALF_PERIOD = 12'd6;        // ~10kHz
    localparam MAX_HALF_PERIOD = 12'd3051;     // ~20Hz
    
    // Button edge detection
    reg [2:0] buttons_prev;
    wire [2:0] button_press;
    
    assign button_press = buttons & ~buttons_prev;

    always @(posedge clk) begin
        if (rst) begin
            window_counter <= 12'd0;
            wave_state <= 1'b0;
            half_period_windows <= DEFAULT_HALF_PERIOD;
            adjustment_mode <= 1'b0;  // Start in linear mode
            buttons_prev <= 3'b0;
            leds <= 4'b0;
            code <= 10'd462;  // Default low state
        end else begin
            buttons_prev <= buttons;
            
            // Handle button presses
            if (button_press[2]) begin
                // Toggle adjustment mode
                adjustment_mode <= ~adjustment_mode;
            end
            
            if (button_press[0]) begin
                // Decrease period (increase frequency)
                if (adjustment_mode == 1'b0) begin
                    // Linear adjustment
                    if (half_period_windows > MIN_HALF_PERIOD + STEP) begin
                        half_period_windows <= half_period_windows - STEP;
                    end else begin
                        half_period_windows <= MIN_HALF_PERIOD;
                    end
                end else begin
                    // Exponential adjustment (halve period)
                    if (half_period_windows > MIN_HALF_PERIOD * 2) begin
                        half_period_windows <= half_period_windows >> 1;
                    end else begin
                        half_period_windows <= MIN_HALF_PERIOD;
                    end
                end
            end
            
            if (button_press[1]) begin
                // Increase period (decrease frequency)
                if (adjustment_mode == 1'b0) begin
                    // Linear adjustment
                    if (half_period_windows < MAX_HALF_PERIOD - STEP) begin
                        half_period_windows <= half_period_windows + STEP;
                    end else begin
                        half_period_windows <= MAX_HALF_PERIOD;
                    end
                end else begin
                    // Exponential adjustment (double period)
                    if (half_period_windows < MAX_HALF_PERIOD >> 1) begin
                        half_period_windows <= half_period_windows << 1;
                    end else begin
                        half_period_windows <= MAX_HALF_PERIOD;
                    end
                end
            end
            
            // Wave generation logic
            if (next_sample) begin
                if (window_counter >= half_period_windows - 1) begin
                    // Switch wave state
                    window_counter <= 12'd0;
                    wave_state <= ~wave_state;
                end else begin
                    window_counter <= window_counter + 1'b1;
                end
                
                // Output code per wave state
                code <= wave_state ? 10'd562 : 10'd462;
            end
            
            // Update LEDs
            leds[0] <= adjustment_mode;  // Show current mode
            leds[3:1] <= half_period_windows[11:9];  // Show rough frequency indication
        end
    end

endmodule
