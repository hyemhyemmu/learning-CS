// 一个简单的2状态FSM
module stateFSM(
  input clk,
  input rst,
  output reg[1:0] state
);

  parameter S0 = 2'b00, S1 = 2'b01;

  always @(posedge clk or posedge rst) begin
          if (rst) 
              state <= S0;  // 复位时跳到初始状态 S0
          else 
              state <= (state == S0) ? S1 : S0;  // 在 S0 时跳到 S1，反之亦然
      end


endmodule


// 加强版
module fsm_with_output (
    input clk,     
    input rst,    
    input in,       
    output reg [1:0] state,  
    output reg out         
);
    parameter S0 = 2'b00, S1 = 2'b01, S2 = 2'b10;

    always @(posedge clk or posedge rst) begin
        if (rst)
            state <= S0; 
        else begin
            case (state)
                S0: 
                    if (in) 
                        state <= S1;  
                    else 
                        state <= S2;  
                S1: 
                    if (!in) 
                        state <= S0;  
                    else 
                        state <= S2;  
                S2: 
                    state <= S0; 
                default: 
                    state <= S0; 
            endcase
        end
    end

    always @(state) begin
        case (state)
            S0: out = 1;  
            S1: out = 0;  
            S2: out = 1;  
            default: out = 0; 
        endcase
    end
endmodule
