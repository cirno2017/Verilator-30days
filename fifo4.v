//
module fifo4 (
    input logic clk,
    input logic rst,

    input  logic       in_valid,
    output logic       in_ready,
    input  logic [7:0] in_data,

    output logic       out_valid,
    input  logic       out_ready,
    output logic [7:0] out_data,

    output logic [2:0] level
);
  timeunit 1ns; timeprecision 1ns;

  logic [7:0] mem[4];
  logic [1:0] wr_ptr, rd_ptr;
  logic [2:0] count;
  logic push, pop;

  assign in_ready  = count < 3'd4;
  assign out_valid = count != 3'd0;
  assign out_data  = out_valid ? mem[rd_ptr] : 8'h00;
  assign level     = count;

  assign push      = in_valid && in_ready;
  assign pop       = out_valid && out_ready;

  always_ff @(posedge clk) begin
    if (rst) begin
      wr_ptr <= '0;
      rd_ptr <= '0;
      count  <= '0;
    end else begin
      if (push) begin
        mem[wr_ptr] <= in_data;
        // mem[wr_ptr] <= in_data ^ 8'h01;
        wr_ptr <= wr_ptr + 2'd1;
      end

      if (pop) rd_ptr <= rd_ptr + 2'd1;

      case ({
        push, pop
      })
        2'b10:   count <= count + 3'd1;
        2'b01:   count <= count - 3'd1;
        default: count <= count;
      endcase
    end
  end
endmodule
