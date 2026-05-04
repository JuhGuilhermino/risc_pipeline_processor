/**
 * @file registers.h
 * @author Júlia Guilhermino (you@domain.com)
 * @brief Definição do banco de registradores
 * @version 0.1
 * @date 2026-05-03
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <systemc.h>
#include "types/types.h"

SC_MODULE(registers) {

    // input
    sc_in<bool> clk;
    sc_in<bool> reg_write;
    sc_in<reg_t> rs1;  // fonte
    sc_in<reg_t> rs2;  // fonte
    sc_in<reg_t> rd;   // destino
    sc_in<word_t> write_data;

    // output
    sc_out<word_t> read_data1;
    sc_out<word_t> read_data2;

    // registers bank
    word_t regs[NUM_REGS];

    //methods
    void read();
    void write();

    SC_CTOR(registers) {
        for (int i = 0; i < NUM_REGS; i++) {
            regs[i] = 0;
        }

        SC_METHOD(read);
        sensitive << rs1 << rs2 << reg_write << rd << write_data;

        SC_METHOD(write);
        sensitive << clk.pos();
    }

};