// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsatadd4.h for the primary calling header

#include "Vsatadd4__pch.h"
#include "Vsatadd4__Syms.h"
#include "Vsatadd4___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsatadd4___024root___dump_triggers__ico(Vsatadd4___024root* vlSelf);
#endif  // VL_DEBUG

void Vsatadd4___024root___eval_triggers__ico(Vsatadd4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsatadd4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsatadd4___024root___eval_triggers__ico\n"); );
    // Body
    vlSelf->__VicoTriggered.set(0U, (IData)(vlSelf->__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vsatadd4___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsatadd4___024root___dump_triggers__act(Vsatadd4___024root* vlSelf);
#endif  // VL_DEBUG

void Vsatadd4___024root___eval_triggers__act(Vsatadd4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsatadd4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsatadd4___024root___eval_triggers__act\n"); );
    // Body
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vsatadd4___024root___dump_triggers__act(vlSelf);
    }
#endif
}
