`timescale 1ns/1ns
`define CLK_PERIOD 8

module sq_wave_gen_tb();
    // Generate 125 Mhz clock
    reg clk = 0;
    always #(`CLK_PERIOD/2) clk = ~clk;

    // I/O
    wire [9:0] code;
    reg [2:0] buttons;
    wire [3:0] leds;
    reg next_sample;
    reg rst;

    sq_wave_gen DUT (
        .clk(clk),
        .rst(rst),
        .code(code),
        .next_sample(next_sample),
        .buttons(buttons),
        .leds(leds)
    );

    integer code_file;
    integer next_sample_fetch;
    integer num_samples_fetched = 0;
    initial begin
        `ifdef IVERILOG
            $dumpfile("sq_wave_gen_tb.fst");
            $dumpvars(0, sq_wave_gen_tb);
        `endif
        `ifndef IVERILOG
            $vcdpluson;
        `endif

        code_file = $fopen("codes.txt", "w");
        
        // Initialize inputs
        rst = 1;
        next_sample = 0;
        buttons = 3'b0;
        
        // Test reset functionality
        $display("Testing reset functionality...");
        repeat (10) @(posedge clk);
        #1;
        rst = 0;
        $display("Reset released at time %t", $time);
        
        // Wait a few cycles after reset
        repeat (5) @(posedge clk); #1;

        fork
            begin
                repeat (122000) begin
                    // Pull next_sample every X cycles where X is a random number in [2, 9]
                    next_sample_fetch = ({$random} % 8) + 2;
                    repeat (next_sample_fetch) @(posedge clk);
                    #1;
                    next_sample = 1;
                    @(posedge clk); #1;
                    $fwrite(code_file, "%d\n", code);
                    num_samples_fetched = num_samples_fetched + 1;
                    next_sample = 0;
                    @(posedge clk); #1;
                end
            end
            begin
                // Test frequency adjustment functionality
                $display("Starting frequency adjustment tests...");
                
                // Test initial frequency (440Hz)
                @(num_samples_fetched == 500);
                $display("Fetched 500 samples at time %t - Default 440Hz", $time);
                $display("Current mode: %s, LEDs: %b", DUT.adjustment_mode ? "Exponential" : "Linear", leds);
                $display("Half period windows: %d", DUT.half_period_windows);
                
                // Test linear mode - decrease frequency (increase period)
                $display("\nTesting linear mode - decreasing frequency...");
                buttons[1] = 1; // Increase period
                @(posedge clk); #1;
                buttons[1] = 0;
                repeat (10) @(posedge clk); // Wait for button processing
                $display("After button[1] press - Half period: %d", DUT.half_period_windows);
                
                // Test linear mode - increase frequency (decrease period)
                $display("\nTesting linear mode - increasing frequency...");
                buttons[0] = 1; // Decrease period
                @(posedge clk); #1;
                buttons[0] = 0;
                repeat (10) @(posedge clk);
                $display("After button[0] press - Half period: %d", DUT.half_period_windows);
                
                // Switch to exponential mode
                $display("\nSwitching to exponential mode...");
                buttons[2] = 1;
                @(posedge clk); #1;
                buttons[2] = 0;
                repeat (10) @(posedge clk);
                $display("Mode switched to: %s, LEDs[0]: %b", DUT.adjustment_mode ? "Exponential" : "Linear", leds[0]);
                
                // Test exponential mode - halve period (double frequency)
                $display("\nTesting exponential mode - doubling frequency...");
                buttons[0] = 1;
                @(posedge clk); #1;
                buttons[0] = 0;
                repeat (10) @(posedge clk);
                $display("After exponential decrease - Half period: %d", DUT.half_period_windows);
                
                // Test exponential mode - double period (halve frequency)
                $display("\nTesting exponential mode - halving frequency...");
                buttons[1] = 1;
                @(posedge clk); #1;
                buttons[1] = 0;
                repeat (10) @(posedge clk);
                $display("After exponential increase - Half period: %d", DUT.half_period_windows);
                
                @(num_samples_fetched == 2000);
                $display("Fetched 2000 samples at time %t", $time);
                
                // Test overflow protection - try to go beyond minimum
                $display("\nTesting minimum frequency overflow protection...");
                repeat (20) begin // Press button many times to test overflow
                    buttons[0] = 1;
                    @(posedge clk); #1;
                    buttons[0] = 0;
                    repeat (5) @(posedge clk);
                    if (DUT.half_period_windows <= 12'd6) begin
                        $display("Reached minimum half period: %d", DUT.half_period_windows);
                        break;
                    end
                end
                
                // Test overflow protection - try to go beyond maximum
                $display("\nTesting maximum frequency overflow protection...");
                repeat (30) begin // Press button many times to test overflow
                    buttons[1] = 1;
                    @(posedge clk); #1;
                    buttons[1] = 0;
                    repeat (5) @(posedge clk);
                    if (DUT.half_period_windows >= 12'd3051) begin
                        $display("Reached maximum half period: %d", DUT.half_period_windows);
                        break;
                    end
                end
                
                @(num_samples_fetched == 4000);
                $display("Fetched 4000 samples at time %t", $time);
                
                // Test reset during operation
                $display("\nTesting reset during operation...");
                $display("Before reset - Half period: %d, Mode: %s", 
                         DUT.half_period_windows, DUT.adjustment_mode ? "Exponential" : "Linear");
                rst = 1;
                @(posedge clk); #1;
                rst = 0;
                repeat (5) @(posedge clk);
                $display("After reset - Half period: %d, Mode: %s", 
                         DUT.half_period_windows, DUT.adjustment_mode ? "Exponential" : "Linear");
                
                @(num_samples_fetched == 5000);
                $display("Fetched 5000 samples at time %t", $time);
                
                // Test rapid button presses (debouncing)
                $display("\nTesting rapid button presses...");
                repeat (5) begin
                    buttons[2] = 1;
                    @(posedge clk); #1;
                    buttons[2] = 0;
                    @(posedge clk); #1; // Very fast presses
                end
                repeat (10) @(posedge clk);
                $display("After rapid mode switches - Mode: %s", DUT.adjustment_mode ? "Exponential" : "Linear");
            end
        join

        $fclose(code_file);

        `ifndef IVERILOG
            $vcdplusoff;
        `endif
        $finish();
    end
endmodule
