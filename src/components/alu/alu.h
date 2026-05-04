/**
 * @file alu.h
 * @author Júlia Guilhermino (juh.guilhermino03@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-03
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <systemc.h>
#include "types/types.h"

SC_MODULE(alu) {
    // input
    sc_in<word_t> A, B;
    sc_in<sc_uint<3>> alu_op;

    // output
    sc_out<word_t> result;
    sc_out<flags_t> flags;

    // methods
    void execute();

    SC_CTOR(alu) {
        SC_METHOD(execute);
        sensitive << A << B << alu_op;
    }
};