// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcounter4.h for the primary calling header

#include "Vcounter4__pch.h"
#include "Vcounter4___024root.h"

VL_ATTR_COLD void Vcounter4___024root___eval_static(Vcounter4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcounter4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter4___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vcounter4___024root___eval_initial(Vcounter4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcounter4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter4___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
}

VL_ATTR_COLD void Vcounter4___024root___eval_final(Vcounter4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcounter4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter4___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vcounter4___024root___eval_settle(Vcounter4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcounter4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter4___024root___eval_settle\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcounter4___024root___dump_triggers__act(Vcounter4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcounter4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter4___024root___dump_triggers__act\n"); );
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
VL_ATTR_COLD void Vcounter4___024root___dump_triggers__nba(Vcounter4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcounter4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter4___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vcounter4___024root___ctor_var_reset(Vcounter4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcounter4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter4___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst = VL_RAND_RESET_I(1);
    vlSelf->en = VL_RAND_RESET_I(1);
    vlSelf->q = VL_RAND_RESET_I(4);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
}
