// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VCOUNTER2__SYMS_H_
#define VERILATED_VCOUNTER2__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vcounter2.h"

// INCLUDE MODULE CLASSES
#include "Vcounter2___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vcounter2__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vcounter2* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vcounter2___024root            TOP;

    // CONSTRUCTORS
    Vcounter2__Syms(VerilatedContext* contextp, const char* namep, Vcounter2* modelp);
    ~Vcounter2__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
