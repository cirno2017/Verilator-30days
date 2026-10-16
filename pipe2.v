//
module pipe2 (
    input  logic       clk,
    input  logic       rst,
    input  logic       in_valid,
    input  logic [7:0] in_data,
    output logic       out_valid,
    output logic [7:0] out_data
);
  timeunit 1ns; timeprecision 1ns;

  logic       stage_valid;
  logic [7:0] stage_data;

  always_ff @(posedge clk) begin
    if (rst) begin
      stage_valid <= 1'b0;
      // stage_valid <= in_valid;
      stage_data  <= '0;
      out_valid   <= 1'b0;
      out_data    <= '0;
    end else begin
      stage_valid <= in_valid;
      if (in_valid) stage_data <= in_data + 8'd1;

      out_valid <= stage_valid;
      if (stage_valid) out_data <= stage_data;
    end
  end
endmodule
