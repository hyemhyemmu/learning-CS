`timescale 1ns/1ns
`define CLK_PERIOD 8

module fsm_tb();
    // Generate 125 Mhz clock
    reg clk = 0;
    always #(`CLK_PERIOD/2) clk = ~clk;

    // I/O
    reg rst;
    reg [2:0] buttons;
    wire [23:0] fcw;
    wire [3:0] leds;
    wire [1:0] leds_state;

    // Override CYCLES_PER_SECOND for faster simulation
    localparam FAST_CYCLES_PER_SECOND = 100; // Reduced for quick simulation

    fsm #(.CYCLES_PER_SECOND(FAST_CYCLES_PER_SECOND)) DUT (
        .clk(clk),
        .rst(rst),
        .buttons(buttons),
        .leds(leds),
        .leds_state(leds_state),
        .fcw(fcw)
    );

    // Helper task to simulate a button press (single cycle pulse)
    task press_button;
        input [2:0] btn_idx_val; // Changed name to avoid conflict
        begin
            buttons = (1 << btn_idx_val); // Assert one button based on index (0, 1, or 2)
            @(posedge clk); #1;
            buttons = 3'b000;         // De-assert
            @(posedge clk); #1;       // Allow FSM to process the pulse
        end
    endtask

    // Helper task to wait for a number of "one_second_tick"s from the FSM
    task wait_fsm_seconds;
        input integer num_seconds;
        integer i;
        begin
            for (i = 0; i < num_seconds; i = i + 1) begin
                @(posedge DUT.one_second_tick);
                $display("Time: %0tns, FSM One Second Tick. Note Addr: %d, State: %b, FCW: %d, LEDs: %b, LED_State: %b", 
                         $time, DUT.current_note_addr, DUT.state, fcw, leds, leds_state);
            end
        end
    endtask

    integer j;
    reg [1:0] addr_before_pause;
    reg [23:0] fcw_of_current_note_before_edit;
    reg [23:0] fcw_in_edit_b4_dec;
    reg [23:0] fcw_in_edit_b4_inc;
    reg [23:0] final_edited_fcw;
    reg [1:0]  addr_of_edited_note;
    
    initial begin
        `ifdef IVERILOG
            $dumpfile("fsm_tb.fst");
            $dumpvars(0, fsm_tb);
        `endif
        `ifndef IVERILOG
            $vcdpluson;
        `endif

        rst = 1;
        @(posedge clk); #1;
        rst = 0;

        buttons = 3'b000; // Initialize buttons to 0

        // --- Test Reset ---
        $display("Time: %0tns, --- Test Reset ---", $time);
        @(posedge clk); #1; // Wait one cycle after reset release
        if (DUT.state !== DUT.REGULAR_PLAY) begin
            $error("Reset failed: State is not REGULAR_PLAY. Got: %b", DUT.state);
        end
        if (DUT.current_note_addr !== 2'b00) begin
            $error("Reset failed: current_note_addr is not 0. Got: %d", DUT.current_note_addr);
        end
        // Initial FCW should be RAM[0] which is 60474 (A4)
        if (fcw === 24'dx || fcw !== 24'd60474) begin // Check after a cycle for RAM read
             @(posedge clk); #1; // Allow one more cycle for initial RAM read if needed
             if (fcw !== 24'd60474) $error("Reset failed: Initial FCW is not for A4 (60474). Got: %d", fcw);
        end
        $display("Time: %0tns, Reset OK. State: REGULAR_PLAY, Addr: %d, FCW: %d", $time, DUT.current_note_addr, fcw);

        // --- Test REGULAR_PLAY for a few notes ---
        $display("Time: %0tns, --- Test REGULAR_PLAY (3 notes) ---", $time);
        wait_fsm_seconds(3); 
        if (DUT.current_note_addr !== 2'b11) begin // After 3 ticks from 0, should be at addr 3
             $error("REGULAR_PLAY failed: Expected addr 3, Got: %d", DUT.current_note_addr);
        end

        // --- Test REGULAR_PLAY -> PAUSED ---
        $display("Time: %0tns, --- Test REGULAR_PLAY -> PAUSED ---", $time);
        press_button(0); // Press Play/Pause button (buttons[0])
        if (DUT.state !== DUT.PAUSED) $error("Transition to PAUSED failed. State: %b", DUT.state);
        if (fcw !== 24'd0) $error("PAUSED state FCW is not 0. Got: %d", fcw);
        if (DUT.current_note_addr !== addr_before_pause) $error("PAUSED state changed addr. Expected: %d, Got: %d", addr_before_pause, DUT.current_note_addr);
        $display("Time: %0tns, PAUSED OK. Addr: %d", $time, DUT.current_note_addr);
        wait_fsm_seconds(1); // Stay in pause for a "second" - timer should not advance note

        // --- Test PAUSED -> REGULAR_PLAY ---
        $display("Time: %0tns, --- Test PAUSED -> REGULAR_PLAY ---", $time);
        press_button(0); // Press Play/Pause button
        if (DUT.state !== DUT.REGULAR_PLAY) $error("Transition back to REGULAR_PLAY failed. State: %b", DUT.state);
        if (DUT.current_note_addr !== addr_before_pause) $error("Resumed REGULAR_PLAY at wrong addr. Expected: %d, Got: %d", addr_before_pause, DUT.current_note_addr);
        $display("Time: %0tns, REGULAR_PLAY resumed. Addr: %d", $time, DUT.current_note_addr);
        wait_fsm_seconds(2); // Play 2 more notes

        // --- Test REGULAR_PLAY -> REVERSE_PLAY ---
        $display("Time: %0tns, --- Test REGULAR_PLAY -> REVERSE_PLAY ---", $time);
        press_button(1); // Press Reverse button (buttons[1])
        if (DUT.state !== DUT.REVERSE_PLAY) $error("Transition to REVERSE_PLAY failed. State: %b", DUT.state);
        $display("Time: %0tns, REVERSE_PLAY OK. Addr: %d", $time, DUT.current_note_addr);
        wait_fsm_seconds(3); // Play 3 notes in reverse

        // --- Test REVERSE_PLAY -> PAUSED ---
        $display("Time: %0tns, --- Test REVERSE_PLAY -> PAUSED ---", $time);
        addr_before_pause = DUT.current_note_addr;
        press_button(0); // Press Play/Pause button
        if (DUT.state !== DUT.PAUSED) $error("Transition from REVERSE to PAUSED failed. State: %b", DUT.state);
        if (fcw !== 24'd0) $error("PAUSED from REVERSE: FCW not 0. Got: %d", fcw);
        if (DUT.current_note_addr !== addr_before_pause) $error("PAUSED from REVERSE changed addr. Expected: %d, Got: %d", addr_before_pause, DUT.current_note_addr);
        $display("Time: %0tns, PAUSED from REVERSE OK. Addr: %d", $time, DUT.current_note_addr);
        
        // --- Test PAUSED -> EDIT ---
        $display("Time: %0tns, --- Test PAUSED -> EDIT ---", $time);
        // Need to wait for d_out_from_ram to be stable based on current_note_addr
        @(posedge clk); #1; @(posedge clk); #1; // Give time for RAM read to propagate to d_out_from_ram 
        fcw_of_current_note_before_edit = DUT.d_out_from_ram;
        press_button(2); // Press Edit button (buttons[2])
        if (DUT.state !== DUT.EDIT) $error("Transition to EDIT failed. State: %b", DUT.state);
        if (fcw !== fcw_of_current_note_before_edit) $error("EDIT entry FCW mismatch. Expected: %d, Got: %d", fcw_of_current_note_before_edit, fcw);
        $display("Time: %0tns, EDIT mode OK. Addr: %d, FCW: %d", $time, DUT.current_note_addr, fcw);

        // --- Test EDIT mode: Decrease frequency ---
        $display("Time: %0tns, --- Test EDIT: Decrease Freq ---", $time);
        fcw_in_edit_b4_dec = fcw;
        press_button(0); // Decrease freq (buttons[0] in EDIT)
        @(posedge clk); #1; // Allow change to propagate
        if (fcw === fcw_in_edit_b4_dec && fcw_in_edit_b4_dec > DUT.MIN_FCW) $error("EDIT Decrease Freq failed or at MIN. FCW before: %d, FCW after: %d", fcw_in_edit_b4_dec, fcw);
        if (!DUT.wr_en_to_ram && (fcw != fcw_in_edit_b4_dec)) $error("EDIT Decrease Freq: wr_en_to_ram not asserted when FCW changed.");
        if (DUT.d_in_to_ram !== fcw && (fcw != fcw_in_edit_b4_dec)) $error("EDIT Decrease Freq: d_in_to_ram (%d) not equal to new fcw (%d).", DUT.d_in_to_ram, fcw);
        $display("Time: %0tns, EDIT Decrease Freq. New FCW: %d", $time, fcw);
        
        // --- Test EDIT mode: Increase frequency ---
        $display("Time: %0tns, --- Test EDIT: Increase Freq ---", $time);
        fcw_in_edit_b4_inc = fcw;
        press_button(1); // Increase freq (buttons[1] in EDIT)
        @(posedge clk); #1; // Allow change to propagate
        if (fcw === fcw_in_edit_b4_inc && fcw_in_edit_b4_inc < DUT.MAX_FCW) $error("EDIT Increase Freq failed or at MAX. FCW before: %d, FCW after: %d", fcw_in_edit_b4_inc, fcw);
        if (!DUT.wr_en_to_ram && (fcw != fcw_in_edit_b4_inc)) $error("EDIT Increase Freq: wr_en_to_ram not asserted when FCW changed.");
        if (DUT.d_in_to_ram !== fcw && (fcw != fcw_in_edit_b4_inc)) $error("EDIT Increase Freq: d_in_to_ram (%d) not equal to new fcw (%d).", DUT.d_in_to_ram, fcw);
        $display("Time: %0tns, EDIT Increase Freq. New FCW: %d", $time, fcw);
        final_edited_fcw = fcw;
        addr_of_edited_note = DUT.current_note_addr;

        // --- Test EDIT -> PAUSED ---
        $display("Time: %0tns, --- Test EDIT -> PAUSED ---", $time);
        press_button(2); // Press Edit button to exit
        if (DUT.state !== DUT.PAUSED) $error("Transition from EDIT to PAUSED failed. State: %b", DUT.state);
        if (fcw !== 24'd0) $error("PAUSED from EDIT: FCW not 0. Got: %d", fcw);
        $display("Time: %0tns, Exited EDIT to PAUSED OK.", $time);

        // --- Verify edited note is played ---
        $display("Time: %0tns, --- Verify Edited Note ---", $time);
        press_button(0); // Go to REGULAR_PLAY from PAUSED
            wait_fsm_seconds(1); // Play one note
            if (DUT.current_note_addr == addr_of_edited_note) begin
                 @(posedge clk); #1; // allow fcw from RAM to propagate
                if (fcw !== final_edited_fcw) begin
                    $error("Edited note verification failed for addr %d. Expected FCW: %d, Got: %d", 
                           addr_of_edited_note, final_edited_fcw, fcw);
                end else begin
                    $display("Time: %0tns, Edited note FCW %d verified at addr %d.", $time, fcw, addr_of_edited_note);
                end
                break; 
            end
            if (j == 3 && DUT.current_note_addr != addr_of_edited_note) begin // Should have found by now
                 $error("Edited note addr %d not reached in verification loop. Current addr: %d", addr_of_edited_note, DUT.current_note_addr);
            end
        end
        wait_fsm_seconds(1); // Play a bit more

        // --- Test REVERSE_PLAY -> REGULAR_PLAY ---
        $display("Time: %0tns, --- Test REVERSE_PLAY -> REGULAR_PLAY ---", $time);
        // First, ensure we are in REVERSE_PLAY if not already
        if (DUT.state != DUT.REVERSE_PLAY) begin
            if (DUT.state == DUT.PAUSED) press_button(0); // from PAUSED to REGULAR
            wait_fsm_seconds(1);
            press_button(1); // from REGULAR to REVERSE
        end
        if (DUT.state !== DUT.REVERSE_PLAY) $error("Could not enter REVERSE_PLAY for final test. State: %b", DUT.state);
        $display("Time: %0tns, In REVERSE_PLAY. Addr: %d", $time, DUT.current_note_addr);
        wait_fsm_seconds(1);
        press_button(1); // Press Reverse again to go to REGULAR_PLAY
        if (DUT.state !== DUT.REGULAR_PLAY) $error("Transition from REVERSE_PLAY to REGULAR_PLAY failed. State: %b", DUT.state);
        $display("Time: %0tns, REVERSE_PLAY to REGULAR_PLAY OK. Addr: %d", $time, DUT.current_note_addr);
        wait_fsm_seconds(2);

        $display("Time: %0tns, --- All FSM Tests Completed ---", $time);

        `ifndef IVERILOG
            $vcdplusoff;
        `endif
        $finish();
    end
endmodule
