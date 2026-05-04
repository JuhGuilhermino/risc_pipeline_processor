/**
 * @file pc.h
 * @author Ludmilla Rodrigues (ludmillarodr178@gmail.com)
 * @version 0.1
 * @date 2026-05-04
 *
 * @copyright Copyright (c) 2026
 *
 */

 #pragma once

#include <systemc.h>

SC_MODULE(control_unit) {

    // input
    sc_in<sc_uint<4>> opcode;

    // outputs
    sc_out<bool> reg_write;
    sc_out<bool> mem_read;
    sc_out<bool> mem_write;
    sc_out<bool> mem_to_reg;
    sc_out<sc_uint<3>> alu_op;
    sc_out<bool> alu_src;
    sc_out<bool> branch;
    sc_out<bool> jump;

    void decode();

    SC_CTOR(control_unit) {
        SC_METHOD(decode);
        sensitive << opcode;
    }
};