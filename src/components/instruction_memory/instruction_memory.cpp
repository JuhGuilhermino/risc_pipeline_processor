#include "instruction_memory.h"

void instruction_memory::load(addr_t addr, word_t instr) {
    if (addr < MEM_SIZE)
        mem[addr] = instr;
}

void instruction_memory::fetch() {
    addr_t addr = address.read();

    if (addr < MEM_SIZE)
        instruction.write(mem[address.read()]);
    else
        instruction.write(0);

    std::cout << "FETCH -> ADDR=" << addr
              << " DATA=" << mem[addr] << std::endl;
}