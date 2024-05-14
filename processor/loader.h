#ifndef LOADER_H
#define LOADER_H

#include "systemc.h"
#include "../components/memory.h"
#include "../components/registerbank.h"

// loading instructions in instruction memory

// msd -> lsd
// 00000000000000000000000000000000   32  0's

void load_instructions(mymemory& InstructionMemory, std::string file) {

    // Operações básicas de ULA
    // InstructionMemory.ram_array[0] = "00101100011000010001000000000001"; // write r[3] + r[1] in r[2]
    // InstructionMemory.ram_array[1] = "00000000000000000000000000000000"; // nada
    // InstructionMemory.ram_array[2] = "00000000000000000000000000000000"; // nada
    // InstructionMemory.ram_array[3] = "00000000000000000000000000000000"; // nada
    // InstructionMemory.ram_array[4] = "00001100011000100000000000000010"; // write r[3] * 2 in r[2]
    // InstructionMemory.ram_array[5] = "00000000000000000000000000000000"; // nada
    // InstructionMemory.ram_array[6] = "00000000000000000000000000000000"; // nada
    // InstructionMemory.ram_array[7] = "00000000000000000000000000000000"; // nada
    // InstructionMemory.ram_array[8] = "00000100010001000000000000000000"; // write r[2] + 0 in r[4]

    // LW
    // Perceba que na memória na posição 1 tem 00000000000000000000000000011111 e r[1] = 00000000000000000000000000000001
    // Dessa forma, o valor que será carregado para r[2] será 00000000000000000000000000011111
    /*
     InstructionMemory.ram_array[0] = "00110000001000100000000000000000"; // load memory at r[1] + 0 to r[2]
     InstructionMemory.ram_array[1] = "00000000000000000000000000000000"; // nada
     InstructionMemory.ram_array[2] = "00000000000000000000000000000000"; // nada
     InstructionMemory.ram_array[3] = "00000000000000000000000000000000"; // nada
     InstructionMemory.ram_array[4] = "00000100010001000000000000000000"; // write r[2] + 0 in r[4]
    */

    // ST (Escrita na memória)
    // InstructionMemory.ram_array[0] = "00110100001000100000000000000000"; // memory[r[1] + 0] = r[2]
    // InstructionMemory.ram_array[1] = "00000000000000000000000000000000"; // nada
    // InstructionMemory.ram_array[2] = "00000000000000000000000000000000"; // nada
    // InstructionMemory.ram_array[3] = "00000000000000000000000000000000"; // nada
    // InstructionMemory.ram_array[4] = "00110000001000110000000000000000"; // r[3] = memory[r[1] + 0] 
    // InstructionMemory.ram_array[5] = "00000000000000000000000000000000"; // nada
    // InstructionMemory.ram_array[6] = "00000000000000000000000000000000"; // nada
    // InstructionMemory.ram_array[7] = "00000000000000000000000000000000"; // nada
    // InstructionMemory.ram_array[8] = "00000100011001000000000000000000"; // write r[3] + 0 in r[4] (r[3] deve ser igual ao r[2])


    InstructionMemory.ram_array[0] = "00111000000000000000000000000100"; // jump 1 instruction (to nada2)
    InstructionMemory.ram_array[1] = "00000000000000000000000000000001"; // nada
    InstructionMemory.ram_array[2] = "00000000000000000000000000000011"; // nada
    InstructionMemory.ram_array[3] = "00000000000000000000000000000111"; // nada
    InstructionMemory.ram_array[4] = "00000000000000000000000000001111"; // nada
    InstructionMemory.ram_array[5] = "00000000000000000000000000011111"; // nada
    InstructionMemory.ram_array[6] = "00000000000000000000000000111111"; // nada
    InstructionMemory.ram_array[7] = "00000000000000000000000001111111"; // nada
    InstructionMemory.ram_array[8] = "00000000000000000000000011111111"; // nada

    // msd -> lsd
    //                                000000 00000 00000 00000 00000 000000
    //                                opcode  r1   w1 r2   w2         func
    //                                  F                              E
    //                                                  |    Immediate
    //                                000000 00000 00000 0000000000000000
}

void load_memory(mymemory& DataMemory, std::string file) {
    // Escrita na memória de dados (st)
    // DataMemory.ram_array[1] = "00000000000000000000000000000000";
}

void load_registers(myregisterbank& RegisterBank, std::string file) {
    // Escrita na memória de dados (st)
    //RegisterBank.bank[1] = "00000000000000000000000000000001";
    // RegisterBank.bank[2] = "00000000000000000000000000011111";
    // RegisterBank.bank[3] = "00000000000000000000000000000011";
}

#endif