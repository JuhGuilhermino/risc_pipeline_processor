/**
 * @file pc.cpp
 * @author Ludmilla Rodrigues
 * @brief Implementação do Contador de Programa
 * @version 0.1
 * @date 2026-05-04
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "pc.h"

/**
 * @brief Atualiza o PC na borda de subida do clock.
 *
 * Prioridade:
 *   1. reset      → PC = PC_RESET (0x00)
 *   2. jump       → PC = jump_addr
 *   3. branch_taken → PC = branch_addr
 *   4. normal     → PC = PC + 1
 */
void pc::update() {
    if (reset.read()) {
        current_pc = PC_RESET;
    } else if (jump.read()) {
        current_pc = jump_addr.read();
    } else if (branch_taken.read()) {
        current_pc = branch_addr.read();
    } else {
        current_pc = current_pc + 1;
    }

    pc_out.write(current_pc);
}

/**
 * @brief Calcula PC + 1 de forma combinacional.
 *
 * Esse valor é propagado pelo registrador IF/ID para que
 * os estágios seguintes possam calcular endereços de branch.
 */
void pc::compute() {
    pc_next.write(pc_out.read() + 1);
}