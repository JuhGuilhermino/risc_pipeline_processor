#pragma once

#include <systemc.h>
#include "types/types.h"
#include "datapath/datapath.h"

SC_MODULE(processor) {

    sc_in<bool> clk;
    sc_in<word_t> instruction_in;

    sc_out<word_t> debug_out;

    // ===== pipeline registers =====
    sc_signal<word_t> if_id_instr;
    sc_signal<word_t> id_ex_instr;

    // datapath interno
    datapath dp;

    void stage_if();
    void stage_id();

    SC_CTOR(processor)
        : dp("datapath")
    {
        // IF stage
        SC_METHOD(stage_if);
        sensitive << clk.pos();

        // ID stage
        SC_METHOD(stage_id);
        sensitive << clk.pos();

        // datapath recebe instrução do estágio ID/EX
        dp.clk(clk);
        dp.instruction(id_ex_instr);
        dp.debug_out(debug_out);
    }
};