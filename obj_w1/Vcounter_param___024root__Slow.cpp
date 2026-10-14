// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcounter_param.h for the primary calling header

#include "Vcounter_param__pch.h"
#include "Vcounter_param__Syms.h"
#include "Vcounter_param___024root.h"

void Vcounter_param___024root___ctor_var_reset(Vcounter_param___024root* vlSelf);

Vcounter_param___024root::Vcounter_param___024root(Vcounter_param__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vcounter_param___024root___ctor_var_reset(this);
}

void Vcounter_param___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vcounter_param___024root::~Vcounter_param___024root() {
}
