// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaes128_encrypt_core.h for the primary calling header

#ifndef VERILATED_VAES128_ENCRYPT_CORE___024ROOT_H_
#define VERILATED_VAES128_ENCRYPT_CORE___024ROOT_H_  // guard

#include "verilated.h"


class Vaes128_encrypt_core__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaes128_encrypt_core___024root final {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(rst_n,0,0);
        VL_IN8(start,0,0);
        VL_OUT8(busy,0,0);
        VL_OUT8(done,0,0);
        CData/*1:0*/ aes128_encrypt_core__DOT__fsm_state;
        CData/*3:0*/ aes128_encrypt_core__DOT__round_index;
        CData/*3:0*/ aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__round_sel;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__31__03a24__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__23__03a16__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__15__03a8__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__7__03a0__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__31__03a24__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__23__03a16__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__15__03a8__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__7__03a0__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__31__03a24__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__23__03a16__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__15__03a8__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__7__03a0__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__31__03a24__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__23__03a16__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__15__03a8__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__7__03a0__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__127__03a120__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__119__03a112__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__111__03a104__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__103__03a96__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__95__03a88__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__87__03a80__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__79__03a72__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__71__03a64__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__63__03a56__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__55__03a48__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__47__03a40__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__39__03a32__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__31__03a24__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__23__03a16__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__15__03a8__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__7__03a0__KET__;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__0__KET____DOT__u_sb__DOT__out_byte;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__1__KET____DOT__u_sb__DOT__out_byte;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__2__KET____DOT__u_sb__DOT__out_byte;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__3__KET____DOT__u_sb__DOT__out_byte;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__4__KET____DOT__u_sb__DOT__out_byte;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__5__KET____DOT__u_sb__DOT__out_byte;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__6__KET____DOT__u_sb__DOT__out_byte;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__7__KET____DOT__u_sb__DOT__out_byte;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__8__KET____DOT__u_sb__DOT__out_byte;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__9__KET____DOT__u_sb__DOT__out_byte;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__10__KET____DOT__u_sb__DOT__out_byte;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__11__KET____DOT__u_sb__DOT__out_byte;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__12__KET____DOT__u_sb__DOT__out_byte;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__13__KET____DOT__u_sb__DOT__out_byte;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__14__KET____DOT__u_sb__DOT__out_byte;
        CData/*7:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__15__KET____DOT__u_sb__DOT__out_byte;
        CData/*7:0*/ __Vfunc_aes_sbox_lut__3__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_sbox_lut__3__in_byte;
        CData/*7:0*/ __Vfunc_aes_sbox_lut__4__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_sbox_lut__4__in_byte;
        CData/*7:0*/ __Vfunc_aes_sbox_lut__5__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_sbox_lut__5__in_byte;
        CData/*7:0*/ __Vfunc_aes_sbox_lut__6__Vfuncout;
        CData/*7:0*/ __Vfunc_aes_sbox_lut__6__in_byte;
    };
    struct {
        CData/*3:0*/ __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__round;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__24__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__24__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__25__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__25__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__26__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__26__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__27__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__27__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__28__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__28__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__29__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__29__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__30__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__30__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__31__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__31__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__32__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__32__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__33__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__33__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__34__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__34__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__35__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__35__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__36__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__36__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__37__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__37__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__38__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__38__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__39__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__39__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__40__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__40__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__41__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__41__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__42__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__42__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__43__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__43__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__44__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__44__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__45__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__45__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__46__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__46__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__47__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__47__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__48__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__48__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__49__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__49__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__50__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__50__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__51__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__51__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__52__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__52__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__53__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__53__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__54__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__54__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__55__Vfuncout;
    };
    struct {
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__55__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__56__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__56__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__57__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__57__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__58__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__58__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__59__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__59__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__60__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__60__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__61__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__61__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__62__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__62__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__63__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__63__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__64__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__64__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__65__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__65__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__66__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__66__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__67__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__67__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__68__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__68__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__69__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_mul3__69__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__70__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__70__b;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__71__Vfuncout;
        CData/*7:0*/ __Vfunc_aes128_encrypt_core__DOT__u_round_transform__DOT__ot_xtime__71__b;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VstlPhaseResult;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__rst_n__0;
        CData/*0:0*/ __VactPhaseResult;
        CData/*0:0*/ __VnbaPhaseResult;
        VL_INW(key,127,0,4);
        VL_INW(plaintext,127,0,4);
        VL_OUTW(ciphertext,127,0,4);
        VlWide<4>/*127:0*/ aes128_encrypt_core__DOT__key_reg;
        VlWide<4>/*127:0*/ aes128_encrypt_core__DOT__plaintext_reg;
        VlWide<4>/*127:0*/ aes128_encrypt_core__DOT__state_reg;
        VlWide<4>/*127:0*/ aes128_encrypt_core__DOT__round_key;
        IData/*31:0*/ aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__i;
        IData/*31:0*/ aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w0;
        IData/*31:0*/ aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w1;
        IData/*31:0*/ aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w2;
        IData/*31:0*/ aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w3;
        IData/*31:0*/ aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__temp;
        IData/*31:0*/ aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw0;
        IData/*31:0*/ aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw1;
        IData/*31:0*/ aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw2;
        IData/*31:0*/ aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw3;
        VlWide<4>/*127:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state;
        VlWide<4>/*127:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__state_out;
        VlWide<4>/*127:0*/ aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire;
        IData/*31:0*/ __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__sub_word__1__Vfuncout;
        IData/*31:0*/ __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__sub_word__1__value;
        IData/*31:0*/ __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rot_word__2__Vfuncout;
        IData/*31:0*/ __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rot_word__2__value;
        IData/*31:0*/ __Vfunc_aes128_encrypt_core__DOT__u_key_schedule__DOT__rcon_word__7__Vfuncout;
    };
    struct {
        IData/*31:0*/ __VactIterCount;
        VlUnpacked<CData/*7:0*/, 16> aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
        VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    };

    // INTERNAL VARIABLES
    Vaes128_encrypt_core__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vaes128_encrypt_core___024root(Vaes128_encrypt_core__Syms* symsp, const char* namep);
    ~Vaes128_encrypt_core___024root();
    VL_UNCOPYABLE(Vaes128_encrypt_core___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
