// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vsatadd4.h for the primary calling header

#ifndef VERILATED_VSATADD4___024ROOT_H_
#define VERILATED_VSATADD4___024ROOT_H_  // guard

#include "verilated.h"


class Vsatadd4__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vsatadd4___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(a,3,0);
    VL_IN8(b,3,0);
    VL_IN8(sat_en,0,0);
    VL_OUT8(y,3,0);
    VL_OUT8(overflow,0,0);
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<0> __VactTriggered;
    VlTriggerVec<0> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vsatadd4__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vsatadd4___024root(Vsatadd4__Syms* symsp, const char* v__name);
    ~Vsatadd4___024root();
    VL_UNCOPYABLE(Vsatadd4___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
