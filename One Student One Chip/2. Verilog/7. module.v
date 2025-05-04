module mod_a (
    input in1,        // 输入信号 in1
    input in2,        // 输入信号 in2
    output out        // 输出信号 out
);

assign out = in1 & in2;  
endmodule

module top_module (
    input wire a,      // 输入信号 a
    input wire b,      // 输入信号 b
    output wire out    // 输出信号 out
);

// 实例化 mod_a 模块
mod_a instance1 (
    .in1(a),    
    .in2(b),    
    .out(out)   
);

endmodule

