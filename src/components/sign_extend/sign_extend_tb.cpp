#include <systemc.h>
#include "components/sign_extend/sign_extend.h"

static void print(const std::string& test, word_t expected, word_t got) {
    bool ok = (expected == got);
    std::cout << (ok ? "[OK]  " : "[FAIL]") << " " << test
              << " | esperado=" << expected
              << " obtido=" << got << "\n";
}

int sc_main(int argc, char* argv[]) {

    sc_signal<sc_uint<6>> imm_in;
    sc_signal<word_t> imm_out;

    sign_extend dut("sign_extend");
    dut.imm_in(imm_in);
    dut.imm_out(imm_out);

    // ── Teste 1: positivo
    imm_in.write(0b000101); // 5
    sc_start(1, SC_NS);
    print("5 → 5", 5, imm_out.read());

    // ── Teste 2: -1
    imm_in.write(0b111111); // -1
    sc_start(1, SC_NS);
    print("-1 → 0xFFFF", 0xFFFF, imm_out.read());

    // ── Teste 3: -32 (mínimo)
    imm_in.write(0b100000);
    sc_start(1, SC_NS);
    print("-32 → 0xFFE0", 0xFFE0, imm_out.read());

    // ── Teste 4: zero
    imm_in.write(0b000000);
    sc_start(1, SC_NS);
    print("0 → 0", 0, imm_out.read());

    std::cout << "\nSimulação concluída.\n";
    return 0;
}