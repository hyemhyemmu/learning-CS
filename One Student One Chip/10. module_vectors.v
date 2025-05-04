module my_dff8 (
    input clk,                  // 时钟信号
    input [7:0] d,              // 8位数据输入
    output reg [7:0] q         // 8位数据输出
);

    always @(posedge clk) begin
        q <= d;  // 在时钟上升沿时，输出等于输入数据
    end

endmodule


module mux8to1 (
    input [7:0] d0, d1, d2, d3, d4, d5, d6, d7,  // 8个输入
    input [2:0] sel,                               // 选择信号，3位
    output [7:0] q                                 // 输出
);
    always @(*) begin
        case (sel)
            3'b000: q = d0;
            3'b001: q = d1;
            3'b010: q = d2;
            3'b011: q = d3;
            3'b100: q = d4;
            3'b101: q = d5;
            3'b110: q = d6;
            3'b111: q = d7;
            default: q = 8'b00000000;  // 默认值
        endcase
    end
endmodule


module top_module(
    input clk;
    input [7:0] d;
    input [1:0] sel;
    output [7:0] q;
);

wire [7:0] q1, q2, q3;

my_dff8 instance_1(
    .clk(clk);
    .d(d);
    .q(q1)
)

my_dff8 instance_2(
    .clk(clk);
    .d(q1);
    .q(q2)
)

my_dff8 instance_3(
    .clk(clk);
    .d(q2);
    .q(q3)
)

mux8to1 mux_inst (
        .d0(q0), .d1(q1), .d2(q2), .d3(8'b0), 
        .d4(8'b0), .d5(8'b0), .d6(8'b0), .d7(8'b0),
        .sel(sel), .q(q)
    );


endmodule
