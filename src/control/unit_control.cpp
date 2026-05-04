#include "unit_control.h"
#include "types/types.h" // se tiver defines de opcode

void control_unit::decode() {

    // default (NOP)
    reg_write.write(false);
    mem_read.write(false);
    mem_write.write(false);
    mem_to_reg.write(false);
    alu_op.write(0);
    alu_src.write(false);
    branch.write(false);
    jump.write(false);

    switch (opcode.read()) {

        case 0x0: // ADD
            reg_write.write(true);
            alu_op.write(ALU_ADD);
            break;

        case 0x1: // SUB
            reg_write.write(true);
            alu_op.write(ALU_SUB);
            break;

        case 0x2: // AND
            reg_write.write(true);
            alu_op.write(ALU_AND);
            break;

        case 0x3: // OR
            reg_write.write(true);
            alu_op.write(ALU_OR);
            break;

        case 0x4: // XOR
            reg_write.write(true);
            alu_op.write(ALU_XOR);
            break;

        case 0x5: // NOT
            reg_write.write(true);
            alu_op.write(ALU_NOT);
            break;

        case 0x6: // CMP
            alu_op.write(ALU_SUB);
            break;

        case 0x7: // ADDI
            reg_write.write(true);
            alu_src.write(true);
            alu_op.write(ALU_ADD);
            break;

        case 0x8: // LOAD
            reg_write.write(true);
            mem_read.write(true);
            mem_to_reg.write(true);
            alu_src.write(true);
            alu_op.write(ALU_ADD);
            break;

        case 0x9: // STORE
            mem_write.write(true);
            alu_src.write(true);
            alu_op.write(ALU_ADD);
            break;

        case 0xA: // BEQ
        case 0xB: // BNE
            branch.write(true);
            alu_op.write(ALU_SUB);
            break;

        case 0xC: // JMP
            jump.write(true);
            break;

        default: // NOP
            break;
    }
}