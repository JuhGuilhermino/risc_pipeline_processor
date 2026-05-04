#include <systemc.h>
#include <iostream>
#include <cassert>
#include "types/types.h"
#include "data_memory.h"

SC_MODULE(dmem_testbench) {

    // ================= SINAIS =================
    sc_signal<bool> clk;
    sc_signal<bool> mem_read;
    sc_signal<bool> mem_write;

    sc_signal<addr_t> address;
    sc_signal<word_t> write_data;
    sc_signal<word_t> read_data;

    // ================= DUT =================
    data_memory* mem;

    // ================= CLOCK =================
    void clock_gen() {
        while (true) {
            clk.write(false);
            wait(5, SC_NS);
            clk.write(true);
            wait(5, SC_NS);
        }
    }

    // ================= TESTES =================
    void generate_tb() {

        // garante alinhamento com clock
        wait(10, SC_NS);

        // ---------------- TESTE 1 ----------------
        std::cout << "\n[TESTE 1] Escrita e leitura simples" << std::endl;

        address.write(10);
        write_data.write(0x1234);
        mem_write.write(true);
        mem_read.write(false);

        wait(10, SC_NS); // escrita no clock

        mem_write.write(false);
        mem_read.write(true);

        wait(10, SC_NS); // leitura

        assert(read_data.read() == 0x1234);
        std::cout << "PASSOU\n";

        // ---------------- TESTE 2 ----------------
        std::cout << "\n[TESTE 2] Sobrescrita de memória" << std::endl;

        address.write(10);
        write_data.write(0xAAAA);
        mem_write.write(true);

        wait(10, SC_NS);

        write_data.write(0x5555);

        wait(10, SC_NS);

        mem_write.write(false);
        mem_read.write(true);

        wait(10, SC_NS);

        assert(read_data.read() == 0x5555);
        std::cout << "PASSOU\n";

        // ---------------- TESTE 3 ----------------
        std::cout << "\n[TESTE 3] Múltiplas posições" << std::endl;

        mem_write.write(true);

        address.write(1); write_data.write(0x1111); wait(10, SC_NS);
        address.write(2); write_data.write(0x2222); wait(10, SC_NS);
        address.write(3); write_data.write(0x3333); wait(10, SC_NS);

        mem_write.write(false);
        mem_read.write(true);

        address.write(1); wait(10, SC_NS);
        assert(read_data.read() == 0x1111);

        address.write(2); wait(10, SC_NS);
        assert(read_data.read() == 0x2222);

        address.write(3); wait(10, SC_NS);
        assert(read_data.read() == 0x3333);

        std::cout << "PASSOU\n";

        // ---------------- TESTE 4 ----------------
        std::cout << "\n[TESTE 4] Estado inicial (reset lógico)" << std::endl;

        mem_write.write(true);

        for (int i = 0; i < 3; i++) {
            address.write(i);
            write_data.write(0);
            wait(10, SC_NS);
        }

        mem_write.write(false);
        mem_read.write(true);

        address.write(0);
        wait(10, SC_NS);

        assert(read_data.read() == 0);

        std::cout << "PASSOU\n";

        sc_stop();
    }

    // ================= CONSTRUTOR =================
    SC_CTOR(dmem_testbench) {

        mem = new data_memory("mem");

        mem->clk(clk);
        mem->mem_read(mem_read);
        mem->mem_write(mem_write);
        mem->address(address);
        mem->write_data(write_data);
        mem->read_data(read_data);

        SC_THREAD(clock_gen);
        SC_THREAD(generate_tb);
    }

    ~dmem_testbench() {
        delete mem;
    }
};

// ================= MAIN =================
int sc_main(int argc, char* argv[]) {

    dmem_testbench tb("tb");
    sc_start();

    return 0;
}