// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vdff4__pch.h"
#include "Vdff4.h"
#include "Vdff4___024root.h"

// FUNCTIONS
Vdff4__Syms::~Vdff4__Syms()
{
}

Vdff4__Syms::Vdff4__Syms(VerilatedContext* contextp, const char* namep, Vdff4* modelp)
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
