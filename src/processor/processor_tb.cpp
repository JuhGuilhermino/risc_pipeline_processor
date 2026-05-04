#include <systemc.h>
#include "processor/processor.h"

static void print(const std::string& test, int got) {
    std::cout << test << " | resultado=" << got << "\n";
}

int sc_main(int argc, char* argv[]) {

    sc_clock clk("clk", 10, SC_NS);

    sc_signal<word_t> instruction;
    sc_signal<word_t> debug_out;

    // ===== CPU =====
    processor cpu("cpu");
    cpu.clk(clk);
    cpu.instruction_in(instruction);
    cpu.debug_out(debug_out);

    // ===== WAVEFORM =====
    sc_trace_file *fp;
    fp = sc_create_vcd_trace_file("processor_wave");
    fp->set_time_unit(1, SC_NS);

    sc_trace(fp, clk, "clk");
    sc_trace(fp, instruction, "instruction");
    sc_trace(fp, debug_out, "debug_out");

    // pipeline
    sc_trace(fp, cpu.if_id_instr, "if_id_instr");
    sc_trace(fp, cpu.id_ex_instr, "id_ex_instr");

    // datapath interno
    sc_trace(fp, cpu.dp.alu_result, "alu_result");
    sc_trace(fp, cpu.dp.reg_data1, "reg_data1");
    sc_trace(fp, cpu.dp.reg_data2, "reg_data2");

    // ===== TESTE =====

    // ciclo 1: ADDI R1 = 5
    instruction.write(0b0111'001'000'000101);
    sc_start(10, SC_NS);

    // ciclo 2: ADD R2 = R1 + R1
    instruction.write(0b0000'010'001'001'000);
    sc_start(10, SC_NS);

    // ciclos extras (pipeline fluir)
    sc_start(40, SC_NS);

    print("Resultado final", debug_out.read());

    // fechar waveform
    sc_close_vcd_trace_file(fp);

    std::cout << "\nSimulação concluída.\n";
    return 0;
}

