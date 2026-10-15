// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vpipe2.h for the primary calling header

#ifndef VERILATED_VPIPE2___024ROOT_H_
#define VERILATED_VPIPE2___024ROOT_H_  // guard

#include "verilated.h"


class Vpipe2__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vpipe2___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(in_valid,0,0);
    VL_IN8(in_data,7,0);
    VL_OUT8(out_valid,0,0);
    VL_OUT8(out_data,7,0);
    CData/*0:0*/ pipe2__DOT__stage_valid;
    CData/*7:0*/ pipe2__DOT__stage_data;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vpipe2__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vpipe2___024root(Vpipe2__Syms* symsp, const char* v__name);
    ~Vpipe2___024root();
    VL_UNCOPYABLE(Vpipe2___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
