module barrel_shifter(
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
