// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vdff4__pch.h"

//============================================================
// Constructors

Vdff4::Vdff4(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vdff4__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , d{vlSymsp->TOP.d}
    , q{vlSymsp->TOP.q}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vdff4::Vdff4(const char* _vcname__)
    : Vdff4(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vdff4::~Vdff4() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vdff4___024root___eval_debug_assertions(Vdff4___024root* vlSelf);
#endif  // VL_DEBUG
void Vdff4___024root___eval_static(Vdff4___024root* vlSelf);
void Vdff4___024root___eval_initial(Vdff4___024root* vlSelf);
void Vdff4___024root___eval_settle(Vdff4___024root* vlSelf);
void Vdff4___024root___eval(Vdff4___024root* vlSelf);

void Vdff4::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vdff4::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vdff4___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vdff4___024root___eval_static(&(vlSymsp->TOP));
        Vdff4___024root___eval_initial(&(vlSymsp->TOP));
        Vdff4___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vdff4___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vdff4::eventsPending() { return false; }

uint64_t Vdff4::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vdff4::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vdff4___024root___eval_final(Vdff4___024root* vlSelf);

VL_ATTR_COLD void Vdff4::final() {
    Vdff4___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vdff4::hierName() const { return vlSymsp->name(); }
const char* Vdff4::modelName() const { return "Vdff4"; }
unsigned Vdff4::threads() const { return 1; }
void Vdff4::prepareClone() const { contextp()->prepareClone(); }
void Vdff4::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vdff4::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vdff4::trace()' called on model that was Verilated without --trace option");
}
