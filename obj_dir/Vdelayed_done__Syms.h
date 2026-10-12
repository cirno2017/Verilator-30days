// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VDELAYED_DONE__SYMS_H_
#define VERILATED_VDELAYED_DONE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vdelayed_done.h"

// INCLUDE MODULE CLASSES
#include "Vdelayed_done___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vdelayed_done__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vdelayed_done* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vdelayed_done___024root        TOP;

    // CONSTRUCTORS
    Vdelayed_done__Syms(VerilatedContext* contextp, const char* namep, Vdelayed_done* modelp);
    ~Vdelayed_done__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
