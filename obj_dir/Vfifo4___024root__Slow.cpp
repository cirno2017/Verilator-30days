// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfifo4.h for the primary calling header

#include "Vfifo4__pch.h"
#include "Vfifo4__Syms.h"
#include "Vfifo4___024root.h"

void Vfifo4___024root___ctor_var_reset(Vfifo4___024root* vlSelf);

Vfifo4___024root::Vfifo4___024root(Vfifo4__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vfifo4___024root___ctor_var_reset(this);
}

void Vfifo4___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vfifo4___024root::~Vfifo4___024root() {
}
