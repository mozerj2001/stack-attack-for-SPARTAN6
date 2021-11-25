//-----------------------------------------------------------------------------
// cpu_subsys_top.v
//-----------------------------------------------------------------------------

module cpu_subsys
  (
    rst_n,
    clk,
    M_APB_PCLK,
    M_APB_PRESETN,
    M_APB_PADDR,
    M_APB_PSEL,
    M_APB_PENABLE,
    M_APB_PWRITE,
    M_APB_PWDATA,
    M_APB_PREADY,
    M_APB_PRDATA,
    M_APB_PSLVERR,
    led,
    sw
  );
  input rst_n;
  input clk;
  output M_APB_PCLK;
  output M_APB_PRESETN;
  output [31:0] M_APB_PADDR;
  output M_APB_PSEL;
  output M_APB_PENABLE;
  output M_APB_PWRITE;
  output [31:0] M_APB_PWDATA;
  input M_APB_PREADY;
  input [31:0] M_APB_PRDATA;
  input M_APB_PSLVERR;
  output [7:0] led;
  input [7:0] sw;


endmodule

