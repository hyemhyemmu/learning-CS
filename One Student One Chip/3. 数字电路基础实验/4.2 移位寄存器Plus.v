module shift_reg(
    input[2:0] sel,
    input[7:0] in,
    input clk,
    input in_bit, //串行输入位
    output reg [7:0] out
);

always @(posedge clk) begin
    case(sel)
        3'b000: out <= 8'b00000000;         
        3'b001: out <= in;                  
        3'b010: out <= out >> 1;            
        3'b011: out <= out << 1;            
        3'b100: out <= out >>> 1;           
        3'b101: out <= {in_bit, out[7:1]}; 
        3'b110: out <= {out[0], out[7:1]};  
        3'b111: out <= {out[6:0], out[7]};  
        default: out <= out;               
    endcase
end

endmodule
