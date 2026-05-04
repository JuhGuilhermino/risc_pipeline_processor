#include <systemc.h>
#include "datapath/datapath.h"

static void print(const std::string& test, int expected, int got) {
    std::cout << ((expected == got) ? "[OK]  " : "[FAIL] ")
              << test
              << " | esperado=" << expected
              << " obtido=" << got << "\n";
}

int sc_main(int argc, char* argv[]) {

    sc_clock clk("clk", 10, SC_NS);

    sc_signal<word_t> instruction;
    sc_signal<word_t> debug_out;

    datapath dut("datapath");
    dut.clk(clk);
    dut.instruction(instruction);
    dut.debug_out(debug_out);

    // ADDI R1 = R0 + 5
    instruction.write(0b0111'001'000'000101);
    sc_start(10, SC_NS);
    print("ADDI resultado", 5, debug_out.read());

    // ADD R2 = R1 + R1
    instruction.write(0b0000'010'001'001'000);
    sc_start(10, SC_NS);
    print("ADD resultado", 10, debug_out.read());

    std::cout << "\nSimulação concluída.\n";
    return 0;
}