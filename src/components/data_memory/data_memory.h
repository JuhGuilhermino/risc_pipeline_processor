#include <systemc.h>
#include "types/types.h"

SC_MODULE(data_memory) {

    // input
    sc_in<bool> clk;
    sc_in<bool> mem_read;
    sc_in<bool> mem_write;
    sc_in<addr_t> address;
    sc_in<word_t> write_data;

    // output
    sc_out<word_t> read_data;

private:
    word_t mem[MEM_SIZE];

public:

    // methods
    void process();

    SC_CTOR(data_memory) {
        for (int i = 0; i < MEM_SIZE; i++)
            mem[i] = 0;

        SC_THREAD(access);
        sensitive << clk.pos();
    }

};