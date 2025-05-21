// an example of FSM

module FSM1(
    input clk, rst;
    input in;
    output out;
);

// defines
parameter IDLE = 2'b00;
parameter S0 = 2'b10;
parameter S1 = 2'b01;
reg out;
reg[1:0] current_state, next_state;

always

// always block for state reg
always @ (posedge clk) begin
  if (rst) current_state <= IDLE;
  else current_state <= next_state; 
end

// always block for combinational logic
always @(*) begin
case(current_state)
    IDLE    : begin
      
            end




endcase
end

endmodule