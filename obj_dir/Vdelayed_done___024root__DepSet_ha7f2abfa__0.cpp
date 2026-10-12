// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdelayed_done.h for the primary calling header

#include "Vdelayed_done__pch.h"
#include "Vdelayed_done__Syms.h"
#include "Vdelayed_done___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdelayed_done___024root___dump_triggers__act(Vdelayed_done___024root* vlSelf);
#endif  // VL_DEBUG

void Vdelayed_done___024root___eval_triggers__act(Vdelayed_done___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdelayed_done__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelayed_done___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, ((IData)(vlSelf->clk) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__clk__0))));
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vdelayed_done___024root___dump_triggers__act(vlSelf);
    }
#endif
}
