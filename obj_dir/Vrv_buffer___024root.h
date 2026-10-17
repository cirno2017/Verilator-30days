// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vrv_buffer.h for the primary calling header

#ifndef VERILATED_VRV_BUFFER___024ROOT_H_
#define VERILATED_VRV_BUFFER___024ROOT_H_  // guard

#include "verilated.h"


class Vrv_buffer__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vrv_buffer___024root final : public VerilatedModule {
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
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vrv_buffer__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vrv_buffer___024root(Vrv_buffer__Syms* symsp, const char* v__name);
    ~Vrv_buffer___024root();
    VL_UNCOPYABLE(Vrv_buffer___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
