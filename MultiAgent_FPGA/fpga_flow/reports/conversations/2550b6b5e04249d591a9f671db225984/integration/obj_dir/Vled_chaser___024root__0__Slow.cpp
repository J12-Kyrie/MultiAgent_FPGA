// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vled_chaser.h for the primary calling header

#include "Vled_chaser__pch.h"

VL_ATTR_COLD void Vled_chaser___024root___eval_static(Vled_chaser___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___eval_static\n"); );
    Vled_chaser__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
}

VL_ATTR_COLD void Vled_chaser___024root___eval_initial(Vled_chaser___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___eval_initial\n"); );
    Vled_chaser__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vled_chaser___024root___eval_final(Vled_chaser___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___eval_final\n"); );
    Vled_chaser__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vled_chaser___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vled_chaser___024root___eval_phase__stl(Vled_chaser___024root* vlSelf);

VL_ATTR_COLD void Vled_chaser___024root___eval_settle(Vled_chaser___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___eval_settle\n"); );
    Vled_chaser__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vled_chaser___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("/Users/kyrie/Downloads/OpenHands-1.5.0/MultiAgent_FPGA/fpga_flow/reports/conversations/2550b6b5e04249d591a9f671db225984/promoted/led_chaser/rtl/led_chaser.v", 3, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vled_chaser___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vled_chaser___024root___eval_triggers_vec__stl(Vled_chaser___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___eval_triggers_vec__stl\n"); );
    Vled_chaser__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL
                                      & vlSelfRef.__VstlTriggered[0U])
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vled_chaser___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vled_chaser___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vled_chaser___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vled_chaser___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___trigger_anySet__stl\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

VL_ATTR_COLD void Vled_chaser___024root___stl_sequent__TOP__0(Vled_chaser___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___stl_sequent__TOP__0\n"); );
    Vled_chaser__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.leds = vlSelfRef.led_chaser__DOT__led_state;
}

VL_ATTR_COLD void Vled_chaser___024root___eval_stl(Vled_chaser___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___eval_stl\n"); );
    Vled_chaser__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vled_chaser___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vled_chaser___024root___eval_phase__stl(Vled_chaser___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___eval_phase__stl\n"); );
    Vled_chaser__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vled_chaser___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vled_chaser___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vled_chaser___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vled_chaser___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vled_chaser___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vled_chaser___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vled_chaser___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vled_chaser___024root___ctor_var_reset(Vled_chaser___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___ctor_var_reset\n"); );
    Vled_chaser__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1638864771569018232ull);
    vlSelf->dir = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5391756592262503340ull);
    vlSelf->leds = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 15857012054290625897ull);
    vlSelf->led_chaser__DOT__led_state = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 2952993339948412384ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
