/**
 * @file pc.h
 * @author Ludmilla Rodrigues
 * @brief Contador de Programa (Program Counter)
 * @version 0.1
 * @date 2026-05-04
 *
 * @copyright Copyright (c) 2026
 *
 */

 #pragma once

#include <systemc.h>
#include "types/types.h"

SC_MODULE(sign_extend) {

    // input: imediato de 6 bits
    sc_in<sc_uint<6>> imm_in;

    // output: palavra de 16 bits com sinal estendido
    sc_out<word_t> imm_out;

    void extend();

    SC_CTOR(sign_extend) {
        SC_METHOD(extend);
        sensitive << imm_in;
    }
};