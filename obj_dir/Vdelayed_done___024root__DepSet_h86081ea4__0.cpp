// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdelayed_done.h for the primary calling header

#include "Vdelayed_done__pch.h"
#include "Vdelayed_done___024root.h"

void Vdelayed_done___024root___eval_act(Vdelayed_done___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdelayed_done__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelayed_done___024root___eval_act\n"); );
}

extern const VlUnpacked<CData/*2:0*/, 64> Vdelayed_done__ConstPool__TABLE_h11d3315c_0;
extern const VlUnpacked<CData/*0:0*/, 64> Vdelayed_done__ConstPool__TABLE_h3a3b38bf_0;
extern const VlUnpacked<CData/*0:0*/, 64> Vdelayed_done__ConstPool__TABLE_h784215a7_0;
extern const VlUnpacked<CData/*1:0*/, 64> Vdelayed_done__ConstPool__TABLE_hd8864fde_0;

VL_INLINE_OPT void Vdelayed_done___024root___nba_sequent__TOP__0(Vdelayed_done___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdelayed_done__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelayed_done___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*5:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    __Vtableidx1 = (((IData)(vlSelf->start) << 5U) 
                    | (((IData)(vlSelf->delayed_done__DOT__remaining) 
                        << 3U) | (((IData)(vlSelf->stall) 
                                   << 2U) | (((IData)(vlSelf->busy) 
                                              << 1U) 
                                             | (IData)(vlSelf->rst)))));
    if ((1U & Vdelayed_done__ConstPool__TABLE_h11d3315c_0
         [__Vtableidx1])) {
        vlSelf->busy = Vdelayed_done__ConstPool__TABLE_h3a3b38bf_0
            [__Vtableidx1];
    }
    if ((2U & Vdelayed_done__ConstPool__TABLE_h11d3315c_0
         [__Vtableidx1])) {
        vlSelf->done = Vdelayed_done__ConstPool__TABLE_h784215a7_0
            [__Vtableidx1];
    }
    if ((4U & Vdelayed_done__ConstPool__TABLE_h11d3315c_0
         [__Vtableidx1])) {
        vlSelf->delayed_done__DOT__remaining = Vdelayed_done__ConstPool__TABLE_hd8864fde_0
            [__Vtableidx1];
    }
}

void Vdelayed_done___024root___eval_nba(Vdelayed_done___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdelayed_done__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelayed_done___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vdelayed_done___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vdelayed_done___024root___eval_triggers__act(Vdelayed_done___024root* vlSelf);

bool Vdelayed_done___024root___eval_phase__act(Vdelayed_done___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdelayed_done__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelayed_done___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vdelayed_done___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vdelayed_done___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vdelayed_done___024root___eval_phase__nba(Vdelayed_done___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdelayed_done__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelayed_done___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vdelayed_done___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdelayed_done___024root___dump_triggers__nba(Vdelayed_done___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vdelayed_done___024root___dump_triggers__act(Vdelayed_done___024root* vlSelf);
#endif  // VL_DEBUG

void Vdelayed_done___024root___eval(Vdelayed_done___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdelayed_done__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelayed_done___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vdelayed_done___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("delayed_done.v", 2, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vdelayed_done___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("delayed_done.v", 2, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vdelayed_done___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vdelayed_done___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vdelayed_done___024root___eval_debug_assertions(Vdelayed_done___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdelayed_done__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdelayed_done___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY((vlSelf->start & 0xfeU))) {
        Verilated::overWidthError("start");}
    if (VL_UNLIKELY((vlSelf->stall & 0xfeU))) {
        Verilated::overWidthError("stall");}
}
#endif  // VL_DEBUG
