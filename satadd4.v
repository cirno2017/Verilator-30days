//
module satadd4 (
    input  logic [3:0] a,
    input  logic [3:0] b,
    input  logic       sat_en,
    output logic [3:0] y,
    output logic       overflow
);
  logic [4:0] total;

  assign total = {1'b0, a} + {1'b0, b};
  assign overflow = total[4];

  always_comb begin
    if (sat_en && (total > 5'd15)) y = 4'd15;
    else y = total[3:0];
  end
endmodule
