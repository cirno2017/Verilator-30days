// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VRESET_PAIR__SYMS_H_
#define VERILATED_VRESET_PAIR__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vreset_pair.h"

// INCLUDE MODULE CLASSES
#include "Vreset_pair___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vreset_pair__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vreset_pair* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vreset_pair___024root          TOP;

    // CONSTRUCTORS
    Vreset_pair__Syms(VerilatedContext* contextp, const char* namep, Vreset_pair* modelp);
    ~Vreset_pair__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
