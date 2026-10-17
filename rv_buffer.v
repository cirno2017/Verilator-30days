//
module rv_buffer (
    input logic clk,
    input logic rst,

    input  logic       in_valid,
    output logic       in_ready,
    input  logic [7:0] in_data,

    output logic       out_valid,
    input  logic       out_ready,
    output logic [7:0] out_data
);
  timeunit 1ns; timeprecision 1ns;

  assign in_ready = !out_valid || out_ready;

  always_ff @(posedge clk) begin
    if (rst) begin
      out_valid <= 1'b0;
      out_data  <= '0;
    end else if (in_ready) begin
      // end else if (in_ready || in_valid) begin
      out_valid <= in_valid;
      if (in_valid) out_data <= in_data;
    end
  end
endmodule
