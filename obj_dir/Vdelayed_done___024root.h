// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vdelayed_done.h for the primary calling header

#ifndef VERILATED_VDELAYED_DONE___024ROOT_H_
#define VERILATED_VDELAYED_DONE___024ROOT_H_  // guard

#include "verilated.h"


class Vdelayed_done__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vdelayed_done___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(start,0,0);
    VL_IN8(stall,0,0);
    VL_OUT8(busy,0,0);
    VL_OUT8(done,0,0);
    CData/*1:0*/ delayed_done__DOT__remaining;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vdelayed_done__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vdelayed_done___024root(Vdelayed_done__Syms* symsp, const char* v__name);
    ~Vdelayed_done___024root();
    VL_UNCOPYABLE(Vdelayed_done___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
