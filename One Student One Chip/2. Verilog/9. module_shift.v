module my_dff (
    input clk,    // 时钟信号
    input d,      // 数据输入
    output q      // 输出信号
);
    // D触发器的行为
    always @(posedge clk) begin
        q <= d;    // 在时钟上升沿时，将d值赋给q
    end
endmodule


module top_module (
    input clk,    // 时钟信号
    input d,      // 数据输入
    output q      // 最终输出信号
);
    // 声明中间的 wire 信号用于连接各个 D 触发器的输出
    wire q1, q2;

    // 实例化三个 D 触发器
    my_dff dff1 (
        .clk(clk),   // 连接时钟信号
        .d(d),       // 连接数据输入
        .q(q1)       // 连接第一个触发器的输出
    );

    my_dff dff2 (
        .clk(clk),   // 连接时钟信号
        .d(q1),      // 连接前一个触发器的输出
        .q(q2)       // 连接第二个触发器的输出
    );

    my_dff dff3 (
        .clk(clk),   // 连接时钟信号
        .d(q2),      // 连接前一个触发器的输出
        .q(q)        // 将最终输出连接到 q
    );

endmodule
