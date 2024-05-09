#ifndef LOADER_H
#define LOADER_H

#include "systemc.h"
#include "../components/memory.h"
#include "../components/registerbank.h"

// loading instructions in instruction memory

// msd -> lsd
// 00000000000000000000000000000000   32  0's

template<int clock_int>
void load_instructions(mymemory<clock_int>& InstructionMemory, std::string file) {


    //InstructionMemory.ram_array[0] = "00000000000000000000000001000111";

    //InstructionMemory.ram_array[0] = "00101100000001000000000001010101";
    //InstructionMemory.ram_array[1] = "00101000000000010000000001010101";

    InstructionMemory.ram_array[0] = "00000100001000100000000000000001"; // write r[1] + 1 in r[2]
    InstructionMemory.ram_array[1] = "00000000000000000000000000000000"; // nada
    InstructionMemory.ram_array[2] = "00000000000000000000000000000000"; // nada
    InstructionMemory.ram_array[3] = "00000100010000110000000000000001"; // write r[2] + 1 in r[3]
    InstructionMemory.ram_array[4] = "00000100011001000000000000000001"; // write r[3] + 1 in r[4]

    // msd -> lsd
    //                                000000 00000 00000 00000 00000 000000
    //                                opcode  r1   w1 r2   w2         func
    //                                                  |    Immediate
    //                                000000 00000 00000 0000000000000000

    // examples:

    // add 0000000001010101 to value at register 00001 -> 000000 00001 00000 0000000001010101
    // write value at register 00011 to memory at 00001 + 0000000001010101 -> 001011 00001 00011 0000000001010101
    // load value in memory at 00001 + 0000000001010101 to register 00011 -> 001010 00001 00011 0000000001010101
}

template<int clock_int>
void load_memory(mymemory<clock_int>& DataMemory, std::string file) {

    DataMemory.ram_array[0] = "00000000000000000000000000000000";
}

void load_registers(myregisterbank& RegisterBank, std::string file) {

    RegisterBank.bank[1] = "00000000000000000000000000000001";
}

#endif