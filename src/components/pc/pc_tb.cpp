/**
 * @file pc_tb.cpp
 * @author Ludmilla Rodrigues
 * @brief Testbench do Contador de Programa
 * @version 0.1
 * @date 2026-05-04
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <systemc.h>
#include "components/pc/pc.h"

static void print(const std::string& test, addr_t expected, addr_t got) {
    bool ok = (expected == got);
    std::cout << (ok ? "[OK]  " : "[FAIL]") << " " << test
              << " | esperado=" << expected
              << " obtido=" << got << "\n";
}

int sc_main(int argc, char* argv[]) {

    // Sinais
    sc_clock        clk("clk", 10, SC_NS);
    sc_signal<bool>   reset("reset");
    sc_signal<bool>   jump("jump");
    sc_signal<bool>   branch_taken("branch_taken");
    sc_signal<addr_t> jump_addr("jump_addr");
    sc_signal<addr_t> branch_addr("branch_addr");
    sc_signal<addr_t> pc_out("pc_out");
    sc_signal<addr_t> pc_next("pc_next");

    // Instância do PC
    pc dut("pc");
    dut.clk(clk);
    dut.reset(reset);
    dut.jump(jump);
    dut.branch_taken(branch_taken);
    dut.jump_addr(jump_addr);
    dut.branch_addr(branch_addr);
    dut.pc_out(pc_out);
    dut.pc_next(pc_next);

    // Inicializa sinais
    reset.write(false);
    jump.write(false);
    branch_taken.write(false);
    jump_addr.write(0);
    branch_addr.write(0);

    // ── Teste 1: Reset 
    reset.write(true);
    sc_start(10, SC_NS);
    print("Reset: pc_out == 0x00", 0x00, pc_out.read());

    reset.write(false);

    // ── Teste 2: Incremento automático 
    sc_start(10, SC_NS);
    print("Incremento 1: pc_out == 0x01", 0x01, pc_out.read());
    print("pc_next == 0x02",              0x02, pc_next.read());

    sc_start(10, SC_NS);
    print("Incremento 2: pc_out == 0x02", 0x02, pc_out.read());

    sc_start(10, SC_NS);
    print("Incremento 3: pc_out == 0x03", 0x03, pc_out.read());

    // ── Teste 3: Jump incondicional
    jump_addr.write(0x20);
    jump.write(true);
    sc_start(10, SC_NS);
    print("Jump para 0x20: pc_out == 0x20", 0x20, pc_out.read());

    jump.write(false);
    sc_start(10, SC_NS);
    print("Após jump, incrementa: pc_out == 0x21", 0x21, pc_out.read());

    // ── Teste 4: Branch tomado 
    branch_addr.write(0x10);
    branch_taken.write(true);
    sc_start(10, SC_NS);
    print("Branch para 0x10: pc_out == 0x10", 0x10, pc_out.read());

    branch_taken.write(false);
    sc_start(10, SC_NS);
    print("Após branch, incrementa: pc_out == 0x11", 0x11, pc_out.read());

    // ── Teste 5: Reset tem prioridade sobre jump 
    jump_addr.write(0xFF);
    jump.write(true);
    reset.write(true);
    sc_start(10, SC_NS);
    print("Reset > Jump: pc_out == 0x00", 0x00, pc_out.read());

    reset.write(false);
    jump.write(false);

    std::cout << "\nSimulação concluída.\n";
    return 0;
}