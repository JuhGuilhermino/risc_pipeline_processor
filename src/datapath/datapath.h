#pragma once

#include <systemc.h>
#include "types/types.h"

#include "components/alu/alu.h"
#include "components/mux/mux.h"
#include "components/sign_extend/sign_extend.h"
#include "components/registers/registers.h"
#include "control/unit_control.h"

SC_MODULE(datapath) {

    // clock
    sc_in<bool> clk;

    // entrada
    sc_in<word_t> instruction;

    // saída de debug
    sc_out<word_t> debug_out;

    // ===== decode =====
    sc_signal<sc_uint<4>> opcode;
    sc_signal<sc_uint<3>> rs1, rs2, rd;
    sc_signal<sc_uint<6>> imm;

    // ===== controle =====
    sc_signal<bool> reg_write;
    sc_signal<bool> mem_read;
    sc_signal<bool> mem_write;
    sc_signal<bool> mem_to_reg;
    sc_signal<sc_uint<3>> alu_op;
    sc_signal<bool> alu_src;
    sc_signal<bool> branch;
    sc_signal<bool> jump;

    // ===== dados =====
    sc_signal<word_t> reg_data1;
    sc_signal<word_t> reg_data2;
    sc_signal<word_t> imm_ext;
    sc_signal<word_t> alu_in2;
    sc_signal<word_t> alu_result;
    sc_signal<flags_t> alu_flags;

    // ===== módulos =====
    control_unit ctrl;
    registers regs;
    sign_extend se;
    mux alu_mux;
    alu my_alu;

    // métodos
    void decode_instruction();
    void debug_assign();

    SC_CTOR(datapath)
        : ctrl("ctrl"),
          regs("regs"),
          se("se"),
          alu_mux("alu_mux"),
          my_alu("alu")
    {
        // decode
        SC_METHOD(decode_instruction);
        sensitive << instruction;

        // debug correto (SEM conflito)
        SC_METHOD(debug_assign);
        sensitive << alu_result;

        // ===== CONTROL UNIT =====
        ctrl.opcode(opcode);
        ctrl.reg_write(reg_write);
        ctrl.mem_read(mem_read);
        ctrl.mem_write(mem_write);
        ctrl.mem_to_reg(mem_to_reg);
        ctrl.alu_op(alu_op);
        ctrl.alu_src(alu_src);
        ctrl.branch(branch);
        ctrl.jump(jump);

        // ===== REGISTERS =====
        regs.clk(clk);
        regs.rs1(rs1);
        regs.rs2(rs2);
        regs.rd(rd);
        regs.write_data(alu_result);
        regs.reg_write(reg_write);
        regs.read_data1(reg_data1);
        regs.read_data2(reg_data2);

        // ===== SIGN EXTEND =====
        se.imm_in(imm);
        se.imm_out(imm_ext);

        // ===== MUX =====
        alu_mux.in0(reg_data2);
        alu_mux.in1(imm_ext);
        alu_mux.sel(alu_src);
        alu_mux.out(alu_in2);

        // ===== ALU =====
        my_alu.A(reg_data1);
        my_alu.B(alu_in2);
        my_alu.alu_op(alu_op);
        my_alu.result(alu_result);
        my_alu.flags(alu_flags);
    }
};