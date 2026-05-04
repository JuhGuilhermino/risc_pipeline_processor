#include "registers.h"

void registers::read() {

    // rs1
    if (rs1.read() == 0) {
        read_data1.write(0);
    }
    else if (reg_write.read() && rs1.read() == rd.read() && rd.read() != 0) {
        read_data1.write(write_data.read()); // bypass
    }
    else {
        read_data1.write(regs[rs1.read()]);
    }

    // rs2 (corrigido: sem duplicação)
    if (rs2.read() == 0) {
        read_data2.write(0);
    }
    else if (reg_write.read() && rs2.read() == rd.read() && rd.read() != 0) {
        read_data2.write(write_data.read()); // bypass
    }
    else {
        read_data2.write(regs[rs2.read()]);
    }
}

void registers::write() {
    // corrigido: registrador 0 é imutável
    if (reg_write.read() && rd.read() != 0) {
        regs[rd.read()] = write_data.read();
    }
}