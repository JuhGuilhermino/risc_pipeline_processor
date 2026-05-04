#include "processor.h"

// IF → ID
void processor::stage_if() {
    if_id_instr.write(instruction_in.read());
}

// ID → EX
void processor::stage_id() {
    id_ex_instr.write(if_id_instr.read());
}