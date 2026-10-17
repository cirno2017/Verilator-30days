// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vrv_buffer.h for the primary calling header

#include "Vrv_buffer__pch.h"
#include "Vrv_buffer__Syms.h"
#include "Vrv_buffer___024root.h"

void Vrv_buffer___024root___ctor_var_reset(Vrv_buffer___024root* vlSelf);

Vrv_buffer___024root::Vrv_buffer___024root(Vrv_buffer__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vrv_buffer___024root___ctor_var_reset(this);
}

void Vrv_buffer___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vrv_buffer___024root::~Vrv_buffer___024root() {
}
