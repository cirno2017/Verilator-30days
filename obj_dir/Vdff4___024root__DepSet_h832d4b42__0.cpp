// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdff4.h for the primary calling header

#include "Vdff4__pch.h"
#include "Vdff4__Syms.h"
#include "Vdff4___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdff4___024root___dump_triggers__act(Vdff4___024root* vlSelf);
#endif  // VL_DEBUG

void Vdff4___024root___eval_triggers__act(Vdff4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdff4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdff4___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, ((IData)(vlSelf->clk) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__clk__0))));
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vdff4___024root___dump_triggers__act(vlSelf);
    }
#endif
}
