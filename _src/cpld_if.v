`timescale 1ns/1ps
`default_nettype none

module cpld_if(
  input  wire clk,
  input  wire rst,
  
  input  wire [7:0] led,
  input  wire [3:0] dig0,
  input  wire [3:0] dig1,
  output wire [7:0] sw,

  output wire cpld_rstn,
  output wire cpld_clk,
  output wire cpld_load,
  output wire cpld_mosi,
  input  wire cpld_miso
);

assign cpld_rstn = ~rst;


reg [14:0] cntr;
always @ (posedge clk)
	cntr <= cntr + 1;

wire dig_sel;
wire [3:0] bit_sel;
	

assign dig_sel  = cntr[14];
assign bit_sel  = cntr[13:10];
assign cpld_clk = cntr[9];

wire cpld_clk_fall;
assign cpld_clk_fall = (cntr[9:0] == 10'b1111111111);

wire [3:0] dig_mux;
assign dig_mux = (dig_sel) ? dig0 : dig1;

reg [7:0] seg_dec;
always @(dig_mux)
case (dig_mux)
	4'b0001 : seg_dec = 8'b11111001;   // 1
	4'b0010 : seg_dec = 8'b10100100;   // 2
	4'b0011 : seg_dec = 8'b10110000;   // 3
	4'b0100 : seg_dec = 8'b10011001;   // 4
	4'b0101 : seg_dec = 8'b10010010;   // 5
	4'b0110 : seg_dec = 8'b10000010;   // 6
	4'b0111 : seg_dec = 8'b11111000;   // 7
	4'b1000 : seg_dec = 8'b10000000;   // 8
	4'b1001 : seg_dec = 8'b10010000;   // 9
	4'b1010 : seg_dec = 8'b10001000;   // A
	4'b1011 : seg_dec = 8'b10000011;   // b
	4'b1100 : seg_dec = 8'b11000110;   // C
	4'b1101 : seg_dec = 8'b10100001;   // d
	4'b1110 : seg_dec = 8'b10000110;   // E
	4'b1111 : seg_dec = 8'b10001110;   // F
	default : seg_dec = 8'b11000000;   // 0
endcase


wire [15:0] bit_mux_in;
assign bit_mux_in = {~seg_dec, led};

assign cpld_load = (bit_sel==15);
assign cpld_mosi = bit_mux_in[bit_sel];


reg [15:0] miso_shr;
always @ (posedge clk)
if (cpld_clk_fall)
	miso_shr <= {cpld_miso, miso_shr[15:1]};

reg [15:0] miso_out_reg;
always @ (posedge clk)
if (cpld_clk_fall & cpld_load)
	miso_out_reg <= miso_shr;
	
assign sw = miso_out_reg[7:0];

endmodule
