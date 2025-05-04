// 一个wire的例子
module top_module(
    input a,
    input b,
    input c,
    input d,
    output out,
    output out_n    ); 

wire or_in_1;
wire or_in_2;
wire or_out;

assign or_in_1 = a & b;
assign or_in_2 = c & d;

assign or_out = or_in_1 | or_in_2;
assign out = or_out;
assign out_n = ~or_out;

endmodule