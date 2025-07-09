module mem_controller #(
  parameter FIFO_WIDTH = 8
) (
  input clk,
  input rst,
  input rx_fifo_empty,
  input tx_fifo_full,
  input [FIFO_WIDTH-1:0] din,

  output rx_fifo_rd_en,
  output tx_fifo_wr_en,
  output [FIFO_WIDTH-1:0] dout,
  output [5:0] state_leds
);

  localparam MEM_WIDTH = 8;
  localparam MEM_DEPTH = 256;
  localparam NUM_BYTES_PER_WORD = MEM_WIDTH / 8;
  localparam MEM_ADDR_WIDTH = $clog2(MEM_DEPTH);

  reg [NUM_BYTES_PER_WORD-1:0] mem_we = 0;
  reg [MEM_ADDR_WIDTH-1:0] mem_addr;
  reg [MEM_WIDTH-1:0] mem_din;
  wire [MEM_WIDTH-1:0] mem_dout;

  memory #(
    .MEM_WIDTH(MEM_WIDTH),
    .DEPTH(MEM_DEPTH)
  ) mem (
    .clk(clk),
    .en(1'b1),
    .we(mem_we),
    .addr(mem_addr),
    .din(mem_din),
    .dout(mem_dout)
  );

  localparam 
    IDLE            = 3'd0,
    READ_CMD        = 3'd1,
    READ_ADDR       = 3'd2,
    READ_DATA       = 3'd3,
    READ_MEM_VAL    = 3'd4,
    ECHO_VAL        = 3'd5,
    WRITE_MEM_VAL   = 3'd6;

  reg [2:0] curr_state;
  reg [2:0] next_state;

  always @(posedge clk) begin
    if (rst)
      curr_state <= IDLE;
    else
      curr_state <= next_state;
  end

  reg [2:0] pkt_rd_cnt;
  reg [MEM_WIDTH-1:0] cmd;
  reg [MEM_WIDTH-1:0] addr;
  reg [MEM_WIDTH-1:0] data;

  // Output regs
  reg rx_fifo_rd_en_reg;
  reg tx_fifo_wr_en_reg;
  reg [FIFO_WIDTH-1:0] dout_reg;

  // Connect regs to outputs
  assign rx_fifo_rd_en = rx_fifo_rd_en_reg;
  assign tx_fifo_wr_en = tx_fifo_wr_en_reg;
  assign dout = dout_reg;

  // State LED display
  assign state_leds = 6'b1 << curr_state;

  // State transition logic
  always @(*) begin
    next_state = curr_state;

    case (curr_state)
      IDLE: begin
        if (!rx_fifo_empty)
          next_state = READ_CMD;
      end

      READ_CMD: begin
        if (!rx_fifo_empty)
          next_state = READ_ADDR;
      end

      READ_ADDR: begin
        if (cmd == 8'd48) // '0' read
          next_state = READ_MEM_VAL;
        else if (cmd == 8'd49) // '1' write
          next_state = READ_DATA;
      end

      READ_DATA: begin
        if (!rx_fifo_empty)
          next_state = WRITE_MEM_VAL;
      end

      WRITE_MEM_VAL: begin
        next_state = IDLE;
      end

      READ_MEM_VAL: begin
        next_state = ECHO_VAL;
      end

      ECHO_VAL: begin
        if (!tx_fifo_full)
          next_state = IDLE;
      end
    endcase
  end

  // Output & memory control logic
  always @(*) begin
    // default values
    rx_fifo_rd_en_reg = 0;
    tx_fifo_wr_en_reg = 0;
    dout_reg = 8'd0;
    mem_we = 0;
    mem_din = 0;
    mem_addr = 0;

    case (curr_state)

      READ_CMD, READ_ADDR, READ_DATA: begin
        rx_fifo_rd_en_reg = 1;
      end

      READ_MEM_VAL: begin
        mem_addr = addr;
      end

      ECHO_VAL: begin
        if (!tx_fifo_full) begin
          dout_reg = mem_dout;
          tx_fifo_wr_en_reg = 1;
        end
      end

      WRITE_MEM_VAL: begin
        mem_addr = addr;
        mem_din = data;
        mem_we = 1;
      end

    endcase
  end

  // Data capture
  always @(posedge clk) begin
    if (rst) begin
      pkt_rd_cnt <= 0;
      cmd <= 0;
      addr <= 0;
      data <= 0;
    end else begin
      case (curr_state)

        READ_CMD: begin
          if (!rx_fifo_empty)
            cmd <= din;
        end

        READ_ADDR: begin
          if (!rx_fifo_empty)
            addr <= din;
        end

        READ_DATA: begin
          if (!rx_fifo_empty)
            data <= din;
        end

      endcase
    end
  end

endmodule
