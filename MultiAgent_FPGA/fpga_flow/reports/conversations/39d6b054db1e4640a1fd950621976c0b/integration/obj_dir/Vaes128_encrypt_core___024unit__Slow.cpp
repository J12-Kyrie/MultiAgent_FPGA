// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaes128_encrypt_core.h for the primary calling header

#include "Vaes128_encrypt_core__pch.h"

void Vaes128_encrypt_core___024unit___ctor_var_reset(Vaes128_encrypt_core___024unit* vlSelf);

Vaes128_encrypt_core___024unit::Vaes128_encrypt_core___024unit() = default;
Vaes128_encrypt_core___024unit::~Vaes128_encrypt_core___024unit() = default;

void Vaes128_encrypt_core___024unit::ctor(Vaes128_encrypt_core__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vaes128_encrypt_core___024unit___ctor_var_reset(this);
}

void Vaes128_encrypt_core___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vaes128_encrypt_core___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
