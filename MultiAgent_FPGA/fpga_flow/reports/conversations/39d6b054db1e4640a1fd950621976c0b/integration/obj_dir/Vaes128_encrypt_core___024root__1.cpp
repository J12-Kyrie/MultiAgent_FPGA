// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaes128_encrypt_core.h for the primary calling header

#include "Vaes128_encrypt_core__pch.h"

void Vaes128_encrypt_core___024root___nba_sequent__TOP__1(Vaes128_encrypt_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root___nba_sequent__TOP__1\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__12__KET____DOT__u_sb__DOT__out_byte
        = ((vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U]
            >> 0x0000001fU) ? ((0x40000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x20000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x10000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x16U
                                                     : 0xbbU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x54U
                                                     : 0xb0U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x0fU
                                                     : 0x2dU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x99U
                                                     : 0x41U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x68U
                                                     : 0x42U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xe6U
                                                     : 0xbfU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x0dU
                                                     : 0x89U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xa1U
                                                     : 0x8cU))))
                                        : ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xdfU
                                                     : 0x28U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x55U
                                                     : 0xceU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xe9U
                                                     : 0x87U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x1eU
                                                     : 0x9bU)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x94U
                                                     : 0x8eU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xd9U
                                                     : 0x69U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x11U
                                                     : 0x98U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xf8U
                                                     : 0xe1U)))))
                                    : ((0x10000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x9eU
                                                     : 0x1dU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xc1U
                                                     : 0x86U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xb9U
                                                     : 0x57U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x35U
                                                     : 0x61U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x0eU
                                                     : 0xf6U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 3U
                                                     : 0x48U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x66U
                                                     : 0xb5U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x3eU
                                                     : 0x70U))))
                                        : ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x8aU
                                                     : 0x8bU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xbdU
                                                     : 0x4bU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x1fU
                                                     : 0x74U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xddU
                                                     : 0xe8U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xc6U
                                                     : 0xb4U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xa6U
                                                     : 0x1cU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x2eU
                                                     : 0x25U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x78U
                                                     : 0xbaU))))))
                                : ((0x20000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x10000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 8U
                                                     : 0xaeU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x7aU
                                                     : 0x65U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xeaU
                                                     : 0xf4U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x56U
                                                     : 0x6cU)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xa9U
                                                     : 0x4eU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xd5U
                                                     : 0x8dU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x6dU
                                                     : 0x37U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xc8U
                                                     : 0xe7U))))
                                        : ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x79U
                                                     : 0xe4U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x95U
                                                     : 0x91U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x62U
                                                     : 0xacU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xd3U
                                                     : 0xc2U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x5cU
                                                     : 0x24U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 6U
                                                     : 0x49U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x0aU
                                                     : 0x3aU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x32U
                                                     : 0xe0U)))))
                                    : ((0x10000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xdbU
                                                     : 0x0bU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x5eU
                                                     : 0xdeU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x14U
                                                     : 0xb8U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xeeU
                                                     : 0x46U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x88U
                                                     : 0x90U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x2aU
                                                     : 0x22U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xdcU
                                                     : 0x4fU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x81U
                                                     : 0x60U))))
                                        : ((0x08000000U
                                            & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                            ? ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x73U
                                                     : 0x19U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x5dU
                                                     : 0x64U))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x3dU
                                                     : 0x7eU)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xa7U
                                                     : 0xc4U)))
                                            : ((0x04000000U
                                                & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                ? (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x17U
                                                     : 0x44U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x97U
                                                     : 0x5fU))
                                                : (
                                                   (0x02000000U
                                                    & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                    ?
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0xecU
                                                     : 0x13U)
                                                    :
                                                   ((0x01000000U
                                                     & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                                     ? 0x0cU
                                                     : 0xcdU)))))))
            : ((0x40000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                ? ((0x20000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                    ? ((0x10000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd2U : 0xf3U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xffU : 0x10U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x21U : 0xdaU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xb6U : 0xbcU)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf5U : 0x38U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x9dU : 0x92U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x8fU : 0x40U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa3U : 0x51U))))
                        : ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa8U : 0x9fU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3cU : 0x50U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7fU : 2U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf9U : 0x45U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x85U : 0x33U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x4dU : 0x43U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xfbU : 0xaaU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xefU : 0xd0U)))))
                    : ((0x10000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xcfU : 0x58U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x4cU : 0x4aU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x39U : 0xbeU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xcbU : 0x6aU)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x5bU : 0xb1U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xfcU : 0x20U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xedU : 0U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd1U : 0x53U))))
                        : ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x84U : 0x2fU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xe3U : 0x29U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xb3U : 0xd6U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3bU : 0x52U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa0U : 0x5aU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x6eU : 0x1bU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x1aU : 0x2cU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x83U : 9U))))))
                : ((0x20000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                    ? ((0x10000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x75U : 0xb2U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x27U : 0xebU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xe2U : 0x80U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x12U : 7U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x9aU : 5U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x96U : 0x18U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc3U : 0x23U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc7U : 4U))))
                        : ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x15U : 0x31U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd8U : 0x71U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf1U : 0xe5U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa5U : 0x34U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xccU : 0xf7U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3fU : 0x36U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x26U : 0x93U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xfdU : 0xb7U)))))
                    : ((0x10000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc0U : 0x72U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa4U : 0x9cU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xafU : 0xa2U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd4U : 0xadU)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf0U : 0x47U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x59U : 0xfaU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7dU : 0xc9U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x82U : 0xcaU))))
                        : ((0x08000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x76U : 0xabU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd7U : 0xfeU))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x2bU : 0x67U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 1U : 0x30U)))
                            : ((0x04000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc5U : 0x6fU)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x6bU : 0xf2U))
                                : ((0x02000000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7bU : 0x77U)
                                    : ((0x01000000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7cU : 0x63U))))))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__13__KET____DOT__u_sb__DOT__out_byte
        = ((0x00800000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
            ? ((0x00400000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                ? ((0x00200000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                    ? ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x16U : 0xbbU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x54U : 0xb0U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x0fU : 0x2dU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x99U : 0x41U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x68U : 0x42U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xe6U : 0xbfU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x0dU : 0x89U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa1U : 0x8cU))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xdfU : 0x28U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x55U : 0xceU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xe9U : 0x87U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x1eU : 0x9bU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x94U : 0x8eU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd9U : 0x69U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x11U : 0x98U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf8U : 0xe1U)))))
                    : ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x9eU : 0x1dU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc1U : 0x86U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xb9U : 0x57U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x35U : 0x61U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x0eU : 0xf6U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 3U : 0x48U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x66U : 0xb5U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3eU : 0x70U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x8aU : 0x8bU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xbdU : 0x4bU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x1fU : 0x74U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xddU : 0xe8U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc6U : 0xb4U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa6U : 0x1cU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x2eU : 0x25U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x78U : 0xbaU))))))
                : ((0x00200000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                    ? ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 8U : 0xaeU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7aU : 0x65U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xeaU : 0xf4U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x56U : 0x6cU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa9U : 0x4eU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd5U : 0x8dU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x6dU : 0x37U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc8U : 0xe7U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x79U : 0xe4U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x95U : 0x91U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x62U : 0xacU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd3U : 0xc2U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x5cU : 0x24U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 6U : 0x49U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x0aU : 0x3aU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x32U : 0xe0U)))))
                    : ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xdbU : 0x0bU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x5eU : 0xdeU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x14U : 0xb8U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xeeU : 0x46U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x88U : 0x90U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x2aU : 0x22U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xdcU : 0x4fU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x81U : 0x60U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x73U : 0x19U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x5dU : 0x64U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3dU : 0x7eU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa7U : 0xc4U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x17U : 0x44U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x97U : 0x5fU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xecU : 0x13U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x0cU : 0xcdU)))))))
            : ((0x00400000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                ? ((0x00200000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                    ? ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd2U : 0xf3U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xffU : 0x10U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x21U : 0xdaU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xb6U : 0xbcU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf5U : 0x38U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x9dU : 0x92U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x8fU : 0x40U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa3U : 0x51U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa8U : 0x9fU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3cU : 0x50U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7fU : 2U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf9U : 0x45U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x85U : 0x33U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x4dU : 0x43U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xfbU : 0xaaU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xefU : 0xd0U)))))
                    : ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xcfU : 0x58U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x4cU : 0x4aU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x39U : 0xbeU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xcbU : 0x6aU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x5bU : 0xb1U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xfcU : 0x20U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xedU : 0U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd1U : 0x53U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x84U : 0x2fU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xe3U : 0x29U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xb3U : 0xd6U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3bU : 0x52U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa0U : 0x5aU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x6eU : 0x1bU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x1aU : 0x2cU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x83U : 9U))))))
                : ((0x00200000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                    ? ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x75U : 0xb2U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x27U : 0xebU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xe2U : 0x80U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x12U : 7U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x9aU : 5U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x96U : 0x18U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc3U : 0x23U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc7U : 4U))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x15U : 0x31U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd8U : 0x71U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf1U : 0xe5U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa5U : 0x34U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xccU : 0xf7U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3fU : 0x36U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x26U : 0x93U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xfdU : 0xb7U)))))
                    : ((0x00100000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc0U : 0x72U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa4U : 0x9cU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xafU : 0xa2U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd4U : 0xadU)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf0U : 0x47U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x59U : 0xfaU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7dU : 0xc9U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x82U : 0xcaU))))
                        : ((0x00080000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x76U : 0xabU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd7U : 0xfeU))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x2bU : 0x67U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 1U : 0x30U)))
                            : ((0x00040000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc5U : 0x6fU)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x6bU : 0xf2U))
                                : ((0x00020000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7bU : 0x77U)
                                    : ((0x00010000U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7cU : 0x63U))))))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__14__KET____DOT__u_sb__DOT__out_byte
        = ((0x00008000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
            ? ((0x00004000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                ? ((0x00002000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                    ? ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x16U : 0xbbU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x54U : 0xb0U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x0fU : 0x2dU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x99U : 0x41U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x68U : 0x42U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xe6U : 0xbfU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x0dU : 0x89U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa1U : 0x8cU))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xdfU : 0x28U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x55U : 0xceU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xe9U : 0x87U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x1eU : 0x9bU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x94U : 0x8eU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd9U : 0x69U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x11U : 0x98U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf8U : 0xe1U)))))
                    : ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x9eU : 0x1dU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc1U : 0x86U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xb9U : 0x57U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x35U : 0x61U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x0eU : 0xf6U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 3U : 0x48U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x66U : 0xb5U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3eU : 0x70U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x8aU : 0x8bU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xbdU : 0x4bU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x1fU : 0x74U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xddU : 0xe8U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc6U : 0xb4U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa6U : 0x1cU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x2eU : 0x25U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x78U : 0xbaU))))))
                : ((0x00002000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                    ? ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 8U : 0xaeU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7aU : 0x65U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xeaU : 0xf4U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x56U : 0x6cU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa9U : 0x4eU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd5U : 0x8dU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x6dU : 0x37U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc8U : 0xe7U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x79U : 0xe4U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x95U : 0x91U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x62U : 0xacU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd3U : 0xc2U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x5cU : 0x24U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 6U : 0x49U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x0aU : 0x3aU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x32U : 0xe0U)))))
                    : ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xdbU : 0x0bU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x5eU : 0xdeU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x14U : 0xb8U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xeeU : 0x46U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x88U : 0x90U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x2aU : 0x22U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xdcU : 0x4fU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x81U : 0x60U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x73U : 0x19U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x5dU : 0x64U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3dU : 0x7eU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa7U : 0xc4U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x17U : 0x44U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x97U : 0x5fU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xecU : 0x13U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x0cU : 0xcdU)))))))
            : ((0x00004000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                ? ((0x00002000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                    ? ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd2U : 0xf3U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xffU : 0x10U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x21U : 0xdaU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xb6U : 0xbcU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf5U : 0x38U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x9dU : 0x92U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x8fU : 0x40U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa3U : 0x51U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa8U : 0x9fU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3cU : 0x50U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7fU : 2U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf9U : 0x45U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x85U : 0x33U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x4dU : 0x43U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xfbU : 0xaaU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xefU : 0xd0U)))))
                    : ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xcfU : 0x58U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x4cU : 0x4aU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x39U : 0xbeU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xcbU : 0x6aU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x5bU : 0xb1U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xfcU : 0x20U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xedU : 0U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd1U : 0x53U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x84U : 0x2fU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xe3U : 0x29U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xb3U : 0xd6U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3bU : 0x52U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa0U : 0x5aU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x6eU : 0x1bU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x1aU : 0x2cU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x83U : 9U))))))
                : ((0x00002000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                    ? ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x75U : 0xb2U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x27U : 0xebU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xe2U : 0x80U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x12U : 7U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x9aU : 5U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x96U : 0x18U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc3U : 0x23U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc7U : 4U))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x15U : 0x31U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd8U : 0x71U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf1U : 0xe5U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa5U : 0x34U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xccU : 0xf7U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3fU : 0x36U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x26U : 0x93U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xfdU : 0xb7U)))))
                    : ((0x00001000U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc0U : 0x72U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa4U : 0x9cU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xafU : 0xa2U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd4U : 0xadU)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf0U : 0x47U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x59U : 0xfaU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7dU : 0xc9U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x82U : 0xcaU))))
                        : ((0x00000800U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x76U : 0xabU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd7U : 0xfeU))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x2bU : 0x67U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 1U : 0x30U)))
                            : ((0x00000400U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc5U : 0x6fU)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x6bU : 0xf2U))
                                : ((0x00000200U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7bU : 0x77U)
                                    : ((0x00000100U
                                        & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7cU : 0x63U))))))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__15__KET____DOT__u_sb__DOT__out_byte
        = ((0x00000080U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
            ? ((0x00000040U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                ? ((0x00000020U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                    ? ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x16U : 0xbbU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x54U : 0xb0U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x0fU : 0x2dU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x99U : 0x41U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x68U : 0x42U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xe6U : 0xbfU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x0dU : 0x89U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa1U : 0x8cU))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xdfU : 0x28U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x55U : 0xceU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xe9U : 0x87U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x1eU : 0x9bU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x94U : 0x8eU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd9U : 0x69U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x11U : 0x98U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf8U : 0xe1U)))))
                    : ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x9eU : 0x1dU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc1U : 0x86U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xb9U : 0x57U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x35U : 0x61U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x0eU : 0xf6U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 3U : 0x48U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x66U : 0xb5U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3eU : 0x70U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x8aU : 0x8bU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xbdU : 0x4bU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x1fU : 0x74U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xddU : 0xe8U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc6U : 0xb4U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa6U : 0x1cU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x2eU : 0x25U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x78U : 0xbaU))))))
                : ((0x00000020U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                    ? ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 8U : 0xaeU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7aU : 0x65U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xeaU : 0xf4U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x56U : 0x6cU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa9U : 0x4eU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd5U : 0x8dU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x6dU : 0x37U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc8U : 0xe7U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x79U : 0xe4U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x95U : 0x91U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x62U : 0xacU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd3U : 0xc2U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x5cU : 0x24U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 6U : 0x49U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x0aU : 0x3aU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x32U : 0xe0U)))))
                    : ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xdbU : 0x0bU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x5eU : 0xdeU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x14U : 0xb8U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xeeU : 0x46U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x88U : 0x90U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x2aU : 0x22U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xdcU : 0x4fU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x81U : 0x60U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x73U : 0x19U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x5dU : 0x64U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3dU : 0x7eU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa7U : 0xc4U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x17U : 0x44U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x97U : 0x5fU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xecU : 0x13U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x0cU : 0xcdU)))))))
            : ((0x00000040U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                ? ((0x00000020U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                    ? ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd2U : 0xf3U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xffU : 0x10U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x21U : 0xdaU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xb6U : 0xbcU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf5U : 0x38U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x9dU : 0x92U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x8fU : 0x40U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa3U : 0x51U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa8U : 0x9fU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3cU : 0x50U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7fU : 2U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf9U : 0x45U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x85U : 0x33U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x4dU : 0x43U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xfbU : 0xaaU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xefU : 0xd0U)))))
                    : ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xcfU : 0x58U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x4cU : 0x4aU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x39U : 0xbeU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xcbU : 0x6aU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x5bU : 0xb1U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xfcU : 0x20U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xedU : 0U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd1U : 0x53U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x84U : 0x2fU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xe3U : 0x29U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xb3U : 0xd6U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3bU : 0x52U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa0U : 0x5aU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x6eU : 0x1bU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x1aU : 0x2cU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x83U : 9U))))))
                : ((0x00000020U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                    ? ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x75U : 0xb2U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x27U : 0xebU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xe2U : 0x80U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x12U : 7U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x9aU : 5U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x96U : 0x18U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc3U : 0x23U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc7U : 4U))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x15U : 0x31U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd8U : 0x71U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf1U : 0xe5U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa5U : 0x34U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xccU : 0xf7U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x3fU : 0x36U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x26U : 0x93U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xfdU : 0xb7U)))))
                    : ((0x00000010U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                        ? ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc0U : 0x72U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xa4U : 0x9cU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xafU : 0xa2U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd4U : 0xadU)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xf0U : 0x47U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x59U : 0xfaU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7dU : 0xc9U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x82U : 0xcaU))))
                        : ((8U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                            ? ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x76U : 0xabU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xd7U : 0xfeU))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x2bU : 0x67U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 1U : 0x30U)))
                            : ((4U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                ? ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0xc5U : 0x6fU)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x6bU : 0xf2U))
                                : ((2U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                    ? ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7bU : 0x77U)
                                    : ((1U & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])
                                        ? 0x7cU : 0x63U))))))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[0U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__0__KET____DOT__u_sb__DOT__out_byte;
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[1U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__1__KET____DOT__u_sb__DOT__out_byte;
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[2U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__2__KET____DOT__u_sb__DOT__out_byte;
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[3U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__3__KET____DOT__u_sb__DOT__out_byte;
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[4U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__4__KET____DOT__u_sb__DOT__out_byte;
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[5U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__5__KET____DOT__u_sb__DOT__out_byte;
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[6U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__6__KET____DOT__u_sb__DOT__out_byte;
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[7U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__7__KET____DOT__u_sb__DOT__out_byte;
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[8U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__8__KET____DOT__u_sb__DOT__out_byte;
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[9U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__9__KET____DOT__u_sb__DOT__out_byte;
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[10U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__10__KET____DOT__u_sb__DOT__out_byte;
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[11U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__11__KET____DOT__u_sb__DOT__out_byte;
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[12U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__12__KET____DOT__u_sb__DOT__out_byte;
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[13U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__13__KET____DOT__u_sb__DOT__out_byte;
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[14U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__14__KET____DOT__u_sb__DOT__out_byte;
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[15U]
        = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__15__KET____DOT__u_sb__DOT__out_byte;
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[0U]
        = (IData)((((QData)((IData)(((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__8__KET____DOT__u_sb__DOT__out_byte)
                                       << 0x00000018U)
                                      | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__9__KET____DOT__u_sb__DOT__out_byte)
                                         << 0x00000010U))
                                     | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__10__KET____DOT__u_sb__DOT__out_byte)
                                         << 8U) | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__11__KET____DOT__u_sb__DOT__out_byte)))))
                    << 0x00000020U) | (QData)((IData)(
                                                      ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__12__KET____DOT__u_sb__DOT__out_byte)
                                                         << 0x00000018U)
                                                        | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__13__KET____DOT__u_sb__DOT__out_byte)
                                                           << 0x00000010U))
                                                       | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__14__KET____DOT__u_sb__DOT__out_byte)
                                                           << 8U)
                                                          | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__15__KET____DOT__u_sb__DOT__out_byte)))))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[1U]
        = (IData)(((((QData)((IData)(((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__8__KET____DOT__u_sb__DOT__out_byte)
                                        << 0x00000018U)
                                       | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__9__KET____DOT__u_sb__DOT__out_byte)
                                          << 0x00000010U))
                                      | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__10__KET____DOT__u_sb__DOT__out_byte)
                                          << 8U) | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__11__KET____DOT__u_sb__DOT__out_byte)))))
                     << 0x00000020U) | (QData)((IData)(
                                                       ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__12__KET____DOT__u_sb__DOT__out_byte)
                                                          << 0x00000018U)
                                                         | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__13__KET____DOT__u_sb__DOT__out_byte)
                                                            << 0x00000010U))
                                                        | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__14__KET____DOT__u_sb__DOT__out_byte)
                                                            << 8U)
                                                           | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__15__KET____DOT__u_sb__DOT__out_byte))))))
                   >> 0x00000020U));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[2U]
        = (IData)((((QData)((IData)(((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__0__KET____DOT__u_sb__DOT__out_byte)
                                       << 0x00000018U)
                                      | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__1__KET____DOT__u_sb__DOT__out_byte)
                                         << 0x00000010U))
                                     | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__2__KET____DOT__u_sb__DOT__out_byte)
                                         << 8U) | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__3__KET____DOT__u_sb__DOT__out_byte)))))
                    << 0x00000020U) | (QData)((IData)(
                                                      ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__4__KET____DOT__u_sb__DOT__out_byte)
                                                         << 0x00000018U)
                                                        | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__5__KET____DOT__u_sb__DOT__out_byte)
                                                           << 0x00000010U))
                                                       | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__6__KET____DOT__u_sb__DOT__out_byte)
                                                           << 8U)
                                                          | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__7__KET____DOT__u_sb__DOT__out_byte)))))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[3U]
        = (IData)(((((QData)((IData)(((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__0__KET____DOT__u_sb__DOT__out_byte)
                                        << 0x00000018U)
                                       | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__1__KET____DOT__u_sb__DOT__out_byte)
                                          << 0x00000010U))
                                      | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__2__KET____DOT__u_sb__DOT__out_byte)
                                          << 8U) | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__3__KET____DOT__u_sb__DOT__out_byte)))))
                     << 0x00000020U) | (QData)((IData)(
                                                       ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__4__KET____DOT__u_sb__DOT__out_byte)
                                                          << 0x00000018U)
                                                         | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__5__KET____DOT__u_sb__DOT__out_byte)
                                                            << 0x00000010U))
                                                        | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__6__KET____DOT__u_sb__DOT__out_byte)
                                                            << 8U)
                                                           | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__7__KET____DOT__u_sb__DOT__out_byte))))))
                   >> 0x00000020U));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
        = ((((0x0000ff00U & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[0U]
                             >> 0x00000010U)) | (0x000000ffU
                                                 & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[3U]
                                                    >> 0x00000010U)))
            << 0x00000010U) | ((0x0000ff00U & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[2U])
                               | (0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[1U])));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
        = ((((0x0000ff00U & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[1U]
                             >> 0x00000010U)) | (0x000000ffU
                                                 & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[0U]
                                                    >> 0x00000010U)))
            << 0x00000010U) | ((0x0000ff00U & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[3U])
                               | (0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[2U])));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
        = ((((0x0000ff00U & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[2U]
                             >> 0x00000010U)) | (0x000000ffU
                                                 & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[1U]
                                                    >> 0x00000010U)))
            << 0x00000010U) | ((0x0000ff00U & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[0U])
                               | (0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[3U])));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
        = ((((0x0000ff00U & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[3U]
                             >> 0x00000010U)) | (0x000000ffU
                                                 & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[2U]
                                                    >> 0x00000010U)))
            << 0x00000010U) | ((0x0000ff00U & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[1U])
                               | (0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state[0U])));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__7__03a0__KET__
        = (0x000000ffU & (((([&]() {
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__24__b
                                = (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                   >> 0x00000018U);
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__24__Vfuncout
                                = ((0x00000080U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__24__b))
                                    ? (0x1bU ^ (0x000000feU
                                                & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__24__b)
                                                   << 1U)))
                                    : (0x000000feU
                                       & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__24__b)
                                          << 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__24__Vfuncout))
                            ^ ([&]() {
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__25__b
                                = (0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                                  >> 0x00000010U));
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__25__Vfuncout
                                = (([&]() {
                                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__26__b
                                            = vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__25__b;
                                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__26__Vfuncout
                                            = ((0x00000080U
                                                & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__26__b))
                                                ? (0x1bU
                                                   ^
                                                   (0x000000feU
                                                    & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__26__b)
                                                       << 1U)))
                                                : (0x000000feU
                                                   & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__26__b)
                                                      << 1U)));
                                    }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__26__Vfuncout))
                                   ^ (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__25__b));
                        }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__25__Vfuncout)))
                           ^ ((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                               << 0x00000018U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                                  >> 8U)))
                          ^ vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__15__03a8__KET__
        = (0x000000ffU & (((((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                              << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                        >> 0x00000018U))
                            ^ ([&]() {
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__27__b
                                = (0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                                  >> 0x00000010U));
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__27__Vfuncout
                                = ((0x00000080U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__27__b))
                                    ? (0x1bU ^ (0x000000feU
                                                & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__27__b)
                                                   << 1U)))
                                    : (0x000000feU
                                       & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__27__b)
                                          << 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__27__Vfuncout)))
                           ^ ([&]() {
                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__28__b
                            = (0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                              >> 8U));
                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__28__Vfuncout
                            = (([&]() {
                                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__29__b
                                        = vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__28__b;
                                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__29__Vfuncout
                                        = ((0x00000080U
                                            & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__29__b))
                                            ? (0x1bU
                                               ^ (0x000000feU
                                                  & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__29__b)
                                                     << 1U)))
                                            : (0x000000feU
                                               & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__29__b)
                                                  << 1U)));
                                }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__29__Vfuncout))
                               ^ (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__28__b));
                    }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__28__Vfuncout)))
                          ^ vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__23__03a16__KET__
        = (0x000000ffU & (((((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                              << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                        >> 0x00000018U))
                            ^ ((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                << 0x00000010U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                                   >> 0x00000010U)))
                           ^ ([&]() {
                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__30__b
                            = (0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                              >> 8U));
                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__30__Vfuncout
                            = ((0x00000080U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__30__b))
                                ? (0x1bU ^ (0x000000feU
                                            & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__30__b)
                                               << 1U)))
                                : (0x000000feU & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__30__b)
                                                  << 1U)));
                    }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__30__Vfuncout)))
                          ^ ([&]() {
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__31__b
                        = (0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]);
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__31__Vfuncout
                        = (([&]() {
                                vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__32__b
                                    = vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__31__b;
                                vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__32__Vfuncout
                                    = ((0x00000080U
                                        & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__32__b))
                                        ? (0x1bU ^
                                           (0x000000feU
                                            & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__32__b)
                                               << 1U)))
                                        : (0x000000feU
                                           & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__32__b)
                                              << 1U)));
                            }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__32__Vfuncout))
                           ^ (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__31__b));
                }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__31__Vfuncout))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__31__03a24__KET__
        = (0x000000ffU & (((([&]() {
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__33__b
                                = (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                   >> 0x00000018U);
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__33__Vfuncout
                                = (([&]() {
                                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__34__b
                                            = vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__33__b;
                                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__34__Vfuncout
                                            = ((0x00000080U
                                                & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__34__b))
                                                ? (0x1bU
                                                   ^
                                                   (0x000000feU
                                                    & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__34__b)
                                                       << 1U)))
                                                : (0x000000feU
                                                   & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__34__b)
                                                      << 1U)));
                                    }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__34__Vfuncout))
                                   ^ (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__33__b));
                        }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__33__Vfuncout))
                            ^ ((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                << 0x00000010U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                                   >> 0x00000010U)))
                           ^ ((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                               << 0x00000018U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                                  >> 8U)))
                          ^ ([&]() {
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__35__b
                        = (0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]);
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__35__Vfuncout
                        = ((0x00000080U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__35__b))
                            ? (0x1bU ^ (0x000000feU
                                        & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__35__b)
                                           << 1U)))
                            : (0x000000feU & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__35__b)
                                              << 1U)));
                }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__35__Vfuncout))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__7__03a0__KET__
        = (0x000000ffU & (((([&]() {
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__36__b
                                = (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                   >> 0x00000018U);
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__36__Vfuncout
                                = ((0x00000080U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__36__b))
                                    ? (0x1bU ^ (0x000000feU
                                                & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__36__b)
                                                   << 1U)))
                                    : (0x000000feU
                                       & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__36__b)
                                          << 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__36__Vfuncout))
                            ^ ([&]() {
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__37__b
                                = (0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                                  >> 0x00000010U));
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__37__Vfuncout
                                = (([&]() {
                                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__38__b
                                            = vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__37__b;
                                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__38__Vfuncout
                                            = ((0x00000080U
                                                & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__38__b))
                                                ? (0x1bU
                                                   ^
                                                   (0x000000feU
                                                    & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__38__b)
                                                       << 1U)))
                                                : (0x000000feU
                                                   & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__38__b)
                                                      << 1U)));
                                    }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__38__Vfuncout))
                                   ^ (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__37__b));
                        }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__37__Vfuncout)))
                           ^ ((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                               << 0x00000018U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                                  >> 8U)))
                          ^ vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__15__03a8__KET__
        = (0x000000ffU & (((((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                              << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                        >> 0x00000018U))
                            ^ ([&]() {
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__39__b
                                = (0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                                  >> 0x00000010U));
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__39__Vfuncout
                                = ((0x00000080U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__39__b))
                                    ? (0x1bU ^ (0x000000feU
                                                & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__39__b)
                                                   << 1U)))
                                    : (0x000000feU
                                       & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__39__b)
                                          << 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__39__Vfuncout)))
                           ^ ([&]() {
                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__40__b
                            = (0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                              >> 8U));
                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__40__Vfuncout
                            = (([&]() {
                                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__41__b
                                        = vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__40__b;
                                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__41__Vfuncout
                                        = ((0x00000080U
                                            & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__41__b))
                                            ? (0x1bU
                                               ^ (0x000000feU
                                                  & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__41__b)
                                                     << 1U)))
                                            : (0x000000feU
                                               & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__41__b)
                                                  << 1U)));
                                }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__41__Vfuncout))
                               ^ (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__40__b));
                    }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__40__Vfuncout)))
                          ^ vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__23__03a16__KET__
        = (0x000000ffU & (((((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                              << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                        >> 0x00000018U))
                            ^ ((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                << 0x00000010U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                                   >> 0x00000010U)))
                           ^ ([&]() {
                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__42__b
                            = (0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                              >> 8U));
                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__42__Vfuncout
                            = ((0x00000080U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__42__b))
                                ? (0x1bU ^ (0x000000feU
                                            & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__42__b)
                                               << 1U)))
                                : (0x000000feU & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__42__b)
                                                  << 1U)));
                    }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__42__Vfuncout)))
                          ^ ([&]() {
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__43__b
                        = (0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]);
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__43__Vfuncout
                        = (([&]() {
                                vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__44__b
                                    = vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__43__b;
                                vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__44__Vfuncout
                                    = ((0x00000080U
                                        & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__44__b))
                                        ? (0x1bU ^
                                           (0x000000feU
                                            & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__44__b)
                                               << 1U)))
                                        : (0x000000feU
                                           & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__44__b)
                                              << 1U)));
                            }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__44__Vfuncout))
                           ^ (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__43__b));
                }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__43__Vfuncout))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__31__03a24__KET__
        = (0x000000ffU & (((([&]() {
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__45__b
                                = (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                   >> 0x00000018U);
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__45__Vfuncout
                                = (([&]() {
                                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__46__b
                                            = vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__45__b;
                                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__46__Vfuncout
                                            = ((0x00000080U
                                                & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__46__b))
                                                ? (0x1bU
                                                   ^
                                                   (0x000000feU
                                                    & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__46__b)
                                                       << 1U)))
                                                : (0x000000feU
                                                   & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__46__b)
                                                      << 1U)));
                                    }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__46__Vfuncout))
                                   ^ (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__45__b));
                        }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__45__Vfuncout))
                            ^ ((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                << 0x00000010U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                                   >> 0x00000010U)))
                           ^ ((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                               << 0x00000018U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                                  >> 8U)))
                          ^ ([&]() {
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__47__b
                        = (0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]);
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__47__Vfuncout
                        = ((0x00000080U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__47__b))
                            ? (0x1bU ^ (0x000000feU
                                        & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__47__b)
                                           << 1U)))
                            : (0x000000feU & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__47__b)
                                              << 1U)));
                }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__47__Vfuncout))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__7__03a0__KET__
        = (0x000000ffU & (((([&]() {
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__48__b
                                = (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                   >> 0x00000018U);
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__48__Vfuncout
                                = ((0x00000080U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__48__b))
                                    ? (0x1bU ^ (0x000000feU
                                                & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__48__b)
                                                   << 1U)))
                                    : (0x000000feU
                                       & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__48__b)
                                          << 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__48__Vfuncout))
                            ^ ([&]() {
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__49__b
                                = (0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                                  >> 0x00000010U));
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__49__Vfuncout
                                = (([&]() {
                                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__50__b
                                            = vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__49__b;
                                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__50__Vfuncout
                                            = ((0x00000080U
                                                & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__50__b))
                                                ? (0x1bU
                                                   ^
                                                   (0x000000feU
                                                    & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__50__b)
                                                       << 1U)))
                                                : (0x000000feU
                                                   & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__50__b)
                                                      << 1U)));
                                    }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__50__Vfuncout))
                                   ^ (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__49__b));
                        }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__49__Vfuncout)))
                           ^ ((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                               << 0x00000018U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                                  >> 8U)))
                          ^ vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__15__03a8__KET__
        = (0x000000ffU & (((((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                              << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                        >> 0x00000018U))
                            ^ ([&]() {
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__51__b
                                = (0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                                  >> 0x00000010U));
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__51__Vfuncout
                                = ((0x00000080U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__51__b))
                                    ? (0x1bU ^ (0x000000feU
                                                & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__51__b)
                                                   << 1U)))
                                    : (0x000000feU
                                       & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__51__b)
                                          << 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__51__Vfuncout)))
                           ^ ([&]() {
                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__52__b
                            = (0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                              >> 8U));
                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__52__Vfuncout
                            = (([&]() {
                                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__53__b
                                        = vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__52__b;
                                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__53__Vfuncout
                                        = ((0x00000080U
                                            & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__53__b))
                                            ? (0x1bU
                                               ^ (0x000000feU
                                                  & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__53__b)
                                                     << 1U)))
                                            : (0x000000feU
                                               & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__53__b)
                                                  << 1U)));
                                }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__53__Vfuncout))
                               ^ (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__52__b));
                    }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__52__Vfuncout)))
                          ^ vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__23__03a16__KET__
        = (0x000000ffU & (((((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                              << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                        >> 0x00000018U))
                            ^ ((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                << 0x00000010U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                                   >> 0x00000010U)))
                           ^ ([&]() {
                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__54__b
                            = (0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                              >> 8U));
                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__54__Vfuncout
                            = ((0x00000080U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__54__b))
                                ? (0x1bU ^ (0x000000feU
                                            & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__54__b)
                                               << 1U)))
                                : (0x000000feU & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__54__b)
                                                  << 1U)));
                    }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__54__Vfuncout)))
                          ^ ([&]() {
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__55__b
                        = (0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]);
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__55__Vfuncout
                        = (([&]() {
                                vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__56__b
                                    = vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__55__b;
                                vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__56__Vfuncout
                                    = ((0x00000080U
                                        & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__56__b))
                                        ? (0x1bU ^
                                           (0x000000feU
                                            & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__56__b)
                                               << 1U)))
                                        : (0x000000feU
                                           & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__56__b)
                                              << 1U)));
                            }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__56__Vfuncout))
                           ^ (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__55__b));
                }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__55__Vfuncout))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__31__03a24__KET__
        = (0x000000ffU & (((([&]() {
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__57__b
                                = (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                   >> 0x00000018U);
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__57__Vfuncout
                                = (([&]() {
                                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__58__b
                                            = vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__57__b;
                                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__58__Vfuncout
                                            = ((0x00000080U
                                                & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__58__b))
                                                ? (0x1bU
                                                   ^
                                                   (0x000000feU
                                                    & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__58__b)
                                                       << 1U)))
                                                : (0x000000feU
                                                   & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__58__b)
                                                      << 1U)));
                                    }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__58__Vfuncout))
                                   ^ (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__57__b));
                        }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__57__Vfuncout))
                            ^ ((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                << 0x00000010U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                                   >> 0x00000010U)))
                           ^ ((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                               << 0x00000018U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                                  >> 8U)))
                          ^ ([&]() {
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__59__b
                        = (0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]);
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__59__Vfuncout
                        = ((0x00000080U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__59__b))
                            ? (0x1bU ^ (0x000000feU
                                        & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__59__b)
                                           << 1U)))
                            : (0x000000feU & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__59__b)
                                              << 1U)));
                }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__59__Vfuncout))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__7__03a0__KET__
        = (0x000000ffU & (((([&]() {
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__60__b
                                = (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                   >> 0x00000018U);
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__60__Vfuncout
                                = ((0x00000080U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__60__b))
                                    ? (0x1bU ^ (0x000000feU
                                                & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__60__b)
                                                   << 1U)))
                                    : (0x000000feU
                                       & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__60__b)
                                          << 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__60__Vfuncout))
                            ^ ([&]() {
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__61__b
                                = (0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                                  >> 0x00000010U));
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__61__Vfuncout
                                = (([&]() {
                                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__62__b
                                            = vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__61__b;
                                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__62__Vfuncout
                                            = ((0x00000080U
                                                & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__62__b))
                                                ? (0x1bU
                                                   ^
                                                   (0x000000feU
                                                    & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__62__b)
                                                       << 1U)))
                                                : (0x000000feU
                                                   & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__62__b)
                                                      << 1U)));
                                    }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__62__Vfuncout))
                                   ^ (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__61__b));
                        }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__61__Vfuncout)))
                           ^ ((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                               << 0x00000018U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                                  >> 8U)))
                          ^ vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__15__03a8__KET__
        = (0x000000ffU & (((((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                              << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                        >> 0x00000018U))
                            ^ ([&]() {
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__63__b
                                = (0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                                  >> 0x00000010U));
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__63__Vfuncout
                                = ((0x00000080U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__63__b))
                                    ? (0x1bU ^ (0x000000feU
                                                & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__63__b)
                                                   << 1U)))
                                    : (0x000000feU
                                       & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__63__b)
                                          << 1U)));
                        }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__63__Vfuncout)))
                           ^ ([&]() {
                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__64__b
                            = (0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                              >> 8U));
                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__64__Vfuncout
                            = (([&]() {
                                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__65__b
                                        = vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__64__b;
                                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__65__Vfuncout
                                        = ((0x00000080U
                                            & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__65__b))
                                            ? (0x1bU
                                               ^ (0x000000feU
                                                  & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__65__b)
                                                     << 1U)))
                                            : (0x000000feU
                                               & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__65__b)
                                                  << 1U)));
                                }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__65__Vfuncout))
                               ^ (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__64__b));
                    }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__64__Vfuncout)))
                          ^ vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__23__03a16__KET__
        = (0x000000ffU & (((((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                              << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                        >> 0x00000018U))
                            ^ ((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                << 0x00000010U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                                   >> 0x00000010U)))
                           ^ ([&]() {
                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__66__b
                            = (0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                              >> 8U));
                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__66__Vfuncout
                            = ((0x00000080U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__66__b))
                                ? (0x1bU ^ (0x000000feU
                                            & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__66__b)
                                               << 1U)))
                                : (0x000000feU & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__66__b)
                                                  << 1U)));
                    }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__66__Vfuncout)))
                          ^ ([&]() {
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__67__b
                        = (0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]);
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__67__Vfuncout
                        = (([&]() {
                                vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__68__b
                                    = vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__67__b;
                                vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__68__Vfuncout
                                    = ((0x00000080U
                                        & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__68__b))
                                        ? (0x1bU ^
                                           (0x000000feU
                                            & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__68__b)
                                               << 1U)))
                                        : (0x000000feU
                                           & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__68__b)
                                              << 1U)));
                            }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__68__Vfuncout))
                           ^ (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__67__b));
                }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__67__Vfuncout))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__31__03a24__KET__
        = (0x000000ffU & (((([&]() {
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__69__b
                                = (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                   >> 0x00000018U);
                            vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__69__Vfuncout
                                = (([&]() {
                                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__70__b
                                            = vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__69__b;
                                        vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__70__Vfuncout
                                            = ((0x00000080U
                                                & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__70__b))
                                                ? (0x1bU
                                                   ^
                                                   (0x000000feU
                                                    & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__70__b)
                                                       << 1U)))
                                                : (0x000000feU
                                                   & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__70__b)
                                                      << 1U)));
                                    }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__70__Vfuncout))
                                   ^ (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__69__b));
                        }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__69__Vfuncout))
                            ^ ((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                << 0x00000010U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                                   >> 0x00000010U)))
                           ^ ((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                               << 0x00000018U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                                  >> 8U)))
                          ^ ([&]() {
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__71__b
                        = (0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]);
                    vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__71__Vfuncout
                        = ((0x00000080U & (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__71__b))
                            ? (0x1bU ^ (0x000000feU
                                        & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__71__b)
                                           << 1U)))
                            : (0x000000feU & ((IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__71__b)
                                              << 1U)));
                }(), (IData)(vlSelfRef.__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__71__Vfuncout))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__127__03a120__KET__
        = (0x000000ffU & ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__7__03a0__KET__)
                          ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[3U]
                              << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__round_key[3U]
                                        >> 0x00000018U))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__119__03a112__KET__
        = (0x000000ffU & ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__15__03a8__KET__)
                          ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[3U]
                              << 0x00000010U) | (vlSelfRef.aes128_encrypt_core__DOT__round_key[3U]
                                                 >> 0x00000010U))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__111__03a104__KET__
        = (0x000000ffU & ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__23__03a16__KET__)
                          ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[3U]
                              << 0x00000018U) | (vlSelfRef.aes128_encrypt_core__DOT__round_key[3U]
                                                 >> 8U))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__103__03a96__KET__
        = (0x000000ffU & ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__31__03a24__KET__)
                          ^ vlSelfRef.aes128_encrypt_core__DOT__round_key[3U]));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__95__03a88__KET__
        = (0x000000ffU & ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__7__03a0__KET__)
                          ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[2U]
                              << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__round_key[2U]
                                        >> 0x00000018U))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__87__03a80__KET__
        = (0x000000ffU & ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__15__03a8__KET__)
                          ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[2U]
                              << 0x00000010U) | (vlSelfRef.aes128_encrypt_core__DOT__round_key[2U]
                                                 >> 0x00000010U))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__79__03a72__KET__
        = (0x000000ffU & ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__23__03a16__KET__)
                          ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[2U]
                              << 0x00000018U) | (vlSelfRef.aes128_encrypt_core__DOT__round_key[2U]
                                                 >> 8U))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__71__03a64__KET__
        = (0x000000ffU & ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__31__03a24__KET__)
                          ^ vlSelfRef.aes128_encrypt_core__DOT__round_key[2U]));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__63__03a56__KET__
        = (0x000000ffU & ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__7__03a0__KET__)
                          ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[1U]
                              << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__round_key[1U]
                                        >> 0x00000018U))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__55__03a48__KET__
        = (0x000000ffU & ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__15__03a8__KET__)
                          ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[1U]
                              << 0x00000010U) | (vlSelfRef.aes128_encrypt_core__DOT__round_key[1U]
                                                 >> 0x00000010U))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__47__03a40__KET__
        = (0x000000ffU & ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__23__03a16__KET__)
                          ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[1U]
                              << 0x00000018U) | (vlSelfRef.aes128_encrypt_core__DOT__round_key[1U]
                                                 >> 8U))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__39__03a32__KET__
        = (0x000000ffU & ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__31__03a24__KET__)
                          ^ vlSelfRef.aes128_encrypt_core__DOT__round_key[1U]));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__31__03a24__KET__
        = (0x000000ffU & ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__7__03a0__KET__)
                          ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[0U]
                              << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__round_key[0U]
                                        >> 0x00000018U))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__23__03a16__KET__
        = (0x000000ffU & ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__15__03a8__KET__)
                          ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[0U]
                              << 0x00000010U) | (vlSelfRef.aes128_encrypt_core__DOT__round_key[0U]
                                                 >> 0x00000010U))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__15__03a8__KET__
        = (0x000000ffU & ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__23__03a16__KET__)
                          ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[0U]
                              << 0x00000018U) | (vlSelfRef.aes128_encrypt_core__DOT__round_key[0U]
                                                 >> 8U))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__7__03a0__KET__
        = (0x000000ffU & ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__31__03a24__KET__)
                          ^ vlSelfRef.aes128_encrypt_core__DOT__round_key[0U]));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__state_out[0U]
        = ((((0x0000ff00U & (((0x0aU == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))
                               ? (((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                    << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                              >> 0x00000018U))
                                  ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[0U]
                                      << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__round_key[0U]
                                                >> 0x00000018U)))
                               : (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__31__03a24__KET__))
                             << 8U)) | (0x000000ffU
                                        & ((0x0aU == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))
                                            ? (((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                                 << 0x00000010U)
                                                | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                                   >> 0x00000010U))
                                               ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[0U]
                                                   << 0x00000010U)
                                                  | (vlSelfRef.aes128_encrypt_core__DOT__round_key[0U]
                                                     >> 0x00000010U)))
                                            : (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__23__03a16__KET__))))
            << 0x00000010U) | ((0x0000ff00U & (((0x0aU
                                                 == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))
                                                 ?
                                                (((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                                   << 0x00000018U)
                                                  | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                                     >> 8U))
                                                 ^
                                                 ((vlSelfRef.aes128_encrypt_core__DOT__round_key[0U]
                                                   << 0x00000018U)
                                                  | (vlSelfRef.aes128_encrypt_core__DOT__round_key[0U]
                                                     >> 8U)))
                                                 : (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__15__03a8__KET__))
                                               << 8U))
                               | (0x000000ffU & ((0x0aU
                                                  == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))
                                                  ?
                                                 (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                                  ^ vlSelfRef.aes128_encrypt_core__DOT__round_key[0U])
                                                  : (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__7__03a0__KET__)))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__state_out[1U]
        = ((((0x0000ff00U & (((0x0aU == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))
                               ? (((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                    << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                              >> 0x00000018U))
                                  ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[1U]
                                      << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__round_key[1U]
                                                >> 0x00000018U)))
                               : (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__63__03a56__KET__))
                             << 8U)) | (0x000000ffU
                                        & ((0x0aU == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))
                                            ? (((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                                 << 0x00000010U)
                                                | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                                   >> 0x00000010U))
                                               ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[1U]
                                                   << 0x00000010U)
                                                  | (vlSelfRef.aes128_encrypt_core__DOT__round_key[1U]
                                                     >> 0x00000010U)))
                                            : (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__55__03a48__KET__))))
            << 0x00000010U) | ((0x0000ff00U & (((0x0aU
                                                 == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))
                                                 ?
                                                (((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                                   << 0x00000018U)
                                                  | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                                     >> 8U))
                                                 ^
                                                 ((vlSelfRef.aes128_encrypt_core__DOT__round_key[1U]
                                                   << 0x00000018U)
                                                  | (vlSelfRef.aes128_encrypt_core__DOT__round_key[1U]
                                                     >> 8U)))
                                                 : (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__47__03a40__KET__))
                                               << 8U))
                               | (0x000000ffU & ((0x0aU
                                                  == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))
                                                  ?
                                                 (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                                  ^ vlSelfRef.aes128_encrypt_core__DOT__round_key[1U])
                                                  : (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__39__03a32__KET__)))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__state_out[2U]
        = ((((0x0000ff00U & (((0x0aU == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))
                               ? (((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                    << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                              >> 0x00000018U))
                                  ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[2U]
                                      << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__round_key[2U]
                                                >> 0x00000018U)))
                               : (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__95__03a88__KET__))
                             << 8U)) | (0x000000ffU
                                        & ((0x0aU == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))
                                            ? (((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                                 << 0x00000010U)
                                                | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                                   >> 0x00000010U))
                                               ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[2U]
                                                   << 0x00000010U)
                                                  | (vlSelfRef.aes128_encrypt_core__DOT__round_key[2U]
                                                     >> 0x00000010U)))
                                            : (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__87__03a80__KET__))))
            << 0x00000010U) | ((0x0000ff00U & (((0x0aU
                                                 == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))
                                                 ?
                                                (((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                                   << 0x00000018U)
                                                  | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                                     >> 8U))
                                                 ^
                                                 ((vlSelfRef.aes128_encrypt_core__DOT__round_key[2U]
                                                   << 0x00000018U)
                                                  | (vlSelfRef.aes128_encrypt_core__DOT__round_key[2U]
                                                     >> 8U)))
                                                 : (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__79__03a72__KET__))
                                               << 8U))
                               | (0x000000ffU & ((0x0aU
                                                  == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))
                                                  ?
                                                 (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                                  ^ vlSelfRef.aes128_encrypt_core__DOT__round_key[2U])
                                                  : (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__71__03a64__KET__)))));
    vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__state_out[3U]
        = ((((0x0000ff00U & (((0x0aU == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))
                               ? (((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                    << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                              >> 0x00000018U))
                                  ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[3U]
                                      << 8U) | (vlSelfRef.aes128_encrypt_core__DOT__round_key[3U]
                                                >> 0x00000018U)))
                               : (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__127__03a120__KET__))
                             << 8U)) | (0x000000ffU
                                        & ((0x0aU == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))
                                            ? (((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                                 << 0x00000010U)
                                                | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                                   >> 0x00000010U))
                                               ^ ((vlSelfRef.aes128_encrypt_core__DOT__round_key[3U]
                                                   << 0x00000010U)
                                                  | (vlSelfRef.aes128_encrypt_core__DOT__round_key[3U]
                                                     >> 0x00000010U)))
                                            : (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__119__03a112__KET__))))
            << 0x00000010U) | ((0x0000ff00U & (((0x0aU
                                                 == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))
                                                 ?
                                                (((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                                   << 0x00000018U)
                                                  | (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                                     >> 8U))
                                                 ^
                                                 ((vlSelfRef.aes128_encrypt_core__DOT__round_key[3U]
                                                   << 0x00000018U)
                                                  | (vlSelfRef.aes128_encrypt_core__DOT__round_key[3U]
                                                     >> 8U)))
                                                 : (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__111__03a104__KET__))
                                               << 8U))
                               | (0x000000ffU & ((0x0aU
                                                  == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))
                                                  ?
                                                 (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                                  ^ vlSelfRef.aes128_encrypt_core__DOT__round_key[3U])
                                                  : (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__103__03a96__KET__)))));
}

