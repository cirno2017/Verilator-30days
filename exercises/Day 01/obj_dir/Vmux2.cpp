// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vmux2__pch.h"

//============================================================
// Constructors

Vmux2::Vmux2(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vmux2__Syms(contextp(), _vcname__, this)}
    , a{vlSymsp->TOP.a}
    , b{vlSymsp->TOP.b}
    , sel{vlSymsp->TOP.sel}
    , y{vlSymsp->TOP.y}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vmux2::Vmux2(const char* _vcname__)
    : Vmux2(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vmux2::~Vmux2() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vmux2___024root___eval_debug_assertions(Vmux2___024root* vlSelf);
#endif  // VL_DEBUG
void Vmux2___024root___eval_static(Vmux2___024root* vlSelf);
void Vmux2___024root___eval_initial(Vmux2___024root* vlSelf);
void Vmux2___024root___eval_settle(Vmux2___024root* vlSelf);
void Vmux2___024root___eval(Vmux2___024root* vlSelf);

void Vmux2::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vmux2::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vmux2___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vmux2___024root___eval_static(&(vlSymsp->TOP));
        Vmux2___024root___eval_initial(&(vlSymsp->TOP));
        Vmux2___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vmux2___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vmux2::eventsPending() { return false; }

uint64_t Vmux2::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vmux2::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vmux2___024root___eval_final(Vmux2___024root* vlSelf);

VL_ATTR_COLD void Vmux2::final() {
    Vmux2___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vmux2::hierName() const { return vlSymsp->name(); }
const char* Vmux2::modelName() const { return "Vmux2"; }
unsigned Vmux2::threads() const { return 1; }
void Vmux2::prepareClone() const { contextp()->prepareClone(); }
void Vmux2::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vmux2::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vmux2::trace()' called on model that was Verilated without --trace option");
}
