// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vrv_buffer__pch.h"
#include "Vrv_buffer.h"
#include "Vrv_buffer___024root.h"

// FUNCTIONS
Vrv_buffer__Syms::~Vrv_buffer__Syms()
{
}

Vrv_buffer__Syms::Vrv_buffer__Syms(VerilatedContext* contextp, const char* namep, Vrv_buffer* modelp)
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
