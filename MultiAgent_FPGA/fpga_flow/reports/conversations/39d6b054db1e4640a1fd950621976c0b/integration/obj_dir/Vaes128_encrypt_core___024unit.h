// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaes128_encrypt_core.h for the primary calling header

#ifndef VERILATED_VAES128_ENCRYPT_CORE___024UNIT_H_
#define VERILATED_VAES128_ENCRYPT_CORE___024UNIT_H_  // guard

#include "verilated.h"


class Vaes128_encrypt_core__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaes128_encrypt_core___024unit final {
  public:

    // INTERNAL VARIABLES
    Vaes128_encrypt_core__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vaes128_encrypt_core___024unit();
    ~Vaes128_encrypt_core___024unit();
    void ctor(Vaes128_encrypt_core__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vaes128_encrypt_core___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
