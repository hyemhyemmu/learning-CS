module fcw_ram(
    input clk,
    input rst,
    input rd_en,
    input wr_en,
    input [1:0] addr,
    input [23:0] d_in,
    output reg [23:0] d_out
);
    reg [23:0] ram [3:0];

    always @(posedge clk) begin
        if (rst) begin
            ram[0] <= 24'd60474; // A4 (440 Hz)
            ram[1] <= 24'd67896; // B4 (494 Hz)
            ram[2] <= 24'd71884; // C5 (523 Hz)
            ram[3] <= 24'd80644; // D5 (587 Hz)
        end
        else if (wr_en)
            ram[addr] <= d_in;
    end

    always @(posedge clk) begin
        if (rd_en) begin
            d_out <= ram[addr];
        end
    end
endmodule
