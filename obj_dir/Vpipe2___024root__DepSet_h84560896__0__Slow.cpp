// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpipe2.h for the primary calling header

#include "Vpipe2__pch.h"
#include "Vpipe2___024root.h"

VL_ATTR_COLD void Vpipe2___024root___eval_static(Vpipe2___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipe2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipe2___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vpipe2___024root___eval_initial(Vpipe2___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipe2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipe2___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
}

VL_ATTR_COLD void Vpipe2___024root___eval_final(Vpipe2___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipe2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipe2___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vpipe2___024root___eval_settle(Vpipe2___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipe2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipe2___024root___eval_settle\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vpipe2___024root___dump_triggers__act(Vpipe2___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipe2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipe2___024root___dump_triggers__act\n"); );
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
VL_ATTR_COLD void Vpipe2___024root___dump_triggers__nba(Vpipe2___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipe2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipe2___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vpipe2___024root___ctor_var_reset(Vpipe2___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipe2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipe2___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst = VL_RAND_RESET_I(1);
    vlSelf->in_valid = VL_RAND_RESET_I(1);
    vlSelf->in_data = VL_RAND_RESET_I(8);
    vlSelf->out_valid = VL_RAND_RESET_I(1);
    vlSelf->out_data = VL_RAND_RESET_I(8);
    vlSelf->pipe2__DOT__stage_valid = VL_RAND_RESET_I(1);
    vlSelf->pipe2__DOT__stage_data = VL_RAND_RESET_I(8);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
}
