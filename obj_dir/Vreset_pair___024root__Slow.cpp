// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vreset_pair.h for the primary calling header

#include "Vreset_pair__pch.h"
#include "Vreset_pair__Syms.h"
#include "Vreset_pair___024root.h"

void Vreset_pair___024root___ctor_var_reset(Vreset_pair___024root* vlSelf);

Vreset_pair___024root::Vreset_pair___024root(Vreset_pair__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vreset_pair___024root___ctor_var_reset(this);
}

void Vreset_pair___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vreset_pair___024root::~Vreset_pair___024root() {
}
