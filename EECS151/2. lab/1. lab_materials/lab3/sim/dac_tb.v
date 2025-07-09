`timescale 1ns/1ns
`define CLK_PERIOD 8

module dac_tb();
    // Generate 125 Mhz clock
    reg clk = 0;
    always #(`CLK_PERIOD/2) clk = ~clk;

    // I/O
    reg [2:0] code;
    wire pwm, next_sample;

    dac #(.CYCLES_PER_WINDOW(8)) DUT (
        .clk(clk),
        .code(code),
        .pwm(pwm),
        .next_sample(next_sample)
    );

    initial begin
        `ifdef IVERILOG
            $dumpfile("dac_tb.fst");
            $dumpvars(0, dac_tb);
        `endif
        `ifndef IVERILOG
            // $vcdpluson;
        `endif

        fork
            // Thread to drive code and check output
            begin
                code = 0;
                #1;
                repeat (7) begin
                    if (pwm != 0) begin
                        $display("ERROR: pwm should be 0 when code is 0");
                        $finish;
                    end
                    @(posedge clk); #1;
                end
                if (pwm != 0) begin
                    $display("ERROR: pwm should be 0 when code is 0");
                    $finish;
                end

                code = 7;
                @(posedge clk); #1;
                repeat (7) begin
                    if (pwm != 1) begin
                        $display("ERROR: pwm should be 1 when code is 7");
                        $finish;
                    end
                    @(posedge clk); #1;
                end
                if (pwm != 1) begin
                    $display("ERROR: pwm should be 1 when code is 7");
                    $finish;
                end

                repeat (2) begin
                    code = 3;
                    repeat (4) begin
						@(posedge clk); #1;
		                if (pwm != 1) begin
                            $display("ERROR: pwm should be 1 on first half of code = 3");
                            $finish;
                        end
					end
                    repeat (4) begin
						@(posedge clk); #1;
					    if (pwm != 0) begin
                            $display("ERROR: pwm should be 0 on second half of code = 3");
                            $finish;
                        end
					end
                end

                repeat (2) begin
                    code = 2;
                    repeat (3) begin
						@(posedge clk); #1;
		                if (pwm != 1) begin
                            $display("ERROR: pwm should be 1 on first part of code = 2");
                            $finish;
                        end
					end
                    repeat (5) begin
						@(posedge clk); #1;
					    if (pwm != 0) begin
                            $display("ERROR: pwm should be 0 on second part of code = 2");
                            $finish;
                        end
					end
                end
            end
            // Thread to check next_sample
            begin
                repeat (6) begin
                    if (next_sample != 0) begin
                        $display("ERROR: next_sample should start at 0");
                        $finish;
                    end
                    repeat (7) @(posedge clk); #1;
                    if (next_sample != 1) begin
                        $display("ERROR: next_sample should become 1 after 7 cycles");
                        $finish;
                    end
                    @(posedge clk); #1;
                    if (next_sample != 0) begin
                        $display("ERROR: next_sample should go back to 0 on the 8th cycle");
                        $finish;
                    end
                end
            end
        join

        $display("Test finished");

        `ifndef IVERILOG
            // $vcdplusoff;
        `endif
        $finish();
    end
endmodule
