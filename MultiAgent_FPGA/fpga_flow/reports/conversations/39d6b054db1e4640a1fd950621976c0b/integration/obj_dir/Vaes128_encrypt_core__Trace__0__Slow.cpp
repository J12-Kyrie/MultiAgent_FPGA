// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vaes128_encrypt_core__Syms.h"


VL_ATTR_COLD void Vaes128_encrypt_core___024root__trace_init_sub__TOP__0(Vaes128_encrypt_core___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root__trace_init_sub__TOP__0\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->pushPrefix("$rootio", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+122,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+123,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+124,0,"start",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+125,0,"key",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+129,0,"plaintext",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBit(c+133,0,"busy",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+134,0,"done",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+135,0,"ciphertext",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->popPrefix();
    tracep->pushPrefix("aes128_encrypt_core", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+122,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+123,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+124,0,"start",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+125,0,"key",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+129,0,"plaintext",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBit(c+133,0,"busy",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+134,0,"done",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+135,0,"ciphertext",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBus(c+139,0,"STATE_IDLE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+140,0,"STATE_ROUND",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+141,0,"STATE_DONE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+0,0,"fsm_state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declArray(c+1,0,"key_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+5,0,"plaintext_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+9,0,"state_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBus(c+13,0,"round_index",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declArray(c+14,0,"round_key",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+18,0,"sub_bytes_state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+22,0,"shift_rows_state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+26,0,"mix_columns_state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+30,0,"round_state_out",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBit(c+34,0,"final_round",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("u_key_schedule", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declArray(c+1,0,"key",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBus(c+13,0,"round_index",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declArray(c+14,0,"round_key",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBus(c+35,0,"expand_round_key__Vstatic__i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+36,0,"expand_round_key__Vstatic__w0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+37,0,"expand_round_key__Vstatic__w1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+38,0,"expand_round_key__Vstatic__w2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+39,0,"expand_round_key__Vstatic__w3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+40,0,"expand_round_key__Vstatic__temp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+41,0,"expand_round_key__Vstatic__nw0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+42,0,"expand_round_key__Vstatic__nw1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+43,0,"expand_round_key__Vstatic__nw2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+44,0,"expand_round_key__Vstatic__nw3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+45,0,"expand_round_key__Vstatic__round_sel",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_round_transform", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declArray(c+9,0,"state_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+14,0,"round_key",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBit(c+34,0,"final_round",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+18,0,"sub_bytes_state",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+22,0,"shift_rows_state",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+26,0,"mix_columns_state",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+30,0,"state_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->pushPrefix("sb_o", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 16; ++i) {
        tracep->declBus(c+46+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 7,0);
    }
    tracep->popPrefix();
    tracep->declArray(c+18,0,"sub_bytes_wire",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+22,0,"shift_rows_wire",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBus(c+62,0,"c0_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+63,0,"c0_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+64,0,"c0_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+65,0,"c0_3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+66,0,"c1_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+67,0,"c1_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+68,0,"c1_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+69,0,"c1_3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+70,0,"c2_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+71,0,"c2_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+72,0,"c2_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+73,0,"c2_3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+74,0,"c3_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+75,0,"c3_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+76,0,"c3_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+77,0,"c3_3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+78,0,"mix_w0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+79,0,"mix_w1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+80,0,"mix_w2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+81,0,"mix_w3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declArray(c+82,0,"mix_columns_wire",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+86,0,"add_round_key_wire",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+30,0,"state_out_wire",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->pushPrefix("g_sbox[0]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_sb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+90,0,"in_byte",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+91,0,"out_byte",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("g_sbox[10]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_sb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+92,0,"in_byte",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+93,0,"out_byte",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("g_sbox[11]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_sb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+94,0,"in_byte",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+95,0,"out_byte",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("g_sbox[12]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_sb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+96,0,"in_byte",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+97,0,"out_byte",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("g_sbox[13]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_sb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+98,0,"in_byte",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+99,0,"out_byte",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("g_sbox[14]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_sb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+100,0,"in_byte",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+101,0,"out_byte",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("g_sbox[15]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_sb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+102,0,"in_byte",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+103,0,"out_byte",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("g_sbox[1]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_sb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+104,0,"in_byte",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+105,0,"out_byte",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("g_sbox[2]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_sb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+106,0,"in_byte",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+107,0,"out_byte",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("g_sbox[3]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_sb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+108,0,"in_byte",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+109,0,"out_byte",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("g_sbox[4]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_sb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+110,0,"in_byte",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+111,0,"out_byte",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("g_sbox[5]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_sb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+112,0,"in_byte",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+113,0,"out_byte",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("g_sbox[6]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_sb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+114,0,"in_byte",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+115,0,"out_byte",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("g_sbox[7]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_sb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+116,0,"in_byte",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+117,0,"out_byte",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("g_sbox[8]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_sb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+118,0,"in_byte",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+119,0,"out_byte",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("g_sbox[9]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_sb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+120,0,"in_byte",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+121,0,"out_byte",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vaes128_encrypt_core___024root__trace_init_top(Vaes128_encrypt_core___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root__trace_init_top\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vaes128_encrypt_core___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vaes128_encrypt_core___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vaes128_encrypt_core___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vaes128_encrypt_core___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vaes128_encrypt_core___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vaes128_encrypt_core___024root__trace_register(Vaes128_encrypt_core___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root__trace_register\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vaes128_encrypt_core___024root__trace_const_0, 0, vlSelf);
    tracep->addFullCb(&Vaes128_encrypt_core___024root__trace_full_0, 0, vlSelf);
    tracep->addChgCb(&Vaes128_encrypt_core___024root__trace_chg_0, 0, vlSelf);
    tracep->addCleanupCb(&Vaes128_encrypt_core___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vaes128_encrypt_core___024root__trace_const_0_sub_0(Vaes128_encrypt_core___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vaes128_encrypt_core___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root__trace_const_0\n"); );
    // Body
    Vaes128_encrypt_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaes128_encrypt_core___024root*>(voidSelf);
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vaes128_encrypt_core___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vaes128_encrypt_core___024root__trace_const_0_sub_0(Vaes128_encrypt_core___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root__trace_const_0_sub_0\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullCData(oldp+139,(0U),2);
    bufp->fullCData(oldp+140,(1U),2);
    bufp->fullCData(oldp+141,(2U),2);
}

VL_ATTR_COLD void Vaes128_encrypt_core___024root__trace_full_0_sub_0(Vaes128_encrypt_core___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vaes128_encrypt_core___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root__trace_full_0\n"); );
    // Body
    Vaes128_encrypt_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaes128_encrypt_core___024root*>(voidSelf);
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vaes128_encrypt_core___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vaes128_encrypt_core___024root__trace_full_0_sub_0(Vaes128_encrypt_core___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes128_encrypt_core___024root__trace_full_0_sub_0\n"); );
    Vaes128_encrypt_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlWide<4>/*127:0*/ __Vtemp_4;
    VlWide<4>/*127:0*/ __Vtemp_6;
    VlWide<4>/*127:0*/ __Vtemp_8;
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullCData(oldp+0,(vlSelfRef.aes128_encrypt_core__DOT__fsm_state),2);
    bufp->fullWData(oldp+1,(vlSelfRef.aes128_encrypt_core__DOT__key_reg),128);
    bufp->fullWData(oldp+5,(vlSelfRef.aes128_encrypt_core__DOT__plaintext_reg),128);
    bufp->fullWData(oldp+9,(vlSelfRef.aes128_encrypt_core__DOT__state_reg),128);
    bufp->fullCData(oldp+13,(vlSelfRef.aes128_encrypt_core__DOT__round_index),4);
    bufp->fullWData(oldp+14,(vlSelfRef.aes128_encrypt_core__DOT__round_key),128);
    bufp->fullWData(oldp+18,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sub_bytes_state),128);
    bufp->fullWData(oldp+22,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire),128);
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
        __Vtemp_4[2U] = (IData)((((QData)((IData)((
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
    bufp->fullWData(oldp+26,(__Vtemp_4),128);
    bufp->fullWData(oldp+30,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__state_out),128);
    bufp->fullBit(oldp+34,((0x0aU == (IData)(vlSelfRef.aes128_encrypt_core__DOT__round_index))));
    bufp->fullIData(oldp+35,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__i),32);
    bufp->fullIData(oldp+36,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w0),32);
    bufp->fullIData(oldp+37,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w1),32);
    bufp->fullIData(oldp+38,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w2),32);
    bufp->fullIData(oldp+39,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__w3),32);
    bufp->fullIData(oldp+40,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__temp),32);
    bufp->fullIData(oldp+41,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw0),32);
    bufp->fullIData(oldp+42,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw1),32);
    bufp->fullIData(oldp+43,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw2),32);
    bufp->fullIData(oldp+44,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__nw3),32);
    bufp->fullCData(oldp+45,(vlSelfRef.aes128_encrypt_core__DOT__u_key_schedule__DOT__expand_round_key__Vstatic__round_sel),4);
    bufp->fullCData(oldp+46,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[0]),8);
    bufp->fullCData(oldp+47,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[1]),8);
    bufp->fullCData(oldp+48,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[2]),8);
    bufp->fullCData(oldp+49,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[3]),8);
    bufp->fullCData(oldp+50,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[4]),8);
    bufp->fullCData(oldp+51,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[5]),8);
    bufp->fullCData(oldp+52,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[6]),8);
    bufp->fullCData(oldp+53,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[7]),8);
    bufp->fullCData(oldp+54,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[8]),8);
    bufp->fullCData(oldp+55,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[9]),8);
    bufp->fullCData(oldp+56,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[10]),8);
    bufp->fullCData(oldp+57,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[11]),8);
    bufp->fullCData(oldp+58,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[12]),8);
    bufp->fullCData(oldp+59,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[13]),8);
    bufp->fullCData(oldp+60,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[14]),8);
    bufp->fullCData(oldp+61,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__sb_o[15]),8);
    bufp->fullCData(oldp+62,((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                              >> 0x00000018U)),8);
    bufp->fullCData(oldp+63,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                             >> 0x00000010U))),8);
    bufp->fullCData(oldp+64,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U]
                                             >> 8U))),8);
    bufp->fullCData(oldp+65,((0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[3U])),8);
    bufp->fullCData(oldp+66,((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                              >> 0x00000018U)),8);
    bufp->fullCData(oldp+67,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                             >> 0x00000010U))),8);
    bufp->fullCData(oldp+68,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U]
                                             >> 8U))),8);
    bufp->fullCData(oldp+69,((0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[2U])),8);
    bufp->fullCData(oldp+70,((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                              >> 0x00000018U)),8);
    bufp->fullCData(oldp+71,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                             >> 0x00000010U))),8);
    bufp->fullCData(oldp+72,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U]
                                             >> 8U))),8);
    bufp->fullCData(oldp+73,((0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[1U])),8);
    bufp->fullCData(oldp+74,((vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                              >> 0x00000018U)),8);
    bufp->fullCData(oldp+75,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                             >> 0x00000010U))),8);
    bufp->fullCData(oldp+76,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U]
                                             >> 8U))),8);
    bufp->fullCData(oldp+77,((0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__shift_rows_wire[0U])),8);
    bufp->fullIData(oldp+78,(((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__31__03a24__KET__)
                                << 0x00000018U) | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__23__03a16__KET__)
                                                   << 0x00000010U))
                              | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__15__03a8__KET__)
                                  << 8U) | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__7__03a0__KET__)))),32);
    bufp->fullIData(oldp+79,(((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__31__03a24__KET__)
                                << 0x00000018U) | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__23__03a16__KET__)
                                                   << 0x00000010U))
                              | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__15__03a8__KET__)
                                  << 8U) | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__7__03a0__KET__)))),32);
    bufp->fullIData(oldp+80,(((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__31__03a24__KET__)
                                << 0x00000018U) | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__23__03a16__KET__)
                                                   << 0x00000010U))
                              | (((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__15__03a8__KET__)
                                  << 8U) | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w2__BRA__7__03a0__KET__)))),32);
    bufp->fullIData(oldp+81,(((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__31__03a24__KET__)
                                << 0x00000018U) | ((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w3__BRA__23__03a16__KET__)
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
    __Vtemp_6[2U] = (IData)((((QData)((IData)(((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__7__03a0__KET__)
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
    __Vtemp_6[3U] = (IData)(((((QData)((IData)(((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w0__BRA__7__03a0__KET__)
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
                                                                     | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__mix_w1__BRA__31__03a24__KET__))))))
                             >> 0x00000020U));
    bufp->fullWData(oldp+82,(__Vtemp_6),128);
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
    __Vtemp_8[2U] = (IData)((((QData)((IData)(((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__127__03a120__KET__)
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
    __Vtemp_8[3U] = (IData)(((((QData)((IData)(((((IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__127__03a120__KET__)
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
                                                                     | (IData)(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__add_round_key_wire__BRA__71__03a64__KET__))))))
                             >> 0x00000020U));
    bufp->fullWData(oldp+86,(__Vtemp_8),128);
    bufp->fullCData(oldp+90,((vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U]
                              >> 0x00000018U)),8);
    bufp->fullCData(oldp+91,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__0__KET____DOT__u_sb__DOT__out_byte),8);
    bufp->fullCData(oldp+92,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U]
                                             >> 8U))),8);
    bufp->fullCData(oldp+93,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__10__KET____DOT__u_sb__DOT__out_byte),8);
    bufp->fullCData(oldp+94,((0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U])),8);
    bufp->fullCData(oldp+95,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__11__KET____DOT__u_sb__DOT__out_byte),8);
    bufp->fullCData(oldp+96,((vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U]
                              >> 0x00000018U)),8);
    bufp->fullCData(oldp+97,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__12__KET____DOT__u_sb__DOT__out_byte),8);
    bufp->fullCData(oldp+98,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U]
                                             >> 0x00000010U))),8);
    bufp->fullCData(oldp+99,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__13__KET____DOT__u_sb__DOT__out_byte),8);
    bufp->fullCData(oldp+100,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U]
                                              >> 8U))),8);
    bufp->fullCData(oldp+101,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__14__KET____DOT__u_sb__DOT__out_byte),8);
    bufp->fullCData(oldp+102,((0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__state_reg[0U])),8);
    bufp->fullCData(oldp+103,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__15__KET____DOT__u_sb__DOT__out_byte),8);
    bufp->fullCData(oldp+104,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U]
                                              >> 0x00000010U))),8);
    bufp->fullCData(oldp+105,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__1__KET____DOT__u_sb__DOT__out_byte),8);
    bufp->fullCData(oldp+106,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U]
                                              >> 8U))),8);
    bufp->fullCData(oldp+107,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__2__KET____DOT__u_sb__DOT__out_byte),8);
    bufp->fullCData(oldp+108,((0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__state_reg[3U])),8);
    bufp->fullCData(oldp+109,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__3__KET____DOT__u_sb__DOT__out_byte),8);
    bufp->fullCData(oldp+110,((vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U]
                               >> 0x00000018U)),8);
    bufp->fullCData(oldp+111,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__4__KET____DOT__u_sb__DOT__out_byte),8);
    bufp->fullCData(oldp+112,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U]
                                              >> 0x00000010U))),8);
    bufp->fullCData(oldp+113,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__5__KET____DOT__u_sb__DOT__out_byte),8);
    bufp->fullCData(oldp+114,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U]
                                              >> 8U))),8);
    bufp->fullCData(oldp+115,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__6__KET____DOT__u_sb__DOT__out_byte),8);
    bufp->fullCData(oldp+116,((0x000000ffU & vlSelfRef.aes128_encrypt_core__DOT__state_reg[2U])),8);
    bufp->fullCData(oldp+117,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__7__KET____DOT__u_sb__DOT__out_byte),8);
    bufp->fullCData(oldp+118,((vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U]
                               >> 0x00000018U)),8);
    bufp->fullCData(oldp+119,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__8__KET____DOT__u_sb__DOT__out_byte),8);
    bufp->fullCData(oldp+120,((0x000000ffU & (vlSelfRef.aes128_encrypt_core__DOT__state_reg[1U]
                                              >> 0x00000010U))),8);
    bufp->fullCData(oldp+121,(vlSelfRef.aes128_encrypt_core__DOT__u_round_transform__DOT__g_sbox__BRA__9__KET____DOT__u_sb__DOT__out_byte),8);
    bufp->fullBit(oldp+122,(vlSelfRef.clk));
    bufp->fullBit(oldp+123,(vlSelfRef.rst_n));
    bufp->fullBit(oldp+124,(vlSelfRef.start));
    bufp->fullWData(oldp+125,(vlSelfRef.key),128);
    bufp->fullWData(oldp+129,(vlSelfRef.plaintext),128);
    bufp->fullBit(oldp+133,(vlSelfRef.busy));
    bufp->fullBit(oldp+134,(vlSelfRef.done));
    bufp->fullWData(oldp+135,(vlSelfRef.ciphertext),128);
}
