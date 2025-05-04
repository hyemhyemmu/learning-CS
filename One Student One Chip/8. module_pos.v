module mod_a (
    input in1,        
    input in2,       
    input in3,
    input in4,    
    output out1,
    output out2        
);

assign out1 = in1 & in2;  
assign out2 = in3 & in4;
endmodule

module top_module ( 
    input a, 
    input b, 
    input c,
    input d,
    output out1,
    output out2
);


mod_a instance_1 (
    .in1(a),
    .in2(b),
    .out1(out1),
    .out2(out2)
);

endmodule
