module ps2_arrow_keys(
    input [15:0] scancode,      // 16位输入扫描码
    output reg up,              // 向上箭头输出
    output reg down,            // 向下箭头输出
    output reg left,            // 向左箭头输出
    output reg right            // 向右箭头输出
);

    // 使用组合逻辑判断扫描码
    always @(*) begin
        // 默认所有输出为0，避免生成锁存器
        up = 1'b0; 
        down = 1'b0; 
        left = 1'b0; 
        right = 1'b0;
        
        // 检查扫描码并设置对应的输出
        case (scancode)
            16'he075: up = 1'b1;      // 向上箭头
            16'he072: down = 1'b1;    // 向下箭头
            16'he06b: left = 1'b1;    // 向左箭头
            16'he074: right = 1'b1;   // 向右箭头
            // 不需要default语句，因为已经为所有输出设置了默认值
        endcase
    end
    
endmodule