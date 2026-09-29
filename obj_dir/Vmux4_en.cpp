// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vmux4_en__pch.h"

//============================================================
// Constructors

Vmux4_en::Vmux4_en(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vmux4_en__Syms(contextp(), _vcname__, this)}
    , a{vlSymsp->TOP.a}
    , b{vlSymsp->TOP.b}
    , en{vlSymsp->TOP.en}
    , sel{vlSymsp->TOP.sel}
    , y{vlSymsp->TOP.y}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vmux4_en::Vmux4_en(const char* _vcname__)
    : Vmux4_en(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vmux4_en::~Vmux4_en() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vmux4_en___024root___eval_debug_assertions(Vmux4_en___024root* vlSelf);
#endif  // VL_DEBUG
void Vmux4_en___024root___eval_static(Vmux4_en___024root* vlSelf);
void Vmux4_en___024root___eval_initial(Vmux4_en___024root* vlSelf);
void Vmux4_en___024root___eval_settle(Vmux4_en___024root* vlSelf);
void Vmux4_en___024root___eval(Vmux4_en___024root* vlSelf);

void Vmux4_en::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vmux4_en::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vmux4_en___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vmux4_en___024root___eval_static(&(vlSymsp->TOP));
        Vmux4_en___024root___eval_initial(&(vlSymsp->TOP));
        Vmux4_en___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vmux4_en___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vmux4_en::eventsPending() { return false; }

uint64_t Vmux4_en::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vmux4_en::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vmux4_en___024root___eval_final(Vmux4_en___024root* vlSelf);

VL_ATTR_COLD void Vmux4_en::final() {
    Vmux4_en___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vmux4_en::hierName() const { return vlSymsp->name(); }
const char* Vmux4_en::modelName() const { return "Vmux4_en"; }
unsigned Vmux4_en::threads() const { return 1; }
void Vmux4_en::prepareClone() const { contextp()->prepareClone(); }
void Vmux4_en::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vmux4_en::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vmux4_en::trace()' called on model that was Verilated without --trace option");
}
