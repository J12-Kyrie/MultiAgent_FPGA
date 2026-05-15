// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaes128_encrypt_core.h for the primary calling header

#include "Vaes128_encrypt_core__pch.h"

void Vaes128_encrypt_core___024root___eval_triggers_vec__act(Vaes128_encrypt_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root___eval_triggers_vec__act\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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

bool Vaes128_encrypt_core___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root___trigger_anySet__act\n"); );
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

void Vaes128_encrypt_core___024root___nba_sequent__TOP__0(Vaes128_encrypt_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root___nba_sequent__TOP__0\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlWide<4>/*127:0*/ __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__Vfuncout;
    VL_ZERO_W(128, __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__Vfuncout);
    VlWide<4>/*127:0*/ __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__key_in;
    VL_ZERO_W(128, __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__key_in);
    CData/*3:0*/ __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__round;
    __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__round = 0;
    VlWide<4>/*127:0*/ __Vdly__aes128_encrypt_core__DOT__key_reg;
    VL_ZERO_W(128, __Vdly__aes128_encrypt_core__DOT__key_reg);
    VlWide<4>/*127:0*/ __Vdly__aes128_encrypt_core__DOT__plaintext_reg;
    VL_ZERO_W(128, __Vdly__aes128_encrypt_core__DOT__plaintext_reg);
    CData/*3:0*/ __Vdly__aes128_encrypt_core__DOT__round_index;
    __Vdly__aes128_encrypt_core__DOT__round_index = 0;
    CData/*1:0*/ __Vdly__aes128_encrypt_core__DOT__fsm_state;
    __Vdly__aes128_encrypt_core__DOT__fsm_state = 0;
    // Body
    __Vdly__aes128_encrypt_core__DOT__plaintext_reg[0U]
        = vlSelfRef.aes128_encrypt_core__DOT__plaintext_reg[0U];
    __Vdly__aes128_encrypt_core__DOT__plaintext_reg[1U]
        = vlSelfRef.aes128_encrypt_core__DOT__plaintext_reg[1U];
    __Vdly__aes128_encrypt_core__DOT__plaintext_reg[2U]
        = vlSelfRef.aes128_encrypt_core__DOT__plaintext_reg[2U];
    __Vdly__aes128_encrypt_core__DOT__plaintext_reg[3U]
        = vlSelfRef.aes128_encrypt_core__DOT__plaintext_reg[3U];
    __Vdly__aes128_encrypt_core__DOT__fsm_state = vlSelfRef.aes128_encrypt_core__DOT__fsm_state;
    __Vdly__aes128_encrypt_core__DOT__key_reg[0U] = vlSelfRef.aes128_encrypt_core__DOT__key_reg[0U];
    __Vdly__aes128_encrypt_core__DOT__key_reg[1U] = vlSelfRef.aes128_encrypt_core__DOT__key_reg[1U];
    __Vdly__aes128_encrypt_core__DOT__key_reg[2U] = vlSelfRef.aes128_encrypt_core__DOT__key_reg[2U];
    __Vdly__aes128_encrypt_core__DOT__key_reg[3U] = vlSelfRef.aes128_encrypt_core__DOT__key_reg[3U];
    __Vdly__aes128_encrypt_core__DOT__round_index = vlSelfRef.aes128_encrypt_core__DOT__round_index;
    if (vlSelfRef.rst_n) {
        vlSelfRef.done = 0U;
        if ((0U == (IData)(vlSelfRef.aes128_encrypt_core__DOT__fsm_state))) {
            vlSelfRef.busy = 0U;
            if (vlSelfRef.start) {
                __Vdly__aes128_encrypt_core__DOT__key_reg[0U]
                    = vlSelfRef.key[0U];
                __Vdly__aes128_encrypt_core__DOT__key_reg[1U]
                    = vlSelfRef.key[1U];
                __Vdly__aes128_encrypt_core__DOT__key_reg[2U]
                    = vlSelfRef.key[2U];
                __Vdly__aes128_encrypt_core__DOT__key_reg[3U]
                    = vlSelfRef.key[3U];
                __Vdly__aes128_encrypt_core__DOT__plaintext_reg[0U]
                    = vlSelfRef.plaintext[0U];
                __Vdly__aes128_encrypt_core__DOT__plaintext_reg[1U]
                    = vlSelfRef.plaintext[1U];
                __Vdly__aes128_encrypt_core__DOT__plaintext_reg[2U]
                    = vlSelfRef.plaintext[2U];
                __Vdly__aes128_encrypt_core__DOT__plaintext_reg[3U]
                    = vlSelfRef.plaintext[3U];
                vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U]
                    = (vlSelfRef.plaintext[0U] ^ vlSelfRef.key[0U]);
                vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U]
                    = (vlSelfRef.plaintext[1U] ^ vlSelfRef.key[1U]);
                vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U]
                    = (vlSelfRef.plaintext[2U] ^ vlSelfRef.key[2U]);
                vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U]
                    = (vlSelfRef.plaintext[3U] ^ vlSelfRef.key[3U]);
                __Vdly__aes128_encrypt_core__DOT__round_index = 1U;
                vlSelfRef.busy = 1U;
                __Vdly__aes128_encrypt_core__DOT__fsm_state = 1U;
            }
        } else if ((1U == (IData)(vlSelfRef.aes128_encrypt_core__DOT__fsm_state))) {
            vlSelfRef.busy = 1U;
            if ((1U <= (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))) {
                vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U]
                    = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__state_out[0U];
                vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U]
                    = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__state_out[1U];
                vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U]
                    = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__state_out[2U];
                vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U]
                    = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__state_out[3U];
                if ((0x0aU == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))) {
                    vlSelfRef.ciphertext[0U] = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__state_out[0U];
                    vlSelfRef.ciphertext[1U] = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__state_out[1U];
                    vlSelfRef.ciphertext[2U] = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__state_out[2U];
                    vlSelfRef.ciphertext[3U] = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__state_out[3U];
                    vlSelfRef.done = 1U;
                    __Vdly__aes128_encrypt_core__DOT__fsm_state = 2U;
                    __Vdly__aes128_encrypt_core__DOT__round_index = 0U;
                } else {
                    __Vdly__aes128_encrypt_core__DOT__round_index
                        = (0x0000000fU & ((IData)(1U)
                                          + (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index)));
                }
            } else {
                vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U]
                    = (vlSelfRef.aes128_encrypt_core__DOT__plaintext_reg[0U]
                       ^ vlSelfRef.aes128_encrypt_core__DOT__key_reg[0U]);
                vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U]
                    = (vlSelfRef.aes128_encrypt_core__DOT__plaintext_reg[1U]
                       ^ vlSelfRef.aes128_encrypt_core__DOT__key_reg[1U]);
                vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U]
                    = (vlSelfRef.aes128_encrypt_core__DOT__plaintext_reg[2U]
                       ^ vlSelfRef.aes128_encrypt_core__DOT__key_reg[2U]);
                vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U]
                    = (vlSelfRef.aes128_encrypt_core__DOT__plaintext_reg[3U]
                       ^ vlSelfRef.aes128_encrypt_core__DOT__key_reg[3U]);
                __Vdly__aes128_encrypt_core__DOT__round_index = 1U;
            }
        } else if ((2U == (IData)(vlSelfRef.aes128_encrypt_core__DOT__fsm_state))) {
            vlSelfRef.busy = 0U;
            __Vdly__aes128_encrypt_core__DOT__fsm_state = 0U;
        } else {
            __Vdly__aes128_encrypt_core__DOT__fsm_state = 0U;
            vlSelfRef.busy = 0U;
        }
    } else {
        __Vdly__aes128_encrypt_core__DOT__fsm_state = 0U;
        __Vdly__aes128_encrypt_core__DOT__key_reg[0U] = 0U;
        __Vdly__aes128_encrypt_core__DOT__key_reg[1U] = 0U;
        __Vdly__aes128_encrypt_core__DOT__key_reg[2U] = 0U;
        __Vdly__aes128_encrypt_core__DOT__key_reg[3U] = 0U;
        __Vdly__aes128_encrypt_core__DOT__plaintext_reg[0U] = 0U;
        __Vdly__aes128_encrypt_core__DOT__plaintext_reg[1U] = 0U;
        __Vdly__aes128_encrypt_core__DOT__plaintext_reg[2U] = 0U;
        __Vdly__aes128_encrypt_core__DOT__plaintext_reg[3U] = 0U;
        vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U] = 0U;
        vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U] = 0U;
        vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U] = 0U;
        vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U] = 0U;
        __Vdly__aes128_encrypt_core__DOT__round_index = 0U;
        vlSelfRef.busy = 0U;
        vlSelfRef.done = 0U;
        vlSelfRef.ciphertext[0U] = 0U;
        vlSelfRef.ciphertext[1U] = 0U;
        vlSelfRef.ciphertext[2U] = 0U;
        vlSelfRef.ciphertext[3U] = 0U;
    }
    vlSelfRef.aes128_encrypt_core__DOT__plaintext_reg[0U]
        = __Vdly__aes128_encrypt_core__DOT__plaintext_reg[0U];
    vlSelfRef.aes128_encrypt_core__DOT__plaintext_reg[1U]
        = __Vdly__aes128_encrypt_core__DOT__plaintext_reg[1U];
    vlSelfRef.aes128_encrypt_core__DOT__plaintext_reg[2U]
        = __Vdly__aes128_encrypt_core__DOT__plaintext_reg[2U];
    vlSelfRef.aes128_encrypt_core__DOT__plaintext_reg[3U]
        = __Vdly__aes128_encrypt_core__DOT__plaintext_reg[3U];
    vlSelfRef.aes128_encrypt_core__DOT__fsm_state = __Vdly__aes128_encrypt_core__DOT__fsm_state;
    vlSelfRef.aes128_encrypt_core__DOT__key_reg[0U]
        = __Vdly__aes128_encrypt_core__DOT__key_reg[0U];
    vlSelfRef.aes128_encrypt_core__DOT__key_reg[1U]
        = __Vdly__aes128_encrypt_core__DOT__key_reg[1U];
    vlSelfRef.aes128_encrypt_core__DOT__key_reg[2U]
        = __Vdly__aes128_encrypt_core__DOT__key_reg[2U];
    vlSelfRef.aes128_encrypt_core__DOT__key_reg[3U]
        = __Vdly__aes128_encrypt_core__DOT__key_reg[3U];
    vlSelfRef.aes128_encrypt_core__DOT__round_index
        = __Vdly__aes128_encrypt_core__DOT__round_index;
    __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__round
        = vlSelfRef.aes128_encrypt_core__DOT__round_index;
    __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__key_in[0U]
        = vlSelfRef.aes128_encrypt_core__DOT__key_reg[0U];
    __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__key_in[1U]
        = vlSelfRef.aes128_encrypt_core__DOT__key_reg[1U];
    __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__key_in[2U]
        = vlSelfRef.aes128_encrypt_core__DOT__key_reg[2U];
    __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__key_in[3U]
        = vlSelfRef.aes128_encrypt_core__DOT__key_reg[3U];
    vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w0
        = __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__key_in[3U];
    vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w1
        = __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__key_in[2U];
    vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w2
        = __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__key_in[1U];
    vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w3
        = __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__key_in[0U];
    vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__i = 1U;
    while ((VL_GTES_III(32, 0x0000000aU, vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__i)
            & (vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__i
               <= (IData)(__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__round)))) {
        vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__round_sel
            = (0x0000000fU & vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__i);
        vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__temp
            = (([&]() {
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rot_word__2__value
                        = vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w3;
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rot_word__2__Vfuncout
                        = ((vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rot_word__2__value
                            << 8U) | (vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rot_word__2__value
                                      >> 0x18U));
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__sub_word__1__value
                        = vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rot_word__2__Vfuncout;
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__sub_word__1__Vfuncout
                        = ((([&]() {
                                    vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte
                                        = (vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__sub_word__1__value
                                           >> 0x18U);
                                    vlSelf->__Vfunc_aes_sbox_lut__3__Vfuncout = 0;
                                    vlSelfRef.__Vfunc_aes_sbox_lut__3__Vfuncout
                                        = ((0x00000080U
                                            & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                            ? ((0x00000040U
                                                & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                ? (
                                                   (0x00000020U
                                                    & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                    ?
                                                   ((0x00000010U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                     ?
                                                    ((8U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                      ?
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x16U
                                                         : 0xbbU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x54U
                                                         : 0xb0U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x0fU
                                                         : 0x2dU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x99U
                                                         : 0x41U)))
                                                      :
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x68U
                                                         : 0x42U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xe6U
                                                         : 0xbfU))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x0dU
                                                         : 0x89U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xa1U
                                                         : 0x8cU))))
                                                     :
                                                    ((8U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                      ?
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xdfU
                                                         : 0x28U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x55U
                                                         : 0xceU))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xe9U
                                                         : 0x87U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x1eU
                                                         : 0x9bU)))
                                                      :
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x94U
                                                         : 0x8eU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xd9U
                                                         : 0x69U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x11U
                                                         : 0x98U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xf8U
                                                         : 0xe1U)))))
                                                    :
                                                   ((0x00000010U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                     ?
                                                    ((8U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                      ?
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x9eU
                                                         : 0x1dU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xc1U
                                                         : 0x86U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xb9U
                                                         : 0x57U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x35U
                                                         : 0x61U)))
                                                      :
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x0eU
                                                         : 0xf6U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 3U
                                                         : 0x48U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x66U
                                                         : 0xb5U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x3eU
                                                         : 0x70U))))
                                                     :
                                                    ((8U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                      ?
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x8aU
                                                         : 0x8bU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xbdU
                                                         : 0x4bU))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x1fU
                                                         : 0x74U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xddU
                                                         : 0xe8U)))
                                                      :
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xc6U
                                                         : 0xb4U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xa6U
                                                         : 0x1cU))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x2eU
                                                         : 0x25U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x78U
                                                         : 0xbaU))))))
                                                : (
                                                   (0x00000020U
                                                    & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                    ?
                                                   ((0x00000010U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                     ?
                                                    ((8U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                      ?
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 8U
                                                         : 0xaeU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x7aU
                                                         : 0x65U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xeaU
                                                         : 0xf4U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x56U
                                                         : 0x6cU)))
                                                      :
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xa9U
                                                         : 0x4eU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xd5U
                                                         : 0x8dU))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x6dU
                                                         : 0x37U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xc8U
                                                         : 0xe7U))))
                                                     :
                                                    ((8U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                      ?
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x79U
                                                         : 0xe4U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x95U
                                                         : 0x91U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x62U
                                                         : 0xacU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xd3U
                                                         : 0xc2U)))
                                                      :
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x5cU
                                                         : 0x24U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 6U
                                                         : 0x49U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x0aU
                                                         : 0x3aU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x32U
                                                         : 0xe0U)))))
                                                    :
                                                   ((0x00000010U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                     ?
                                                    ((8U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                      ?
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xdbU
                                                         : 0x0bU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x5eU
                                                         : 0xdeU))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x14U
                                                         : 0xb8U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xeeU
                                                         : 0x46U)))
                                                      :
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x88U
                                                         : 0x90U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x2aU
                                                         : 0x22U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xdcU
                                                         : 0x4fU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x81U
                                                         : 0x60U))))
                                                     :
                                                    ((8U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                      ?
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x73U
                                                         : 0x19U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x5dU
                                                         : 0x64U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x3dU
                                                         : 0x7eU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xa7U
                                                         : 0xc4U)))
                                                      :
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x17U
                                                         : 0x44U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x97U
                                                         : 0x5fU))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xecU
                                                         : 0x13U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x0cU
                                                         : 0xcdU)))))))
                                            : ((0x00000040U
                                                & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                ? (
                                                   (0x00000020U
                                                    & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                    ?
                                                   ((0x00000010U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                     ?
                                                    ((8U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                      ?
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xd2U
                                                         : 0xf3U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xffU
                                                         : 0x10U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x21U
                                                         : 0xdaU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xb6U
                                                         : 0xbcU)))
                                                      :
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xf5U
                                                         : 0x38U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x9dU
                                                         : 0x92U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x8fU
                                                         : 0x40U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xa3U
                                                         : 0x51U))))
                                                     :
                                                    ((8U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                      ?
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xa8U
                                                         : 0x9fU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x3cU
                                                         : 0x50U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x7fU
                                                         : 2U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xf9U
                                                         : 0x45U)))
                                                      :
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x85U
                                                         : 0x33U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x4dU
                                                         : 0x43U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xfbU
                                                         : 0xaaU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xefU
                                                         : 0xd0U)))))
                                                    :
                                                   ((0x00000010U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                     ?
                                                    ((8U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                      ?
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xcfU
                                                         : 0x58U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x4cU
                                                         : 0x4aU))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x39U
                                                         : 0xbeU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xcbU
                                                         : 0x6aU)))
                                                      :
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x5bU
                                                         : 0xb1U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xfcU
                                                         : 0x20U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xedU
                                                         : 0U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xd1U
                                                         : 0x53U))))
                                                     :
                                                    ((8U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                      ?
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x84U
                                                         : 0x2fU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xe3U
                                                         : 0x29U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xb3U
                                                         : 0xd6U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x3bU
                                                         : 0x52U)))
                                                      :
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xa0U
                                                         : 0x5aU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x6eU
                                                         : 0x1bU))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x1aU
                                                         : 0x2cU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x83U
                                                         : 9U))))))
                                                : (
                                                   (0x00000020U
                                                    & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                    ?
                                                   ((0x00000010U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                     ?
                                                    ((8U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                      ?
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x75U
                                                         : 0xb2U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x27U
                                                         : 0xebU))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xe2U
                                                         : 0x80U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x12U
                                                         : 7U)))
                                                      :
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x9aU
                                                         : 5U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x96U
                                                         : 0x18U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xc3U
                                                         : 0x23U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xc7U
                                                         : 4U))))
                                                     :
                                                    ((8U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                      ?
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x15U
                                                         : 0x31U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xd8U
                                                         : 0x71U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xf1U
                                                         : 0xe5U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xa5U
                                                         : 0x34U)))
                                                      :
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xccU
                                                         : 0xf7U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x3fU
                                                         : 0x36U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x26U
                                                         : 0x93U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xfdU
                                                         : 0xb7U)))))
                                                    :
                                                   ((0x00000010U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                     ?
                                                    ((8U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                      ?
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xc0U
                                                         : 0x72U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xa4U
                                                         : 0x9cU))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xafU
                                                         : 0xa2U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xd4U
                                                         : 0xadU)))
                                                      :
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xf0U
                                                         : 0x47U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x59U
                                                         : 0xfaU))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x7dU
                                                         : 0xc9U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x82U
                                                         : 0xcaU))))
                                                     :
                                                    ((8U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                      ?
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x76U
                                                         : 0xabU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xd7U
                                                         : 0xfeU))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x2bU
                                                         : 0x67U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 1U
                                                         : 0x30U)))
                                                      :
                                                     ((4U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                       ?
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0xc5U
                                                         : 0x6fU)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x6bU
                                                         : 0xf2U))
                                                       :
                                                      ((2U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                        ?
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x7bU
                                                         : 0x77U)
                                                        :
                                                       ((1U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__in_byte))
                                                         ? 0x7cU
                                                         : 0x63U))))))));
                                }(), (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__3__Vfuncout))
                            << 0x00000018U) | ((([&]() {
                                        vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte
                                            = (0x000000ffU
                                               & (vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__sub_word__1__value
                                                  >> 0x10U));
                                        vlSelf->__Vfunc_aes_sbox_lut__4__Vfuncout = 0;
                                        vlSelfRef.__Vfunc_aes_sbox_lut__4__Vfuncout
                                            = ((0x00000080U
                                                & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                ? (
                                                   (0x00000040U
                                                    & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                    ?
                                                   ((0x00000020U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                     ?
                                                    ((0x00000010U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                      ?
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x16U
                                                          : 0xbbU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x54U
                                                          : 0xb0U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x0fU
                                                          : 0x2dU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x99U
                                                          : 0x41U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x68U
                                                          : 0x42U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xe6U
                                                          : 0xbfU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x0dU
                                                          : 0x89U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xa1U
                                                          : 0x8cU))))
                                                      :
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xdfU
                                                          : 0x28U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x55U
                                                          : 0xceU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xe9U
                                                          : 0x87U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x1eU
                                                          : 0x9bU)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x94U
                                                          : 0x8eU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xd9U
                                                          : 0x69U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x11U
                                                          : 0x98U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xf8U
                                                          : 0xe1U)))))
                                                     :
                                                    ((0x00000010U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                      ?
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x9eU
                                                          : 0x1dU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xc1U
                                                          : 0x86U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xb9U
                                                          : 0x57U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x35U
                                                          : 0x61U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x0eU
                                                          : 0xf6U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 3U
                                                          : 0x48U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x66U
                                                          : 0xb5U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x3eU
                                                          : 0x70U))))
                                                      :
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x8aU
                                                          : 0x8bU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xbdU
                                                          : 0x4bU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x1fU
                                                          : 0x74U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xddU
                                                          : 0xe8U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xc6U
                                                          : 0xb4U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xa6U
                                                          : 0x1cU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x2eU
                                                          : 0x25U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x78U
                                                          : 0xbaU))))))
                                                    :
                                                   ((0x00000020U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                     ?
                                                    ((0x00000010U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                      ?
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 8U
                                                          : 0xaeU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x7aU
                                                          : 0x65U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xeaU
                                                          : 0xf4U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x56U
                                                          : 0x6cU)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xa9U
                                                          : 0x4eU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xd5U
                                                          : 0x8dU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x6dU
                                                          : 0x37U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xc8U
                                                          : 0xe7U))))
                                                      :
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x79U
                                                          : 0xe4U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x95U
                                                          : 0x91U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x62U
                                                          : 0xacU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xd3U
                                                          : 0xc2U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x5cU
                                                          : 0x24U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 6U
                                                          : 0x49U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x0aU
                                                          : 0x3aU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x32U
                                                          : 0xe0U)))))
                                                     :
                                                    ((0x00000010U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                      ?
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xdbU
                                                          : 0x0bU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x5eU
                                                          : 0xdeU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x14U
                                                          : 0xb8U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xeeU
                                                          : 0x46U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x88U
                                                          : 0x90U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x2aU
                                                          : 0x22U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xdcU
                                                          : 0x4fU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x81U
                                                          : 0x60U))))
                                                      :
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x73U
                                                          : 0x19U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x5dU
                                                          : 0x64U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x3dU
                                                          : 0x7eU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xa7U
                                                          : 0xc4U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x17U
                                                          : 0x44U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x97U
                                                          : 0x5fU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xecU
                                                          : 0x13U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x0cU
                                                          : 0xcdU)))))))
                                                : (
                                                   (0x00000040U
                                                    & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                    ?
                                                   ((0x00000020U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                     ?
                                                    ((0x00000010U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                      ?
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xd2U
                                                          : 0xf3U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xffU
                                                          : 0x10U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x21U
                                                          : 0xdaU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xb6U
                                                          : 0xbcU)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xf5U
                                                          : 0x38U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x9dU
                                                          : 0x92U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x8fU
                                                          : 0x40U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xa3U
                                                          : 0x51U))))
                                                      :
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xa8U
                                                          : 0x9fU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x3cU
                                                          : 0x50U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x7fU
                                                          : 2U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xf9U
                                                          : 0x45U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x85U
                                                          : 0x33U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x4dU
                                                          : 0x43U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xfbU
                                                          : 0xaaU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xefU
                                                          : 0xd0U)))))
                                                     :
                                                    ((0x00000010U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                      ?
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xcfU
                                                          : 0x58U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x4cU
                                                          : 0x4aU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x39U
                                                          : 0xbeU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xcbU
                                                          : 0x6aU)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x5bU
                                                          : 0xb1U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xfcU
                                                          : 0x20U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xedU
                                                          : 0U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xd1U
                                                          : 0x53U))))
                                                      :
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x84U
                                                          : 0x2fU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xe3U
                                                          : 0x29U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xb3U
                                                          : 0xd6U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x3bU
                                                          : 0x52U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xa0U
                                                          : 0x5aU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x6eU
                                                          : 0x1bU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x1aU
                                                          : 0x2cU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x83U
                                                          : 9U))))))
                                                    :
                                                   ((0x00000020U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                     ?
                                                    ((0x00000010U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                      ?
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x75U
                                                          : 0xb2U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x27U
                                                          : 0xebU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xe2U
                                                          : 0x80U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x12U
                                                          : 7U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x9aU
                                                          : 5U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x96U
                                                          : 0x18U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xc3U
                                                          : 0x23U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xc7U
                                                          : 4U))))
                                                      :
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x15U
                                                          : 0x31U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xd8U
                                                          : 0x71U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xf1U
                                                          : 0xe5U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xa5U
                                                          : 0x34U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xccU
                                                          : 0xf7U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x3fU
                                                          : 0x36U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x26U
                                                          : 0x93U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xfdU
                                                          : 0xb7U)))))
                                                     :
                                                    ((0x00000010U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                      ?
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xc0U
                                                          : 0x72U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xa4U
                                                          : 0x9cU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xafU
                                                          : 0xa2U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xd4U
                                                          : 0xadU)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xf0U
                                                          : 0x47U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x59U
                                                          : 0xfaU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x7dU
                                                          : 0xc9U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x82U
                                                          : 0xcaU))))
                                                      :
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x76U
                                                          : 0xabU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xd7U
                                                          : 0xfeU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x2bU
                                                          : 0x67U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 1U
                                                          : 0x30U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0xc5U
                                                          : 0x6fU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x6bU
                                                          : 0xf2U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x7bU
                                                          : 0x77U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__in_byte))
                                                          ? 0x7cU
                                                          : 0x63U))))))));
                                    }(), (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__4__Vfuncout))
                                                << 0x00000010U)
                                               | ((([&]() {
                                            vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte
                                                = (0x000000ffU
                                                   & (vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__sub_word__1__value
                                                      >> 8U));
                                            vlSelf->__Vfunc_aes_sbox_lut__5__Vfuncout = 0;
                                            vlSelfRef.__Vfunc_aes_sbox_lut__5__Vfuncout
                                                = (
                                                   (0x00000080U
                                                    & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                    ?
                                                   ((0x00000040U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                     ?
                                                    ((0x00000020U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                      ?
                                                     ((0x00000010U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                       ?
                                                      ((8U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                        ?
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x16U
                                                           : 0xbbU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x54U
                                                           : 0xb0U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x0fU
                                                           : 0x2dU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x99U
                                                           : 0x41U)))
                                                        :
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x68U
                                                           : 0x42U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xe6U
                                                           : 0xbfU))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x0dU
                                                           : 0x89U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xa1U
                                                           : 0x8cU))))
                                                       :
                                                      ((8U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                        ?
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xdfU
                                                           : 0x28U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x55U
                                                           : 0xceU))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xe9U
                                                           : 0x87U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x1eU
                                                           : 0x9bU)))
                                                        :
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x94U
                                                           : 0x8eU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xd9U
                                                           : 0x69U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x11U
                                                           : 0x98U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xf8U
                                                           : 0xe1U)))))
                                                      :
                                                     ((0x00000010U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                       ?
                                                      ((8U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                        ?
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x9eU
                                                           : 0x1dU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xc1U
                                                           : 0x86U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xb9U
                                                           : 0x57U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x35U
                                                           : 0x61U)))
                                                        :
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x0eU
                                                           : 0xf6U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 3U
                                                           : 0x48U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x66U
                                                           : 0xb5U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x3eU
                                                           : 0x70U))))
                                                       :
                                                      ((8U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                        ?
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x8aU
                                                           : 0x8bU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xbdU
                                                           : 0x4bU))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x1fU
                                                           : 0x74U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xddU
                                                           : 0xe8U)))
                                                        :
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xc6U
                                                           : 0xb4U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xa6U
                                                           : 0x1cU))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x2eU
                                                           : 0x25U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x78U
                                                           : 0xbaU))))))
                                                     :
                                                    ((0x00000020U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                      ?
                                                     ((0x00000010U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                       ?
                                                      ((8U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                        ?
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 8U
                                                           : 0xaeU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x7aU
                                                           : 0x65U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xeaU
                                                           : 0xf4U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x56U
                                                           : 0x6cU)))
                                                        :
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xa9U
                                                           : 0x4eU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xd5U
                                                           : 0x8dU))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x6dU
                                                           : 0x37U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xc8U
                                                           : 0xe7U))))
                                                       :
                                                      ((8U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                        ?
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x79U
                                                           : 0xe4U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x95U
                                                           : 0x91U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x62U
                                                           : 0xacU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xd3U
                                                           : 0xc2U)))
                                                        :
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x5cU
                                                           : 0x24U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 6U
                                                           : 0x49U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x0aU
                                                           : 0x3aU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x32U
                                                           : 0xe0U)))))
                                                      :
                                                     ((0x00000010U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                       ?
                                                      ((8U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                        ?
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xdbU
                                                           : 0x0bU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x5eU
                                                           : 0xdeU))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x14U
                                                           : 0xb8U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xeeU
                                                           : 0x46U)))
                                                        :
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x88U
                                                           : 0x90U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x2aU
                                                           : 0x22U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xdcU
                                                           : 0x4fU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x81U
                                                           : 0x60U))))
                                                       :
                                                      ((8U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                        ?
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x73U
                                                           : 0x19U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x5dU
                                                           : 0x64U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x3dU
                                                           : 0x7eU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xa7U
                                                           : 0xc4U)))
                                                        :
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x17U
                                                           : 0x44U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x97U
                                                           : 0x5fU))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xecU
                                                           : 0x13U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x0cU
                                                           : 0xcdU)))))))
                                                    :
                                                   ((0x00000040U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                     ?
                                                    ((0x00000020U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                      ?
                                                     ((0x00000010U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                       ?
                                                      ((8U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                        ?
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xd2U
                                                           : 0xf3U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xffU
                                                           : 0x10U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x21U
                                                           : 0xdaU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xb6U
                                                           : 0xbcU)))
                                                        :
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xf5U
                                                           : 0x38U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x9dU
                                                           : 0x92U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x8fU
                                                           : 0x40U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xa3U
                                                           : 0x51U))))
                                                       :
                                                      ((8U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                        ?
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xa8U
                                                           : 0x9fU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x3cU
                                                           : 0x50U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x7fU
                                                           : 2U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xf9U
                                                           : 0x45U)))
                                                        :
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x85U
                                                           : 0x33U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x4dU
                                                           : 0x43U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xfbU
                                                           : 0xaaU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xefU
                                                           : 0xd0U)))))
                                                      :
                                                     ((0x00000010U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                       ?
                                                      ((8U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                        ?
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xcfU
                                                           : 0x58U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x4cU
                                                           : 0x4aU))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x39U
                                                           : 0xbeU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xcbU
                                                           : 0x6aU)))
                                                        :
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x5bU
                                                           : 0xb1U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xfcU
                                                           : 0x20U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xedU
                                                           : 0U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xd1U
                                                           : 0x53U))))
                                                       :
                                                      ((8U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                        ?
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x84U
                                                           : 0x2fU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xe3U
                                                           : 0x29U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xb3U
                                                           : 0xd6U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x3bU
                                                           : 0x52U)))
                                                        :
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xa0U
                                                           : 0x5aU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x6eU
                                                           : 0x1bU))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x1aU
                                                           : 0x2cU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x83U
                                                           : 9U))))))
                                                     :
                                                    ((0x00000020U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                      ?
                                                     ((0x00000010U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                       ?
                                                      ((8U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                        ?
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x75U
                                                           : 0xb2U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x27U
                                                           : 0xebU))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xe2U
                                                           : 0x80U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x12U
                                                           : 7U)))
                                                        :
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x9aU
                                                           : 5U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x96U
                                                           : 0x18U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xc3U
                                                           : 0x23U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xc7U
                                                           : 4U))))
                                                       :
                                                      ((8U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                        ?
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x15U
                                                           : 0x31U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xd8U
                                                           : 0x71U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xf1U
                                                           : 0xe5U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xa5U
                                                           : 0x34U)))
                                                        :
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xccU
                                                           : 0xf7U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x3fU
                                                           : 0x36U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x26U
                                                           : 0x93U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xfdU
                                                           : 0xb7U)))))
                                                      :
                                                     ((0x00000010U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                       ?
                                                      ((8U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                        ?
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xc0U
                                                           : 0x72U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xa4U
                                                           : 0x9cU))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xafU
                                                           : 0xa2U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xd4U
                                                           : 0xadU)))
                                                        :
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xf0U
                                                           : 0x47U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x59U
                                                           : 0xfaU))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x7dU
                                                           : 0xc9U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x82U
                                                           : 0xcaU))))
                                                       :
                                                      ((8U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                        ?
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x76U
                                                           : 0xabU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xd7U
                                                           : 0xfeU))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x2bU
                                                           : 0x67U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 1U
                                                           : 0x30U)))
                                                        :
                                                       ((4U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                         ?
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0xc5U
                                                           : 0x6fU)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x6bU
                                                           : 0xf2U))
                                                         :
                                                        ((2U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                          ?
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x7bU
                                                           : 0x77U)
                                                          :
                                                         ((1U
                                                           & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__in_byte))
                                                           ? 0x7cU
                                                           : 0x63U))))))));
                                        }(), (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__5__Vfuncout))
                                                   << 8U)
                                                  | ([&]() {
                                        vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte
                                            = (0x000000ffU
                                               & vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__sub_word__1__value);
                                        vlSelf->__Vfunc_aes_sbox_lut__6__Vfuncout = 0;
                                        vlSelfRef.__Vfunc_aes_sbox_lut__6__Vfuncout
                                            = ((0x00000080U
                                                & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                ? (
                                                   (0x00000040U
                                                    & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                    ?
                                                   ((0x00000020U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                     ?
                                                    ((0x00000010U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                      ?
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x16U
                                                          : 0xbbU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x54U
                                                          : 0xb0U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x0fU
                                                          : 0x2dU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x99U
                                                          : 0x41U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x68U
                                                          : 0x42U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xe6U
                                                          : 0xbfU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x0dU
                                                          : 0x89U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xa1U
                                                          : 0x8cU))))
                                                      :
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xdfU
                                                          : 0x28U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x55U
                                                          : 0xceU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xe9U
                                                          : 0x87U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x1eU
                                                          : 0x9bU)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x94U
                                                          : 0x8eU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xd9U
                                                          : 0x69U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x11U
                                                          : 0x98U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xf8U
                                                          : 0xe1U)))))
                                                     :
                                                    ((0x00000010U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                      ?
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x9eU
                                                          : 0x1dU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xc1U
                                                          : 0x86U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xb9U
                                                          : 0x57U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x35U
                                                          : 0x61U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x0eU
                                                          : 0xf6U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 3U
                                                          : 0x48U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x66U
                                                          : 0xb5U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x3eU
                                                          : 0x70U))))
                                                      :
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x8aU
                                                          : 0x8bU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xbdU
                                                          : 0x4bU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x1fU
                                                          : 0x74U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xddU
                                                          : 0xe8U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xc6U
                                                          : 0xb4U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xa6U
                                                          : 0x1cU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x2eU
                                                          : 0x25U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x78U
                                                          : 0xbaU))))))
                                                    :
                                                   ((0x00000020U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                     ?
                                                    ((0x00000010U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                      ?
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 8U
                                                          : 0xaeU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x7aU
                                                          : 0x65U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xeaU
                                                          : 0xf4U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x56U
                                                          : 0x6cU)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xa9U
                                                          : 0x4eU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xd5U
                                                          : 0x8dU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x6dU
                                                          : 0x37U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xc8U
                                                          : 0xe7U))))
                                                      :
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x79U
                                                          : 0xe4U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x95U
                                                          : 0x91U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x62U
                                                          : 0xacU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xd3U
                                                          : 0xc2U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x5cU
                                                          : 0x24U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 6U
                                                          : 0x49U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x0aU
                                                          : 0x3aU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x32U
                                                          : 0xe0U)))))
                                                     :
                                                    ((0x00000010U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                      ?
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xdbU
                                                          : 0x0bU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x5eU
                                                          : 0xdeU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x14U
                                                          : 0xb8U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xeeU
                                                          : 0x46U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x88U
                                                          : 0x90U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x2aU
                                                          : 0x22U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xdcU
                                                          : 0x4fU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x81U
                                                          : 0x60U))))
                                                      :
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x73U
                                                          : 0x19U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x5dU
                                                          : 0x64U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x3dU
                                                          : 0x7eU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xa7U
                                                          : 0xc4U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x17U
                                                          : 0x44U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x97U
                                                          : 0x5fU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xecU
                                                          : 0x13U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x0cU
                                                          : 0xcdU)))))))
                                                : (
                                                   (0x00000040U
                                                    & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                    ?
                                                   ((0x00000020U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                     ?
                                                    ((0x00000010U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                      ?
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xd2U
                                                          : 0xf3U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xffU
                                                          : 0x10U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x21U
                                                          : 0xdaU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xb6U
                                                          : 0xbcU)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xf5U
                                                          : 0x38U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x9dU
                                                          : 0x92U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x8fU
                                                          : 0x40U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xa3U
                                                          : 0x51U))))
                                                      :
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xa8U
                                                          : 0x9fU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x3cU
                                                          : 0x50U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x7fU
                                                          : 2U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xf9U
                                                          : 0x45U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x85U
                                                          : 0x33U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x4dU
                                                          : 0x43U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xfbU
                                                          : 0xaaU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xefU
                                                          : 0xd0U)))))
                                                     :
                                                    ((0x00000010U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                      ?
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xcfU
                                                          : 0x58U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x4cU
                                                          : 0x4aU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x39U
                                                          : 0xbeU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xcbU
                                                          : 0x6aU)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x5bU
                                                          : 0xb1U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xfcU
                                                          : 0x20U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xedU
                                                          : 0U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xd1U
                                                          : 0x53U))))
                                                      :
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x84U
                                                          : 0x2fU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xe3U
                                                          : 0x29U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xb3U
                                                          : 0xd6U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x3bU
                                                          : 0x52U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xa0U
                                                          : 0x5aU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x6eU
                                                          : 0x1bU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x1aU
                                                          : 0x2cU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x83U
                                                          : 9U))))))
                                                    :
                                                   ((0x00000020U
                                                     & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                     ?
                                                    ((0x00000010U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                      ?
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x75U
                                                          : 0xb2U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x27U
                                                          : 0xebU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xe2U
                                                          : 0x80U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x12U
                                                          : 7U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x9aU
                                                          : 5U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x96U
                                                          : 0x18U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xc3U
                                                          : 0x23U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xc7U
                                                          : 4U))))
                                                      :
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x15U
                                                          : 0x31U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xd8U
                                                          : 0x71U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xf1U
                                                          : 0xe5U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xa5U
                                                          : 0x34U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xccU
                                                          : 0xf7U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x3fU
                                                          : 0x36U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x26U
                                                          : 0x93U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xfdU
                                                          : 0xb7U)))))
                                                     :
                                                    ((0x00000010U
                                                      & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                      ?
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xc0U
                                                          : 0x72U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xa4U
                                                          : 0x9cU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xafU
                                                          : 0xa2U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xd4U
                                                          : 0xadU)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xf0U
                                                          : 0x47U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x59U
                                                          : 0xfaU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x7dU
                                                          : 0xc9U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x82U
                                                          : 0xcaU))))
                                                      :
                                                     ((8U
                                                       & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                       ?
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x76U
                                                          : 0xabU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xd7U
                                                          : 0xfeU))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x2bU
                                                          : 0x67U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 1U
                                                          : 0x30U)))
                                                       :
                                                      ((4U
                                                        & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                        ?
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0xc5U
                                                          : 0x6fU)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x6bU
                                                          : 0xf2U))
                                                        :
                                                       ((2U
                                                         & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                         ?
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x7bU
                                                          : 0x77U)
                                                         :
                                                        ((1U
                                                          & (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__in_byte))
                                                          ? 0x7cU
                                                          : 0x63U))))))));
                                    }(), (IData)(vlSelfRef.__Vfunc_aes_sbox_lut__6__Vfuncout)))));
                }(), vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__sub_word__1__Vfuncout)
               ^ ([&]() {
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__round
                        = vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__round_sel;
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__Vfuncout
                        = ((8U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__round))
                            ? ((4U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__round))
                                ? 0U : ((2U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__round))
                                         ? ((1U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__round))
                                             ? 0U : 0x36000000U)
                                         : ((1U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__round))
                                             ? 0x1b000000U
                                             : 0x80000000U)))
                            : ((4U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__round))
                                ? ((2U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__round))
                                    ? ((1U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__round))
                                        ? 0x40000000U
                                        : 0x20000000U)
                                    : ((1U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__round))
                                        ? 0x10000000U
                                        : 0x08000000U))
                                : ((2U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__round))
                                    ? ((1U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__round))
                                        ? 0x04000000U
                                        : 0x02000000U)
                                    : ((1U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__round))
                                        ? 0x01000000U
                                        : 0U))));
                }(), vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__Vfuncout));
        vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw0
            = (vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w0
               ^ vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__temp);
        vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw1
            = (vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w1
               ^ vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw0);
        vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw2
            = (vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w2
               ^ vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw1);
        vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw3
            = (vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w3
               ^ vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw2);
        vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w0
            = vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw0;
        vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w1
            = vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw1;
        vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w2
            = vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw2;
        vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w3
            = vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw3;
        vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__i
            = ((IData)(1U) + vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__i);
    }
    __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__Vfuncout[0U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w3;
    __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__Vfuncout[1U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w2;
    __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__Vfuncout[2U]
        = (IData)((((QData)((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w0))
                    << 0x00000020U) | (QData)((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w1))));
    __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__Vfuncout[3U]
        = (IData)(((((QData)((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w0))
                     << 0x00000020U) | (QData)((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w1)))
                   >> 0x00000020U));
    vlSelfRef.aes128_encrypt_core__DOT__round_key[0U]
        = __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__Vfuncout[0U];
    vlSelfRef.aes128_encrypt_core__DOT__round_key[1U]
        = __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__Vfuncout[1U];
    vlSelfRef.aes128_encrypt_core__DOT__round_key[2U]
        = __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__Vfuncout[2U];
    vlSelfRef.aes128_encrypt_core__DOT__round_key[3U]
        = __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__0__Vfuncout[3U];
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__0__KET____DOT__u_sb__DOT__out_byte
        = ((vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U]
            >> 0x0000001fU) ? ((0x40000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x20000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x10000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x16U
                                                     : 0xbbU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x54U
                                                     : 0xb0U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x0fU
                                                     : 0x2dU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x99U
                                                     : 0x41U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x68U
                                                     : 0x42U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xe6U
                                                     : 0xbfU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x0dU
                                                     : 0x89U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xa1U
                                                     : 0x8cU))))
                                        : ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xdfU
                                                     : 0x28U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x55U
                                                     : 0xceU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xe9U
                                                     : 0x87U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x1eU
                                                     : 0x9bU)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x94U
                                                     : 0x8eU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xd9U
                                                     : 0x69U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x11U
                                                     : 0x98U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xf8U
                                                     : 0xe1U)))))
                                    : ((0x10000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x9eU
                                                     : 0x1dU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xc1U
                                                     : 0x86U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xb9U
                                                     : 0x57U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x35U
                                                     : 0x61U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x0eU
                                                     : 0xf6U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 3U
                                                     : 0x48U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x66U
                                                     : 0xb5U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x3eU
                                                     : 0x70U))))
                                        : ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x8aU
                                                     : 0x8bU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xbdU
                                                     : 0x4bU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x1fU
                                                     : 0x74U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xddU
                                                     : 0xe8U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xc6U
                                                     : 0xb4U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xa6U
                                                     : 0x1cU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x2eU
                                                     : 0x25U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x78U
                                                     : 0xbaU))))))
                                : ((0x20000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x10000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 8U
                                                     : 0xaeU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x7aU
                                                     : 0x65U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xeaU
                                                     : 0xf4U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x56U
                                                     : 0x6cU)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xa9U
                                                     : 0x4eU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xd5U
                                                     : 0x8dU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x6dU
                                                     : 0x37U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xc8U
                                                     : 0xe7U))))
                                        : ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x79U
                                                     : 0xe4U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x95U
                                                     : 0x91U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x62U
                                                     : 0xacU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xd3U
                                                     : 0xc2U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x5cU
                                                     : 0x24U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 6U
                                                     : 0x49U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x0aU
                                                     : 0x3aU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x32U
                                                     : 0xe0U)))))
                                    : ((0x10000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xdbU
                                                     : 0x0bU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x5eU
                                                     : 0xdeU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x14U
                                                     : 0xb8U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xeeU
                                                     : 0x46U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x88U
                                                     : 0x90U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x2aU
                                                     : 0x22U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xdcU
                                                     : 0x4fU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x81U
                                                     : 0x60U))))
                                        : ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x73U
                                                     : 0x19U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x5dU
                                                     : 0x64U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x3dU
                                                     : 0x7eU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xa7U
                                                     : 0xc4U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x17U
                                                     : 0x44U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x97U
                                                     : 0x5fU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0xecU
                                                     : 0x13U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                                     ? 0x0cU
                                                     : 0xcdU)))))))
            : ((0x40000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                ? ((0x20000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                    ? ((0x10000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd2U : 0xf3U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xffU : 0x10U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x21U : 0xdaU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xb6U : 0xbcU)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf5U : 0x38U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x9dU : 0x92U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x8fU : 0x40U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa3U : 0x51U))))
                        : ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa8U : 0x9fU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3cU : 0x50U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7fU : 2U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf9U : 0x45U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x85U : 0x33U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x4dU : 0x43U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xfbU : 0xaaU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xefU : 0xd0U)))))
                    : ((0x10000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xcfU : 0x58U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x4cU : 0x4aU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x39U : 0xbeU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xcbU : 0x6aU)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x5bU : 0xb1U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xfcU : 0x20U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xedU : 0U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd1U : 0x53U))))
                        : ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x84U : 0x2fU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xe3U : 0x29U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xb3U : 0xd6U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3bU : 0x52U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa0U : 0x5aU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x6eU : 0x1bU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x1aU : 0x2cU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x83U : 9U))))))
                : ((0x20000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                    ? ((0x10000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x75U : 0xb2U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x27U : 0xebU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xe2U : 0x80U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x12U : 7U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x9aU : 5U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x96U : 0x18U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc3U : 0x23U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc7U : 4U))))
                        : ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x15U : 0x31U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd8U : 0x71U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf1U : 0xe5U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa5U : 0x34U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xccU : 0xf7U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3fU : 0x36U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x26U : 0x93U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xfdU : 0xb7U)))))
                    : ((0x10000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc0U : 0x72U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa4U : 0x9cU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xafU : 0xa2U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd4U : 0xadU)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf0U : 0x47U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x59U : 0xfaU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7dU : 0xc9U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x82U : 0xcaU))))
                        : ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x76U : 0xabU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd7U : 0xfeU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x2bU : 0x67U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 1U : 0x30U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc5U : 0x6fU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x6bU : 0xf2U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7bU : 0x77U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7cU : 0x63U))))))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__1__KET____DOT__u_sb__DOT__out_byte
        = ((0x00800000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
            ? ((0x00400000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                ? ((0x00200000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                    ? ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x16U : 0xbbU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x54U : 0xb0U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x0fU : 0x2dU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x99U : 0x41U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x68U : 0x42U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xe6U : 0xbfU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x0dU : 0x89U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa1U : 0x8cU))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xdfU : 0x28U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x55U : 0xceU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xe9U : 0x87U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x1eU : 0x9bU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x94U : 0x8eU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd9U : 0x69U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x11U : 0x98U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf8U : 0xe1U)))))
                    : ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x9eU : 0x1dU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc1U : 0x86U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xb9U : 0x57U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x35U : 0x61U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x0eU : 0xf6U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 3U : 0x48U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x66U : 0xb5U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3eU : 0x70U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x8aU : 0x8bU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xbdU : 0x4bU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x1fU : 0x74U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xddU : 0xe8U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc6U : 0xb4U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa6U : 0x1cU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x2eU : 0x25U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x78U : 0xbaU))))))
                : ((0x00200000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                    ? ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 8U : 0xaeU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7aU : 0x65U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xeaU : 0xf4U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x56U : 0x6cU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa9U : 0x4eU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd5U : 0x8dU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x6dU : 0x37U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc8U : 0xe7U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x79U : 0xe4U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x95U : 0x91U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x62U : 0xacU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd3U : 0xc2U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x5cU : 0x24U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 6U : 0x49U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x0aU : 0x3aU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x32U : 0xe0U)))))
                    : ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xdbU : 0x0bU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x5eU : 0xdeU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x14U : 0xb8U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xeeU : 0x46U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x88U : 0x90U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x2aU : 0x22U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xdcU : 0x4fU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x81U : 0x60U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x73U : 0x19U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x5dU : 0x64U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3dU : 0x7eU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa7U : 0xc4U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x17U : 0x44U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x97U : 0x5fU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xecU : 0x13U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x0cU : 0xcdU)))))))
            : ((0x00400000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                ? ((0x00200000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                    ? ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd2U : 0xf3U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xffU : 0x10U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x21U : 0xdaU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xb6U : 0xbcU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf5U : 0x38U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x9dU : 0x92U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x8fU : 0x40U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa3U : 0x51U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa8U : 0x9fU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3cU : 0x50U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7fU : 2U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf9U : 0x45U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x85U : 0x33U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x4dU : 0x43U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xfbU : 0xaaU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xefU : 0xd0U)))))
                    : ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xcfU : 0x58U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x4cU : 0x4aU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x39U : 0xbeU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xcbU : 0x6aU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x5bU : 0xb1U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xfcU : 0x20U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xedU : 0U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd1U : 0x53U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x84U : 0x2fU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xe3U : 0x29U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xb3U : 0xd6U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3bU : 0x52U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa0U : 0x5aU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x6eU : 0x1bU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x1aU : 0x2cU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x83U : 9U))))))
                : ((0x00200000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                    ? ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x75U : 0xb2U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x27U : 0xebU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xe2U : 0x80U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x12U : 7U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x9aU : 5U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x96U : 0x18U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc3U : 0x23U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc7U : 4U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x15U : 0x31U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd8U : 0x71U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf1U : 0xe5U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa5U : 0x34U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xccU : 0xf7U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3fU : 0x36U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x26U : 0x93U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xfdU : 0xb7U)))))
                    : ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc0U : 0x72U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa4U : 0x9cU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xafU : 0xa2U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd4U : 0xadU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf0U : 0x47U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x59U : 0xfaU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7dU : 0xc9U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x82U : 0xcaU))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x76U : 0xabU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd7U : 0xfeU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x2bU : 0x67U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 1U : 0x30U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc5U : 0x6fU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x6bU : 0xf2U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7bU : 0x77U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7cU : 0x63U))))))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__2__KET____DOT__u_sb__DOT__out_byte
        = ((0x00008000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
            ? ((0x00004000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                ? ((0x00002000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                    ? ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x16U : 0xbbU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x54U : 0xb0U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x0fU : 0x2dU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x99U : 0x41U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x68U : 0x42U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xe6U : 0xbfU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x0dU : 0x89U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa1U : 0x8cU))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xdfU : 0x28U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x55U : 0xceU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xe9U : 0x87U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x1eU : 0x9bU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x94U : 0x8eU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd9U : 0x69U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x11U : 0x98U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf8U : 0xe1U)))))
                    : ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x9eU : 0x1dU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc1U : 0x86U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xb9U : 0x57U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x35U : 0x61U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x0eU : 0xf6U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 3U : 0x48U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x66U : 0xb5U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3eU : 0x70U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x8aU : 0x8bU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xbdU : 0x4bU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x1fU : 0x74U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xddU : 0xe8U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc6U : 0xb4U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa6U : 0x1cU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x2eU : 0x25U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x78U : 0xbaU))))))
                : ((0x00002000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                    ? ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 8U : 0xaeU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7aU : 0x65U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xeaU : 0xf4U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x56U : 0x6cU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa9U : 0x4eU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd5U : 0x8dU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x6dU : 0x37U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc8U : 0xe7U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x79U : 0xe4U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x95U : 0x91U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x62U : 0xacU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd3U : 0xc2U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x5cU : 0x24U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 6U : 0x49U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x0aU : 0x3aU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x32U : 0xe0U)))))
                    : ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xdbU : 0x0bU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x5eU : 0xdeU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x14U : 0xb8U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xeeU : 0x46U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x88U : 0x90U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x2aU : 0x22U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xdcU : 0x4fU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x81U : 0x60U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x73U : 0x19U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x5dU : 0x64U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3dU : 0x7eU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa7U : 0xc4U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x17U : 0x44U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x97U : 0x5fU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xecU : 0x13U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x0cU : 0xcdU)))))))
            : ((0x00004000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                ? ((0x00002000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                    ? ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd2U : 0xf3U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xffU : 0x10U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x21U : 0xdaU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xb6U : 0xbcU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf5U : 0x38U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x9dU : 0x92U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x8fU : 0x40U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa3U : 0x51U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa8U : 0x9fU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3cU : 0x50U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7fU : 2U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf9U : 0x45U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x85U : 0x33U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x4dU : 0x43U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xfbU : 0xaaU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xefU : 0xd0U)))))
                    : ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xcfU : 0x58U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x4cU : 0x4aU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x39U : 0xbeU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xcbU : 0x6aU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x5bU : 0xb1U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xfcU : 0x20U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xedU : 0U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd1U : 0x53U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x84U : 0x2fU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xe3U : 0x29U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xb3U : 0xd6U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3bU : 0x52U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa0U : 0x5aU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x6eU : 0x1bU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x1aU : 0x2cU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x83U : 9U))))))
                : ((0x00002000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                    ? ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x75U : 0xb2U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x27U : 0xebU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xe2U : 0x80U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x12U : 7U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x9aU : 5U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x96U : 0x18U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc3U : 0x23U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc7U : 4U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x15U : 0x31U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd8U : 0x71U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf1U : 0xe5U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa5U : 0x34U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xccU : 0xf7U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3fU : 0x36U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x26U : 0x93U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xfdU : 0xb7U)))))
                    : ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc0U : 0x72U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa4U : 0x9cU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xafU : 0xa2U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd4U : 0xadU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf0U : 0x47U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x59U : 0xfaU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7dU : 0xc9U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x82U : 0xcaU))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x76U : 0xabU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd7U : 0xfeU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x2bU : 0x67U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 1U : 0x30U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc5U : 0x6fU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x6bU : 0xf2U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7bU : 0x77U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7cU : 0x63U))))))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__3__KET____DOT__u_sb__DOT__out_byte
        = ((0x00000080U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
            ? ((0x00000040U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                ? ((0x00000020U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                    ? ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x16U : 0xbbU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x54U : 0xb0U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x0fU : 0x2dU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x99U : 0x41U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x68U : 0x42U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xe6U : 0xbfU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x0dU : 0x89U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa1U : 0x8cU))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xdfU : 0x28U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x55U : 0xceU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xe9U : 0x87U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x1eU : 0x9bU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x94U : 0x8eU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd9U : 0x69U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x11U : 0x98U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf8U : 0xe1U)))))
                    : ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x9eU : 0x1dU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc1U : 0x86U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xb9U : 0x57U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x35U : 0x61U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x0eU : 0xf6U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 3U : 0x48U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x66U : 0xb5U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3eU : 0x70U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x8aU : 0x8bU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xbdU : 0x4bU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x1fU : 0x74U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xddU : 0xe8U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc6U : 0xb4U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa6U : 0x1cU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x2eU : 0x25U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x78U : 0xbaU))))))
                : ((0x00000020U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                    ? ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 8U : 0xaeU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7aU : 0x65U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xeaU : 0xf4U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x56U : 0x6cU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa9U : 0x4eU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd5U : 0x8dU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x6dU : 0x37U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc8U : 0xe7U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x79U : 0xe4U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x95U : 0x91U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x62U : 0xacU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd3U : 0xc2U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x5cU : 0x24U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 6U : 0x49U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x0aU : 0x3aU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x32U : 0xe0U)))))
                    : ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xdbU : 0x0bU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x5eU : 0xdeU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x14U : 0xb8U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xeeU : 0x46U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x88U : 0x90U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x2aU : 0x22U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xdcU : 0x4fU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x81U : 0x60U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x73U : 0x19U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x5dU : 0x64U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3dU : 0x7eU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa7U : 0xc4U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x17U : 0x44U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x97U : 0x5fU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xecU : 0x13U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x0cU : 0xcdU)))))))
            : ((0x00000040U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                ? ((0x00000020U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                    ? ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd2U : 0xf3U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xffU : 0x10U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x21U : 0xdaU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xb6U : 0xbcU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf5U : 0x38U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x9dU : 0x92U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x8fU : 0x40U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa3U : 0x51U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa8U : 0x9fU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3cU : 0x50U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7fU : 2U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf9U : 0x45U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x85U : 0x33U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x4dU : 0x43U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xfbU : 0xaaU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xefU : 0xd0U)))))
                    : ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xcfU : 0x58U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x4cU : 0x4aU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x39U : 0xbeU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xcbU : 0x6aU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x5bU : 0xb1U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xfcU : 0x20U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xedU : 0U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd1U : 0x53U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x84U : 0x2fU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xe3U : 0x29U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xb3U : 0xd6U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3bU : 0x52U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa0U : 0x5aU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x6eU : 0x1bU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x1aU : 0x2cU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x83U : 9U))))))
                : ((0x00000020U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                    ? ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x75U : 0xb2U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x27U : 0xebU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xe2U : 0x80U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x12U : 7U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x9aU : 5U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x96U : 0x18U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc3U : 0x23U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc7U : 4U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x15U : 0x31U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd8U : 0x71U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf1U : 0xe5U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa5U : 0x34U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xccU : 0xf7U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x3fU : 0x36U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x26U : 0x93U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xfdU : 0xb7U)))))
                    : ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc0U : 0x72U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xa4U : 0x9cU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xafU : 0xa2U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd4U : 0xadU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xf0U : 0x47U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x59U : 0xfaU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7dU : 0xc9U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x82U : 0xcaU))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x76U : 0xabU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xd7U : 0xfeU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x2bU : 0x67U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 1U : 0x30U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0xc5U : 0x6fU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x6bU : 0xf2U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7bU : 0x77U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])
                                        ? 0x7cU : 0x63U))))))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__4__KET____DOT__u_sb__DOT__out_byte
        = ((vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U]
            >> 0x0000001fU) ? ((0x40000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x20000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x10000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x16U
                                                     : 0xbbU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x54U
                                                     : 0xb0U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x0fU
                                                     : 0x2dU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x99U
                                                     : 0x41U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x68U
                                                     : 0x42U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xe6U
                                                     : 0xbfU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x0dU
                                                     : 0x89U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xa1U
                                                     : 0x8cU))))
                                        : ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xdfU
                                                     : 0x28U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x55U
                                                     : 0xceU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xe9U
                                                     : 0x87U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x1eU
                                                     : 0x9bU)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x94U
                                                     : 0x8eU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xd9U
                                                     : 0x69U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x11U
                                                     : 0x98U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xf8U
                                                     : 0xe1U)))))
                                    : ((0x10000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x9eU
                                                     : 0x1dU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xc1U
                                                     : 0x86U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xb9U
                                                     : 0x57U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x35U
                                                     : 0x61U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x0eU
                                                     : 0xf6U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 3U
                                                     : 0x48U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x66U
                                                     : 0xb5U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x3eU
                                                     : 0x70U))))
                                        : ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x8aU
                                                     : 0x8bU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xbdU
                                                     : 0x4bU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x1fU
                                                     : 0x74U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xddU
                                                     : 0xe8U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xc6U
                                                     : 0xb4U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xa6U
                                                     : 0x1cU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x2eU
                                                     : 0x25U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x78U
                                                     : 0xbaU))))))
                                : ((0x20000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x10000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 8U
                                                     : 0xaeU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x7aU
                                                     : 0x65U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xeaU
                                                     : 0xf4U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x56U
                                                     : 0x6cU)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xa9U
                                                     : 0x4eU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xd5U
                                                     : 0x8dU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x6dU
                                                     : 0x37U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xc8U
                                                     : 0xe7U))))
                                        : ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x79U
                                                     : 0xe4U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x95U
                                                     : 0x91U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x62U
                                                     : 0xacU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xd3U
                                                     : 0xc2U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x5cU
                                                     : 0x24U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 6U
                                                     : 0x49U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x0aU
                                                     : 0x3aU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x32U
                                                     : 0xe0U)))))
                                    : ((0x10000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xdbU
                                                     : 0x0bU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x5eU
                                                     : 0xdeU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x14U
                                                     : 0xb8U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xeeU
                                                     : 0x46U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x88U
                                                     : 0x90U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x2aU
                                                     : 0x22U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xdcU
                                                     : 0x4fU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x81U
                                                     : 0x60U))))
                                        : ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x73U
                                                     : 0x19U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x5dU
                                                     : 0x64U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x3dU
                                                     : 0x7eU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xa7U
                                                     : 0xc4U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x17U
                                                     : 0x44U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x97U
                                                     : 0x5fU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0xecU
                                                     : 0x13U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                                     ? 0x0cU
                                                     : 0xcdU)))))))
            : ((0x40000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                ? ((0x20000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                    ? ((0x10000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd2U : 0xf3U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xffU : 0x10U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x21U : 0xdaU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xb6U : 0xbcU)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf5U : 0x38U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x9dU : 0x92U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x8fU : 0x40U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa3U : 0x51U))))
                        : ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa8U : 0x9fU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3cU : 0x50U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7fU : 2U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf9U : 0x45U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x85U : 0x33U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x4dU : 0x43U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xfbU : 0xaaU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xefU : 0xd0U)))))
                    : ((0x10000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xcfU : 0x58U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x4cU : 0x4aU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x39U : 0xbeU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xcbU : 0x6aU)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x5bU : 0xb1U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xfcU : 0x20U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xedU : 0U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd1U : 0x53U))))
                        : ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x84U : 0x2fU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xe3U : 0x29U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xb3U : 0xd6U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3bU : 0x52U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa0U : 0x5aU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x6eU : 0x1bU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x1aU : 0x2cU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x83U : 9U))))))
                : ((0x20000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                    ? ((0x10000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x75U : 0xb2U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x27U : 0xebU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xe2U : 0x80U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x12U : 7U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x9aU : 5U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x96U : 0x18U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc3U : 0x23U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc7U : 4U))))
                        : ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x15U : 0x31U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd8U : 0x71U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf1U : 0xe5U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa5U : 0x34U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xccU : 0xf7U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3fU : 0x36U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x26U : 0x93U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xfdU : 0xb7U)))))
                    : ((0x10000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc0U : 0x72U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa4U : 0x9cU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xafU : 0xa2U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd4U : 0xadU)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf0U : 0x47U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x59U : 0xfaU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7dU : 0xc9U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x82U : 0xcaU))))
                        : ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x76U : 0xabU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd7U : 0xfeU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x2bU : 0x67U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 1U : 0x30U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc5U : 0x6fU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x6bU : 0xf2U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7bU : 0x77U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7cU : 0x63U))))))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__5__KET____DOT__u_sb__DOT__out_byte
        = ((0x00800000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
            ? ((0x00400000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                ? ((0x00200000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                    ? ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x16U : 0xbbU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x54U : 0xb0U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x0fU : 0x2dU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x99U : 0x41U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x68U : 0x42U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xe6U : 0xbfU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x0dU : 0x89U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa1U : 0x8cU))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xdfU : 0x28U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x55U : 0xceU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xe9U : 0x87U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x1eU : 0x9bU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x94U : 0x8eU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd9U : 0x69U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x11U : 0x98U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf8U : 0xe1U)))))
                    : ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x9eU : 0x1dU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc1U : 0x86U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xb9U : 0x57U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x35U : 0x61U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x0eU : 0xf6U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 3U : 0x48U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x66U : 0xb5U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3eU : 0x70U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x8aU : 0x8bU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xbdU : 0x4bU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x1fU : 0x74U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xddU : 0xe8U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc6U : 0xb4U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa6U : 0x1cU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x2eU : 0x25U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x78U : 0xbaU))))))
                : ((0x00200000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                    ? ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 8U : 0xaeU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7aU : 0x65U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xeaU : 0xf4U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x56U : 0x6cU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa9U : 0x4eU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd5U : 0x8dU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x6dU : 0x37U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc8U : 0xe7U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x79U : 0xe4U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x95U : 0x91U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x62U : 0xacU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd3U : 0xc2U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x5cU : 0x24U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 6U : 0x49U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x0aU : 0x3aU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x32U : 0xe0U)))))
                    : ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xdbU : 0x0bU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x5eU : 0xdeU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x14U : 0xb8U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xeeU : 0x46U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x88U : 0x90U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x2aU : 0x22U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xdcU : 0x4fU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x81U : 0x60U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x73U : 0x19U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x5dU : 0x64U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3dU : 0x7eU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa7U : 0xc4U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x17U : 0x44U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x97U : 0x5fU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xecU : 0x13U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x0cU : 0xcdU)))))))
            : ((0x00400000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                ? ((0x00200000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                    ? ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd2U : 0xf3U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xffU : 0x10U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x21U : 0xdaU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xb6U : 0xbcU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf5U : 0x38U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x9dU : 0x92U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x8fU : 0x40U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa3U : 0x51U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa8U : 0x9fU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3cU : 0x50U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7fU : 2U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf9U : 0x45U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x85U : 0x33U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x4dU : 0x43U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xfbU : 0xaaU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xefU : 0xd0U)))))
                    : ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xcfU : 0x58U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x4cU : 0x4aU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x39U : 0xbeU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xcbU : 0x6aU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x5bU : 0xb1U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xfcU : 0x20U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xedU : 0U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd1U : 0x53U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x84U : 0x2fU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xe3U : 0x29U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xb3U : 0xd6U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3bU : 0x52U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa0U : 0x5aU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x6eU : 0x1bU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x1aU : 0x2cU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x83U : 9U))))))
                : ((0x00200000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                    ? ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x75U : 0xb2U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x27U : 0xebU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xe2U : 0x80U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x12U : 7U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x9aU : 5U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x96U : 0x18U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc3U : 0x23U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc7U : 4U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x15U : 0x31U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd8U : 0x71U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf1U : 0xe5U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa5U : 0x34U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xccU : 0xf7U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3fU : 0x36U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x26U : 0x93U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xfdU : 0xb7U)))))
                    : ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc0U : 0x72U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa4U : 0x9cU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xafU : 0xa2U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd4U : 0xadU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf0U : 0x47U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x59U : 0xfaU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7dU : 0xc9U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x82U : 0xcaU))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x76U : 0xabU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd7U : 0xfeU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x2bU : 0x67U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 1U : 0x30U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc5U : 0x6fU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x6bU : 0xf2U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7bU : 0x77U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7cU : 0x63U))))))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__6__KET____DOT__u_sb__DOT__out_byte
        = ((0x00008000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
            ? ((0x00004000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                ? ((0x00002000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                    ? ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x16U : 0xbbU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x54U : 0xb0U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x0fU : 0x2dU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x99U : 0x41U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x68U : 0x42U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xe6U : 0xbfU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x0dU : 0x89U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa1U : 0x8cU))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xdfU : 0x28U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x55U : 0xceU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xe9U : 0x87U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x1eU : 0x9bU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x94U : 0x8eU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd9U : 0x69U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x11U : 0x98U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf8U : 0xe1U)))))
                    : ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x9eU : 0x1dU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc1U : 0x86U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xb9U : 0x57U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x35U : 0x61U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x0eU : 0xf6U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 3U : 0x48U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x66U : 0xb5U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3eU : 0x70U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x8aU : 0x8bU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xbdU : 0x4bU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x1fU : 0x74U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xddU : 0xe8U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc6U : 0xb4U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa6U : 0x1cU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x2eU : 0x25U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x78U : 0xbaU))))))
                : ((0x00002000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                    ? ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 8U : 0xaeU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7aU : 0x65U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xeaU : 0xf4U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x56U : 0x6cU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa9U : 0x4eU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd5U : 0x8dU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x6dU : 0x37U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc8U : 0xe7U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x79U : 0xe4U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x95U : 0x91U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x62U : 0xacU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd3U : 0xc2U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x5cU : 0x24U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 6U : 0x49U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x0aU : 0x3aU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x32U : 0xe0U)))))
                    : ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xdbU : 0x0bU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x5eU : 0xdeU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x14U : 0xb8U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xeeU : 0x46U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x88U : 0x90U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x2aU : 0x22U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xdcU : 0x4fU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x81U : 0x60U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x73U : 0x19U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x5dU : 0x64U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3dU : 0x7eU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa7U : 0xc4U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x17U : 0x44U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x97U : 0x5fU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xecU : 0x13U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x0cU : 0xcdU)))))))
            : ((0x00004000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                ? ((0x00002000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                    ? ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd2U : 0xf3U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xffU : 0x10U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x21U : 0xdaU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xb6U : 0xbcU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf5U : 0x38U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x9dU : 0x92U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x8fU : 0x40U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa3U : 0x51U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa8U : 0x9fU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3cU : 0x50U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7fU : 2U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf9U : 0x45U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x85U : 0x33U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x4dU : 0x43U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xfbU : 0xaaU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xefU : 0xd0U)))))
                    : ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xcfU : 0x58U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x4cU : 0x4aU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x39U : 0xbeU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xcbU : 0x6aU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x5bU : 0xb1U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xfcU : 0x20U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xedU : 0U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd1U : 0x53U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x84U : 0x2fU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xe3U : 0x29U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xb3U : 0xd6U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3bU : 0x52U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa0U : 0x5aU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x6eU : 0x1bU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x1aU : 0x2cU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x83U : 9U))))))
                : ((0x00002000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                    ? ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x75U : 0xb2U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x27U : 0xebU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xe2U : 0x80U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x12U : 7U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x9aU : 5U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x96U : 0x18U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc3U : 0x23U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc7U : 4U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x15U : 0x31U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd8U : 0x71U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf1U : 0xe5U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa5U : 0x34U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xccU : 0xf7U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3fU : 0x36U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x26U : 0x93U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xfdU : 0xb7U)))))
                    : ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc0U : 0x72U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa4U : 0x9cU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xafU : 0xa2U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd4U : 0xadU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf0U : 0x47U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x59U : 0xfaU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7dU : 0xc9U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x82U : 0xcaU))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x76U : 0xabU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd7U : 0xfeU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x2bU : 0x67U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 1U : 0x30U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc5U : 0x6fU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x6bU : 0xf2U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7bU : 0x77U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7cU : 0x63U))))))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__7__KET____DOT__u_sb__DOT__out_byte
        = ((0x00000080U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
            ? ((0x00000040U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                ? ((0x00000020U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                    ? ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x16U : 0xbbU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x54U : 0xb0U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x0fU : 0x2dU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x99U : 0x41U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x68U : 0x42U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xe6U : 0xbfU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x0dU : 0x89U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa1U : 0x8cU))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xdfU : 0x28U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x55U : 0xceU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xe9U : 0x87U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x1eU : 0x9bU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x94U : 0x8eU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd9U : 0x69U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x11U : 0x98U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf8U : 0xe1U)))))
                    : ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x9eU : 0x1dU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc1U : 0x86U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xb9U : 0x57U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x35U : 0x61U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x0eU : 0xf6U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 3U : 0x48U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x66U : 0xb5U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3eU : 0x70U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x8aU : 0x8bU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xbdU : 0x4bU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x1fU : 0x74U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xddU : 0xe8U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc6U : 0xb4U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa6U : 0x1cU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x2eU : 0x25U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x78U : 0xbaU))))))
                : ((0x00000020U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                    ? ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 8U : 0xaeU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7aU : 0x65U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xeaU : 0xf4U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x56U : 0x6cU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa9U : 0x4eU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd5U : 0x8dU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x6dU : 0x37U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc8U : 0xe7U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x79U : 0xe4U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x95U : 0x91U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x62U : 0xacU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd3U : 0xc2U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x5cU : 0x24U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 6U : 0x49U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x0aU : 0x3aU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x32U : 0xe0U)))))
                    : ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xdbU : 0x0bU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x5eU : 0xdeU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x14U : 0xb8U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xeeU : 0x46U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x88U : 0x90U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x2aU : 0x22U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xdcU : 0x4fU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x81U : 0x60U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x73U : 0x19U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x5dU : 0x64U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3dU : 0x7eU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa7U : 0xc4U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x17U : 0x44U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x97U : 0x5fU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xecU : 0x13U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x0cU : 0xcdU)))))))
            : ((0x00000040U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                ? ((0x00000020U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                    ? ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd2U : 0xf3U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xffU : 0x10U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x21U : 0xdaU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xb6U : 0xbcU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf5U : 0x38U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x9dU : 0x92U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x8fU : 0x40U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa3U : 0x51U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa8U : 0x9fU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3cU : 0x50U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7fU : 2U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf9U : 0x45U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x85U : 0x33U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x4dU : 0x43U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xfbU : 0xaaU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xefU : 0xd0U)))))
                    : ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xcfU : 0x58U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x4cU : 0x4aU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x39U : 0xbeU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xcbU : 0x6aU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x5bU : 0xb1U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xfcU : 0x20U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xedU : 0U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd1U : 0x53U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x84U : 0x2fU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xe3U : 0x29U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xb3U : 0xd6U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3bU : 0x52U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa0U : 0x5aU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x6eU : 0x1bU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x1aU : 0x2cU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x83U : 9U))))))
                : ((0x00000020U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                    ? ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x75U : 0xb2U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x27U : 0xebU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xe2U : 0x80U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x12U : 7U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x9aU : 5U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x96U : 0x18U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc3U : 0x23U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc7U : 4U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x15U : 0x31U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd8U : 0x71U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf1U : 0xe5U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa5U : 0x34U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xccU : 0xf7U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x3fU : 0x36U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x26U : 0x93U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xfdU : 0xb7U)))))
                    : ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc0U : 0x72U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xa4U : 0x9cU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xafU : 0xa2U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd4U : 0xadU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xf0U : 0x47U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x59U : 0xfaU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7dU : 0xc9U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x82U : 0xcaU))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x76U : 0xabU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xd7U : 0xfeU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x2bU : 0x67U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 1U : 0x30U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0xc5U : 0x6fU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x6bU : 0xf2U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7bU : 0x77U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])
                                        ? 0x7cU : 0x63U))))))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__8__KET____DOT__u_sb__DOT__out_byte
        = ((vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U]
            >> 0x0000001fU) ? ((0x40000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x20000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x10000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x16U
                                                     : 0xbbU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x54U
                                                     : 0xb0U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x0fU
                                                     : 0x2dU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x99U
                                                     : 0x41U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x68U
                                                     : 0x42U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xe6U
                                                     : 0xbfU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x0dU
                                                     : 0x89U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xa1U
                                                     : 0x8cU))))
                                        : ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xdfU
                                                     : 0x28U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x55U
                                                     : 0xceU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xe9U
                                                     : 0x87U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x1eU
                                                     : 0x9bU)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x94U
                                                     : 0x8eU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xd9U
                                                     : 0x69U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x11U
                                                     : 0x98U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xf8U
                                                     : 0xe1U)))))
                                    : ((0x10000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x9eU
                                                     : 0x1dU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xc1U
                                                     : 0x86U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xb9U
                                                     : 0x57U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x35U
                                                     : 0x61U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x0eU
                                                     : 0xf6U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 3U
                                                     : 0x48U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x66U
                                                     : 0xb5U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x3eU
                                                     : 0x70U))))
                                        : ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x8aU
                                                     : 0x8bU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xbdU
                                                     : 0x4bU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x1fU
                                                     : 0x74U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xddU
                                                     : 0xe8U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xc6U
                                                     : 0xb4U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xa6U
                                                     : 0x1cU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x2eU
                                                     : 0x25U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x78U
                                                     : 0xbaU))))))
                                : ((0x20000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x10000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 8U
                                                     : 0xaeU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x7aU
                                                     : 0x65U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xeaU
                                                     : 0xf4U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x56U
                                                     : 0x6cU)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xa9U
                                                     : 0x4eU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xd5U
                                                     : 0x8dU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x6dU
                                                     : 0x37U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xc8U
                                                     : 0xe7U))))
                                        : ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x79U
                                                     : 0xe4U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x95U
                                                     : 0x91U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x62U
                                                     : 0xacU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xd3U
                                                     : 0xc2U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x5cU
                                                     : 0x24U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 6U
                                                     : 0x49U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x0aU
                                                     : 0x3aU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x32U
                                                     : 0xe0U)))))
                                    : ((0x10000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xdbU
                                                     : 0x0bU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x5eU
                                                     : 0xdeU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x14U
                                                     : 0xb8U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xeeU
                                                     : 0x46U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x88U
                                                     : 0x90U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x2aU
                                                     : 0x22U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xdcU
                                                     : 0x4fU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x81U
                                                     : 0x60U))))
                                        : ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x73U
                                                     : 0x19U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x5dU
                                                     : 0x64U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x3dU
                                                     : 0x7eU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xa7U
                                                     : 0xc4U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x17U
                                                     : 0x44U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x97U
                                                     : 0x5fU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0xecU
                                                     : 0x13U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                                     ? 0x0cU
                                                     : 0xcdU)))))))
            : ((0x40000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                ? ((0x20000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                    ? ((0x10000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd2U : 0xf3U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xffU : 0x10U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x21U : 0xdaU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xb6U : 0xbcU)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf5U : 0x38U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x9dU : 0x92U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x8fU : 0x40U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa3U : 0x51U))))
                        : ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa8U : 0x9fU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3cU : 0x50U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7fU : 2U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf9U : 0x45U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x85U : 0x33U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x4dU : 0x43U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xfbU : 0xaaU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xefU : 0xd0U)))))
                    : ((0x10000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xcfU : 0x58U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x4cU : 0x4aU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x39U : 0xbeU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xcbU : 0x6aU)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x5bU : 0xb1U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xfcU : 0x20U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xedU : 0U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd1U : 0x53U))))
                        : ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x84U : 0x2fU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xe3U : 0x29U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xb3U : 0xd6U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3bU : 0x52U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa0U : 0x5aU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x6eU : 0x1bU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x1aU : 0x2cU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x83U : 9U))))))
                : ((0x20000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                    ? ((0x10000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x75U : 0xb2U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x27U : 0xebU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xe2U : 0x80U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x12U : 7U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x9aU : 5U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x96U : 0x18U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc3U : 0x23U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc7U : 4U))))
                        : ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x15U : 0x31U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd8U : 0x71U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf1U : 0xe5U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa5U : 0x34U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xccU : 0xf7U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3fU : 0x36U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x26U : 0x93U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xfdU : 0xb7U)))))
                    : ((0x10000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc0U : 0x72U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa4U : 0x9cU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xafU : 0xa2U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd4U : 0xadU)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf0U : 0x47U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x59U : 0xfaU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7dU : 0xc9U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x82U : 0xcaU))))
                        : ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x76U : 0xabU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd7U : 0xfeU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x2bU : 0x67U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 1U : 0x30U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc5U : 0x6fU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x6bU : 0xf2U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7bU : 0x77U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7cU : 0x63U))))))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__9__KET____DOT__u_sb__DOT__out_byte
        = ((0x00800000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
            ? ((0x00400000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                ? ((0x00200000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                    ? ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x16U : 0xbbU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x54U : 0xb0U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x0fU : 0x2dU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x99U : 0x41U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x68U : 0x42U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xe6U : 0xbfU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x0dU : 0x89U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa1U : 0x8cU))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xdfU : 0x28U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x55U : 0xceU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xe9U : 0x87U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x1eU : 0x9bU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x94U : 0x8eU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd9U : 0x69U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x11U : 0x98U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf8U : 0xe1U)))))
                    : ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x9eU : 0x1dU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc1U : 0x86U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xb9U : 0x57U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x35U : 0x61U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x0eU : 0xf6U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 3U : 0x48U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x66U : 0xb5U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3eU : 0x70U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x8aU : 0x8bU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xbdU : 0x4bU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x1fU : 0x74U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xddU : 0xe8U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc6U : 0xb4U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa6U : 0x1cU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x2eU : 0x25U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x78U : 0xbaU))))))
                : ((0x00200000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                    ? ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 8U : 0xaeU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7aU : 0x65U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xeaU : 0xf4U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x56U : 0x6cU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa9U : 0x4eU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd5U : 0x8dU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x6dU : 0x37U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc8U : 0xe7U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x79U : 0xe4U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x95U : 0x91U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x62U : 0xacU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd3U : 0xc2U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x5cU : 0x24U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 6U : 0x49U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x0aU : 0x3aU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x32U : 0xe0U)))))
                    : ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xdbU : 0x0bU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x5eU : 0xdeU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x14U : 0xb8U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xeeU : 0x46U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x88U : 0x90U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x2aU : 0x22U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xdcU : 0x4fU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x81U : 0x60U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x73U : 0x19U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x5dU : 0x64U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3dU : 0x7eU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa7U : 0xc4U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x17U : 0x44U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x97U : 0x5fU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xecU : 0x13U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x0cU : 0xcdU)))))))
            : ((0x00400000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                ? ((0x00200000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                    ? ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd2U : 0xf3U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xffU : 0x10U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x21U : 0xdaU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xb6U : 0xbcU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf5U : 0x38U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x9dU : 0x92U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x8fU : 0x40U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa3U : 0x51U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa8U : 0x9fU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3cU : 0x50U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7fU : 2U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf9U : 0x45U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x85U : 0x33U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x4dU : 0x43U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xfbU : 0xaaU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xefU : 0xd0U)))))
                    : ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xcfU : 0x58U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x4cU : 0x4aU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x39U : 0xbeU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xcbU : 0x6aU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x5bU : 0xb1U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xfcU : 0x20U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xedU : 0U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd1U : 0x53U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x84U : 0x2fU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xe3U : 0x29U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xb3U : 0xd6U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3bU : 0x52U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa0U : 0x5aU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x6eU : 0x1bU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x1aU : 0x2cU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x83U : 9U))))))
                : ((0x00200000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                    ? ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x75U : 0xb2U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x27U : 0xebU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xe2U : 0x80U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x12U : 7U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x9aU : 5U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x96U : 0x18U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc3U : 0x23U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc7U : 4U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x15U : 0x31U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd8U : 0x71U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf1U : 0xe5U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa5U : 0x34U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xccU : 0xf7U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3fU : 0x36U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x26U : 0x93U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xfdU : 0xb7U)))))
                    : ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc0U : 0x72U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa4U : 0x9cU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xafU : 0xa2U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd4U : 0xadU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf0U : 0x47U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x59U : 0xfaU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7dU : 0xc9U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x82U : 0xcaU))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x76U : 0xabU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd7U : 0xfeU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x2bU : 0x67U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 1U : 0x30U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc5U : 0x6fU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x6bU : 0xf2U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7bU : 0x77U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7cU : 0x63U))))))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__10__KET____DOT__u_sb__DOT__out_byte
        = ((0x00008000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
            ? ((0x00004000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                ? ((0x00002000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                    ? ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x16U : 0xbbU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x54U : 0xb0U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x0fU : 0x2dU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x99U : 0x41U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x68U : 0x42U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xe6U : 0xbfU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x0dU : 0x89U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa1U : 0x8cU))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xdfU : 0x28U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x55U : 0xceU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xe9U : 0x87U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x1eU : 0x9bU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x94U : 0x8eU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd9U : 0x69U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x11U : 0x98U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf8U : 0xe1U)))))
                    : ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x9eU : 0x1dU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc1U : 0x86U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xb9U : 0x57U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x35U : 0x61U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x0eU : 0xf6U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 3U : 0x48U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x66U : 0xb5U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3eU : 0x70U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x8aU : 0x8bU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xbdU : 0x4bU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x1fU : 0x74U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xddU : 0xe8U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc6U : 0xb4U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa6U : 0x1cU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x2eU : 0x25U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x78U : 0xbaU))))))
                : ((0x00002000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                    ? ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 8U : 0xaeU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7aU : 0x65U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xeaU : 0xf4U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x56U : 0x6cU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa9U : 0x4eU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd5U : 0x8dU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x6dU : 0x37U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc8U : 0xe7U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x79U : 0xe4U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x95U : 0x91U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x62U : 0xacU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd3U : 0xc2U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x5cU : 0x24U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 6U : 0x49U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x0aU : 0x3aU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x32U : 0xe0U)))))
                    : ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xdbU : 0x0bU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x5eU : 0xdeU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x14U : 0xb8U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xeeU : 0x46U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x88U : 0x90U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x2aU : 0x22U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xdcU : 0x4fU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x81U : 0x60U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x73U : 0x19U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x5dU : 0x64U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3dU : 0x7eU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa7U : 0xc4U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x17U : 0x44U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x97U : 0x5fU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xecU : 0x13U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x0cU : 0xcdU)))))))
            : ((0x00004000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                ? ((0x00002000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                    ? ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd2U : 0xf3U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xffU : 0x10U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x21U : 0xdaU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xb6U : 0xbcU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf5U : 0x38U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x9dU : 0x92U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x8fU : 0x40U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa3U : 0x51U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa8U : 0x9fU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3cU : 0x50U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7fU : 2U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf9U : 0x45U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x85U : 0x33U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x4dU : 0x43U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xfbU : 0xaaU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xefU : 0xd0U)))))
                    : ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xcfU : 0x58U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x4cU : 0x4aU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x39U : 0xbeU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xcbU : 0x6aU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x5bU : 0xb1U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xfcU : 0x20U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xedU : 0U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd1U : 0x53U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x84U : 0x2fU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xe3U : 0x29U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xb3U : 0xd6U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3bU : 0x52U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa0U : 0x5aU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x6eU : 0x1bU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x1aU : 0x2cU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x83U : 9U))))))
                : ((0x00002000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                    ? ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x75U : 0xb2U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x27U : 0xebU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xe2U : 0x80U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x12U : 7U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x9aU : 5U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x96U : 0x18U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc3U : 0x23U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc7U : 4U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x15U : 0x31U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd8U : 0x71U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf1U : 0xe5U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa5U : 0x34U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xccU : 0xf7U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3fU : 0x36U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x26U : 0x93U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xfdU : 0xb7U)))))
                    : ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc0U : 0x72U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa4U : 0x9cU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xafU : 0xa2U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd4U : 0xadU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf0U : 0x47U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x59U : 0xfaU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7dU : 0xc9U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x82U : 0xcaU))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x76U : 0xabU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd7U : 0xfeU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x2bU : 0x67U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 1U : 0x30U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc5U : 0x6fU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x6bU : 0xf2U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7bU : 0x77U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7cU : 0x63U))))))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__11__KET____DOT__u_sb__DOT__out_byte
        = ((0x00000080U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
            ? ((0x00000040U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                ? ((0x00000020U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                    ? ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x16U : 0xbbU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x54U : 0xb0U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x0fU : 0x2dU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x99U : 0x41U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x68U : 0x42U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xe6U : 0xbfU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x0dU : 0x89U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa1U : 0x8cU))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xdfU : 0x28U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x55U : 0xceU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xe9U : 0x87U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x1eU : 0x9bU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x94U : 0x8eU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd9U : 0x69U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x11U : 0x98U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf8U : 0xe1U)))))
                    : ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x9eU : 0x1dU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc1U : 0x86U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xb9U : 0x57U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x35U : 0x61U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x0eU : 0xf6U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 3U : 0x48U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x66U : 0xb5U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3eU : 0x70U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x8aU : 0x8bU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xbdU : 0x4bU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x1fU : 0x74U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xddU : 0xe8U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc6U : 0xb4U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa6U : 0x1cU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x2eU : 0x25U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x78U : 0xbaU))))))
                : ((0x00000020U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                    ? ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 8U : 0xaeU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7aU : 0x65U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xeaU : 0xf4U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x56U : 0x6cU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa9U : 0x4eU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd5U : 0x8dU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x6dU : 0x37U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc8U : 0xe7U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x79U : 0xe4U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x95U : 0x91U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x62U : 0xacU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd3U : 0xc2U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x5cU : 0x24U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 6U : 0x49U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x0aU : 0x3aU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x32U : 0xe0U)))))
                    : ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xdbU : 0x0bU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x5eU : 0xdeU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x14U : 0xb8U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xeeU : 0x46U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x88U : 0x90U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x2aU : 0x22U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xdcU : 0x4fU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x81U : 0x60U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x73U : 0x19U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x5dU : 0x64U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3dU : 0x7eU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa7U : 0xc4U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x17U : 0x44U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x97U : 0x5fU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xecU : 0x13U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x0cU : 0xcdU)))))))
            : ((0x00000040U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                ? ((0x00000020U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                    ? ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd2U : 0xf3U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xffU : 0x10U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x21U : 0xdaU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xb6U : 0xbcU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf5U : 0x38U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x9dU : 0x92U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x8fU : 0x40U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa3U : 0x51U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa8U : 0x9fU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3cU : 0x50U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7fU : 2U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf9U : 0x45U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x85U : 0x33U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x4dU : 0x43U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xfbU : 0xaaU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xefU : 0xd0U)))))
                    : ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xcfU : 0x58U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x4cU : 0x4aU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x39U : 0xbeU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xcbU : 0x6aU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x5bU : 0xb1U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xfcU : 0x20U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xedU : 0U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd1U : 0x53U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x84U : 0x2fU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xe3U : 0x29U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xb3U : 0xd6U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3bU : 0x52U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa0U : 0x5aU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x6eU : 0x1bU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x1aU : 0x2cU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x83U : 9U))))))
                : ((0x00000020U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                    ? ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x75U : 0xb2U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x27U : 0xebU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xe2U : 0x80U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x12U : 7U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x9aU : 5U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x96U : 0x18U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc3U : 0x23U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc7U : 4U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x15U : 0x31U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd8U : 0x71U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf1U : 0xe5U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa5U : 0x34U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xccU : 0xf7U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x3fU : 0x36U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x26U : 0x93U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xfdU : 0xb7U)))))
                    : ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc0U : 0x72U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xa4U : 0x9cU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xafU : 0xa2U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd4U : 0xadU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xf0U : 0x47U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x59U : 0xfaU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7dU : 0xc9U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x82U : 0xcaU))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x76U : 0xabU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xd7U : 0xfeU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x2bU : 0x67U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 1U : 0x30U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0xc5U : 0x6fU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x6bU : 0xf2U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7bU : 0x77U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])
                                        ? 0x7cU : 0x63U))))))));
}
