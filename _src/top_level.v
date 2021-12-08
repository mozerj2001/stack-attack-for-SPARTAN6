`timescale 1ns/1ps
`default_nettype none


module top_level(
  input  wire clk50M,
  input  wire rstbt,
  
  input  wire [2:0] bt,
  
  output wire cpld_jtagen,
  output wire cpld_rstn,
  output wire cpld_clk,
  output wire cpld_load,
  output wire cpld_mosi,
  input  wire cpld_miso,
  
  output wire spi_sdcard_csn,
  output wire spi_flash_csn,
  output wire spi_lcd_csn,
  
  // VGA controller outputs
  output wire r0,
  output wire r1,
  output wire g0,
  output wire g1,
  output wire b0,
  output wire b1,
  
  output wire hsync,
  output wire vsync,
  output wire BLANK
  
);

assign cpld_jtagen = 1'b0;
assign spi_sdcard_csn = 1'b1;
assign spi_flash_csn = 1'b1;
assign spi_lcd_csn = 1'b1;


wire clk;
wire rst;
wire M_APB_PRESETN;
wire [31:0] M_APB_PADDR;
wire M_APB_PSEL;
wire M_APB_PENABLE;
wire M_APB_PWRITE;
wire [31:0] M_APB_PWDATA;
wire M_APB_PREADY;
reg [31:0] M_APB_PRDATA;		// reg, hogy multiplexálhassunk vele, de így is kombinációs lesz
wire M_APB_PSLVERR;
wire [7:0] led;
wire [7:0] sw;

assign M_APB_PSLVERR = 1'b0;

wire apb_write;
// APB bus has selected the chip, enabled the chip and has an active write signal.
assign apb_write = M_APB_PSEL & M_APB_PENABLE & M_APB_PWRITE;	
// APB bus is ready to interact when it has selected the periphery and enabled it.	
assign M_APB_PREADY = M_APB_PSEL & M_APB_PENABLE;

reg [3:0] dig[1:0];

// regiszterírás (digitek címtartományának kiválasztása)
always @ (posedge clk)
begin
	if(apb_write == 1'b1 & M_APB_PADDR[30:14] == 0)
	begin
		dig[0] <= M_APB_PWDATA[3:0];
	end
	if(apb_write == 1'b1 & M_APB_PADDR[30:14] == 1)
	begin
		dig[1] <= M_APB_PWDATA[3:0];
	end
end

// címdekódoló multiplexer leírása
always @ (*)
case(M_APB_PADDR[30:14])
	17'h0: M_APB_PRDATA <= {28'b0, dig[0]};
	17'h1: M_APB_PRDATA <= {28'b0, dig[1]};
	default: M_APB_PRDATA <= 32'b0;
endcase


assign rst = ~rstbt;
cpu_subsys cpu_subsys_i
(
    .rst_n          (rstbt),
    .clk            (clk50M),
    .M_APB_PCLK     (clk),
    .M_APB_PRESETN  (M_APB_PRESETN),
    .M_APB_PADDR    (M_APB_PADDR),
    .M_APB_PSEL     (M_APB_PSEL),
    .M_APB_PENABLE  (M_APB_PENABLE),
    .M_APB_PWRITE   (M_APB_PWRITE),
    .M_APB_PWDATA   (M_APB_PWDATA),
    .M_APB_PREADY   (M_APB_PREADY),
    .M_APB_PRDATA   (M_APB_PRDATA),
    .M_APB_PSLVERR  (M_APB_PSLVERR),
    .led            (led),
    .sw             (sw)
);

cpld_if cpld_if_i(
  .clk              (clk),
  .rst              (rst),
  .led              (led),
  .dig0             (dig[0]),
  .dig1             (dig[1]),
  .sw               (sw),
  .cpld_rstn        (cpld_rstn),
  .cpld_clk         (cpld_clk),
  .cpld_load        (cpld_load),
  .cpld_mosi        (cpld_mosi),
  .cpld_miso        (cpld_miso)
);

// Create input and output signals from the APB bus signals
// for the VGA controller.


wire [5:0] dout;				// to VGA pins
wire write_enable;			// from processor to VGA controller
 
// Write frame buffer if the bus is in write mode and the Frame Buffer's memory address is selected.
assign write_enable = (apb_write == 1'b1) & (M_APB_PADDR[30:17] == 1);


vga_controller vga_ctrl(
    .rst					(rst),
    .clk					(clk),
	 // syn signal ports
	 .hsync				(hsync),
	 .vsync				(vsync),
	 .BLANK				(BLANK),
	 //.h_end				(h_end),

	 .dout				(dout),
	 
	 .write_enable		(write_enable),
	 .din					(M_APB_PWDATA[5:0]),
	 .din_address		(M_APB_PADDR[16:2])
    );
	 
// assign outputs to wires to pins
reg [5:0] top_dout;
always @ (posedge clk)
begin
	if(~BLANK)
		top_dout <= dout;
	else
		top_dout <= 6'h0;
end
	
assign b0 = top_dout[5];
assign b1 = top_dout[4];
assign g0 = top_dout[3];
assign g1 = top_dout[2];
assign r0 = top_dout[1];
assign r1 = top_dout[0];

endmodule
