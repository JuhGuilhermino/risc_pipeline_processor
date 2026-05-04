#include <systemc.h>
#include <cassert>
#include "types/types.h"
#include "instruction_memory.h"

SC_MODULE(imem_testbench) {
    sc_signal<addr_t> address;
    sc_signal<word_t> instruction;
    instruction_memory* imem;

    void generate_tb() {
        wait(1, SC_NS);

        /*
        std::cout << "\n[TESTE 1] LOAD + FETCH SIMPLES\n";
        imem->load(0, 0x1234);
        address.write(0);
        wait(1, SC_NS);
        assert(instruction.read() == 0x1234);
        std::cout << "PASSOU\n";
        */
        std::cout << "\n[TESTE 2] MÚLTIPLAS INSTRUÇÕES\n";
        imem->load(1, 0xAAAA);
        imem->load(2, 0xBBBB);
        imem->load(3, 0xCCCC);
        address.write(1); wait(1, SC_NS);
        assert(instruction.read() == 0xAAAA);
        address.write(2); wait(1, SC_NS);
        assert(instruction.read() == 0xBBBB);
        address.write(3); wait(1, SC_NS);
        assert(instruction.read() == 0xCCCC);
        std::cout << "PASSOU\n";

        std::cout << "\n[TESTE 3] OVERWRITE\n";
        imem->load(5, 0x1111);
        imem->load(5, 0x2222);
        address.write(5);
        wait(1, SC_NS);
        assert(instruction.read() == 0x2222);
        std::cout << "PASSOU\n";

        std::cout << "\n[TESTE 4] MEMÓRIA INICIAL (NOP)\n";
        address.write(10);
        wait(1, SC_NS);
        assert(instruction.read() == NOP_INSTR);
        std::cout << "PASSOU\n";

        std::cout << "\n[TESTE 5] ACESSO LIMITE\n";
        imem->load(MEM_SIZE - 1, 0xDEAD);
        address.write(MEM_SIZE - 1);
        wait(1, SC_NS);
        assert(instruction.read() == 0xDEAD);
        std::cout << "PASSOU\n";

        sc_stop();
    }

    SC_CTOR(imem_testbench) {

        imem = new instruction_memory("imem");

        // binding
        imem->address(address);
        imem->instruction(instruction);

        SC_THREAD(generate_tb);
    }
};

int sc_main(int argc, char* argv[]) {

    imem_testbench tb("tb");

    sc_start();

    return 0;
}