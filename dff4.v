//
module dff4 (
    input  logic       clk,
    input  logic [3:0] d,
    output logic [3:0] q
);
  timeunit 1ns; timeprecision 1ns;

  always_ff @(posedge clk) begin
    q <= d;
  end
endmodule
