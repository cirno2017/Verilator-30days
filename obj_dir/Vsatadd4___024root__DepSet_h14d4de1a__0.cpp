// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsatadd4.h for the primary calling header

#include "Vsatadd4__pch.h"
#include "Vsatadd4___024root.h"

VL_INLINE_OPT void Vsatadd4___024root___ico_sequent__TOP__0(Vsatadd4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsatadd4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsatadd4___024root___ico_sequent__TOP__0\n"); );
    // Init
    CData/*4:0*/ satadd4__DOT__total;
    satadd4__DOT__total = 0;
    // Body
    satadd4__DOT__total = (0x1fU & ((IData)(vlSelf->a) 
                                    + (IData)(vlSelf->b)));
    vlSelf->overflow = (1U & ((IData)(satadd4__DOT__total) 
                              >> 4U));
    vlSelf->y = (((IData)(vlSelf->sat_en) & (0xfU < (IData)(satadd4__DOT__total)))
                  ? 0xfU : (0xfU & (IData)(satadd4__DOT__total)));
}

void Vsatadd4___024root___eval_ico(Vsatadd4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsatadd4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsatadd4___024root___eval_ico\n"); );
    // Body
    if ((1ULL & vlSelf->__VicoTriggered.word(0U))) {
        Vsatadd4___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vsatadd4___024root___eval_triggers__ico(Vsatadd4___024root* vlSelf);

bool Vsatadd4___024root___eval_phase__ico(Vsatadd4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsatadd4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsatadd4___024root___eval_phase__ico\n"); );
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vsatadd4___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelf->__VicoTriggered.any();
    if (__VicoExecute) {
        Vsatadd4___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vsatadd4___024root___eval_act(Vsatadd4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsatadd4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsatadd4___024root___eval_act\n"); );
}

void Vsatadd4___024root___eval_nba(Vsatadd4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsatadd4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsatadd4___024root___eval_nba\n"); );
}

void Vsatadd4___024root___eval_triggers__act(Vsatadd4___024root* vlSelf);

bool Vsatadd4___024root___eval_phase__act(Vsatadd4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsatadd4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsatadd4___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<0> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vsatadd4___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vsatadd4___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vsatadd4___024root___eval_phase__nba(Vsatadd4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsatadd4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsatadd4___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vsatadd4___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsatadd4___024root___dump_triggers__ico(Vsatadd4___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vsatadd4___024root___dump_triggers__nba(Vsatadd4___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vsatadd4___024root___dump_triggers__act(Vsatadd4___024root* vlSelf);
#endif  // VL_DEBUG

void Vsatadd4___024root___eval(Vsatadd4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsatadd4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsatadd4___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelf->__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY((0x64U < __VicoIterCount))) {
#ifdef VL_DEBUG
            Vsatadd4___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("satadd4.v", 2, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vsatadd4___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelf->__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vsatadd4___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("satadd4.v", 2, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vsatadd4___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("satadd4.v", 2, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vsatadd4___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vsatadd4___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vsatadd4___024root___eval_debug_assertions(Vsatadd4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsatadd4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsatadd4___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->a & 0xf0U))) {
        Verilated::overWidthError("a");}
    if (VL_UNLIKELY((vlSelf->b & 0xf0U))) {
        Verilated::overWidthError("b");}
    if (VL_UNLIKELY((vlSelf->sat_en & 0xfeU))) {
        Verilated::overWidthError("sat_en");}
}
#endif  // VL_DEBUG
