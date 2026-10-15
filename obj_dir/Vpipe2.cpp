// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vpipe2__pch.h"

//============================================================
// Constructors

Vpipe2::Vpipe2(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vpipe2__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , in_valid{vlSymsp->TOP.in_valid}
    , in_data{vlSymsp->TOP.in_data}
    , out_valid{vlSymsp->TOP.out_valid}
    , out_data{vlSymsp->TOP.out_data}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vpipe2::Vpipe2(const char* _vcname__)
    : Vpipe2(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vpipe2::~Vpipe2() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vpipe2___024root___eval_debug_assertions(Vpipe2___024root* vlSelf);
#endif  // VL_DEBUG
void Vpipe2___024root___eval_static(Vpipe2___024root* vlSelf);
void Vpipe2___024root___eval_initial(Vpipe2___024root* vlSelf);
void Vpipe2___024root___eval_settle(Vpipe2___024root* vlSelf);
void Vpipe2___024root___eval(Vpipe2___024root* vlSelf);

void Vpipe2::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vpipe2::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vpipe2___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vpipe2___024root___eval_static(&(vlSymsp->TOP));
        Vpipe2___024root___eval_initial(&(vlSymsp->TOP));
        Vpipe2___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vpipe2___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vpipe2::eventsPending() { return false; }

uint64_t Vpipe2::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vpipe2::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vpipe2___024root___eval_final(Vpipe2___024root* vlSelf);

VL_ATTR_COLD void Vpipe2::final() {
    Vpipe2___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vpipe2::hierName() const { return vlSymsp->name(); }
const char* Vpipe2::modelName() const { return "Vpipe2"; }
unsigned Vpipe2::threads() const { return 1; }
void Vpipe2::prepareClone() const { contextp()->prepareClone(); }
void Vpipe2::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vpipe2::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vpipe2::trace()' called on model that was Verilated without --trace option");
}
