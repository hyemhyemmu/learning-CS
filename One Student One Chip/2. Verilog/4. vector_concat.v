// vector concat practice
module top_module(
    input [4:0] a, b, c, d, e, f,
    output [7:0] w, x, y, z
);

wire [29:0] input_signal;
assign input_signal = {a, b, c, d, e, f};

assign w = input_signals[7:0];       
assign x = input_signals[15:8];      
assign y = input_signals[23:16];     
assign z = input_signals[29:24];

endmodule