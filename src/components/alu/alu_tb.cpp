#include <systemc.h>
#include <cassert>
#include "../src/types/types.h"
#include "alu.h"

SC_MODULE(alu_testbench) {
    sc_out<word_t> A, B;
    sc_out<sc_uint<3>> alu_op;
    sc_in<bool> Clk;

    void generate_tb() {
        wait();

        // AND
        A.write(1);
        B.write(0);
        alu_op.write(ALU_AND);
        wait();

        // OR
        A.write(1);
        B.write(0);
        alu_op.write(ALU_OR);
        wait();

        // XOR
        A.write(1);
        B.write(1);
        alu_op.write(ALU_XOR);
        wait();

        // NOT
        A.write(1);
        B.write(0);
        alu_op.write(ALU_NOT);
        wait();

        // ADD
        A.write(2);
        B.write(4);
        alu_op.write(ALU_ADD);
        wait();

        // SUB
        A.write(8);
        B.write(4);
        alu_op.write(ALU_SUB);
        wait();

        sc_stop();
    }

    SC_CTOR(alu_testbench) {
        SC_THREAD(generate_tb);
        sensitive << Clk.pos();
    }
};



int sc_main(int argc, char *argv[]) {
    cout << "ENTROU NO SC_MAIN" << endl;
    
    sc_signal<word_t> A, B;
    sc_signal<sc_uint<3>> alu_op;
    sc_signal<word_t> result;
    sc_signal<flags_t> flags;
    sc_clock TestClk("TestClock", 10, SC_NS, 0.5);

    // testbench
    alu_testbench Tb("Stimulus");
    Tb.A(A);
    Tb.B(B);
    Tb.alu_op(alu_op);
    Tb.Clk(TestClk);

    // alu
    alu myAlu("alu");
    myAlu.A(A);
    myAlu.B(B);
    myAlu.alu_op(alu_op);
    myAlu.result(result);
    myAlu.flags(flags);

    //========================= waveform
    sc_trace_file *fp;
    fp = sc_create_vcd_trace_file("../data/alu");
    fp->set_time_unit(1, sc_core::SC_NS);

    sc_trace(fp, A, "A");
    sc_trace(fp, B, "B");
    sc_trace(fp, alu_op, "alu_op");
    sc_trace(fp, result, "result");
    sc_trace(fp, flags, "flags");
    sc_trace(fp, TestClk, "CLK");
    //=========================

    sc_start(100, SC_NS);

    sc_signal<int> x;

    return 0;
}
