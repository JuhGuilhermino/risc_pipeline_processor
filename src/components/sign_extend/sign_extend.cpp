#include "sign_extend.h"

void sign_extend::extend() {
    int imm = imm_in.read().to_int();

    sc_int<6> signed_imm = imm;

    sc_int<16> extended = signed_imm;

    imm_out.write((word_t) extended);
}