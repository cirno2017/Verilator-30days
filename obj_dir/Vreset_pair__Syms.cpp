// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vreset_pair__pch.h"
#include "Vreset_pair.h"
#include "Vreset_pair___024root.h"

// FUNCTIONS
Vreset_pair__Syms::~Vreset_pair__Syms()
{
}

Vreset_pair__Syms::Vreset_pair__Syms(VerilatedContext* contextp, const char* namep, Vreset_pair* modelp)
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
