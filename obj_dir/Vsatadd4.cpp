// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vsatadd4__pch.h"

//============================================================
// Constructors

Vsatadd4::Vsatadd4(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vsatadd4__Syms(contextp(), _vcname__, this)}
    , a{vlSymsp->TOP.a}
    , b{vlSymsp->TOP.b}
    , sat_en{vlSymsp->TOP.sat_en}
    , y{vlSymsp->TOP.y}
    , overflow{vlSymsp->TOP.overflow}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vsatadd4::Vsatadd4(const char* _vcname__)
    : Vsatadd4(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vsatadd4::~Vsatadd4() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vsatadd4___024root___eval_debug_assertions(Vsatadd4___024root* vlSelf);
#endif  // VL_DEBUG
void Vsatadd4___024root___eval_static(Vsatadd4___024root* vlSelf);
void Vsatadd4___024root___eval_initial(Vsatadd4___024root* vlSelf);
void Vsatadd4___024root___eval_settle(Vsatadd4___024root* vlSelf);
void Vsatadd4___024root___eval(Vsatadd4___024root* vlSelf);

void Vsatadd4::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vsatadd4::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vsatadd4___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vsatadd4___024root___eval_static(&(vlSymsp->TOP));
        Vsatadd4___024root___eval_initial(&(vlSymsp->TOP));
        Vsatadd4___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vsatadd4___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vsatadd4::eventsPending() { return false; }

uint64_t Vsatadd4::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vsatadd4::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vsatadd4___024root___eval_final(Vsatadd4___024root* vlSelf);

VL_ATTR_COLD void Vsatadd4::final() {
    Vsatadd4___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vsatadd4::hierName() const { return vlSymsp->name(); }
const char* Vsatadd4::modelName() const { return "Vsatadd4"; }
unsigned Vsatadd4::threads() const { return 1; }
void Vsatadd4::prepareClone() const { contextp()->prepareClone(); }
void Vsatadd4::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vsatadd4::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vsatadd4::trace()' called on model that was Verilated without --trace option");
}
