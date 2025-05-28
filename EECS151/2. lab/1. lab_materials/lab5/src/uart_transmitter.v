module uart_transmitter #(
    parameter CLOCK_FREQ = 125_000_000,
    parameter BAUD_RATE = 115_200)
(
    input clk,
    input reset,

    input [7:0] data_in,
    input data_in_valid,
    output reg data_in_ready,

    output reg serial_out // 1 at a time
);
    // See diagram in the lab guide
    localparam  SYMBOL_EDGE_TIME    =   CLOCK_FREQ / BAUD_RATE;
    localparam  CLOCK_COUNTER_WIDTH =   $clog2(SYMBOL_EDGE_TIME);

    // states
    localparam IDLE = 0;
    localparam TRANSMITT = 1;
    reg state, next_state;

    // temp params
    reg [9:0] shift_reg; // data temp store
    reg [3:0] bit_counter; // bits we have sent
    reg [CLOCK_COUNTER_WIDTH-1:0] clk_counter; 

    reg data_in_ready_int;
    reg serial_out_int;

    reg transmitt_done;

    assign data_in_ready = data_in_ready_int;
    assign serial_out    = serial_out_int;

    // 1. update state
    always @ (posedge clk or posedge reset) begin
        if (reset) 
            state <= IDLE;
        else
            state <= next_state;
    end

    // 2. state update logic
    always @ (*) begin
        // default - if not updated
        next_state = state;
        data_in_ready_int = 0;

        case(state)
            IDLE:begin
                  data_in_ready_int = 1;
                  if (data_in_valid)
                    next_state = TRANSMITT;
                end
            TRANSMITT:begin
                  data_in_ready_int = 0;
                  // if transmitt mode started, block input
                  // only open when finish transfer
                  // decided by main function
                  if (transmitt_done)
                    next_state = IDLE;
                end
            endcase
    end

    // 3. behaviour logic
    always @ (posedge clk or posedge reset) begin
      if (reset) begin
        shift_reg <= 10'b1111111111;
        bit_counter     <= 0;
        clk_counter     <= 0;
        serial_out_int  <= 1; 
      end else begin
        case (state)
            IDLE:
                bit_counter     <= 0;
                clk_counter     <= 0;
                serial_out_int  <= 1; 
            
                if (data_in_valid) begin
                  shift_reg <= {1'b1, data_in, 1'b0};
                end

            TRANSMITT:
                // make "ready" when finish transfer
                if (clk_counter < SYMBOL_EDGE_TIME -1)
                    clk_counter <= clk_counter + 1;
                else begin
                  clk_counter <= 0;
                  serial_out_int <= shift_reg[0];
                  shift_reg <= {1'b1, shift_reg[9:1]};
                  bit_counter <= bit_counter + 1;

                    // finish transmitt
                  if (bit_counter == 9) // not 10!
                    transmitt_done <= 1;
                end 
        endcase
      end
    end
endmodule
