//
module counter2 (
    input  logic       clk,
    input  logic       rst,
    input  logic       en,
    output logic [1:0] q
);
  timeunit 1ns; timeprecision 1ns;

  always_ff @(posedge clk) begin
    if (rst) q <= 2'd0;
    else if (en) q <= q + 2'd1;
  end
endmodule
