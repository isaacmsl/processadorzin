#include "systemc.h"
#include "components/memory.h"

// loading instructions in instruction memory

void load_instructions(mymemory& InstructionMemory, std::string file) {

    //std::string inst = "00000000000000000000000001000111";
    //std::reverse(inst.begin(), inst.end()); //.c_str()
    InstructionMemory.ram_array[0] = "00000000000000000000000001000111";
    //10001110000000000000000000000000


    // msd -> lsd
    //                                000000 00000 00000 00000 00000 000000
    //                                opcode  r1   w1r2   w2          func
    //                                                  |      Immediate
    //                                000000 00000 00000 0000000001000111
}