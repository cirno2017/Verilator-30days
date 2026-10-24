// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfifo4.h for the primary calling header

#include "Vfifo4__pch.h"
#include "Vfifo4___024root.h"

VL_INLINE_OPT void Vfifo4___024root___ico_sequent__TOP__0(Vfifo4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfifo4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo4___024root___ico_sequent__TOP__0\n"); );
    // Body
    vlSelf->fifo4__DOT__push = ((IData)(vlSelf->in_valid) 
                                & (IData)(vlSelf->in_ready));
    vlSelf->fifo4__DOT__pop = ((IData)(vlSelf->out_valid) 
                               & (IData)(vlSelf->out_ready));
}

void Vfifo4___024root___eval_ico(Vfifo4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfifo4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo4___024root___eval_ico\n"); );
    // Body
    if ((1ULL & vlSelf->__VicoTriggered.word(0U))) {
        Vfifo4___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vfifo4___024root___eval_triggers__ico(Vfifo4___024root* vlSelf);

bool Vfifo4___024root___eval_phase__ico(Vfifo4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfifo4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo4___024root___eval_phase__ico\n"); );
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vfifo4___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelf->__VicoTriggered.any();
    if (__VicoExecute) {
        Vfifo4___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vfifo4___024root___eval_act(Vfifo4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfifo4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo4___024root___eval_act\n"); );
}

void Vfifo4___024root___nba_sequent__TOP__0(Vfifo4___024root* vlSelf);

void Vfifo4___024root___eval_nba(Vfifo4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfifo4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo4___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vfifo4___024root___nba_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
}

void Vfifo4___024root___eval_triggers__act(Vfifo4___024root* vlSelf);

bool Vfifo4___024root___eval_phase__act(Vfifo4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfifo4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo4___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vfifo4___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vfifo4___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vfifo4___024root___eval_phase__nba(Vfifo4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfifo4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo4___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vfifo4___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfifo4___024root___dump_triggers__ico(Vfifo4___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vfifo4___024root___dump_triggers__nba(Vfifo4___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vfifo4___024root___dump_triggers__act(Vfifo4___024root* vlSelf);
#endif  // VL_DEBUG

void Vfifo4___024root___eval(Vfifo4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfifo4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo4___024root___eval\n"); );
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
            Vfifo4___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("fifo4.v", 2, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vfifo4___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelf->__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vfifo4___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("fifo4.v", 2, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vfifo4___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("fifo4.v", 2, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vfifo4___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vfifo4___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vfifo4___024root___eval_debug_assertions(Vfifo4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfifo4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo4___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY((vlSelf->in_valid & 0xfeU))) {
        Verilated::overWidthError("in_valid");}
    if (VL_UNLIKELY((vlSelf->out_ready & 0xfeU))) {
        Verilated::overWidthError("out_ready");}
}
#endif  // VL_DEBUG