void Vaes128_encrypt_core___024root___nba_sequent__TOP__0(Vaes128_encrypt_core___024root* vlSelf);

void Vaes128_encrypt_core___024root___eval_nba(Vaes128_encrypt_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root___eval_nba\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vaes128_encrypt_core___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
        Vaes128_encrypt_core___024root___nba_sequent__TOP__1(vlSelf);
    }
}

void Vaes128_encrypt_core___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

void Vaes128_encrypt_core___024root___eval_triggers_vec__act(Vaes128_encrypt_core___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vaes128_encrypt_core___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vaes128_encrypt_core___024root___eval_phase__act(Vaes128_encrypt_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root___eval_phase__act\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vaes128_encrypt_core___024root___eval_triggers_vec__act(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vaes128_encrypt_core___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vaes128_encrypt_core___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vaes128_encrypt_core___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vaes128_encrypt_core___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

bool Vaes128_encrypt_core___024root___eval_phase__nba(Vaes128_encrypt_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root___eval_phase__nba\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vaes128_encrypt_core___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vaes128_encrypt_core___024root___eval_nba(vlSelf);
        Vaes128_encrypt_core___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vaes128_encrypt_core___024root___eval(Vaes128_encrypt_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root___eval\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vaes128_encrypt_core___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("/Users/kyrie/Downloads/OpenHands-1.5.0/MultiAgent_FPGA/fpga_flow/reports/conversations/39d6b054db1e4640a1fd950621976c0b/promoted/aes128_encrypt_core/rtl/aes128_encrypt_core.v", 1, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vaes128_encrypt_core___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("/Users/kyrie/Downloads/OpenHands-1.5.0/MultiAgent_FPGA/fpga_flow/reports/conversations/39d6b054db1e4640a1fd950621976c0b/promoted/aes128_encrypt_core/rtl/aes128_encrypt_core.v", 1, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U)
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vaes128_encrypt_core___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vaes128_encrypt_core___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vaes128_encrypt_core___024root___eval_debug_assertions(Vaes128_encrypt_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root___eval_debug_assertions\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst_n & 0xfeU)))) {
        Verilated::overWidthError("rst_n");
    }
    if (VL_UNLIKELY(((vlSelfRef.start & 0xfeU)))) {
        Verilated::overWidthError("start");
    }
}
#endif  // VL_DEBUG
