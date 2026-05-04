#include "register_pipeline.h"

void register_pipeline::procress() {
    buffer = in_data.read();
    out_data.write(buffer);
}

