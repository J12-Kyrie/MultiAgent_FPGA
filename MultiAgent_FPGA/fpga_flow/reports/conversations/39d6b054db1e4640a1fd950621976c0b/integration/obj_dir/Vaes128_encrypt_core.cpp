// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vaes128_encrypt_core__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vaes128_encrypt_core::Vaes128_encrypt_core(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vaes128_encrypt_core__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst_n{vlSymsp->TOP.rst_n}
    , start{vlSymsp->TOP.start}
    , busy{vlSymsp->TOP.busy}
    , done{vlSymsp->TOP.done}
    , key{vlSymsp->TOP.key}
    , plaintext{vlSymsp->TOP.plaintext}
    , ciphertext{vlSymsp->TOP.ciphertext}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vaes128_encrypt_core::Vaes128_encrypt_core(const char* _vcname__)
    : Vaes128_encrypt_core(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vaes128_encrypt_core::~Vaes128_encrypt_core() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vaes128_encrypt_core___024root___eval_debug_assertions(Vaes128_encrypt_core___024root* vlSelf);
#endif  // VL_DEBUG
void Vaes128_encrypt_core___024root___eval_static(Vaes128_encrypt_core___024root* vlSelf);
void Vaes128_encrypt_core___024root___eval_initial(Vaes128_encrypt_core___024root* vlSelf);
void Vaes128_encrypt_core___024root___eval_settle(Vaes128_encrypt_core___024root* vlSelf);
void Vaes128_encrypt_core___024root___eval(Vaes128_encrypt_core___024root* vlSelf);

void Vaes128_encrypt_core::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vaes128_encrypt_core::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vaes128_encrypt_core___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vaes128_encrypt_core___024root___eval_static(&(vlSymsp->TOP));
        Vaes128_encrypt_core___024root___eval_initial(&(vlSymsp->TOP));
        Vaes128_encrypt_core___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vaes128_encrypt_core___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vaes128_encrypt_core::eventsPending() { return false; }

uint64_t Vaes128_encrypt_core::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vaes128_encrypt_core::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vaes128_encrypt_core___024root___eval_final(Vaes128_encrypt_core___024root* vlSelf);

VL_ATTR_COLD void Vaes128_encrypt_core::final() {
    Vaes128_encrypt_core___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vaes128_encrypt_core::hierName() const { return vlSymsp->name(); }
const char* Vaes128_encrypt_core::modelName() const { return "Vaes128_encrypt_core"; }
unsigned Vaes128_encrypt_core::threads() const { return 1; }
void Vaes128_encrypt_core::prepareClone() const { contextp()->prepareClone(); }
void Vaes128_encrypt_core::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vaes128_encrypt_core::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vaes128_encrypt_core___024root__trace_decl_types(VerilatedVcd* tracep);

void Vaes128_encrypt_core___024root__trace_init_top(Vaes128_encrypt_core___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vaes128_encrypt_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaes128_encrypt_core___024root*>(voidSelf);
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    Vaes128_encrypt_core___024root__trace_decl_types(tracep);
    Vaes128_encrypt_core___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vaes128_encrypt_core___024root__trace_register(Vaes128_encrypt_core___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vaes128_encrypt_core::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vaes128_encrypt_core::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP), name(), false, 142);
    Vaes128_encrypt_core___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
