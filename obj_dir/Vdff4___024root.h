// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vdff4.h for the primary calling header

#ifndef VERILATED_VDFF4___024ROOT_H_
#define VERILATED_VDFF4___024ROOT_H_  // guard

#include "verilated.h"


class Vdff4__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vdff4___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(d,3,0);
    VL_OUT8(q,3,0);
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vdff4__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vdff4___024root(Vdff4__Syms* symsp, const char* v__name);
    ~Vdff4___024root();
    VL_UNCOPYABLE(Vdff4___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
