module structural_adder (
    input [13:0] a,
    input [13:0] b,
    output [14:0] sum
);

    wire [14:0] carry; 
    assign carry[0] = 1'b0;

    genvar i;
    generate
        for (i = 0; i < 14; i++) begin: adder_stage
            full_adder fa (
                .a(a[i]),
                .b(b[i]),
                .carry_in(carry[i]),
                .sum(sum[i]),
                .carry_out(carry[i+1])
            );
        end
    endgenerate

    assign sum[14] = carry[14]
endmodule
