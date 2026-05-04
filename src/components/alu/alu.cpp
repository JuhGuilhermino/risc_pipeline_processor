#include "alu.h"

void alu::execute() {
    word_t a = A.read();
    word_t b = B.read();
    word_t res = 0;

    sword_t sa = (sword_t)a;
    sword_t sb = (sword_t)b;

    switch (alu_op.read()) {
        case ALU_AND:
            res = a & b;
            break;
        case ALU_OR:
            res = a | b;
            break;
        case ALU_XOR:
            res = a ^ b;
            break;
        case ALU_NOT:
            res = ~a;
            break;
        case ALU_ADD:
            res = (word_t)(sa + sb);
            break;
        case 7: // Sub
            case ALU_SUB:
            res = (word_t)(sa - sb);
            break;
    }

    // flags
    flags_t f = 0;

    // Zero flag
    if (res == 0)
        f[FLAG_Z_BIT] = 1;
    else
        f[FLAG_Z_BIT] = 0;

    // Negativo (bit de sinal)
    f[FLAG_N_BIT] = res[WORD_SIZE - 1];

    // Escrita das saídas
    result.write(res);
    flags.write(f);
}