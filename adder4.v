//
module adder4 (
    input  logic [3:0] a,
    input  logic [3:0] b,
    output logic [3:0] sum,
    output logic       carry
);
  assign {carry, sum} = {1'b0, a} + {1'b0, b};
endmodule
