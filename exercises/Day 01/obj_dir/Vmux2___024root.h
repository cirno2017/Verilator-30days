// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vmux2.h for the primary calling header

#ifndef VERILATED_VMUX2___024ROOT_H_
#define VERILATED_VMUX2___024ROOT_H_  // guard

#include "verilated.h"


class Vmux2__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vmux2___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(a,7,0);
    VL_IN8(b,7,0);
    VL_IN8(sel,0,0);
    VL_OUT8(y,7,0);
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<0> __VactTriggered;
    VlTriggerVec<0> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vmux2__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vmux2___024root(Vmux2__Syms* symsp, const char* v__name);
    ~Vmux2___024root();
    VL_UNCOPYABLE(Vmux2___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
