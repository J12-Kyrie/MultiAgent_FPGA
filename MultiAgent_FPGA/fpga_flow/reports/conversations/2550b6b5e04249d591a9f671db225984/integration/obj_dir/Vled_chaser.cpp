// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vled_chaser__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vled_chaser::Vled_chaser(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vled_chaser__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst_n{vlSymsp->TOP.rst_n}
    , dir{vlSymsp->TOP.dir}
    , leds{vlSymsp->TOP.leds}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vled_chaser::Vled_chaser(const char* _vcname__)
    : Vled_chaser(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vled_chaser::~Vled_chaser() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vled_chaser___024root___eval_debug_assertions(Vled_chaser___024root* vlSelf);
#endif  // VL_DEBUG
void Vled_chaser___024root___eval_static(Vled_chaser___024root* vlSelf);
void Vled_chaser___024root___eval_initial(Vled_chaser___024root* vlSelf);
void Vled_chaser___024root___eval_settle(Vled_chaser___024root* vlSelf);
void Vled_chaser___024root___eval(Vled_chaser___024root* vlSelf);

void Vled_chaser::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vled_chaser::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vled_chaser___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vled_chaser___024root___eval_static(&(vlSymsp->TOP));
        Vled_chaser___024root___eval_initial(&(vlSymsp->TOP));
        Vled_chaser___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vled_chaser___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vled_chaser::eventsPending() { return false; }

uint64_t Vled_chaser::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vled_chaser::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vled_chaser___024root___eval_final(Vled_chaser___024root* vlSelf);

VL_ATTR_COLD void Vled_chaser::final() {
    Vled_chaser___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vled_chaser::hierName() const { return vlSymsp->name(); }
const char* Vled_chaser::modelName() const { return "Vled_chaser"; }
unsigned Vled_chaser::threads() const { return 1; }
void Vled_chaser::prepareClone() const { contextp()->prepareClone(); }
void Vled_chaser::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vled_chaser::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vled_chaser___024root__trace_decl_types(VerilatedVcd* tracep);

void Vled_chaser___024root__trace_init_top(Vled_chaser___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vled_chaser___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vled_chaser___024root*>(voidSelf);
    Vled_chaser__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    Vled_chaser___024root__trace_decl_types(tracep);
    Vled_chaser___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vled_chaser___024root__trace_register(Vled_chaser___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vled_chaser::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vled_chaser::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP), name(), false, 5);
    Vled_chaser___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
