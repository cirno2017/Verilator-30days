//
module delayed_done (
    input  logic clk,
    input  logic rst,
    input  logic start,
    input  logic stall,
    output logic busy,
    output logic done
);
  timeunit 1ns; timeprecision 1ns;

  logic [1:0] remaining;

  always_ff @(posedge clk) begin
    if (rst) begin
      busy      <= 1'b0;
      done      <= 1'b0;
      remaining <= 2'd0;
    end else if (!busy) begin
      if (start) begin
        busy      <= 1'b1;
        done      <= 1'b0;
        remaining <= 2'd3;
      end
    end else if (!stall) begin
      if (remaining == 2'd1) begin
        remaining <= 2'd0;
        busy      <= 1'b0;
        done      <= 1'b1;
      end else begin
        remaining <= remaining - 2'd1;
      end
    end
  end
endmodule
