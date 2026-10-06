// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vcounter3.h for the primary calling header

#ifndef VERILATED_VCOUNTER3___024ROOT_H_
#define VERILATED_VCOUNTER3___024ROOT_H_  // guard

#include "verilated.h"


class Vcounter3__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vcounter3___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(en,0,0);
    VL_OUT8(q,2,0);
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vcounter3__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vcounter3___024root(Vcounter3__Syms* symsp, const char* v__name);
    ~Vcounter3___024root();
    VL_UNCOPYABLE(Vcounter3___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
