// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VPIPE2__SYMS_H_
#define VERILATED_VPIPE2__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vpipe2.h"

// INCLUDE MODULE CLASSES
#include "Vpipe2___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vpipe2__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vpipe2* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vpipe2___024root               TOP;

    // CONSTRUCTORS
    Vpipe2__Syms(VerilatedContext* contextp, const char* namep, Vpipe2* modelp);
    ~Vpipe2__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
