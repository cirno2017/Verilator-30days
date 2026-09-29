// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VMUX4_EN__SYMS_H_
#define VERILATED_VMUX4_EN__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vmux4_en.h"

// INCLUDE MODULE CLASSES
#include "Vmux4_en___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vmux4_en__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vmux4_en* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vmux4_en___024root             TOP;

    // CONSTRUCTORS
    Vmux4_en__Syms(VerilatedContext* contextp, const char* namep, Vmux4_en* modelp);
    ~Vmux4_en__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
