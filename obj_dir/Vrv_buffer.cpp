// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vrv_buffer__pch.h"

//============================================================
// Constructors

Vrv_buffer::Vrv_buffer(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vrv_buffer__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , in_valid{vlSymsp->TOP.in_valid}
    , in_ready{vlSymsp->TOP.in_ready}
    , in_data{vlSymsp->TOP.in_data}
    , out_valid{vlSymsp->TOP.out_valid}
    , out_ready{vlSymsp->TOP.out_ready}
    , out_data{vlSymsp->TOP.out_data}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vrv_buffer::Vrv_buffer(const char* _vcname__)
    : Vrv_buffer(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vrv_buffer::~Vrv_buffer() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vrv_buffer___024root___eval_debug_assertions(Vrv_buffer___024root* vlSelf);
#endif  // VL_DEBUG
void Vrv_buffer___024root___eval_static(Vrv_buffer___024root* vlSelf);
void Vrv_buffer___024root___eval_initial(Vrv_buffer___024root* vlSelf);
void Vrv_buffer___024root___eval_settle(Vrv_buffer___024root* vlSelf);
void Vrv_buffer___024root___eval(Vrv_buffer___024root* vlSelf);

void Vrv_buffer::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vrv_buffer::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vrv_buffer___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vrv_buffer___024root___eval_static(&(vlSymsp->TOP));
        Vrv_buffer___024root___eval_initial(&(vlSymsp->TOP));
        Vrv_buffer___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vrv_buffer___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vrv_buffer::eventsPending() { return false; }

uint64_t Vrv_buffer::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vrv_buffer::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vrv_buffer___024root___eval_final(Vrv_buffer___024root* vlSelf);

VL_ATTR_COLD void Vrv_buffer::final() {
    Vrv_buffer___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vrv_buffer::hierName() const { return vlSymsp->name(); }
const char* Vrv_buffer::modelName() const { return "Vrv_buffer"; }
unsigned Vrv_buffer::threads() const { return 1; }
void Vrv_buffer::prepareClone() const { contextp()->prepareClone(); }
void Vrv_buffer::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vrv_buffer::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vrv_buffer::trace()' called on model that was Verilated without --trace option");
}
