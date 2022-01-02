`timescale 1ns / 1ps

/////////////////////////////////////////
/*    Unified VGA controller module    */
/////////////////////////////////////////


/* The purpose of this module is to create the hsync and vsync signals as well
*	as all other output signals for a 640x480 VGA-driven display. In this current version, 16 pixel wide*
*	borders are assumed. 
*	1: Sync and BLANK signal generator. 
*	2: Frame buffer address generator.
*	3: Frame buffer. 
*/


module vga_controller(
    input wire rst,
    input wire clk,
	 // syn signal ports
	 output wire hsync,
	 output wire vsync,
	 output wire BLANK,
	 output wire h_end,
	 // frame buffer ports
	 input wire write_enable,
    output reg [5:0] dout,			//RGB
		// input data and its address
	 input wire [5:0] din,
	 input wire [13:0] din_address
    );


reg ce;
always @ (posedge clk)
	if(rst)
		ce <= 0;
	else
		ce <= ~ce;

/*****************************************/
/*    Sync and BLANK signal generator.   */
/*****************************************/


// hsync counter
// 10 bit counter, counting to 12'h31F (the width of the display with the border)
// inputs: clock, reset and chip enable, output: 10 bit number

wire hsync_OverFlow;
assign hsync_OverFlow = (HSYNC_COUNTER == 799);				// comparator for pixel row end
reg [9:0] HSYNC_COUNTER;											// counter register

always @ (posedge clk)
begin
	if (rst) 
		HSYNC_COUNTER <= 0;
	else if (ce)
		if(hsync_OverFlow) 
			HSYNC_COUNTER <= 0;
		else
			HSYNC_COUNTER <= HSYNC_COUNTER + 1;
	else;
end

// vsync counter
// 10 bit counter, counting to 12'h208 (the height of the display with the border)
// inputs: clock, reset and chip enable (created by the overflow of the hsync counter), 
// output: 10 bit number

wire vsync_ce;
assign vsync_ce = hsync_OverFlow & ce;								// count enabled by the carry of the hsync counter
wire vsync_OverFlow;
assign vsync_OverFlow = (VSYNC_COUNTER == 520);			// comparator
reg [9:0] VSYNC_COUNTER;												// counter register

always @ (posedge clk)
begin
	if (rst) 
		VSYNC_COUNTER <= 0;
	else if (vsync_ce)
		if(vsync_OverFlow)
			VSYNC_COUNTER <= 0;
		else
			VSYNC_COUNTER <= VSYNC_COUNTER + 1;
	else;
end

/* Create hsync and vsync flip-flops.
	If they go over the min value for the signal, they are set to zero.
	If they go over the max value for the signal, they will be reset to 1.
	Resets sets them to 1, because that resets the counters as well, and these
	signals are low-active.*/

// create hsync signal:

reg hsync_FF;
always @ (posedge clk)
begin
	if(rst) hsync_FF <= 1;
	else if (ce)
		if(HSYNC_COUNTER == 655) hsync_FF <= 0;				// set hsync signal
		else if(HSYNC_COUNTER == 751) hsync_FF <= 1;			// reset hsync signal
end

assign hsync = hsync_FF;

// create vsync signal:

reg vsync_FF;
always @ (posedge clk)
begin
	if(rst) vsync_FF <= 1;
	else if(vsync_ce)
		if(VSYNC_COUNTER == 489) vsync_FF <= 0;				// set vsync signal
		else if(VSYNC_COUNTER == 491) vsync_FF <= 1;			// reset vsync signal
end

assign vsync = vsync_FF;

// create BLANK signal:

reg vertical_BLANK;
always @ (posedge clk)
begin
	if(rst)
		vertical_BLANK <= 0;
	// vertical end of visible area + horizontal end of line --> set vertical_BLANK
	else if(ce & (VSYNC_COUNTER == 479) & (HSYNC_COUNTER == 799))
		vertical_BLANK <= 1;
	// vertical end of blank area + horizontal end of line --> reset vertical_BLANK
	else if(ce & (VSYNC_COUNTER == 520) & (HSYNC_COUNTER == 799))
		vertical_BLANK <= 0;
end

reg horizontal_BLANK;
always @ (posedge clk)
begin
	if(rst)
		horizontal_BLANK <= 0;
	// horizontal end of visible area --> set horizontal_BLANK
	else if(ce & (HSYNC_COUNTER == 639))
		horizontal_BLANK <= 1;
	// horizontal end of blank area --> reset horizontal_BLANK
	else if(ce & (HSYNC_COUNTER == 799))
		horizontal_BLANK <= 0;
end

// delay the BLANK signal output by one CLK period
reg blank_FF;
always @ (posedge clk)
begin
	if(rst) 
		blank_FF <= 0;
	else if(ce)
		blank_FF <= (horizontal_BLANK | vertical_BLANK);
end

assign BLANK = blank_FF;

// emit h_end signal, every time the vsync counter counts (at the real end of every horizontal parse)

assign h_end = hsync_OverFlow; 			// vsync_ce;



/****************************************/
/*    Frame buffer address generator.   */
/****************************************/

// create start counter 
// (a counter that will provide the data load input for our address counter)
reg [14:0] start_cntr;
always @ (posedge clk)
begin
	if(rst) 
		start_cntr <= 0;
	else if((VSYNC_COUNTER < 480) & ce & hsync_OverFlow & (VSYNC_COUNTER[1:0] == 2'b10)) 
		start_cntr <= start_cntr + 160;
	else if (ce & (VSYNC_COUNTER == 520) & hsync_OverFlow)
		start_cntr <= 0;	//TODO: visszanullázás a képernyo végén ? --> ez itt megtörténik...
end

/*	Create address counter. This register will load n/4 * 160 at every fourth h_end,
	and counts from there to 159, iterating through the frame buffer. Because of the
	unified pixels, the lowest two bits will be ignored in the output. (Handling horizontal
	pixel unification.) */

// create address counter register
reg [14:0] address_cntr;
always @ (posedge clk)
begin
	if(rst) 
		address_cntr <= 0;
	else if(vsync_ce & vsync_OverFlow) 
		address_cntr <= 0;
	else if(ce & hsync_OverFlow) 
		address_cntr <= start_cntr;
	else if(~BLANK & ce & HSYNC_COUNTER[1:0]==2'b11)
		address_cntr <= address_cntr + 1;
end

// emit address
wire [14:0] address;
assign address[14:0] = address_cntr[14:0];


/**********************/
/*    Frame buffer.   */
/**********************/

/* The frame buffer is an 19,2k memory area of 6 bit units (taking 32kB of total memory), 
	containing the RGB information per pixel for the next
	frame to be written. In order to avoid screan-tearing, a double-buffering
	system is NOT implemented, because of memory limitations. Data will be written during
	the verticalBlank phase. */


// create our "register array" (it'll be in BRAM, not an actual regtister array)
reg [5:0] mem[160*120-1:0];

// read buffer, when the enable signal is high	
// (There is no harm in writing to output every clk, so I'll default to that.)


// write frame buffer (read the APB bus for address and data)
always @ (posedge clk)
begin
	if(write_enable)
		mem[din_address] <= din;
end

// read frame buffer (transfer data from buffer to VGA)
always @ (posedge clk)
begin
	if(~BLANK)
		dout <= mem[address];
	else
		dout <= 0;
end

endmodule






