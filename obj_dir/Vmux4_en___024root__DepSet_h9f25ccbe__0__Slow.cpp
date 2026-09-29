// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmux4_en.h for the primary calling header

#include "Vmux4_en__pch.h"
#include "Vmux4_en__Syms.h"
#include "Vmux4_en___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmux4_en___024root___dump_triggers__stl(Vmux4_en___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vmux4_en___024root___eval_triggers__stl(Vmux4_en___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmux4_en__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux4_en___024root___eval_triggers__stl\n"); );
    // Body
    vlSelf->__VstlTriggered.set(0U, (IData)(vlSelf->__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vmux4_en___024root___dump_triggers__stl(vlSelf);
    }
#endif
}
