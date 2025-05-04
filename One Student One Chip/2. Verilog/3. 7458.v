module top_module (
    input wire [9:0] in,   // 10 个输入端口
    output wire p1y,       // 第一个输出端口
    output wire p2y        // 第二个输出端口
);

    // AND 门连接
    wire p1a, p1b, p1c, p1d, p1e, p1f;
    and (p1a, in[0], in[1]); // AND 门 1
    and (p1b, in[2], in[3]); // AND 门 2
    and (p1c, in[4], in[5]); // AND 门 3
    and (p1d, in[6], in[7]); // AND 门 4
    and (p1e, in[8], in[9]); // AND 门 5
    and (p1f, p1a, p1b);    // AND 门 6（组合AND）

    // OR 门连接
    wire p2a, p2b, p2c, p2d;
    or (p2a, in[0], in[1]);  // OR 门 1
    or (p2b, in[2], in[3]);  // OR 门 2
    or (p2c, p2a, p2b);      // OR 门 3（组合OR）

    // 输出
    assign p1y = p1f;  // 输出 1
    assign p2y = p2c;  // 输出 2

endmodule
