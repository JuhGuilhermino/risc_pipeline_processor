/**
 * @file types.h
 * @author Ludmilla Rodrigues (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-01
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once

#include <systemc.h>

//  Tipos base do processador RISC 16-bit Pipeline

// Tamanhos fundamentais
static constexpr int WORD_SIZE  = 16;  
static constexpr int ADDR_SIZE  = 8;    
static constexpr int REG_BITS   = 3;    
static constexpr int OPCODE_BITS= 4;    
static constexpr int IMM_BITS   = 6;    
static constexpr int JADDR_BITS = 12;   
static constexpr int NUM_REGS   = 8;    
static constexpr int MEM_SIZE   = 256;  

// Tipos básicos de dados
typedef sc_uint<WORD_SIZE>   word_t;   
typedef sc_uint<ADDR_SIZE>   addr_t;   
typedef sc_uint<REG_BITS>    reg_t;    
typedef sc_uint<OPCODE_BITS> opcode_t; 
typedef sc_int<WORD_SIZE>    sword_t;  
typedef sc_uint<IMM_BITS>    imm_t;    
typedef sc_uint<JADDR_BITS>  jaddr_t;  


typedef sc_uint<2> flags_t;

static constexpr int FLAG_Z_BIT = 1;   // posição do flag Zero
static constexpr int FLAG_N_BIT = 0;   // posição do flag Negativo

enum Opcode : uint8_t {
    OP_ADD   = 0b0000, 
    OP_SUB   = 0b0001,  
    OP_AND   = 0b0010,  
    OP_OR    = 0b0011,  
    OP_XOR   = 0b0100,  
    OP_NOT   = 0b0101,  
    OP_CMP   = 0b0110,  
    OP_ADDI  = 0b0111,  
    OP_LOAD  = 0b1000,  
    OP_STORE = 0b1001,  
    OP_BEQ   = 0b1010,  
    OP_BNE   = 0b1011,  
    OP_JMP   = 0b1100,  
    OP_NOP   = 0b1111   
};

// Operações internas da ALU (sinal alu_op — 3 bits)
enum AluOp : uint8_t {
    ALU_ADD  = 0b000,
    ALU_SUB  = 0b001,
    ALU_AND  = 0b010,
    ALU_OR   = 0b011,
    ALU_XOR  = 0b100,
    ALU_NOT  = 0b101,
    ALU_NOP  = 0b111    // passthrough / sem operação
};

// ----------------------------------------------------------
// Formato da instrução
// Campos extraídos de uma word_t de 16 bits:
//
//  Formato R: [15:12] opcode | [11:9] rd | [8:6] rs1 | [5:3] rs2 | [2:0] func
//  Formato I: [15:12] opcode | [11:9] rd | [8:6] rs1 | [5:0] imm (sign-extended)
//  Formato J: [15:12] opcode | [11:0] addr
// ----------------------------------------------------------
struct InstrFields {
    opcode_t opcode;
    reg_t    rd;
    reg_t    rs1;
    reg_t    rs2;
    sword_t  imm;       // imediato de 6 bits com extensão de sinal para 16
    jaddr_t  jaddr;     // endereço absoluto de 12 bits (formato J)

    // Decodifica uma instrução de 16 bits
    explicit InstrFields(word_t instr) {
        opcode = instr.range(15, 12);
        rd     = instr.range(11,  9);
        rs1    = instr.range( 8,  6);
        rs2    = instr.range( 5,  3);
        jaddr  = instr.range(11,  0);

        // Extensão de sinal do imediato de 6 bits
        sc_uint<6> raw_imm = instr.range(5, 0);
        if (raw_imm[5] == 1)                   
            imm = (sword_t)(sc_int<6>(raw_imm));
        else
            imm = (sword_t)(sc_uint<6>(raw_imm));
    }
};

// Sinais de controle propagados pelo pipeline
struct ControlSignals {
    bool    reg_write;  
    bool    mem_read;   
    bool    mem_write;  
    bool    mem_to_reg; 
    bool    alu_src;    
    bool    branch;     
    bool    jump;       
    sc_uint<3> alu_op;  

    ControlSignals()
        : reg_write(false), mem_read(false), mem_write(false),
          mem_to_reg(false), alu_src(false),
          branch(false), jump(false), alu_op(ALU_NOP)
    {}
};

// Constantes utilitárias
static const word_t NOP_INSTR = 0xFFFF;  
static const addr_t PC_RESET  = 0x00;    
