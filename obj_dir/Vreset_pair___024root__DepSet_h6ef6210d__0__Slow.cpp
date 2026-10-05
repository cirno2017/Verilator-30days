// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vreset_pair.h for the primary calling header

#include "Vreset_pair__pch.h"
#include "Vreset_pair___024root.h"

VL_ATTR_COLD void Vreset_pair___024root___eval_static(Vreset_pair___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vreset_pair__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreset_pair___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vreset_pair___024root___eval_initial(Vreset_pair___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vreset_pair__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreset_pair___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
    vlSelf->__Vtrigprevexpr___TOP__rst_async__0 = vlSelf->rst_async;
}

VL_ATTR_COLD void Vreset_pair___024root___eval_final(Vreset_pair___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vreset_pair__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreset_pair___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vreset_pair___024root___eval_settle(Vreset_pair___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vreset_pair__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreset_pair___024root___eval_settle\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vreset_pair___024root___dump_triggers__act(Vreset_pair___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vreset_pair__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreset_pair___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge clk or posedge rst_async)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vreset_pair___024root___dump_triggers__nba(Vreset_pair___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vreset_pair__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreset_pair___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge clk or posedge rst_async)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vreset_pair___024root___ctor_var_reset(Vreset_pair___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vreset_pair__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreset_pair___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst_sync = VL_RAND_RESET_I(1);
    vlSelf->rst_async = VL_RAND_RESET_I(1);
    vlSelf->d = VL_RAND_RESET_I(4);
    vlSelf->q_sync = VL_RAND_RESET_I(4);
    vlSelf->q_async = VL_RAND_RESET_I(4);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__rst_async__0 = VL_RAND_RESET_I(1);
}
