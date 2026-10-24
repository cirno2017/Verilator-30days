// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfifo4.h for the primary calling header

#include "Vfifo4__pch.h"
#include "Vfifo4__Syms.h"
#include "Vfifo4___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfifo4___024root___dump_triggers__ico(Vfifo4___024root* vlSelf);
#endif  // VL_DEBUG

void Vfifo4___024root___eval_triggers__ico(Vfifo4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfifo4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo4___024root___eval_triggers__ico\n"); );
    // Body
    vlSelf->__VicoTriggered.set(0U, (IData)(vlSelf->__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vfifo4___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfifo4___024root___dump_triggers__act(Vfifo4___024root* vlSelf);
#endif  // VL_DEBUG

void Vfifo4___024root___eval_triggers__act(Vfifo4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfifo4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo4___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, ((IData)(vlSelf->clk) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__clk__0))));
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vfifo4___024root___dump_triggers__act(vlSelf);
    }
#endif
}

VL_INLINE_OPT void Vfifo4___024root___nba_sequent__TOP__0(Vfifo4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfifo4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo4___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*1:0*/ __Vdly__fifo4__DOT__rd_ptr;
    __Vdly__fifo4__DOT__rd_ptr = 0;
    CData/*1:0*/ __Vdly__fifo4__DOT__wr_ptr;
    __Vdly__fifo4__DOT__wr_ptr = 0;
    CData/*1:0*/ __Vdlyvdim0__fifo4__DOT__mem__v0;
    __Vdlyvdim0__fifo4__DOT__mem__v0 = 0;
    CData/*7:0*/ __Vdlyvval__fifo4__DOT__mem__v0;
    __Vdlyvval__fifo4__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__fifo4__DOT__mem__v0;
    __Vdlyvset__fifo4__DOT__mem__v0 = 0;
    // Body
    ++(vlSymsp->__Vcoverage[9]);
    if ((1U & (~ (IData)(vlSelf->rst)))) {
        ++(vlSymsp->__Vcoverage[8]);
        if ((1U & (~ (IData)(vlSelf->fifo4__DOT__push)))) {
            ++(vlSymsp->__Vcoverage[1]);
        }
        if (vlSelf->fifo4__DOT__push) {
            ++(vlSymsp->__Vcoverage[0]);
        }
        if ((1U & (~ (IData)(vlSelf->fifo4__DOT__pop)))) {
            ++(vlSymsp->__Vcoverage[3]);
        }
        if (vlSelf->fifo4__DOT__pop) {
            ++(vlSymsp->__Vcoverage[2]);
        }
        if ((2U == (((IData)(vlSelf->fifo4__DOT__push) 
                     << 1U) | (IData)(vlSelf->fifo4__DOT__pop)))) {
            ++(vlSymsp->__Vcoverage[4]);
        }
        if ((2U != (((IData)(vlSelf->fifo4__DOT__push) 
                     << 1U) | (IData)(vlSelf->fifo4__DOT__pop)))) {
            if ((1U == (((IData)(vlSelf->fifo4__DOT__push) 
                         << 1U) | (IData)(vlSelf->fifo4__DOT__pop)))) {
                ++(vlSymsp->__Vcoverage[5]);
            }
            if ((1U != (((IData)(vlSelf->fifo4__DOT__push) 
                         << 1U) | (IData)(vlSelf->fifo4__DOT__pop)))) {
                ++(vlSymsp->__Vcoverage[6]);
            }
        }
    }
    __Vdly__fifo4__DOT__rd_ptr = vlSelf->fifo4__DOT__rd_ptr;
    __Vdly__fifo4__DOT__wr_ptr = vlSelf->fifo4__DOT__wr_ptr;
    __Vdlyvset__fifo4__DOT__mem__v0 = 0U;
    if (vlSelf->rst) {
        ++(vlSymsp->__Vcoverage[7]);
        __Vdly__fifo4__DOT__rd_ptr = 0U;
        __Vdly__fifo4__DOT__wr_ptr = 0U;
        vlSelf->fifo4__DOT__count = 0U;
    } else {
        if (vlSelf->fifo4__DOT__pop) {
            __Vdly__fifo4__DOT__rd_ptr = (3U & ((IData)(1U) 
                                                + (IData)(vlSelf->fifo4__DOT__rd_ptr)));
        }
        if (vlSelf->fifo4__DOT__push) {
            __Vdlyvval__fifo4__DOT__mem__v0 = vlSelf->in_data;
            __Vdlyvset__fifo4__DOT__mem__v0 = 1U;
            __Vdlyvdim0__fifo4__DOT__mem__v0 = vlSelf->fifo4__DOT__wr_ptr;
            __Vdly__fifo4__DOT__wr_ptr = (3U & ((IData)(1U) 
                                                + (IData)(vlSelf->fifo4__DOT__wr_ptr)));
        }
        vlSelf->fifo4__DOT__count = (7U & ((2U == (
                                                   ((IData)(vlSelf->fifo4__DOT__push) 
                                                    << 1U) 
                                                   | (IData)(vlSelf->fifo4__DOT__pop)))
                                            ? ((IData)(1U) 
                                               + (IData)(vlSelf->fifo4__DOT__count))
                                            : ((1U 
                                                == 
                                                (((IData)(vlSelf->fifo4__DOT__push) 
                                                  << 1U) 
                                                 | (IData)(vlSelf->fifo4__DOT__pop)))
                                                ? ((IData)(vlSelf->fifo4__DOT__count) 
                                                   - (IData)(1U))
                                                : (IData)(vlSelf->fifo4__DOT__count))));
    }
    vlSelf->fifo4__DOT__rd_ptr = __Vdly__fifo4__DOT__rd_ptr;
    vlSelf->fifo4__DOT__wr_ptr = __Vdly__fifo4__DOT__wr_ptr;
    if (__Vdlyvset__fifo4__DOT__mem__v0) {
        vlSelf->fifo4__DOT__mem[__Vdlyvdim0__fifo4__DOT__mem__v0] 
            = __Vdlyvval__fifo4__DOT__mem__v0;
    }
    vlSelf->level = vlSelf->fifo4__DOT__count;
    vlSelf->in_ready = (4U > (IData)(vlSelf->fifo4__DOT__count));
    vlSelf->out_valid = (0U != (IData)(vlSelf->fifo4__DOT__count));
    vlSelf->fifo4__DOT__push = ((IData)(vlSelf->in_valid) 
                                & (IData)(vlSelf->in_ready));
    if (vlSelf->out_valid) {
        vlSelf->fifo4__DOT__pop = vlSelf->out_ready;
        vlSelf->out_data = vlSelf->fifo4__DOT__mem[vlSelf->fifo4__DOT__rd_ptr];
    } else {
        vlSelf->fifo4__DOT__pop = 0U;
        vlSelf->out_data = 0U;
    }
}
