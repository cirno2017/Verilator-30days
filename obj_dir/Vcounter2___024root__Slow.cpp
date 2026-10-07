// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcounter2.h for the primary calling header

#include "Vcounter2__pch.h"
#include "Vcounter2__Syms.h"
#include "Vcounter2___024root.h"

void Vcounter2___024root___ctor_var_reset(Vcounter2___024root* vlSelf);

Vcounter2___024root::Vcounter2___024root(Vcounter2__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vcounter2___024root___ctor_var_reset(this);
}

void Vcounter2___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vcounter2___024root::~Vcounter2___024root() {
}
