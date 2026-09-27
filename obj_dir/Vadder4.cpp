// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vadder4__pch.h"

//============================================================
// Constructors

Vadder4::Vadder4(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vadder4__Syms(contextp(), _vcname__, this)}
    , a{vlSymsp->TOP.a}
    , b{vlSymsp->TOP.b}
    , sum{vlSymsp->TOP.sum}
    , carry{vlSymsp->TOP.carry}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vadder4::Vadder4(const char* _vcname__)
    : Vadder4(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vadder4::~Vadder4() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vadder4___024root___eval_debug_assertions(Vadder4___024root* vlSelf);
#endif  // VL_DEBUG
void Vadder4___024root___eval_static(Vadder4___024root* vlSelf);
void Vadder4___024root___eval_initial(Vadder4___024root* vlSelf);
void Vadder4___024root___eval_settle(Vadder4___024root* vlSelf);
void Vadder4___024root___eval(Vadder4___024root* vlSelf);

void Vadder4::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vadder4::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vadder4___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vadder4___024root___eval_static(&(vlSymsp->TOP));
        Vadder4___024root___eval_initial(&(vlSymsp->TOP));
        Vadder4___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vadder4___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vadder4::eventsPending() { return false; }

uint64_t Vadder4::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vadder4::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vadder4___024root___eval_final(Vadder4___024root* vlSelf);

VL_ATTR_COLD void Vadder4::final() {
    Vadder4___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vadder4::hierName() const { return vlSymsp->name(); }
const char* Vadder4::modelName() const { return "Vadder4"; }
unsigned Vadder4::threads() const { return 1; }
void Vadder4::prepareClone() const { contextp()->prepareClone(); }
void Vadder4::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vadder4::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vadder4::trace()' called on model that was Verilated without --trace option");
}
