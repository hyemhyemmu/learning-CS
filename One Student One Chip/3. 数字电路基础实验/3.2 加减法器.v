// 一个简单的加减法器
// 输入信号有：两个32位的参与运算的数据的补码操作数A和操作数B，
// 一个控制做加法还是做减法的加/减控制端Sub/Add，为1时进行减法运算。
// 输出信号有：一个32位的结果Result、一位进位位，一位溢出位和一位判断结果是否为零的输出位。
module simALU(
    input [31:0] A,
    input [31:0] B,
    input sign,
    output [31:0] result,
    output overflow,
    output zero,
    output carry
);

wire [31:0] B_input; //处理加减法
wire [31:0] P, G;
wire [32:0] C;

assign B_input = sign ? ~B : B; // sign为1
assign P = A ^ B_input;
assign G = A & B_input; 

 genvar i;
    generate
        for (i = 0; i < 32; i = i + 1) begin : carry_loop
            assign C[i+1] = G[i] | (P[i] & C[i]);
        end
    endgenerate

    // 计算结果
    assign result = P ^ C[31:0];
    
    // 输出进位
    assign carry = C[32];
    
    // 溢出检测
    assign overflow = C[32] ^ C[31]; // 当最高位进位和次高位进位不同时，发生溢出
    
    // 零标志位
    assign zero = ~( | Result );

endmodule
