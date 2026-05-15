// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vaes128_encrypt_core__Syms.h"


void Vaes128_encrypt_core___024root__trace_chg_0_sub_0(Vaes128_encrypt_core___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vaes128_encrypt_core___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root__trace_chg_0\n"); );
    // Body
    Vaes128_encrypt_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaes128_encrypt_core___024root*>(voidSelf);
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vaes128_encrypt_core___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vaes128_encrypt_core___024root__trace_chg_0_sub_0(Vaes128_encrypt_core___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root__trace_chg_0_sub_0\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlWide<4>/*127:0*/ __Vtemp_4;
    VlWide<4>/*127:0*/ __Vtemp_6;
    VlWide<4>/*127:0*/ __Vtemp_8;
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 0);
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgCData(oldp+0,(vlSelfRef.aes128_encrypt_core__DOT__fsm_state),2);
        bufp->chgWData(oldp+1,(vlSelfRef.aes128_encrypt_core__DOT__key_reg),128);
        bufp->chgWData(oldp+5,(vlSelfRef.aes128_encrypt_core__DOT__plaintext_reg),128);
        bufp->chgWData(oldp+9,(vlSelfRef.aes128_encrypt_core__DOT__state_reg),128);
        bufp->chgCData(oldp+13,(vlSelfRef.aes128_encrypt_core__DOT__round_index),4);
        bufp->chgWData(oldp+14,(vlSelfRef.aes128_encrypt_core__DOT__round_key),128);
        bufp->chgWData(oldp+18,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state),128);
        bufp->chgWData(oldp+22,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire),128);
        if ((0x0aU == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))) {
            __Vtemp_4[0U] = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U];
            __Vtemp_4[1U] = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U];
            __Vtemp_4[2U] = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U];
            __Vtemp_4[3U] = vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U];
        } else {
            __Vtemp_4[0U] = ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__7__03a0__KET__)
                               << 0x00000018U) | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__15__03a8__KET__)
                                                  << 0x00000010U))
                             | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__23__03a16__KET__)
                                 << 8U) | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__31__03a24__KET__)));
            __Vtemp_4[1U] = ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__7__03a0__KET__)
                               << 0x00000018U) | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__15__03a8__KET__)
                                                  << 0x00000010U))
                             | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__23__03a16__KET__)
                                 << 8U) | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__31__03a24__KET__)));
            __Vtemp_4[2U] = (IData)((((QData)((IData)(
                                                      ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__7__03a0__KET__)
                                                         << 0x00000018U)
                                                        | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__15__03a8__KET__)
                                                           << 0x00000010U))
                                                       | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__23__03a16__KET__)
                                                           << 8U)
                                                          | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__31__03a24__KET__)))))
                                      << 0x00000020U)
                                     | (QData)((IData)(
                                                       ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__7__03a0__KET__)
                                                          << 0x00000018U)
                                                         | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__15__03a8__KET__)
                                                            << 0x00000010U))
                                                        | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__23__03a16__KET__)
                                                            << 8U)
                                                           | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__31__03a24__KET__)))))));
            __Vtemp_4[3U] = (IData)(((((QData)((IData)(
                                                       ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__7__03a0__KET__)
                                                          << 0x00000018U)
                                                         | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__15__03a8__KET__)
                                                            << 0x00000010U))
                                                        | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__23__03a16__KET__)
                                                            << 8U)
                                                           | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__31__03a24__KET__)))))
                                       << 0x00000020U)
                                      | (QData)((IData)(
                                                        ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__7__03a0__KET__)
                                                           << 0x00000018U)
                                                          | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__15__03a8__KET__)
                                                             << 0x00000010U))
                                                         | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__23__03a16__KET__)
                                                             << 8U)
                                                            | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__31__03a24__KET__))))))
                                     >> 0x00000020U));
        }
        bufp->chgWData(oldp+26,(__Vtemp_4),128);
        bufp->chgWData(oldp+30,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__state_out),128);
        bufp->chgBit(oldp+34,((0x0aU == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))));
        bufp->chgIData(oldp+35,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__i),32);
        bufp->chgIData(oldp+36,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w0),32);
        bufp->chgIData(oldp+37,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w1),32);
        bufp->chgIData(oldp+38,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w2),32);
        bufp->chgIData(oldp+39,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w3),32);
        bufp->chgIData(oldp+40,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__temp),32);
        bufp->chgIData(oldp+41,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw0),32);
        bufp->chgIData(oldp+42,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw1),32);
        bufp->chgIData(oldp+43,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw2),32);
        bufp->chgIData(oldp+44,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw3),32);
        bufp->chgCData(oldp+45,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__round_sel),4);
        bufp->chgCData(oldp+46,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[0]),8);
        bufp->chgCData(oldp+47,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[1]),8);
        bufp->chgCData(oldp+48,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[2]),8);
        bufp->chgCData(oldp+49,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[3]),8);
        bufp->chgCData(oldp+50,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[4]),8);
        bufp->chgCData(oldp+51,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[5]),8);
        bufp->chgCData(oldp+52,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[6]),8);
        bufp->chgCData(oldp+53,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[7]),8);
        bufp->chgCData(oldp+54,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[8]),8);
        bufp->chgCData(oldp+55,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[9]),8);
        bufp->chgCData(oldp+56,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[10]),8);
        bufp->chgCData(oldp+57,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[11]),8);
        bufp->chgCData(oldp+58,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[12]),8);
        bufp->chgCData(oldp+59,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[13]),8);
        bufp->chgCData(oldp+60,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[14]),8);
        bufp->chgCData(oldp+61,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[15]),8);
        bufp->chgCData(oldp+62,((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                 >> 0x00000018U)),8);
        bufp->chgCData(oldp+63,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                                >> 0x00000010U))),8);
        bufp->chgCData(oldp+64,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                                >> 8U))),8);
        bufp->chgCData(oldp+65,((0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U])),8);
        bufp->chgCData(oldp+66,((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                 >> 0x00000018U)),8);
        bufp->chgCData(oldp+67,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                                >> 0x00000010U))),8);
        bufp->chgCData(oldp+68,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                                >> 8U))),8);
        bufp->chgCData(oldp+69,((0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U])),8);
        bufp->chgCData(oldp+70,((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                 >> 0x00000018U)),8);
        bufp->chgCData(oldp+71,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                                >> 0x00000010U))),8);
        bufp->chgCData(oldp+72,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                                >> 8U))),8);
        bufp->chgCData(oldp+73,((0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U])),8);
        bufp->chgCData(oldp+74,((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                 >> 0x00000018U)),8);
        bufp->chgCData(oldp+75,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                                >> 0x00000010U))),8);
        bufp->chgCData(oldp+76,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                                >> 8U))),8);
        bufp->chgCData(oldp+77,((0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U])),8);
        bufp->chgIData(oldp+78,(((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__31__03a24__KET__)
                                   << 0x00000018U)
                                  | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__23__03a16__KET__)
                                     << 0x00000010U))
                                 | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__15__03a8__KET__)
                                     << 8U) | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__7__03a0__KET__)))),32);
        bufp->chgIData(oldp+79,(((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__31__03a24__KET__)
                                   << 0x00000018U)
                                  | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__23__03a16__KET__)
                                     << 0x00000010U))
                                 | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__15__03a8__KET__)
                                     << 8U) | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__7__03a0__KET__)))),32);
        bufp->chgIData(oldp+80,(((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__31__03a24__KET__)
                                   << 0x00000018U)
                                  | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__23__03a16__KET__)
                                     << 0x00000010U))
                                 | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__15__03a8__KET__)
                                     << 8U) | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__7__03a0__KET__)))),32);
        bufp->chgIData(oldp+81,(((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__31__03a24__KET__)
                                   << 0x00000018U)
                                  | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__23__03a16__KET__)
                                     << 0x00000010U))
                                 | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__15__03a8__KET__)
                                     << 8U) | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__7__03a0__KET__)))),32);
        __Vtemp_6[0U] = ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__7__03a0__KET__)
                           << 0x00000018U) | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__15__03a8__KET__)
                                              << 0x00000010U))
                         | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__23__03a16__KET__)
                             << 8U) | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__31__03a24__KET__)));
        __Vtemp_6[1U] = ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__7__03a0__KET__)
                           << 0x00000018U) | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__15__03a8__KET__)
                                              << 0x00000010U))
                         | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__23__03a16__KET__)
                             << 8U) | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__31__03a24__KET__)));
        __Vtemp_6[2U] = (IData)((((QData)((IData)((
                                                   (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__7__03a0__KET__)
                                                     << 0x00000018U)
                                                    | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__15__03a8__KET__)
                                                       << 0x00000010U))
                                                   | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__23__03a16__KET__)
                                                       << 8U)
                                                      | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__31__03a24__KET__)))))
                                  << 0x00000020U) | (QData)((IData)(
                                                                    ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__7__03a0__KET__)
                                                                       << 0x00000018U)
                                                                      | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__15__03a8__KET__)
                                                                         << 0x00000010U))
                                                                     | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__23__03a16__KET__)
                                                                         << 8U)
                                                                        | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__31__03a24__KET__)))))));
        __Vtemp_6[3U] = (IData)(((((QData)((IData)(
                                                   ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__7__03a0__KET__)
                                                      << 0x00000018U)
                                                     | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__15__03a8__KET__)
                                                        << 0x00000010U))
                                                    | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__23__03a16__KET__)
                                                        << 8U)
                                                       | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__31__03a24__KET__)))))
                                   << 0x00000020U)
                                  | (QData)((IData)(
                                                    ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__7__03a0__KET__)
                                                       << 0x00000018U)
                                                      | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__15__03a8__KET__)
                                                         << 0x00000010U))
                                                     | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__23__03a16__KET__)
                                                         << 8U)
                                                        | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__31__03a24__KET__))))))
                                 >> 0x00000020U));
        bufp->chgWData(oldp+82,(__Vtemp_6),128);
        __Vtemp_8[0U] = ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__31__03a24__KET__)
                           << 0x00000018U) | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__23__03a16__KET__)
                                              << 0x00000010U))
                         | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__15__03a8__KET__)
                             << 8U) | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__7__03a0__KET__)));
        __Vtemp_8[1U] = ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__63__03a56__KET__)
                           << 0x00000018U) | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__55__03a48__KET__)
                                              << 0x00000010U))
                         | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__47__03a40__KET__)
                             << 8U) | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__39__03a32__KET__)));
        __Vtemp_8[2U] = (IData)((((QData)((IData)((
                                                   (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__127__03a120__KET__)
                                                     << 0x00000018U)
                                                    | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__119__03a112__KET__)
                                                       << 0x00000010U))
                                                   | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__111__03a104__KET__)
                                                       << 8U)
                                                      | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__103__03a96__KET__)))))
                                  << 0x00000020U) | (QData)((IData)(
                                                                    ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__95__03a88__KET__)
                                                                       << 0x00000018U)
                                                                      | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__87__03a80__KET__)
                                                                         << 0x00000010U))
                                                                     | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__79__03a72__KET__)
                                                                         << 8U)
                                                                        | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__71__03a64__KET__)))))));
        __Vtemp_8[3U] = (IData)(((((QData)((IData)(
                                                   ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__127__03a120__KET__)
                                                      << 0x00000018U)
                                                     | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__119__03a112__KET__)
                                                        << 0x00000010U))
                                                    | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__111__03a104__KET__)
                                                        << 8U)
                                                       | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__103__03a96__KET__)))))
                                   << 0x00000020U)
                                  | (QData)((IData)(
                                                    ((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__95__03a88__KET__)
                                                       << 0x00000018U)
                                                      | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__87__03a80__KET__)
                                                         << 0x00000010U))
                                                     | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__79__03a72__KET__)
                                                         << 8U)
                                                        | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__71__03a64__KET__))))))
                                 >> 0x00000020U));
        bufp->chgWData(oldp+86,(__Vtemp_8),128);
        bufp->chgCData(oldp+90,((vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U]
                                 >> 0x00000018U)),8);
        bufp->chgCData(oldp+91,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__0__KET____DOT__u_sb__DOT__out_byte),8);
        bufp->chgCData(oldp+92,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U]
                                                >> 8U))),8);
        bufp->chgCData(oldp+93,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__10__KET____DOT__u_sb__DOT__out_byte),8);
        bufp->chgCData(oldp+94,((0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])),8);
        bufp->chgCData(oldp+95,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__11__KET____DOT__u_sb__DOT__out_byte),8);
        bufp->chgCData(oldp+96,((vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U]
                                 >> 0x00000018U)),8);
        bufp->chgCData(oldp+97,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__12__KET____DOT__u_sb__DOT__out_byte),8);
        bufp->chgCData(oldp+98,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U]
                                                >> 0x00000010U))),8);
        bufp->chgCData(oldp+99,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__13__KET____DOT__u_sb__DOT__out_byte),8);
        bufp->chgCData(oldp+100,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U]
                                                 >> 8U))),8);
        bufp->chgCData(oldp+101,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__14__KET____DOT__u_sb__DOT__out_byte),8);
        bufp->chgCData(oldp+102,((0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])),8);
        bufp->chgCData(oldp+103,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__15__KET____DOT__u_sb__DOT__out_byte),8);
        bufp->chgCData(oldp+104,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U]
                                                 >> 0x00000010U))),8);
        bufp->chgCData(oldp+105,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__1__KET____DOT__u_sb__DOT__out_byte),8);
        bufp->chgCData(oldp+106,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U]
                                                 >> 8U))),8);
        bufp->chgCData(oldp+107,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__2__KET____DOT__u_sb__DOT__out_byte),8);
        bufp->chgCData(oldp+108,((0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])),8);
        bufp->chgCData(oldp+109,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__3__KET____DOT__u_sb__DOT__out_byte),8);
        bufp->chgCData(oldp+110,((vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U]
                                  >> 0x00000018U)),8);
        bufp->chgCData(oldp+111,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__4__KET____DOT__u_sb__DOT__out_byte),8);
        bufp->chgCData(oldp+112,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U]
                                                 >> 0x00000010U))),8);
        bufp->chgCData(oldp+113,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__5__KET____DOT__u_sb__DOT__out_byte),8);
        bufp->chgCData(oldp+114,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U]
                                                 >> 8U))),8);
        bufp->chgCData(oldp+115,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__6__KET____DOT__u_sb__DOT__out_byte),8);
        bufp->chgCData(oldp+116,((0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])),8);
        bufp->chgCData(oldp+117,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__7__KET____DOT__u_sb__DOT__out_byte),8);
        bufp->chgCData(oldp+118,((vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U]
                                  >> 0x00000018U)),8);
        bufp->chgCData(oldp+119,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__8__KET____DOT__u_sb__DOT__out_byte),8);
        bufp->chgCData(oldp+120,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U]
                                                 >> 0x00000010U))),8);
        bufp->chgCData(oldp+121,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__9__KET____DOT__u_sb__DOT__out_byte),8);
    }
    bufp->chgBit(oldp+122,(vlSelfRef.clk));
    bufp->chgBit(oldp+123,(vlSelfRef.rst_n));
    bufp->chgBit(oldp+124,(vlSelfRef.start));
    bufp->chgWData(oldp+125,(vlSelfRef.key),128);
    bufp->chgWData(oldp+129,(vlSelfRef.plaintext),128);
    bufp->chgBit(oldp+133,(vlSelfRef.busy));
    bufp->chgBit(oldp+134,(vlSelfRef.done));
    bufp->chgWData(oldp+135,(vlSelfRef.ciphertext),128);
}

void Vaes128_encrypt_core___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root__trace_cleanup\n"); );
    // Body
    Vaes128_encrypt_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaes128_encrypt_core___024root*>(voidSelf);
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
