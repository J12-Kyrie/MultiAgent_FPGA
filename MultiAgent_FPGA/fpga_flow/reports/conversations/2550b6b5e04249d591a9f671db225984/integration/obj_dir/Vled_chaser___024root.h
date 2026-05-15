// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vled_chaser.h for the primary calling header

#ifndef VERILATED_VLED_CHASER___024ROOT_H_
#define VERILATED_VLED_CHASER___024ROOT_H_  // guard

#include "verilated.h"


class Vled_chaser__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vled_chaser___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    VL_IN8(dir,0,0);
    VL_OUT8(leds,3,0);
    CData/*3:0*/ led_chaser__DOT__led_state;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__rst_n__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vled_chaser__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vled_chaser___024root(Vled_chaser__Syms* symsp, const char* namep);
    ~Vled_chaser___024root();
    VL_UNCOPYABLE(Vled_chaser___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
