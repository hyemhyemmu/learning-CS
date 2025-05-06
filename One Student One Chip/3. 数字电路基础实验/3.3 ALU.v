module ALU(
    input [2:0] sel,
    input [3:0] A,
    input [3:0] B,
    output reg[3:0] result,
    output zero,
    output overflow,
    output carrys
);

wire [3:0] add_result;
wire [3:0] sub_result;

assign carry = 0; // 初始化
assign overflow = 0;


always @(*) begin
    case(sel)
        3'b000: result = add_result; //输出一个四位二进制数
        3'b001: result = sub_result;
        3'b010: result = ~A;
        3'b011: result = A & B;                   
        3'b100: result = A | B;                   
        3'b101: result = A ^ B;
        3'b110: result = {3'b000, less_than};
        3'b111: result = {3'b000, (A==B)};

        default: result = 4'b0000;
    endcase 

end

// 加法
adder add__inst(
    .A(A),
    .B(B),
    .result(add_result),
    .overflow(overflow),
    .zero(zero),
    .carry(carry)
);

// 减法
adder sub__inst(
    .A(A),
    .B(~B),
    .result(add_result),
    .overflow(overflow),
    .zero(zero),
    .carry(carry)
);

// 比较大小，如果a小于b就输出1
assign less_than = (A[3] & ~B[3]) | // 首先判断符号位，然后只需要比较最好为
                ((A[3] == B[3]) &                
                   ((A[3]) ? (A[2:0] > B[2:0]) :   
                             (A[2:0] < B[2:0])));

endmodule


module adder(
    input [3:0] A,
    input [3:0] B,
    output [3:0] result,
    output overflow,
    output zero,
    output carry
);

wire [3:0] P, G;
wire [4:0] C;

assign P = A ^ B;
assign G = A & B; 

 genvar i;
    generate
        for (i = 0; i < 4; i = i + 1) begin : carry_loop
            assign C[i+1] = G[i] | (P[i] & C[i]);
        end
    endgenerate

    // 计算结果
    assign result = P ^ C[3:0];
    
    // 输出进位
    assign carry = C[4];
    
    // 溢出检测
    assign overflow = C[4] ^ C[3]; // 当最高位进位和次高位进位不同时，发生溢出
    
    // 零标志位
    assign zero = ~( | Result );

endmodule
