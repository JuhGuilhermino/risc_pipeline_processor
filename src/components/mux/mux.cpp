#include "mux.h"

/**
 * @brief Seleciona entre in0 e in1 com base no sinal sel.
 *
 * sel == 0 → out = in0
 * sel == 1 → out = in1
 */
void mux::select() {
    if (sel.read()) {
        out.write(in1.read());
    } else {
        out.write(in0.read());
    }
}