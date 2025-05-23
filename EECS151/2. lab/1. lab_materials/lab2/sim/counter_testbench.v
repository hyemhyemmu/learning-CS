`timescale 1ns/1ns

`define SECOND 1000000000
`define MS 1000000

module counter_testbench();
    reg clock = 0;
    reg ce;
    wire [3:0] LEDS;

    counter ctr (
        .clk(clock),
        .ce(ce),
        .LEDS(LEDS)
    );

    // Notice that this code causes the `clock` signal to constantly
    // switch up and down every 4 time steps.
    always #(4) clock <= ~clock;

    initial begin
        `ifdef IVERILOG
            $dumpfile("counter_testbench.fst");
            $dumpvars(0, counter_testbench);
        `endif
        `ifndef IVERILOG
            $vcdpluson;
        `endif

        // Initialize signals
        ce = 0;
        
        // Wait for a few clock cycles for initialization
        repeat (5) @(posedge clock);
        
        $display("Starting counter testbench");
        $display("Time: %0t, CE: %b, LEDS: %d", $time, ce, LEDS);
        
        // Test 1: Enable clock, counter should start counting
        $display("\n=== Test 1: Enable clock (ce=1) ===");
        ce = 1;
        
        // Since 125M cycles is too long for simulation, let's wait for several cycles
        // and check that the internal cycle_counter is incrementing
        repeat (10) @(posedge clock);
        $display("Time: %0t, CE: %b, LEDS: %d", $time, ce, LEDS);
        
        // Check if cycle counter is working (should be non-zero after some cycles)
        if (ctr.cycle_counter > 0) begin
            $display("PASS: Cycle counter is incrementing (%d)", ctr.cycle_counter);
        end else begin
            $display("FAIL: Cycle counter not incrementing");
        end
        
        // Test 2: Disable clock enable, counter should stop
        $display("\n=== Test 2: Disable clock (ce=0) ===");
        ce = 0;
        
        // Store current values
        integer saved_cycle_counter = ctr.cycle_counter;
        integer saved_led_value = LEDS;
        
        repeat (10) @(posedge clock);
        $display("Time: %0t, CE: %b, LEDS: %d", $time, ce, LEDS);
        
        // Check that counters didn't change
        if (ctr.cycle_counter == saved_cycle_counter && LEDS == saved_led_value) begin
            $display("PASS: Counter stopped when ce=0");
        end else begin
            $display("FAIL: Counter continued when ce=0");
        end
        
        // Test 3: Re-enable and test overflow behavior
        $display("\n=== Test 3: Re-enable clock and test behavior ===");
        ce = 1;
        
        // Force the cycle counter close to overflow to test LED increment
        // This is a white-box test accessing internal signals
        ctr.cycle_counter = 27'd124_999_995; // Close to CYCLES_PER_SECOND - 1
        
        $display("Forcing cycle_counter to near overflow: %d", ctr.cycle_counter);
        
        repeat (10) @(posedge clock);
        $display("Time: %0t, CE: %b, LEDS: %d, cycle_counter: %d", $time, ce, LEDS, ctr.cycle_counter);
        
        // Check if LED incremented and cycle counter reset
        if (ctr.cycle_counter < 10 && LEDS == 1) begin
            $display("PASS: LED incremented and cycle counter reset");
        end else begin
            $display("FAIL: LED increment or cycle counter reset failed");
        end
        
        // Test 4: Test 4-bit overflow (LED counter wraps from 15 to 0)
        $display("\n=== Test 4: Test 4-bit LED counter overflow ===");
        
        // Force LED counter to 15 and test wrap-around
        ctr.led_cnt_value = 4'd15;
        ctr.cycle_counter = 27'd124_999_999; // One cycle before overflow
        
        @(posedge clock); // This should trigger LED overflow
        $display("Time: %0t, CE: %b, LEDS: %d", $time, ce, LEDS);
        
        if (LEDS == 0) begin
            $display("PASS: LED counter wrapped from 15 to 0");
        end else begin
            $display("FAIL: LED counter wrap-around failed");
        end
        
        // Test 5: Multiple increments
        $display("\n=== Test 5: Test multiple increments ===");
        for (integer i = 0; i < 3; i = i + 1) begin
            // Force near overflow
            ctr.cycle_counter = 27'd124_999_999;
            @(posedge clock);
            $display("Increment %0d: LEDS = %d", i+1, LEDS);
        end
        
        $display("\n=== All tests completed ===");
        $display("Final state - CE: %b, LEDS: %d, cycle_counter: %d", ce, LEDS, ctr.cycle_counter);

        `ifndef IVERILOG
            $vcdplusoff;
        `endif
        $finish();
    end
endmodule

