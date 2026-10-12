// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdelayed_done.h for the primary calling header

#include "Vdelayed_done__pch.h"
#include "Vdelayed_done___024root.h"

VL_ATTR_COLD void Vdelayed_done___024root___eval_static(Vdelayed_done___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdelayed_done__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelayed_done___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vdelayed_done___024root___eval_initial(Vdelayed_done___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdelayed_done__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelayed_done___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
}

VL_ATTR_COLD void Vdelayed_done___024root___eval_final(Vdelayed_done___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdelayed_done__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelayed_done___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vdelayed_done___024root___eval_settle(Vdelayed_done___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdelayed_done__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelayed_done___024root___eval_settle\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdelayed_done___024root___dump_triggers__act(Vdelayed_done___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdelayed_done__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelayed_done___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdelayed_done___024root___dump_triggers__nba(Vdelayed_done___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdelayed_done__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelayed_done___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vdelayed_done___024root___ctor_var_reset(Vdelayed_done___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdelayed_done__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelayed_done___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst = VL_RAND_RESET_I(1);
    vlSelf->start = VL_RAND_RESET_I(1);
    vlSelf->stall = VL_RAND_RESET_I(1);
    vlSelf->busy = VL_RAND_RESET_I(1);
    vlSelf->done = VL_RAND_RESET_I(1);
    vlSelf->delayed_done__DOT__remaining = VL_RAND_RESET_I(2);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
}
