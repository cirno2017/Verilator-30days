// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VCOUNTER_PARAM__SYMS_H_
#define VERILATED_VCOUNTER_PARAM__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vcounter_param.h"

// INCLUDE MODULE CLASSES
#include "Vcounter_param___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vcounter_param__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vcounter_param* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vcounter_param___024root       TOP;

    // CONSTRUCTORS
    Vcounter_param__Syms(VerilatedContext* contextp, const char* namep, Vcounter_param* modelp);
    ~Vcounter_param__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
