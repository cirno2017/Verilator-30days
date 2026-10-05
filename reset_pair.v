//
module reset_pair (
    input  logic       clk,
    input  logic       rst_sync,
    input  logic       rst_async,
    input  logic [3:0] d,
    output logic [3:0] q_sync,
    output logic [3:0] q_async
);
  timeunit 1ns; timeprecision 1ns;

  always_ff @(posedge clk) begin
    if (rst_sync) q_sync <= 4'd0;
    else q_sync <= d;
  end

  always_ff @(posedge clk or posedge rst_async) begin
    if (rst_async) q_async <= 4'd0;
    else q_async <= d;
  end
endmodule
