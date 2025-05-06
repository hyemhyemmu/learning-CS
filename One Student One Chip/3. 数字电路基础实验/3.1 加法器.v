// 一位加法器的实现
module full_adder(
    input A,
    input B,
    input Cin,
    output Sum,
    output Cout
);

    assign Sum = A ^ B ^ Cin; // 异或求和
    assign Cout = (A & B) | (Cin & (A ^ B));

endmodule


// 八位加法器 - 串行的多个一位加法器
module eight_bit_adder(
    input [7:0] A,
    input [7:0] B,
    input Cin,
    output [7:0] Sum,
    output Cout
)

wire [7:0] C;  // 存储每一位的进位输出

// 为每一位使用一个全加器
full_adder FA0 (
    .A(A[0]), .B(B[0]), .Cin(Cin), 
    .Sum(Sum[0]), .Cout(C[0])
);
full_adder FA1 (
    .A(A[1]), .B(B[1]), .Cin(C[0]), 
    .Sum(Sum[1]), .Cout(C[1])
);
full_adder FA2 (
    .A(A[2]), .B(B[2]), .Cin(C[1]), 
    .Sum(Sum[2]), .Cout(C[2])
);
full_adder FA3 (
    .A(A[3]), .B(B[3]), .Cin(C[2]), 
    .Sum(Sum[3]), .Cout(C[3])
);
full_adder FA4 (
    .A(A[4]), .B(B[4]), .Cin(C[3]), 
    .Sum(Sum[4]), .Cout(C[4])
);
full_adder FA5 (
    .A(A[5]), .B(B[5]), .Cin(C[4]), 
    .Sum(Sum[5]), .Cout(C[5])
);
full_adder FA6 (
    .A(A[6]), .B(B[6]), .Cin(C[5]), 
    .Sum(Sum[6]), .Cout(C[6])
);
full_adder FA7 (
    .A(A[7]), .B(B[7]), .Cin(C[6]), 
    .Sum(Sum[7]), .Cout(Cout)
);

endmodule


// 用for的抽象实现方式
module eight_bit_adder_for (
    input [7:0] A,    
    input [7:0] B,    
    input Cin,         
    output [7:0] Sum,  
    output Cout        
);

reg [7:0] Sum;    
reg Cout;         

integer i;        
reg carry;        

always @(*) begin
    carry = Cin;   
    Sum = 8'b0;    
    for (i = 0; i < 8; i = i + 1) begin
        // 逐位计算和
        Sum[i] = A[i] ^ B[i] ^ carry;  
        carry = (A[i] & B[i]) | (carry & (A[i] ^ B[i]));  
    end
    Cout = carry;  
end

endmodule


// 尝试进行并行优化： 避免进位的逐位传递
// 当前位是否会生成进位：只有两个都为1时
// 当前位是否会传播进位：只有当两个都为0时为否

// 加法器的优化
module adder (
    input [7:0] A,      
    input [7:0] B,      
    input Cin,          
    output [7:0] Sum,   
    output Cout         
);

wire [7:0] G, P; // 预测函数 空位
wire [7:0] C // 进位

assign G = A & B; // 都为1才可以
assign P = A | B; // 都为0才为真

assign C[0] = Cin;
assign C[1] = G[0] | (P[0] & Cin) // 前一个生成了进位 或者 前一位传播了进位
assign C[2] = G[1] | (P[1] & C[1]); 
assign C[3] = G[2] | (P[2] & C[2]); 
assign C[4] = G[3] | (P[3] & C[3]); 
assign C[5] = G[4] | (P[4] & C[4]); 
assign C[6] = G[5] | (P[5] & C[5]); 
assign C[7] = G[6] | (P[6] & C[6]); 


assign Sum = A ^ B ^ C
assign Cout = G[7] | (P[7] & C[7]);

endmodule