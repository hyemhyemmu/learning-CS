// 1位全加器
module add1(
    input a, b, cin,
    output sum, cout
);
    assign sum = a ^ b ^ cin;
    assign cout = (a & b) | (a & cin) | (b & cin);
endmodule

// 16位加法器
module add16(
    input [15:0] a, b,
    input cin,
    output [15:0] sum,
    output cout
);
    wire [15:0] internal_cout;
    
    // 第一个1位全加器
    add1 adder0(
        .a(a[0]),
        .b(b[0]),
        .cin(cin),
        .sum(sum[0]),
        .cout(internal_cout[0])
    );
    
    // 剩余的1位全加器
    genvar i;
    generate
        for(i = 1; i < 16; i = i + 1) begin : gen_adders
            add1 adder(
                .a(a[i]),
                .b(b[i]),
                .cin(internal_cout[i-1]),
                .sum(sum[i]),
                .cout(internal_cout[i])
            );
        end
    endgenerate
    
    // 最终进位输出
    assign cout = internal_cout[15];
endmodule

// 32位顶层模块
module top_module(
    input [31:0] a, b,
    output [31:0] sum
);
    wire cout_low; // 低16位的进位输出
    
    // 低16位加法器
    add16 low_adder(
        .a(a[15:0]),
        .b(b[15:0]),
        .cin(1'b0),
        .sum(sum[15:0]),
        .cout(cout_low)
    );
    
    // 高16位加法器
    add16 high_adder(
        .a(a[31:16]),
        .b(b[31:16]),
        .cin(cout_low),
        .sum(sum[31:16]),
        .cout() // 最高位进位不使用
    );
endmodule
