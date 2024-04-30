#include "systemc.h"
#include "processor_variables.h"
#include "global.h"

#include "components/memory.h"
#include "components/mux.h"
#include "components/pc.h"
#include "components/instructionspliter.h"

#include "loader.h"

// --------------- IF/ID sector ---------------

void ifid(sc_clock &myclock) {
    instMemRead.write(1);

    mymux<myword> pcMux("pcMux");
    pcMux.sel(PCSrc_);
    pcMux.in1(adderLeft_out);
    pcMux.in2(adderRight_out);
    pcMux.S(pcMux_out);

    mypc pc("pc");
    pc.d(pcMux_out);
    pc.q(pc_out);
    pc.clk(myclock);

    sc_signal<myword> address_displacement;
    address_displacement.write(myword(1));

    mymemory<1> InstructionMemory("InstructionMemory");
    InstructionMemory.read(instMemRead);
    InstructionMemory.write(instMemWrite);
    InstructionMemory.data(instMemData);
    InstructionMemory.addr(pc_out);
    InstructionMemory.out(instructionMemory_out);
    InstructionMemory.clk(myclock);

    load_instructions(InstructionMemory, "-");

    // incremented pc buffer IF/ID
    myregister<myword> PC_IFID("PC_IFID");
    PC_IFID.clk(myclock);
    PC_IFID.ld(pcLd_IFID); // TODO: when CLK = 1
    PC_IFID.clr(pcClr_IFID); // TODO: when?
    PC_IFID.d(adderLeft_out);
    PC_IFID.q(pc_IFID); // used to buffer in ID/EX

    // instruction buffer IF/ID
    myregister<myword> Instruction_IFID("Instruction_IFID");
    Instruction_IFID.clk(myclock);
    Instruction_IFID.ld(instructionMemoryLd_IFID); // TODO: when CLK = 1
    Instruction_IFID.clr(instructionMemoryClr_IFID); // TODO: when?
    Instruction_IFID.d(instructionMemory_out);
    Instruction_IFID.q(instructionMemory_IFID);

    // splitting instructionMemory_out to A,B,C ...
    myinstructionspliter InstructionSpliter("InstructionSpliter");
    InstructionSpliter.instruction(instructionMemory_IFID); // uses from IF/ID buffer
    InstructionSpliter.instruction2(instructionMemory_IDEX); // uses from ID/EX buffer
    InstructionSpliter.instructionMemory_outA(instructionMemory_outA);
    InstructionSpliter.instructionMemory_outB(instructionMemory_outB);
    InstructionSpliter.instructionMemory_outC(instructionMemory_outC);
    InstructionSpliter.instructionMemory_outD(instructionMemory_outD);
    InstructionSpliter.instructionMemory_outE(instructionMemory_outE);
    InstructionSpliter.instructionMemory_outF(instructionMemory_outF);
}