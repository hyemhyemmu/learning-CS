`timescale 1ns/1ps

module counter_tb();
    reg clk;
    reg [3:0] buttons;
    wire [3:0] leds;
    
    // instance
    counter #(
        .CYCLES_PER_SECOND(125_000_000)
    ) dut (
        .clk(clk),
        .buttons(buttons),
        .leds(leds)
    );
    
    // Clock generation
    initial begin
        clk = 0;
        forever #5 clk = ~clk; // 100MHz clock
    end
    
    // Test variables
    integer test_count = 0;
    
    // Helper task: wait for clock rising edge
    task wait_clk;
        begin
            @(posedge clk);
            #1; // Small delay to ensure signal stability
        end
    endtask
    
    // Helper task: press button for one clock cycle
    task press_button;
        input [3:0] btn;
        begin
            buttons = btn;
            wait_clk();
            buttons = 4'b0000;
        end
    endtask
    
    // Helper task: verify counter value
    task check_counter;
        input [3:0] expected;
        input string test_name;
        begin
            test_count = test_count + 1;
            if (leds !== expected) begin
                $error("Test %0d FAILED: %s - Expected: %b, Got: %b", 
                       test_count, test_name, expected, leds);
            end else begin
                $display("Test %0d PASSED: %s - Counter value: %b", 
                         test_count, test_name, leds);
            end
        end
    endtask
    
    // Main test sequence
    initial begin
        $display("Starting counter testbench...");
        
        // Initialize
        buttons = 4'b0000;
        
        // Wait a few clock cycles for system to stabilize
        repeat(3) wait_clk();
        
        // ===== Test 1: Initial state =====
        check_counter(4'b0000, "Initial state");
        
        // ===== Test 2: Increment functionality =====
        $display("\n--- Testing increment functionality ---");
        
        // Increment once
        press_button(4'b0001); // buttons[0] = 1
        wait_clk();
        check_counter(4'b0001, "Increment to 1");
        
        // Increment a few more times
        press_button(4'b0001);
        wait_clk();
        check_counter(4'b0010, "Increment to 2");
        
        press_button(4'b0001);
        wait_clk();
        check_counter(4'b0011, "Increment to 3");
        
        // Increment to larger value
        repeat(5) begin
            press_button(4'b0001);
            wait_clk();
        end
        check_counter(4'b1000, "Increment to 8");
        
        // ===== Test 3: Decrement functionality =====
        $display("\n--- Testing decrement functionality ---");
        
        // Decrement once
        press_button(4'b0010); // buttons[1] = 1
        wait_clk();
        check_counter(4'b0111, "Decrement to 7");
        
        // Decrement a few more times
        press_button(4'b0010);
        wait_clk();
        check_counter(4'b0110, "Decrement to 6");
        
        press_button(4'b0010);
        wait_clk();
        check_counter(4'b0101, "Decrement to 5");
        
        // ===== Test 4: Reset functionality =====
        $display("\n--- Testing reset functionality ---");
        
        press_button(4'b1000); // buttons[3] = 1
        wait_clk();
        check_counter(4'b0000, "Reset to 0");
        
        // ===== Test 5: Boundary conditions test =====
        $display("\n--- Testing boundary conditions ---");
        
        // Test decrement from 0 (underflow)
        press_button(4'b0010);
        wait_clk();
        check_counter(4'b1111, "Underflow from 0 to 15");
        
        // Test increment from 15 (overflow)
        press_button(4'b0001);
        wait_clk();
        check_counter(4'b0000, "Overflow from 15 to 0");
        
        // ===== Test 6: Multiple button priority test =====
        $display("\n--- Testing button priority ---");
        
        // Set initial value
        repeat(3) begin
            press_button(4'b0001);
            wait_clk();
        end
        check_counter(4'b0011, "Setup for priority test");
        
        // Press increment and decrement simultaneously, should execute increment (higher priority)
        buttons = 4'b0011; // buttons[0] and buttons[1] pressed simultaneously
        wait_clk();
        buttons = 4'b0000;
        wait_clk();
        check_counter(4'b0100, "Increment priority over decrement");
        
        // Press increment and reset simultaneously, should execute increment (higher priority)
        buttons = 4'b1001; // buttons[0] and buttons[3] pressed simultaneously
        wait_clk();
        buttons = 4'b0000;
        wait_clk();
        check_counter(4'b0101, "Increment priority over reset");
        
        // Press decrement and reset simultaneously, should execute decrement (higher priority)
        buttons = 4'b1010; // buttons[1] and buttons[3] pressed simultaneously
        wait_clk();
        buttons = 4'b0000;
        wait_clk();
        check_counter(4'b0100, "Decrement priority over reset");
        
        // ===== Test 7: No-operation state =====
        $display("\n--- Testing no-operation state ---");
        
        // No buttons pressed, counter should remain unchanged
        buttons = 4'b0000;
        repeat(5) wait_clk();
        check_counter(4'b0100, "No change when no buttons pressed");
        
        // Only press buttons[2] (unused button), counter should remain unchanged
        buttons = 4'b0100;
        wait_clk();
        buttons = 4'b0000;
        wait_clk();
        check_counter(4'b0100, "No change when unused button pressed");
        
        // ===== Test 8: Continuous operations test =====
        $display("\n--- Testing continuous operations ---");
        
        // Reset to 0
        press_button(4'b1000);
        wait_clk();
        
        // Rapid continuous increment
        repeat(10) begin
            press_button(4'b0001);
            wait_clk();
        end
        check_counter(4'b1010, "Continuous increment to 10");
        
        // Rapid continuous decrement
        repeat(5) begin
            press_button(4'b0010);
            wait_clk();
        end
        check_counter(4'b0101, "Continuous decrement to 5");
        
        // ===== Test completed =====
        $display("\n--- All tests completed ---");
        if (test_count > 0) begin
            $display("Total tests run: %0d", test_count);
        end
        
        #100;
        $display("Counter testbench finished successfully!");
        $finish;
    end
    
    // Monitor signal changes
    initial begin
        $monitor("Time: %0t, buttons: %b, leds: %b (%0d)", 
                 $time, buttons, leds, leds);
    end
    
    // Timeout protection
    initial begin
        #10000;
        $error("Testbench timeout!");
        $finish;
    end
    
endmodule
