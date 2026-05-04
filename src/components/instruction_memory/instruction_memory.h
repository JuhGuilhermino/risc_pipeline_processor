#include <systemc.h>
#include "types/types.h"

SC_MODULE(instruction_memory) {

    // input
    sc_in<addr_t> address;

    // output
    sc_out<word_t> instruction;

private:
    word_t mem[MEM_SIZE];

public:

    // methods
    void load(addr_t addr, word_t instr);
    void fetch();

    SC_CTOR(instruction_memory) {
        for (int i = 0; i < MEM_SIZE; i++)
            mem[i] = NOP_INSTR;

        SC_METHOD(fetch);
        sensitive << address;
    }

};