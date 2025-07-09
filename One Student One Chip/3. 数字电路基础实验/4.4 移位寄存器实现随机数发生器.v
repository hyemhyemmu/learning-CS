module LSFR(
    input [7:0] in,
    input button,
    output reg [7:0] out
);

reg newDigit;

always @(posedge button ) begin
    case(in)
        8'b00000000: out = 8'b00000001;
        default: begin
            newDigit = in[4] ^ in[3] ^ in[2] ^ in[0];
            out <= {newDigit, in[7:1]};
        end
    endcase
end

endmodule