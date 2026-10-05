// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vreset_pair.h for the primary calling header

#ifndef VERILATED_VRESET_PAIR___024ROOT_H_
#define VERILATED_VRESET_PAIR___024ROOT_H_  // guard

#include "verilated.h"


class Vreset_pair__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vreset_pair___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst_async,0,0);
    VL_IN8(rst_sync,0,0);
    VL_IN8(d,3,0);
    VL_OUT8(q_sync,3,0);
    VL_OUT8(q_async,3,0);
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__rst_async__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vreset_pair__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vreset_pair___024root(Vreset_pair__Syms* symsp, const char* v__name);
    ~Vreset_pair___024root();
    VL_UNCOPYABLE(Vreset_pair___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
