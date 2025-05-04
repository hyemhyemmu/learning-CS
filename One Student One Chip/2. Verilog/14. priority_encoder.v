module top_module (
    input [3:0] in,
    output reg [1:0] pos  );

always @(*) begin
    casez(in)
        4'b???1: pos = 2'd0;  // 最低位(bit 0)为1时，输出位置0
        4'b??10: pos = 2'd1;  // bit 0为0，bit 1为1时，输出位置1
        4'b?100: pos = 2'd2;  // bit 1,0为0，bit 2为1时，输出位置2
        4'b1000: pos = 2'd3;  // 只有最高位(bit 3)为1时，输出位置3
        default: pos = 2'd0;  // 全为0的情况，输出0
    endcase
end

endmodule


// 只用case的做法
module top_module (
	input [3:0] in,
	output reg [1:0] pos
);

	always @(*) begin			// Combinational always block
		case (in)
			4'h0: pos = 2'h0;	// I like hexadecimal because it saves typing.
			4'h1: pos = 2'h0;
			4'h2: pos = 2'h1;
			4'h3: pos = 2'h0;
			4'h4: pos = 2'h2;
			4'h5: pos = 2'h0;
			4'h6: pos = 2'h1;
			4'h7: pos = 2'h0;
			4'h8: pos = 2'h3;
			4'h9: pos = 2'h0;
			4'ha: pos = 2'h1;
			4'hb: pos = 2'h0;
			4'hc: pos = 2'h2;
			4'hd: pos = 2'h0;
			4'he: pos = 2'h1;
			4'hf: pos = 2'h0;
			default: pos = 2'b0;	// Default case is not strictly necessary because all 16 combinations are covered.
		endcase
	end
		
endmodule
