/**
 * @file registers_pipeline.h
 * @author Júlia Guilhermino (juh.guilhermino03@gmail.com)
 * @brief Define o modelo 4 registradores de pipeline que captura os sinais na borda
 * do clock para envia-los a próxima etapa no próximo ciclo do clock.
 * OBS: tra-se de um pipiline de 5 estados: IF, ID, EX, MEM, WB.
 * @version 0.1
 * @date 2026-05-04
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#pragma once

#include <systemc.h>
#include "types/types.h"

SC_MODULE(register_pipeline) {

    sc_in<bool> clk;
    sc_in<word_t> in_data;
    sc_out<word_t> out_data;

    word_t buffer;

    void process();

    SC_CTOR(register_pipeline) {
        buffer = 0;

        SC_METHOD(process);
        sensitive << clk.pos();
    }
};