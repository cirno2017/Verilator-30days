// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vreset_pair.h for the primary calling header

#include "Vreset_pair__pch.h"
#include "Vreset_pair__Syms.h"
#include "Vreset_pair___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vreset_pair___024root___dump_triggers__act(Vreset_pair___024root* vlSelf);
#endif  // VL_DEBUG

void Vreset_pair___024root___eval_triggers__act(Vreset_pair___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vreset_pair__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreset_pair___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, ((IData)(vlSelf->clk) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__clk__0))));
    vlSelf->__VactTriggered.set(1U, (((IData)(vlSelf->clk) 
                                      & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__clk__0))) 
                                     | ((IData)(vlSelf->rst_async) 
                                        & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__rst_async__0)))));
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
    vlSelf->__Vtrigprevexpr___TOP__rst_async__0 = vlSelf->rst_async;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vreset_pair___024root___dump_triggers__act(vlSelf);
    }
#endif
}
