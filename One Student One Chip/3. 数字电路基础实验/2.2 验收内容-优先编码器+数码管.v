//  实现一个8-3优先编码器并在七段数码管上显示。
//  编码结果及指示位以二进制形式显示在四个发光二极管LED上。
//  再将此结果跟据七段数码管的显示进行译码，
//  将二进制的优先编码结果以十进制的形式显示在数码管上。

// 8-3优先编码器
// 输入一个8位二进制数，对此8位二进制数进行高位优先编码
// 成一个3位二进制值，并根据是否有输入增加一位输入指示位
module encoder83 (
    input [7:0] in,
    output reg [3:0] out
);

always @(*) begin
    casez (in)
        8'b1xxxxxxx: out = 4'b1001;
        8'b01xxxxxx: out = 4'b1010;
        8'b001xxxxx: out = 4'b1011;
        8'b0001xxxx: out = 4'b1100;
        8'b00001xxx: out = 4'b1101;
        8'b000001xx: out = 4'b1110;
        8'b0000001x: out = 4'b1111;
        8'b00000001: out = 4'b1000;
        default: out = 4'b0000; // 无输入
    endcase

end

endmodule

// 七段数码管编码的模块接口
// 七段数码管编码的模块接口
module bcd7seg(
  input  [3:0] b,
  output reg [6:0] h
);

  // h[6:0] 对应 gfedcba 七段数码管
  // 假设 0 表示点亮，1 表示熄灭
  
  always @(*) begin
    case(b)
      4'b0000: h = 7'b1000000; // 0
      4'b0001: h = 7'b1111001; // 1
      4'b0010: h = 7'b0100100; // 2
      4'b0011: h = 7'b0110000; // 3
      4'b0100: h = 7'b0011001; // 4
      4'b0101: h = 7'b0010010; // 5
      4'b0110: h = 7'b0000010; // 6
      4'b0111: h = 7'b1111000; // 7
      4'b1000: h = 7'b0000000; // 8
      4'b1001: h = 7'b0010000; // 9
      4'b1010: h = 7'b0001000; // A
      4'b1011: h = 7'b0000011; // b
      4'b1100: h = 7'b1000110; // C
      4'b1101: h = 7'b0100001; // d
      4'b1110: h = 7'b0000110; // E
      4'b1111: h = 7'b0001110; // F
      default: h = 7'b1111111; // 全灭
    endcase
  end

endmodule


// 顶层组装模块
module top_module(
    input [7:0] SW, // 8个开关输入 - 进入编码器
    output [3:0] LED, // 连接4个LED灯
    output [6:0] HEX // 连接7段数码管
 );

    wire [3:0] encoder_out;

    encoder83 encoder_inst(
        .in(SW),
        .out(encoder_out)
    );

    assign LED = encoder_out;

    bcd7seg seg_inst(
        .b(encoder_out),
        .h(HEX)
    );

endmodule
