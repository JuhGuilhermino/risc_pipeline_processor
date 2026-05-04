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

SC_MODULE(pc) {

    // inputs
    sc_in<bool>   clk;
    sc_in<bool>   reset;
    sc_in<bool>   jump;        // sinal de salto incondicional (JMP)
    sc_in<bool>   branch_taken;// sinal de desvio condicional resolvido (BEQ/BNE)
    sc_in<addr_t> jump_addr;   // endereço absoluto para JMP (12 bits truncados em 8)
    sc_in<addr_t> branch_addr; // endereço alvo do branch (PC + imm, calculado no EX)

    // output
    sc_out<addr_t> pc_out;     // endereço atual (enviado para memória de instrução)
    sc_out<addr_t> pc_next;    // PC + 1 (propagado para os registradores de pipeline)

    // state
    addr_t current_pc;

    // methods
    void update();   // atualiza PC na borda de subida do clock
    void compute();  // calcula pc_next de forma combinacional

    SC_CTOR(pc) {
        current_pc = PC_RESET;

        SC_METHOD(update);
        sensitive << clk.pos();

        SC_METHOD(compute);
        sensitive << pc_out << jump << branch_taken << jump_addr << branch_addr;
    }
};