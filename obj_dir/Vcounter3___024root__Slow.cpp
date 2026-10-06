// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcounter3.h for the primary calling header

#include "Vcounter3__pch.h"
#include "Vcounter3__Syms.h"
#include "Vcounter3___024root.h"

void Vcounter3___024root___ctor_var_reset(Vcounter3___024root* vlSelf);

Vcounter3___024root::Vcounter3___024root(Vcounter3__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vcounter3___024root___ctor_var_reset(this);
}

void Vcounter3___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vcounter3___024root::~Vcounter3___024root() {
}
