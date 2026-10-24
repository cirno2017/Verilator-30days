// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vfifo4__Syms.h"


void Vfifo4___024root__trace_chg_0_sub_0(Vfifo4___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vfifo4___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo4___024root__trace_chg_0\n"); );
    // Init
    Vfifo4___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vfifo4___024root*>(voidSelf);
    Vfifo4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vfifo4___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vfifo4___024root__trace_chg_0_sub_0(Vfifo4___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vfifo4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo4___024root__trace_chg_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgCData(oldp+0,(vlSelf->fifo4__DOT__mem[0]),8);
        bufp->chgCData(oldp+1,(vlSelf->fifo4__DOT__mem[1]),8);
        bufp->chgCData(oldp+2,(vlSelf->fifo4__DOT__mem[2]),8);
        bufp->chgCData(oldp+3,(vlSelf->fifo4__DOT__mem[3]),8);
        bufp->chgCData(oldp+4,(vlSelf->fifo4__DOT__wr_ptr),2);
        bufp->chgCData(oldp+5,(vlSelf->fifo4__DOT__rd_ptr),2);
        bufp->chgCData(oldp+6,(vlSelf->fifo4__DOT__count),3);
    }
    bufp->chgBit(oldp+7,(vlSelf->clk));
    bufp->chgBit(oldp+8,(vlSelf->rst));
    bufp->chgBit(oldp+9,(vlSelf->in_valid));
    bufp->chgBit(oldp+10,(vlSelf->in_ready));
    bufp->chgCData(oldp+11,(vlSelf->in_data),8);
    bufp->chgBit(oldp+12,(vlSelf->out_valid));
    bufp->chgBit(oldp+13,(vlSelf->out_ready));
    bufp->chgCData(oldp+14,(vlSelf->out_data),8);
    bufp->chgCData(oldp+15,(vlSelf->level),3);
    bufp->chgBit(oldp+16,(vlSelf->fifo4__DOT__push));
    bufp->chgBit(oldp+17,(vlSelf->fifo4__DOT__pop));
}

void Vfifo4___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo4___024root__trace_cleanup\n"); );
    // Init
    Vfifo4___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vfifo4___024root*>(voidSelf);
    Vfifo4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
