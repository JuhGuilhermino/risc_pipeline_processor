#include "data_memory.h"

void data_memory::access() {

    while (true) {
        wait(); // espera borda de clock (posedge)

        addr_t addr = address.read();

        // proteção contra overflow
        if (addr >= MEM_SIZE) {
            read_data.write(0);
            SC_REPORT_WARNING("DATA_MEMORY", "Acesso inválido de memória");
            continue;
        }

        // escrita (prioridade controlada)
        if (mem_write.read()) {
            mem[addr] = write_data.read();
        }

        // leitura
        if (mem_read.read()) {
            read_data.write(mem[addr]);
        }
    }
}