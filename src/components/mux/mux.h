/**
 * @file mux.h
 * @author Ludmilla Rodrigues (ludmillarodr178@gmail.com)
 * @brief Multiplexador 2x1 de 16 bits
 * @version 0.1
 * @date 2026-05-04
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <systemc.h>
#include "types/types.h"

SC_MODULE(mux) {

    // inputs
    sc_in<word_t> in0;  // entrada 0 (selecionada quando sel == 0)
    sc_in<word_t> in1;  // entrada 1 (selecionada quando sel == 1)
    sc_in<bool>   sel;  // sinal de seleção

    // output
    sc_out<word_t> out;

    // method
    void select();

    SC_CTOR(mux) {
        SC_METHOD(select);
        sensitive << in0 << in1 << sel;
    }
};