// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vadder4.h for the primary calling header

#include "Vadder4__pch.h"
#include "Vadder4___024root.h"

VL_ATTR_COLD void Vadder4___024root___eval_static(Vadder4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vadder4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vadder4___024root___eval_initial(Vadder4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vadder4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4___024root___eval_initial\n"); );
}

VL_ATTR_COLD void Vadder4___024root___eval_final(Vadder4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vadder4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder4___024root___dump_triggers__stl(Vadder4___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vadder4___024root___eval_phase__stl(Vadder4___024root* vlSelf);

VL_ATTR_COLD void Vadder4___024root___eval_settle(Vadder4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vadder4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4___024root___eval_settle\n"); );
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelf->__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vadder4___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("adder4.v", 2, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vadder4___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder4___024root___dump_triggers__stl(Vadder4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vadder4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

void Vadder4___024root___ico_sequent__TOP__0(Vadder4___024root* vlSelf);

VL_ATTR_COLD void Vadder4___024root___eval_stl(Vadder4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vadder4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        Vadder4___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vadder4___024root___eval_triggers__stl(Vadder4___024root* vlSelf);

VL_ATTR_COLD bool Vadder4___024root___eval_phase__stl(Vadder4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vadder4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vadder4___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        Vadder4___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder4___024root___dump_triggers__ico(Vadder4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vadder4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VicoTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder4___024root___dump_triggers__act(Vadder4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vadder4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder4___024root___dump_triggers__nba(Vadder4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vadder4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vadder4___024root___ctor_var_reset(Vadder4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vadder4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->a = VL_RAND_RESET_I(4);
    vlSelf->b = VL_RAND_RESET_I(4);
    vlSelf->sum = VL_RAND_RESET_I(4);
    vlSelf->carry = VL_RAND_RESET_I(1);
}
