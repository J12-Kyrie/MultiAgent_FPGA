// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaes128_encrypt_core.h for the primary calling header

#include "Vaes128_encrypt_core__pch.h"

VL_ATTR_COLD void Vaes128_encrypt_core___024root___stl_sequent__TOP__0(Vaes128_encrypt_core___024root* vlSelf);
VL_ATTR_COLD void Vaes128_encrypt_core___024root____Vm_traceActivitySetAll(Vaes128_encrypt_core___024root* vlSelf);
void Vaes128_encrypt_core___024root___nba_sequent__TOP__1(Vaes128_encrypt_core___024root* vlSelf);

VL_ATTR_COLD void Vaes128_encrypt_core___024root___eval_stl(Vaes128_encrypt_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root___eval_stl\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vaes128_encrypt_core___024root___stl_sequent__TOP__0(vlSelf);
        Vaes128_encrypt_core___024root____Vm_traceActivitySetAll(vlSelf);
        Vaes128_encrypt_core___024root___nba_sequent__TOP__1(vlSelf);
    }
}

VL_ATTR_COLD void Vaes128_encrypt_core___024root___eval_triggers_vec__stl(Vaes128_encrypt_core___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vaes128_encrypt_core___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vaes128_encrypt_core___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

VL_ATTR_COLD bool Vaes128_encrypt_core___024root___eval_phase__stl(Vaes128_encrypt_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root___eval_phase__stl\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vaes128_encrypt_core___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vaes128_encrypt_core___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vaes128_encrypt_core___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vaes128_encrypt_core___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vaes128_encrypt_core___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaes128_encrypt_core___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vaes128_encrypt_core___024root___trigger_anySet__act(triggers))))) {
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

VL_ATTR_COLD void Vaes128_encrypt_core___024root____Vm_traceActivitySetAll(Vaes128_encrypt_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root____Vm_traceActivitySetAll\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
}

VL_ATTR_COLD void Vaes128_encrypt_core___024root___ctor_var_reset(Vaes128_encrypt_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root___ctor_var_reset\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1638864771569018232ull);
    vlSelf->start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9867861323841650631ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->key, __VscopeHash, 14066609003741847747ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->plaintext, __VscopeHash, 15306753485699558102ull);
    vlSelf->busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6386567572483775230ull);
    vlSelf->done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10296494685231209730ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->ciphertext, __VscopeHash, 5156948722554576173ull);
    vlSelf->aes128_encrypt_core__DOT__fsm_state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 18017237565404907284ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->aes128_encrypt_core__DOT__key_reg, __VscopeHash, 3440368550612027421ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->aes128_encrypt_core__DOT__plaintext_reg, __VscopeHash, 5644756770379768039ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->aes128_encrypt_core__DOT__state_reg, __VscopeHash, 12754802840114045114ull);
    vlSelf->aes128_encrypt_core__DOT__round_index = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 1453102101081527324ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->aes128_encrypt_core__DOT__round_key, __VscopeHash, 3161998637255990381ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state, __VscopeHash, 13116236271665614566ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__state_out, __VscopeHash, 4944789435428628908ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6010612405068050213ull);
    }
    VL_SCOPED_RAND_RESET_W(128, vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire, __VscopeHash, 18206701679694414048ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__31__03a24__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2964202976942030839ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__23__03a16__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1236536687646160164ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__15__03a8__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11735080022077601717ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__7__03a0__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16962232363380702796ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__31__03a24__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11323218458534155916ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__23__03a16__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7887945112004651785ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__15__03a8__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 17661151951421326263ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__7__03a0__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9044937383892902809ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__31__03a24__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 13742013640904213683ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__23__03a16__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15661503500962756030ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__15__03a8__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 17206289113369482232ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__7__03a0__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 12637048988801006870ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__31__03a24__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 236102306403126490ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__23__03a16__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7020266739631773384ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__15__03a8__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2274138102428510197ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__7__03a0__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16899921237112440125ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__127__03a120__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2283340882011889039ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__119__03a112__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 13025803385092033833ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__111__03a104__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 12590011643334598922ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__103__03a96__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16268276429488081123ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__95__03a88__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 13460109547703278680ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__87__03a80__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16722357634830102587ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__79__03a72__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6768969530261677809ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__71__03a64__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6954105696107613966ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__63__03a56__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 18092143322215528457ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__55__03a48__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16607398477667324178ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__47__03a40__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11757526278771442687ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__39__03a32__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15814321278106033560ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__31__03a24__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 12281208029141979841ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__23__03a16__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1114766993093235906ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__15__03a8__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3235111933816586892ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__7__03a0__KET__ = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7839624381955935436ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__0__KET____DOT__u_sb__DOT__out_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 13298754003604631441ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__1__KET____DOT__u_sb__DOT__out_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11550694597992074696ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__2__KET____DOT__u_sb__DOT__out_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 12538484728010651313ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__3__KET____DOT__u_sb__DOT__out_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16054850003855030405ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__4__KET____DOT__u_sb__DOT__out_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 4784429540969059482ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__5__KET____DOT__u_sb__DOT__out_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11624824812249253578ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__6__KET____DOT__u_sb__DOT__out_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 584171628348724937ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__7__KET____DOT__u_sb__DOT__out_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8704417818926233875ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__8__KET____DOT__u_sb__DOT__out_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14947236735259149595ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__9__KET____DOT__u_sb__DOT__out_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15562631397868348571ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__10__KET____DOT__u_sb__DOT__out_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5103938783662974341ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__11__KET____DOT__u_sb__DOT__out_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8843519728797175634ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__12__KET____DOT__u_sb__DOT__out_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1505354394933126693ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__13__KET____DOT__u_sb__DOT__out_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10393194680850626130ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__14__KET____DOT__u_sb__DOT__out_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5386043617268539564ull);
    vlSelf->aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__15__KET____DOT__u_sb__DOT__out_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10080398614447407271ull);
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__sub_word__1__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__sub_word__1__value = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rot_word__2__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rot_word__2__value = 0;
    vlSelf->__Vfunc_aes_sbox_lut__3__Vfuncout = 0;
    vlSelf->__Vfunc_aes_sbox_lut__3__in_byte = 0;
    vlSelf->__Vfunc_aes_sbox_lut__4__Vfuncout = 0;
    vlSelf->__Vfunc_aes_sbox_lut__4__in_byte = 0;
    vlSelf->__Vfunc_aes_sbox_lut__5__Vfuncout = 0;
    vlSelf->__Vfunc_aes_sbox_lut__5__in_byte = 0;
    vlSelf->__Vfunc_aes_sbox_lut__6__Vfuncout = 0;
    vlSelf->__Vfunc_aes_sbox_lut__6__in_byte = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__round = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__24__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__24__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__25__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__25__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__26__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__26__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__27__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__27__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__28__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__28__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__29__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__29__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__30__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__30__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__31__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__31__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__32__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__32__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__33__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__33__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__34__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__34__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__35__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__35__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__36__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__36__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__37__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__37__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__38__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__38__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__39__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__39__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__40__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__40__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__41__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__41__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__42__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__42__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__43__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__43__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__44__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__44__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__45__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__45__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__46__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__46__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__47__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__47__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__48__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__48__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__49__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__49__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__50__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__50__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__51__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__51__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__52__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__52__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__53__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__53__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__54__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__54__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__55__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__55__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__56__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__56__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__57__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__57__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__58__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__58__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__59__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__59__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__60__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__60__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__61__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__61__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__62__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__62__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__63__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__63__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__64__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__64__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__65__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__65__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__66__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__66__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__67__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__67__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__68__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__68__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__69__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__69__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__70__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__70__b = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__71__Vfuncout = 0;
    vlSelf->__Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__71__b = 0;
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
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
