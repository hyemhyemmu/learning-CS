module fsm #(
    parameter CYCLES_PER_SECOND = 125_000_000,
    parameter WIDTH = $clog2(CYCLES_PER_SECOND)
)(
    input clk,
    input rst,
    input [2:0] buttons,
    output [3:0] leds,
    output [23:0] fcw,
    output [1:0] leds_state
);
    // State definitions
    localparam REGULAR_PLAY = 2'b00;
    localparam REVERSE_PLAY = 2'b01;
    localparam PAUSED       = 2'b10;
    localparam EDIT         = 2'b11;

    // FCW limits and step for EDIT mode
    localparam MIN_FCW = 24'd2748;  // Approx 20 Hz
    localparam MAX_FCW = 24'd274877; // Approx 2000 Hz
    localparam FCW_STEP = 24'd1024;   // Arbitrary step for frequency change

    reg [WIDTH-1:0] timer_count;
    reg one_second_tick;

    reg [1:0] state, next_state;
    reg [1:0] current_note_addr;
    reg [23:0] edited_fcw;

    // Debounced button signals 
    wire play_pause_btn = buttons[0];
    wire reverse_btn    = buttons[1];
    wire edit_btn       = buttons[2];

    // RAM interface signals
    wire [1:0] addr_to_ram;
    wire wr_en_to_ram;
    wire rd_en_to_ram;
    wire [23:0] d_in_to_ram;
    wire [23:0] d_out_from_ram;

    fcw_ram my_ram (
        .clk(clk),
        .rst(rst),
        .rd_en(rd_en_to_ram),
        .wr_en(wr_en_to_ram),
        .addr(addr_to_ram),
        .d_in(d_in_to_ram),
        .d_out(d_out_from_ram)
    );

    // Timer logic for 1-second tick
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            timer_count <= 0;
            one_second_tick <= 1'b0;
        end else begin
            one_second_tick <= 1'b0; // Default to no tick
            if (state == REGULAR_PLAY || state == REVERSE_PLAY) begin
                if (timer_count == CYCLES_PER_SECOND - 1) begin
                    timer_count <= 0;
                    one_second_tick <= 1'b1;
                end else begin
                    timer_count <= timer_count + 1;
                end
            end else begin
                 timer_count <= 0; // Reset timer if not in play modes
            end
        end
    end

    // State register and current_note_addr logic
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state <= REGULAR_PLAY;
            current_note_addr <= 2'b00;
            edited_fcw <= 24'd0;
        end else begin
            state <= next_state;
            if (next_state != state && next_state == EDIT) begin // Entering EDIT state
                 edited_fcw <= d_out_from_ram; // Load current note's FCW for editing
            end else if (state == EDIT) begin
                // Handle FCW modification in EDIT state
                if (play_pause_btn && !reverse_btn) begin // Button[0] decreases frequency
                    if (edited_fcw > MIN_FCW + FCW_STEP)
                        edited_fcw <= edited_fcw - FCW_STEP;
                    else
                        edited_fcw <= MIN_FCW;
                end else if (reverse_btn && !play_pause_btn) begin // Button[1] increases frequency
                    if (edited_fcw < MAX_FCW - FCW_STEP)
                        edited_fcw <= edited_fcw + FCW_STEP;
                    else
                        edited_fcw <= MAX_FCW;
                end
            end


            if (one_second_tick) begin
                if (state == REGULAR_PLAY) begin
                    current_note_addr <= current_note_addr + 1;
                end else if (state == REVERSE_PLAY) begin
                    current_note_addr <= current_note_addr - 1;
                end
            end
            // current_note_addr holds its value in PAUSED and EDIT states unless changed by play modes
        end
    end

    // Next state logic (combinational)
    always @(*) begin
        next_state = state; // Default: stay in current state
        case (state)
            REGULAR_PLAY: begin
                if (play_pause_btn) next_state = PAUSED;
                else if (reverse_btn) next_state = REVERSE_PLAY;
            end
            REVERSE_PLAY: begin
                if (play_pause_btn) next_state = PAUSED;
                else if (reverse_btn) next_state = REGULAR_PLAY;
            end
            PAUSED: begin
                if (play_pause_btn) next_state = REGULAR_PLAY;
                else if (edit_btn) next_state = EDIT;
            end
            EDIT: begin
                if (edit_btn) next_state = PAUSED;
                // Frequency changes handled in sequential block, write to RAM also there via wr_en
            end
            default: next_state = REGULAR_PLAY;
        endcase
    end

    // Output logic (combinational)
    assign addr_to_ram = current_note_addr;
    assign rd_en_to_ram = 1'b1; // Always read from RAM

    // wr_en is active in EDIT state if freq change buttons are pressed
    assign wr_en_to_ram = (state == EDIT) && ((play_pause_btn && !reverse_btn) || (reverse_btn && !play_pause_btn)) && !edit_btn; // Prevent write if exiting EDIT

    assign d_in_to_ram = edited_fcw;

    assign fcw = (state == PAUSED) ? 24'd0 :
                 (state == EDIT) ? edited_fcw :
                 d_out_from_ram;

    assign leds[0] = (current_note_addr == 2'b00);
    assign leds[1] = (current_note_addr == 2'b01);
    assign leds[2] = (current_note_addr == 2'b10);
    assign leds[3] = (current_note_addr == 2'b11);

    assign leds_state = state;

endmodule
