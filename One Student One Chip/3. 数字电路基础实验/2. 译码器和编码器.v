// decoder
module decode24(x,en,y);
  input  [1:0] x;
  input  en;
  output reg [3:0]y;

  always @(x or en)
    if (en)
    begin
      case (x)
            2'd0 : y = 4'b0001;
            2'd1 : y = 4'b0010;
            2'd2 : y = 4'b0100;
            2'd3 : y = 4'b1000;
      endcase
    end
    else  y = 4'b0000;

endmodule


// 用for循环的更简洁的实现方式
module decode24_for(x,en,y);
  input  [1:0] x;
  input  en;
  output reg [3:0]y;
  
  integer i;
  
  always @(x or en)
  begin
    y = 4'b0000; // 默认输出为0
    
    if (en)
    begin
      for (i = 0; i < 4; i = i + 1)
      begin
        if (x == i)
          y[i] = 1'b1;
      end
    end
  end
  
endmodule



// encoder
module encode42(x,en,y);
  input  [3:0] x;
  input  en;
  output reg [1:0]y;

  always @(x or en) begin
    if (en) begin
      case (x)
          4'b0001 : y = 2'b00;
          4'b0010 : y = 2'b01;
          4'b0100 : y = 2'b10;
          4'b1000 : y = 2'b11;
          default: y = 2'b00;
      endcase
    end
    else  y = 2'b00;
  end
endmodule