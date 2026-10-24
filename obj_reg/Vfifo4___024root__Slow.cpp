// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfifo4.h for the primary calling header

#include "Vfifo4__pch.h"
#include "Vfifo4__Syms.h"
#include "Vfifo4___024root.h"

void Vfifo4___024root___ctor_var_reset(Vfifo4___024root* vlSelf);

Vfifo4___024root::Vfifo4___024root(Vfifo4__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vfifo4___024root___ctor_var_reset(this);
}

void Vfifo4___024root___configure_coverage(Vfifo4___024root* vlSelf, bool first);

void Vfifo4___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
    Vfifo4___024root___configure_coverage(this, first);
}

Vfifo4___024root::~Vfifo4___024root() {
}

// Coverage
void Vfifo4___024root::__vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
    const char* hierp, const char* pagep, const char* commentp, const char* linescovp) {
    uint32_t* count32p = countp;
    static uint32_t fake_zero_count = 0;
    if (!enable) count32p = &fake_zero_count;
    *count32p = 0;
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), count32p,  "filename",filenamep,  "lineno",lineno,  "column",column,
        "hier",std::string{name()} + hierp,  "page",pagep,  "comment",commentp,  (linescovp[0] ? "linescov" : ""), linescovp);
}
