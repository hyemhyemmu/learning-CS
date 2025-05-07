// 桶形移位器

// 这是一个抽象化的，利用条件判断构建的移位器，理解起来更简单
module barrel_shifter_abstract(
    input[7:0] din,
    input[2:0] shamt, // 移位位数
    input LR, // 左右方向
    input AL, // 移位类型 A算术L逻辑
    output[7:0] dout
);

always @(*) begin
        if (LR == 0) begin  // 向左移位
            if (AL == 0) begin  // 逻辑左移
                dout = din << shamt;
            end else begin  // 算术左移
                dout = din << shamt;
            end
        end else begin  // 向右移位
            if (AL == 0) begin  // 逻辑右移
                dout = din >> shamt;
            end else begin  // 算术右移
                dout = $signed(din) >>> shamt;
            end
        end
end

endmodule


// 一个更“硬件”的桶形寄存器
module barrel_shifter(
    input [7:0] din,        
    input [2:0] shamt,      
    input LR,               
    input AL,               
    output reg [7:0] dout  
);

    wire [7:0] stage_1, stage_2, stage_3, stage_4;

    // 第一阶段 移动1位
    assign stage_1 = (shamt[0] == 1) ? (LR ? din >> 1 : din << 1) : din;

    // 第二阶段 移动2位
    assign stage_2 = (shamt[1] == 1) ? (LR ? stage_1 >> 2 : stage_1 << 2) : stage_1;

    // 第三阶段 移动4位
    assign stage_3 = (shamt[2] == 1) ? (LR ? stage_2 >> 4 : stage_2 << 4) : stage_2;

    // 输出最终移位结果
    assign dout = stage_3;

endmodule
