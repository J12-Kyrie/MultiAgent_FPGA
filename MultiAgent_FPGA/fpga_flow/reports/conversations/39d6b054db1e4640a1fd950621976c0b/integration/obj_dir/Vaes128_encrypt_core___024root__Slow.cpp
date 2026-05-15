// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaes128_encrypt_core.h for the primary calling header

#include "Vaes128_encrypt_core__pch.h"

void Vaes128_encrypt_core___024root___ctor_var_reset(Vaes128_encrypt_core___024root* vlSelf);

Vaes128_encrypt_core___024root::Vaes128_encrypt_core___024root(Vaes128_encrypt_core__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vaes128_encrypt_core___024root___ctor_var_reset(this);
}

void Vaes128_encrypt_core___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vaes128_encrypt_core___024root::~Vaes128_encrypt_core___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
