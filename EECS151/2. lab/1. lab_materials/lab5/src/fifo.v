module fifo #(
    parameter WIDTH = 8,
    parameter DEPTH = 32,
    parameter POINTER_WIDTH = $clog2(DEPTH)
) (
    input clk, rst,

    // Write side
    input wr_en,
    input [WIDTH-1:0] din,
    output full,

    // Read side
    input rd_en,
    output reg [WIDTH-1:0] dout,
    output empty
);
    
    reg [WIDTH-1:0] buffer [0:DEPTH-1];
    reg [POINTER_WIDTH-1:0] write_ptr, read_ptr;
    reg [POINTER_WIDTH:0] fifo_count; 

    always @ (posedge clk) begin
        if (rst) begin
            write_ptr <= 0;
            read_ptr <= 0;
            fifo_count <= 0;
            dout <= 0;
        end else begin
            if (wr_en && !full) begin
                buffer[write_ptr] <= din;
                write_ptr <= write_ptr + 1;
                fifo_count <= fifo_count + 1;
            end
            if (rd_en && !empty) begin
                dout <= buffer[read_ptr];
                read_ptr <= read_ptr + 1;
                fifo_count <= fifo_count - 1;
            end
        end
    end 

    assign empty = !fifo_count;
    assign full = (fifo_count == DEPTH);

endmodule
