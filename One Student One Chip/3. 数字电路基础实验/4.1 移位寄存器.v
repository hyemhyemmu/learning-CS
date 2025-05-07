module shift_reg_mini(
    input D,
    input clk,
    output [3:0] Q
);

reg [3:0] shift_reg;

always @(posedge clk) begin
   shift_reg <= {shift_reg[2:0], D}; 
end

assign Q = shift_reg;

endmodule