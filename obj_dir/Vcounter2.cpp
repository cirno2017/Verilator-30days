// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vcounter2__pch.h"
#include "verilated_vcd_c.h"

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
    vlSymsp->__Vm_activity = true;
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
std::unique_ptr<VerilatedTraceConfig> Vcounter2::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vcounter2___024root__trace_decl_types(VerilatedVcd* tracep);

void Vcounter2___024root__trace_init_top(Vcounter2___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vcounter2___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcounter2___024root*>(voidSelf);
    Vcounter2__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    Vcounter2___024root__trace_decl_types(tracep);
    Vcounter2___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vcounter2___024root__trace_register(Vcounter2___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vcounter2::trace(VerilatedVcdC* tfp, int levels, int options) {
    if (tfp->isOpen()) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vcounter2::trace()' shall not be called after 'VerilatedVcdC::open()'.");
    }
    if (false && levels && options) {}  // Prevent unused
    tfp->spTrace()->addModel(this);
    tfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vcounter2___024root__trace_register(&(vlSymsp->TOP), tfp->spTrace());
}
