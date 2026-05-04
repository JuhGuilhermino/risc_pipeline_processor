#include <systemc.h>
#include "mux.h"

static void print(const std::string& test, word_t expected, word_t got) {
    bool ok = (expected == got);
    std::cout << (ok ? "[OK]  " : "[FAIL]") << " " << test
              << " | esperado=" << expected
              << " obtido=" << got << "\n";
}

int sc_main(int argc, char* argv[]) {

    // Sinais
    sc_signal<word_t> in0("in0");
    sc_signal<word_t> in1("in1");
    sc_signal<bool>   sel("sel");
    sc_signal<word_t> out("out");

    // Instância
    mux dut("mux");
    dut.in0(in0);
    dut.in1(in1);
    dut.sel(sel);
    dut.out(out);

    // ── Teste 1: sel=0 seleciona in0 
    in0.write(0xAAAA);
    in1.write(0x5555);
    sel.write(false);
    sc_start(1, SC_NS);
    print("sel=0 → out == in0 (0xAAAA)", 0xAAAA, out.read());

    // ── Teste 2: sel=1 seleciona in1 
    sel.write(true);
    sc_start(1, SC_NS);
    print("sel=1 → out == in1 (0x5555)", 0x5555, out.read());

    // ── Teste 3: muda in0 com sel=0 
    sel.write(false);
    in0.write(0x1234);
    sc_start(1, SC_NS);
    print("sel=0, in0 muda → out == 0x1234", 0x1234, out.read());

    // ── Teste 4: muda in1 com sel=1 
    sel.write(true);
    in1.write(0xABCD);
    sc_start(1, SC_NS);
    print("sel=1, in1 muda → out == 0xABCD", 0xABCD, out.read());

    // ── Teste 5: zero 
    in0.write(0x0000);
    in1.write(0xFFFF);
    sel.write(false);
    sc_start(1, SC_NS);
    print("sel=0, in0=0x0000 → out == 0x0000", 0x0000, out.read());

    std::cout << "\nSimulação concluída.\n";
    return 0;
}