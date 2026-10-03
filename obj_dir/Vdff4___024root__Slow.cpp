// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdff4.h for the primary calling header

#include "Vdff4__pch.h"
#include "Vdff4__Syms.h"
#include "Vdff4___024root.h"

void Vdff4___024root___ctor_var_reset(Vdff4___024root* vlSelf);

Vdff4___024root::Vdff4___024root(Vdff4__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vdff4___024root___ctor_var_reset(this);
}

void Vdff4___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vdff4___024root::~Vdff4___024root() {
}
