#include "datapath.h"

void datapath::decode_instruction() {
    sc_uint<16> instr = instruction.read();

    opcode.write(instr.range(15,12));
    rd.write(instr.range(11,9));
    rs1.write(instr.range(8,6));
    rs2.write(instr.range(5,3));
    imm.write(instr.range(5,0));
}

void datapath::debug_assign() {
    debug_out.write(alu_result.read());
}