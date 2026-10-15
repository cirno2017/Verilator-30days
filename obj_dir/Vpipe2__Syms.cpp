// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vpipe2__pch.h"
#include "Vpipe2.h"
#include "Vpipe2___024root.h"

// FUNCTIONS
Vpipe2__Syms::~Vpipe2__Syms()
{
}

Vpipe2__Syms::Vpipe2__Syms(VerilatedContext* contextp, const char* namep, Vpipe2* modelp)
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
