// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vcounter2__pch.h"

//============================================================
// Constructors

Vcounter2::Vcounter2(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vcounter2__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , en{vlSymsp->TOP.en}
    , q{vlSymsp->TOP.q}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vcounter2::Vcounter2(const char* _vcname__)
    : Vcounter2(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vcounter2::~Vcounter2() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vcounter2___024root___eval_debug_assertions(Vcounter2___024root* vlSelf);
#endif  // VL_DEBUG
void Vcounter2___024root___eval_static(Vcounter2___024root* vlSelf);
void Vcounter2___024root___eval_initial(Vcounter2___024root* vlSelf);
void Vcounter2___024root___eval_settle(Vcounter2___024root* vlSelf);
void Vcounter2___024root___eval(Vcounter2___024root* vlSelf);

void Vcounter2::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vcounter2::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vcounter2___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vcounter2___024root___eval_static(&(vlSymsp->TOP));
        Vcounter2___024root___eval_initial(&(vlSymsp->TOP));
        Vcounter2___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vcounter2___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vcounter2::eventsPending() { return false; }

uint64_t Vcounter2::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vcounter2::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vcounter2___024root___eval_final(Vcounter2___024root* vlSelf);

VL_ATTR_COLD void Vcounter2::final() {
    Vcounter2___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vcounter2::hierName() const { return vlSymsp->name(); }
const char* Vcounter2::modelName() const { return "Vcounter2"; }
unsigned Vcounter2::threads() const { return 1; }
void Vcounter2::prepareClone() const { contextp()->prepareClone(); }
void Vcounter2::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vcounter2::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vcounter2::trace()' called on model that was Verilated without --trace option");
}
