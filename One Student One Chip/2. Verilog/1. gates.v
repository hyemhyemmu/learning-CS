// not gate
module notGate (input in, output out);
assign out = ~in;
endmodule

// and gate
module andGate(input a, intput b, output out);
assign out = a & b;
endmodule

// nor gate
module norGate(input a, intput b, output out);
assign out = ~(a | b);
endmodule
