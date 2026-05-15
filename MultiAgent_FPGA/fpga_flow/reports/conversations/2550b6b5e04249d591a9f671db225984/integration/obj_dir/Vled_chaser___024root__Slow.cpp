// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vled_chaser.h for the primary calling header

#include "Vled_chaser__pch.h"

void Vled_chaser___024root___ctor_var_reset(Vled_chaser___024root* vlSelf);

Vled_chaser___024root::Vled_chaser___024root(Vled_chaser__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vled_chaser___024root___ctor_var_reset(this);
}

void Vled_chaser___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vled_chaser___024root::~Vled_chaser___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
