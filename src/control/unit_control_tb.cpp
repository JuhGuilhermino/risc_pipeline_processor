#include <systemc.h>
#include "unit_control.h"
#include "types/types.h" 

static void print_bool(const std::string& name, bool expected, bool got) {
    std::cout << ((expected == got) ? "[OK]  " : "[FAIL] ")
              << name << " esperado=" << expected
              << " obtido=" << got << "\n";
}

static void print_int(const std::string& name, int expected, int got) {
    std::cout << ((expected == got) ? "[OK]  " : "[FAIL] ")
              << name << " esperado=" << expected
              << " obtido=" << got << "\n";
}

int sc_main(int argc, char* argv[]) {

    sc_signal<sc_uint<4>> opcode;

    sc_signal<bool> reg_write;
    sc_signal<bool> mem_read;
    sc_signal<bool> mem_write;
    sc_signal<bool> mem_to_reg;
    sc_signal<sc_uint<3>> alu_op;
    sc_signal<bool> alu_src;
    sc_signal<bool> branch;
    sc_signal<bool> jump;

    control_unit dut("control_unit");

    dut.opcode(opcode);
    dut.reg_write(reg_write);
    dut.mem_read(mem_read);
    dut.mem_write(mem_write);
    dut.mem_to_reg(mem_to_reg);
    dut.alu_op(alu_op);
    dut.alu_src(alu_src);
    dut.branch(branch);
    dut.jump(jump);

    // TESTE 1: ADD
    opcode.write(0x0);
    sc_start(1, SC_NS);

    print_bool("ADD reg_write", true, reg_write.read());
    print_bool("ADD alu_src", false, alu_src.read());
    print_int ("ADD alu_op", ALU_ADD, alu_op.read());

    // TESTE 2: ADDI 
    opcode.write(0x7);
    sc_start(1, SC_NS);

    print_bool("ADDI reg_write", true, reg_write.read());
    print_bool("ADDI alu_src", true, alu_src.read());
    print_int ("ADDI alu_op", ALU_ADD, alu_op.read());

    // TESTE 3: LOAD 
    opcode.write(0x8);
    sc_start(1, SC_NS);

    print_bool("LOAD mem_read", true, mem_read.read());
    print_bool("LOAD mem_to_reg", true, mem_to_reg.read());
    print_int ("LOAD alu_op", ALU_ADD, alu_op.read());

    // TESTE 4: STORE 
    opcode.write(0x9);
    sc_start(1, SC_NS);

    print_bool("STORE mem_write", true, mem_write.read());
    print_bool("STORE reg_write", false, reg_write.read());
    print_int ("STORE alu_op", ALU_ADD, alu_op.read());

    // TESTE 5: BEQ 
    opcode.write(0xA);
    sc_start(1, SC_NS);

    print_bool("BEQ branch", true, branch.read());
    print_int ("BEQ alu_op (SUB)", ALU_SUB, alu_op.read());

    // TESTE 6: JMP 
    opcode.write(0xC);
    sc_start(1, SC_NS);

    print_bool("JMP jump", true, jump.read());

    // TESTE 7: LIMPEZA DE SINAIS 
    opcode.write(0x8); // LOAD (ativa mem_read)
    sc_start(1, SC_NS);

    opcode.write(0x0); // ADD (não deveria ter mem_read)
    sc_start(1, SC_NS);

    print_bool("ADD não herda mem_read", false, mem_read.read());
    print_bool("ADD não herda mem_write", false, mem_write.read());

    std::cout << "\nSimulação concluída.\n";
    return 0;
}