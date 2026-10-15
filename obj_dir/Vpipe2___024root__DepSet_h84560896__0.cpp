// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpipe2.h for the primary calling header

#include "Vpipe2__pch.h"
#include "Vpipe2___024root.h"

void Vpipe2___024root___eval_act(Vpipe2___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipe2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipe2___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vpipe2___024root___nba_sequent__TOP__0(Vpipe2___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipe2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipe2___024root___nba_sequent__TOP__0\n"); );
    // Body
    if (vlSelf->rst) {
        vlSelf->out_valid = 0U;
        vlSelf->out_data = 0U;
        vlSelf->pipe2__DOT__stage_data = 0U;
    } else {
        if (vlSelf->pipe2__DOT__stage_valid) {
            vlSelf->out_valid = 1U;
            vlSelf->out_data = vlSelf->pipe2__DOT__stage_data;
        } else {
            vlSelf->out_valid = 0U;
        }
        if (vlSelf->in_valid) {
            vlSelf->pipe2__DOT__stage_data = (0xffU 
                                              & ((IData)(1U) 
                                                 + (IData)(vlSelf->in_data)));
        }
    }
    vlSelf->pipe2__DOT__stage_valid = ((1U & (~ (IData)(vlSelf->rst))) 
                                       && (IData)(vlSelf->in_valid));
}

void Vpipe2___024root___eval_nba(Vpipe2___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipe2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipe2___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vpipe2___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vpipe2___024root___eval_triggers__act(Vpipe2___024root* vlSelf);

bool Vpipe2___024root___eval_phase__act(Vpipe2___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipe2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipe2___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vpipe2___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vpipe2___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vpipe2___024root___eval_phase__nba(Vpipe2___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipe2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipe2___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vpipe2___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vpipe2___024root___dump_triggers__nba(Vpipe2___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vpipe2___024root___dump_triggers__act(Vpipe2___024root* vlSelf);
#endif  // VL_DEBUG

void Vpipe2___024root___eval(Vpipe2___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipe2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipe2___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vpipe2___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("pipe2.v", 2, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vpipe2___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("pipe2.v", 2, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vpipe2___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vpipe2___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vpipe2___024root___eval_debug_assertions(Vpipe2___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipe2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipe2___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY((vlSelf->in_valid & 0xfeU))) {
        Verilated::overWidthError("in_valid");}
}
#endif  // VL_DEBUG
