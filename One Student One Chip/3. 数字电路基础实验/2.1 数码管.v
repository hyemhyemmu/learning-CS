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


// 模块实例化
// 举例：把cpubgdata[23:20]作为输入，输出是HEX5。bcd7seg作为一个类似于转换器的操作
bcd7seg seg5(cpubgdata[23:20],HEX5); 
bcd7seg seg4(cpubgdata[19:16],HEX4);
bcd7seg seg3(cpubgdata[15:12],HEX3);
bcd7seg seg2(cpubgdata[11:8],HEX2);
bcd7seg seg1(cpubgdata[7:4],HEX1);
bcd7seg seg0(cpubgdata[3:0],HEX0);
