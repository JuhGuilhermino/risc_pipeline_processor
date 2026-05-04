#include "register_pipeline.h"

void register_pipeline::process() {
    // primeiro escreve o valor antigo
    out_data.write(buffer);

    // depois captura o novo valor
    buffer = in_data.read();
}
