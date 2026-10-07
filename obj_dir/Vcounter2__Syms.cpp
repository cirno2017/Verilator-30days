// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vcounter2__pch.h"
#include "Vcounter2.h"
#include "Vcounter2___024root.h"

// FUNCTIONS
Vcounter2__Syms::~Vcounter2__Syms()
{
}

Vcounter2__Syms::Vcounter2__Syms(VerilatedContext* contextp, const char* namep, Vcounter2* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-9);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
}
