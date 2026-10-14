//
module counter_param #(
    parameter int unsigned WIDTH = 4
) (
    input  logic             clk,
    input  logic             rst,
    input  logic             en,
    output logic [WIDTH-1:0] q,
    output logic [      7:0] width_tag
);
  timeunit 1ns; timeprecision 1ns;

  assign width_tag = 8'(WIDTH);

  always_ff @(posedge clk) begin
    if (rst) q <= '0;
    else if (en) q <= q + WIDTH'(1);
  end
endmodule
