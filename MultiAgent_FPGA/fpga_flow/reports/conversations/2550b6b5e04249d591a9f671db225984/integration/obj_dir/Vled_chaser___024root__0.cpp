// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vled_chaser.h for the primary calling header

#include "Vled_chaser__pch.h"

void Vled_chaser___024root___eval_triggers_vec__act(Vled_chaser___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___eval_triggers_vec__act\n"); );
    Vled_chaser__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((((~ (IData)(vlSelfRef.rst_n))
                                                       & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0))
                                                      << 1U)
                                                     | ((IData)(vlSelfRef.clk)
                                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
}

bool Vled_chaser___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___trigger_anySet__act\n"); );
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

extern const VlUnpacked<CData/*3:0*/, 64> Vled_chaser__ConstPool__TABLE_h15cbfe7c_0;

void Vled_chaser___024root___nba_sequent__TOP__0(Vled_chaser___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___nba_sequent__TOP__0\n"); );
    Vled_chaser__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*5:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    __Vtableidx1 = (((IData)(vlSelfRef.led_chaser__DOT__led_state)
                     << 2U) | (((IData)(vlSelfRef.dir)
                                << 1U) | (IData)(vlSelfRef.rst_n)));
    vlSelfRef.led_chaser__DOT__led_state = Vled_chaser__ConstPool__TABLE_h15cbfe7c_0
        [__Vtableidx1];
    vlSelfRef.leds = vlSelfRef.led_chaser__DOT__led_state;
}

void Vled_chaser___024root___eval_nba(Vled_chaser___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___eval_nba\n"); );
    Vled_chaser__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vled_chaser___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vled_chaser___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vled_chaser___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vled_chaser___024root___eval_phase__act(Vled_chaser___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___eval_phase__act\n"); );
    Vled_chaser__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vled_chaser___024root___eval_triggers_vec__act(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vled_chaser___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vled_chaser___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vled_chaser___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vled_chaser___024root___eval_phase__nba(Vled_chaser___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___eval_phase__nba\n"); );
    Vled_chaser__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vled_chaser___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vled_chaser___024root___eval_nba(vlSelf);
        Vled_chaser___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vled_chaser___024root___eval(Vled_chaser___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___eval\n"); );
    Vled_chaser__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vled_chaser___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("/Users/kyrie/Downloads/OpenHands-1.5.0/MultiAgent_FPGA/fpga_flow/reports/conversations/2550b6b5e04249d591a9f671db225984/promoted/led_chaser/rtl/led_chaser.v", 3, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vled_chaser___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("/Users/kyrie/Downloads/OpenHands-1.5.0/MultiAgent_FPGA/fpga_flow/reports/conversations/2550b6b5e04249d591a9f671db225984/promoted/led_chaser/rtl/led_chaser.v", 3, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U)
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vled_chaser___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vled_chaser___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vled_chaser___024root___eval_debug_assertions(Vled_chaser___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vled_chaser___024root___eval_debug_assertions\n"); );
    Vled_chaser__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst_n & 0xfeU)))) {
        Verilated::overWidthError("rst_n");
    }
    if (VL_UNLIKELY(((vlSelfRef.dir & 0xfeU)))) {
        Verilated::overWidthError("dir");
    }
}
#endif  // VL_DEBUG
