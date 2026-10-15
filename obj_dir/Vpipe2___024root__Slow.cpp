// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpipe2.h for the primary calling header

#include "Vpipe2__pch.h"
#include "Vpipe2__Syms.h"
#include "Vpipe2___024root.h"

void Vpipe2___024root___ctor_var_reset(Vpipe2___024root* vlSelf);

Vpipe2___024root::Vpipe2___024root(Vpipe2__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vpipe2___024root___ctor_var_reset(this);
}

void Vpipe2___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vpipe2___024root::~Vpipe2___024root() {
}
