// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmux2.h for the primary calling header

#include "Vmux2__pch.h"
#include "Vmux2__Syms.h"
#include "Vmux2___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmux2___024root___dump_triggers__ico(Vmux2___024root* vlSelf);
#endif  // VL_DEBUG

void Vmux2___024root___eval_triggers__ico(Vmux2___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmux2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux2___024root___eval_triggers__ico\n"); );
    // Body
    vlSelf->__VicoTriggered.set(0U, (IData)(vlSelf->__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vmux2___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmux2___024root___dump_triggers__act(Vmux2___024root* vlSelf);
#endif  // VL_DEBUG

void Vmux2___024root___eval_triggers__act(Vmux2___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmux2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux2___024root___eval_triggers__act\n"); );
    // Body
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vmux2___024root___dump_triggers__act(vlSelf);
    }
#endif
}
