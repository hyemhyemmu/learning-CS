module top_module (
    input [7:0] a, b, c, d,
    output [7:0] min);//

    // assign intermediate_result1 = compare? true: false;
    wire [7:0] mid1, mid2;

    assign mid1 = (a < b) ? a : b;
    assign mid2 = (c < d) ? c : d;
    assign min = (mid1 < mid2) ? mid1 : mid2;


endmodule
