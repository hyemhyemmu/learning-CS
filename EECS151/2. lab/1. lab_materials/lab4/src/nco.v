module nco(
    input clk,
    input rst,
    input [23:0] fcw,
    input next_sample,
    output reg [9:0] code
);
    reg [23:0] phase_accumulator;
    reg [9:0] sine_lut [0:255];

    initial begin
        $readmemb("sine.bin", sine_lut);
    end

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            phase_accumulator <= 24'd0;
            code <= sine_lut[0];
        end else begin
            if (next_sample) begin
                code <= sine_lut[phase_accumulator[23:16]];
                phase_accumulator <= phase_accumulator + fcw;
            end
        end
    end
endmodule
