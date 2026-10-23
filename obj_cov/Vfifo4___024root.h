// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vfifo4.h for the primary calling header

#ifndef VERILATED_VFIFO4___024ROOT_H_
#define VERILATED_VFIFO4___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"


class Vfifo4__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vfifo4___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(in_valid,0,0);
    VL_OUT8(in_ready,0,0);
    VL_IN8(in_data,7,0);
    VL_OUT8(out_valid,0,0);
    VL_IN8(out_ready,0,0);
    VL_OUT8(out_data,7,0);
    VL_OUT8(level,2,0);
    CData/*1:0*/ fifo4__DOT__wr_ptr;
    CData/*1:0*/ fifo4__DOT__rd_ptr;
    CData/*2:0*/ fifo4__DOT__count;
    CData/*0:0*/ fifo4__DOT__push;
    CData/*0:0*/ fifo4__DOT__pop;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<CData/*7:0*/, 4> fifo4__DOT__mem;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vfifo4__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vfifo4___024root(Vfifo4__Syms* symsp, const char* v__name);
    ~Vfifo4___024root();
    VL_UNCOPYABLE(Vfifo4___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
};


#endif  // guard
