// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfifo4.h for the primary calling header

#include "Vfifo4__pch.h"
#include "Vfifo4__Syms.h"
#include "Vfifo4___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfifo4___024root___dump_triggers__stl(Vfifo4___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vfifo4___024root___eval_triggers__stl(Vfifo4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfifo4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo4___024root___eval_triggers__stl\n"); );
    // Body
    vlSelf->__VstlTriggered.set(0U, (IData)(vlSelf->__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vfifo4___024root___dump_triggers__stl(vlSelf);
    }
#endif
}

VL_ATTR_COLD void Vfifo4___024root___configure_coverage(Vfifo4___024root* vlSelf, bool first) {
    if (false && vlSelf) {}  // Prevent unused
    Vfifo4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo4___024root___configure_coverage\n"); );
    // Body
    if (false && first) {}  // Prevent unused
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[0]), first, "fifo4.v", 33, 7, ".fifo4", "v_branch/fifo4", "if", "33-35");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[1]), first, "fifo4.v", 33, 8, ".fifo4", "v_branch/fifo4", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[2]), first, "fifo4.v", 38, 7, ".fifo4", "v_branch/fifo4", "if", "38");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[3]), first, "fifo4.v", 38, 8, ".fifo4", "v_branch/fifo4", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[4]), first, "fifo4.v", 43, 14, ".fifo4", "v_line/fifo4", "case", "43");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[5]), first, "fifo4.v", 44, 14, ".fifo4", "v_line/fifo4", "case", "44");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[6]), first, "fifo4.v", 45, 9, ".fifo4", "v_line/fifo4", "case", "45");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[7]), first, "fifo4.v", 28, 5, ".fifo4", "v_branch/fifo4", "if", "28-31");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[8]), first, "fifo4.v", 28, 6, ".fifo4", "v_branch/fifo4", "else", "32,40-41");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[9]), first, "fifo4.v", 27, 3, ".fifo4", "v_line/fifo4", "block", "27");
}
