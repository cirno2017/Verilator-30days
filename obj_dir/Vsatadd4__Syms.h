// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VSATADD4__SYMS_H_
#define VERILATED_VSATADD4__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vsatadd4.h"

// INCLUDE MODULE CLASSES
#include "Vsatadd4___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vsatadd4__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vsatadd4* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vsatadd4___024root             TOP;

    // CONSTRUCTORS
    Vsatadd4__Syms(VerilatedContext* contextp, const char* namep, Vsatadd4* modelp);
    ~Vsatadd4__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
