module edge_detector #(
    parameter WIDTH = 1
)(
    input clk,
    input [WIDTH-1:0] signal_in,
    output [WIDTH-1:0] edge_detect_pulse
);
    // implement a multi-bit edge detector that detects a rising edge of 'signal_in[x]'
    // and outputs a one-cycle pulse 'edge_detect_pulse[x]' at the next clock edge

    reg [WIDTH-1:0] signal_prev;
    
    always @(posedge clk) begin
        signal_prev <= signal_in;
    end
    
    // detect: curr = 1, prev = 0
    assign edge_detect_pulse = signal_in & ~signal_prev;
    
endmodule
