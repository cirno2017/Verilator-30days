// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcounter4.h for the primary calling header

#include "Vcounter4__pch.h"
#include "Vcounter4___024root.h"

void Vcounter4___024root___eval_act(Vcounter4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcounter4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter4___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vcounter4___024root___nba_sequent__TOP__0(Vcounter4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcounter4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter4___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*3:0*/ __Vdly__q;
    __Vdly__q = 0;
    // Body
    __Vdly__q = vlSelf->q;
    if (vlSelf->rst) {
        __Vdly__q = 0U;
    } else if (vlSelf->en) {
        __Vdly__q = (0xfU & ((IData)(1U) + (IData)(vlSelf->q)));
    }
    vlSelf->q = __Vdly__q;
}

void Vcounter4___024root___eval_nba(Vcounter4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcounter4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter4___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vcounter4___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vcounter4___024root___eval_triggers__act(Vcounter4___024root* vlSelf);

bool Vcounter4___024root___eval_phase__act(Vcounter4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcounter4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter4___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vcounter4___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vcounter4___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vcounter4___024root___eval_phase__nba(Vcounter4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcounter4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter4___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vcounter4___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcounter4___024root___dump_triggers__nba(Vcounter4___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vcounter4___024root___dump_triggers__act(Vcounter4___024root* vlSelf);
#endif  // VL_DEBUG

void Vcounter4___024root___eval(Vcounter4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcounter4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter4___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vcounter4___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("counter4.v", 2, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vcounter4___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("counter4.v", 2, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vcounter4___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vcounter4___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vcounter4___024root___eval_debug_assertions(Vcounter4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcounter4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter4___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY((vlSelf->en & 0xfeU))) {
        Verilated::overWidthError("en");}
}
#endif  // VL_DEBUG
