// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vadder4.h for the primary calling header

#ifndef VERILATED_VADDER4___024ROOT_H_
#define VERILATED_VADDER4___024ROOT_H_  // guard

#include "verilated.h"


class Vadder4__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vadder4___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(a,3,0);
    VL_IN8(b,3,0);
    VL_OUT8(sum,3,0);
    VL_OUT8(carry,0,0);
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<0> __VactTriggered;
    VlTriggerVec<0> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vadder4__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vadder4___024root(Vadder4__Syms* symsp, const char* v__name);
    ~Vadder4___024root();
    VL_UNCOPYABLE(Vadder4___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
