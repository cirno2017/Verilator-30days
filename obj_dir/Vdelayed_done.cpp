// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vdelayed_done__pch.h"

//============================================================
// Constructors

Vdelayed_done::Vdelayed_done(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vdelayed_done__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , start{vlSymsp->TOP.start}
    , stall{vlSymsp->TOP.stall}
    , busy{vlSymsp->TOP.busy}
    , done{vlSymsp->TOP.done}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vdelayed_done::Vdelayed_done(const char* _vcname__)
    : Vdelayed_done(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vdelayed_done::~Vdelayed_done() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vdelayed_done___024root___eval_debug_assertions(Vdelayed_done___024root* vlSelf);
#endif  // VL_DEBUG
void Vdelayed_done___024root___eval_static(Vdelayed_done___024root* vlSelf);
void Vdelayed_done___024root___eval_initial(Vdelayed_done___024root* vlSelf);
void Vdelayed_done___024root___eval_settle(Vdelayed_done___024root* vlSelf);
void Vdelayed_done___024root___eval(Vdelayed_done___024root* vlSelf);

void Vdelayed_done::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vdelayed_done::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vdelayed_done___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vdelayed_done___024root___eval_static(&(vlSymsp->TOP));
        Vdelayed_done___024root___eval_initial(&(vlSymsp->TOP));
        Vdelayed_done___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vdelayed_done___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vdelayed_done::eventsPending() { return false; }

uint64_t Vdelayed_done::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vdelayed_done::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vdelayed_done___024root___eval_final(Vdelayed_done___024root* vlSelf);

VL_ATTR_COLD void Vdelayed_done::final() {
    Vdelayed_done___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vdelayed_done::hierName() const { return vlSymsp->name(); }
const char* Vdelayed_done::modelName() const { return "Vdelayed_done"; }
unsigned Vdelayed_done::threads() const { return 1; }
void Vdelayed_done::prepareClone() const { contextp()->prepareClone(); }
void Vdelayed_done::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vdelayed_done::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vdelayed_done::trace()' called on model that was Verilated without --trace option");
}
