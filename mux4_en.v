//
module mux4_en (
    input  logic [3:0] a,
    input  logic [3:0] b,
    input  logic       en,
    input  logic       sel,
    output logic [3:0] y
);
  assign y = en ? (sel ? b : a) : 4'b0000;
endmodule
