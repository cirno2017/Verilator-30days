// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vadder4.h for the primary calling header

#include "Vadder4__pch.h"
#include "Vadder4__Syms.h"
#include "Vadder4___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder4___024root___dump_triggers__stl(Vadder4___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vadder4___024root___eval_triggers__stl(Vadder4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vadder4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4___024root___eval_triggers__stl\n"); );
    // Body
    vlSelf->__VstlTriggered.set(0U, (IData)(vlSelf->__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vadder4___024root___dump_triggers__stl(vlSelf);
    }
#endif
}
