#include <systemc.h>
#include "registers.h"
#include "types/types.h"

SC_MODULE(reg_testbench) {

    sc_signal<bool> clk;
    sc_signal<bool> reg_write;
    sc_signal<reg_t> rs1, rs2, rd;
    sc_signal<word_t> write_data;
    sc_signal<word_t> read_data1, read_data2;

    registers* regfile;

    void clock_gen() {
        while (true) {
            clk = 0;
            wait(5, SC_NS);
            clk = 1;
            wait(5, SC_NS);
        }
    }

    void generate_tb() {
        wait(10, SC_NS); // estabilizar

        std::cout << "\n[TESTE 1] Escrita simples: " << std::endl;
        rd = 1;
        write_data = 42;
        reg_write = 1;
        wait(10, SC_NS);
        reg_write = 0;
        rs1 = 1;
        wait(1, SC_NS);
        assert(read_data1.read() == 42);
        std::cout << "PASSOU\n";

        std::cout << "\n[TESTE 2] Leitura dupla" << std::endl;
        rd = 2;
        write_data = 99;
        reg_write = 1;
        wait(10, SC_NS);
        reg_write = 0;
        rs1 = 1;
        rs2 = 2;
        wait(1, SC_NS);
        assert(read_data1.read() == 42);
        assert(read_data2.read() == 99);
        std::cout << "PASSOU\n";

        std::cout << "\n[TESTE 3] Sobrescrita" << std::endl;
        rd = 1;
        write_data = 7;
        reg_write = 1;
        wait(10, SC_NS);
        reg_write = 0;
        rs1 = 1;
        wait(1, SC_NS);
        assert(read_data1.read() == 7);
        std::cout << "PASSOU\n";

        std::cout << "\n[TESTE 4] Registrador 0 (deve permanecer 0)" << std::endl;
        rd = 0;
        write_data = 123;
        reg_write = 1;
        wait(10, SC_NS);
        reg_write = 0;
        rs1 = 0;
        wait(1, SC_NS);
        assert(read_data1.read() == 0);
        std::cout << "PASSOU\n";

        std::cout << "\n[TESTE 5] Leitura e escrita no mesmo ciclo (esperado: 55)" << std::endl;
        rd = 3;
        rs1 = 3;
        write_data = 55;
        reg_write = 1;
        wait(1, SC_NS);
        std::cout << "Resultado = " << read_data1.read() << std::endl;

        wait(10, SC_NS);
        reg_write = 0;

        std::cout << "\n[TESTE 6] Sem escrita (reg_write = 0)" << std::endl;
        rd = 4;
        write_data = 88;
        reg_write = 0;
        wait(10, SC_NS);
        rs1 = 4;
        wait(1, SC_NS);
        assert(read_data1.read() == 0);
        std::cout << "PASSOU\n";

        std::cout << "\n[TESTE 7] Sensibilidade de leitura" << std::endl;
        rs1 = 1;
        wait(1, SC_NS);
        rs1 = 2;
        wait(1, SC_NS);
        assert(read_data1.read() == 99);
        std::cout << "PASSOU\n";

        sc_stop();
    }

    // Construtor
    SC_CTOR(reg_testbench) {

        regfile = new registers("RegisterFile");

        // Conections
        regfile->clk(clk);
        regfile->reg_write(reg_write);
        regfile->rs1(rs1);
        regfile->rs2(rs2);
        regfile->rd(rd);
        regfile->write_data(write_data);
        regfile->read_data1(read_data1);
        regfile->read_data2(read_data2);

        // Threads
        SC_THREAD(clock_gen);
        SC_THREAD(generate_tb);
    }
};


int sc_main(int argc, char* argv[]) {
    reg_testbench tb("tb");

    sc_start();

    return 0;
}