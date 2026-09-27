// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VADDER4__SYMS_H_
#define VERILATED_VADDER4__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vadder4.h"

// INCLUDE MODULE CLASSES
#include "Vadder4___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vadder4__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vadder4* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vadder4___024root              TOP;

    // CONSTRUCTORS
    Vadder4__Syms(VerilatedContext* contextp, const char* namep, Vadder4* modelp);
    ~Vadder4__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
