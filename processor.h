#include "systemc.h"
#include "global.h"
#include "loader.h"
#include "components/adder.h"
#include "components/bitshifter.h"
#include "components/ulacontrol.h"
#include "components/control.h"
#include "components/instructionspliter.h"
#include "components/memory.h"
#include "components/mux.h"
#include "components/pc.h"
#include "components/prePCSrc.h"
#include "components/registerbank.h"
#include "components/signalextender.h"
#include "components/ula.h"
#include "processor_monitor.h"



void processor() {
    
    sc_clock clock("clk", 1, SC_SEC, 0.5, 0, SC_SEC, false);

    // Signals

    sc_signal<bool> instructionMemory_read, MemRead, MemWrite, MemToReg, 
                    ula_zero, ula_carry,
                    RegDst, ALUSrc, RegWrite, PCSrc, PCSrc_, InstMemWrite,
                    pcLd_IFID, pcClr_IFID, instructionMemoryLd_IFID, instructionMemoryClr_IFID,
                    pcLd_IDEX, pcClr_IDEX, instructionMemoryLd_IDEX, instructionMemoryClr_IDEX;
    
    sc_signal<myword> instructionMemory_out, dataMemory_out,
                        ula_out,
                        UlaMux_out, DataMemoryMux_out, pcMux_out,
                        data_read1, data_read2,
                        signExtend_out,
                        BitShifter_out,
                        adderRight_out, adderLeft_out,
                        pc_out,
                        InstMemData,
                        instructionMemory_IFID, pc_IFID,
                        instructionMemory_IDEX, pc_IDEX, dataRead1_IDEX, dataRead2_IDEX, signalExtend_IDEX;
    
    sc_signal<myaddressword> address_write,
                            RegisterMux_out,
                            instructionMemory_outA, instructionMemory_outB, instructionMemory_outC;

    sc_signal<myshortword> instructionMemory_outD;

    sc_signal<my6bitword> ALUop, instructionMemory_outE, instructionMemory_outF; // opcode, func

    sc_signal<myopword> ula_sel;
    

    // Monitor

    mon<myword> Monitor("Monitor");
	Monitor.clk(clock);
    Monitor.myword_out1(data_read2);
    Monitor.myword_out2(ula_out);
    Monitor.my6bit_out(instructionMemory_outF);
    Monitor.myadd_out(instructionMemory_outB);
    Monitor.myshortword_out(instructionMemory_outD);
    Monitor.myword_out3(DataMemoryMux_out);
    Monitor.bit_out(MemWrite);
    
    // --------------- processor ---------------

    // --------------- IF/ID sector ---------------
    instructionMemory_read.write(1);

    mymux<myword> pcMux("pcMux");
    pcMux.sel(PCSrc_);
    pcMux.in1(adderLeft_out);
    pcMux.in2(adderRight_out);
    pcMux.S(pcMux_out);

    mypc pc("pc");
    pc.d(pcMux_out);
    pc.q(pc_out);
    pc.clk(clock);

    myprePCSrc prePCSrc("PCScrc");
    prePCSrc.PCSrc(PCSrc);
    prePCSrc.Ula_out(ula_out);
    prePCSrc.opcode(instructionMemory_outF);
    prePCSrc.PCSrc_(PCSrc_);

    sc_signal<myword> address_displacement;
    address_displacement.write(myword(1));

    myadder adderLeft("adderLeft");
	adderLeft.A(pc_out);
	adderLeft.B(address_displacement);
	adderLeft.S(adderLeft_out); // TODO: save into IF/ID buffer
    sc_signal<bool> left_co;adderLeft.CO(left_co);

    mymemory InstructionMemory("InstructionMemory");

    InstructionMemory.read(instructionMemory_read);
    InstructionMemory.write(InstMemWrite);
    InstructionMemory.data(InstMemData);
    InstructionMemory.addr(pc_out);
    InstructionMemory.out(instructionMemory_out);
    InstructionMemory.clk(clock);

    load_instructions(InstructionMemory, "-");

    // incremented pc buffer IF/ID
    myregister PC_IFID("PC_IFID");
    PC_IFID.clk(clock);
    PC_IFID.ld(pcLd_IFID); // TODO: when CLK = 1
    PC_IFID.clr(pcClr_IFID); // TODO: when?
    PC_IFID.d(pc_out);
    PC_IFID.q(pc_IFID); // used to buffer in ID/EX

    // instruction buffer IF/ID
    myregister Instruction_IFID("Instruction_IFID");
    Instruction_IFID.clk(clock);
    Instruction_IFID.ld(instructionMemoryLd_IFID); // TODO: when CLK = 1
    Instruction_IFID.clr(instructionMemoryClr_IFID); // TODO: when?
    Instruction_IFID.d(instructionMemory_out);
    Instruction_IFID.q(instructionMemory_IFID);

    // splitting instructionMemory_out to A,B,C ...
    myinstructionspliter InstructionSpliter("InstructionSpliter");
    InstructionSpliter.instruction(instructionMemory_IFID); // uses from IF/ID buffer
    InstructionSpliter.instructionMemory_outA(instructionMemory_outA);
    InstructionSpliter.instructionMemory_outB(instructionMemory_outB);
    InstructionSpliter.instructionMemory_outC(instructionMemory_outC);
    InstructionSpliter.instructionMemory_outD(instructionMemory_outD);
    InstructionSpliter.instructionMemory_outE(instructionMemory_outE);
    InstructionSpliter.instructionMemory_outF(instructionMemory_outF);

    // --------------- ID/EX sector ---------------

    mycontrol Control("Control");
	Control.opcode(instructionMemory_outF);
    Control.zero(ula_zero);
    Control.MemWrite(MemWrite);
    Control.MemRead(MemRead);
    Control.RegDst(RegDst);
    Control.ALUSrc(ALUSrc);
    Control.RegWrite(RegWrite);
    Control.ALUop(ALUop);
    Control.MemToReg(MemToReg);
    Control.PCSrc(PCSrc);
    
    mymux<myaddressword> RegisterMux("RegisterMux");
    RegisterMux.sel(RegDst);
    RegisterMux.in1(instructionMemory_outB);
    RegisterMux.in2(instructionMemory_outC);
    RegisterMux.S(RegisterMux_out);

    myregisterbank Registers("Registers");
    Registers.write(RegWrite);
    Registers.data(DataMemoryMux_out);
    Registers.addr1(instructionMemory_outA);
    Registers.addr2(instructionMemory_outB);
    Registers.addr_write(RegisterMux_out);
    Registers.out1(data_read1);
    Registers.out2(data_read2);
    Registers.clk(clock);

    load_registers(Registers, "-");

    mysigextender signalExtend("signalExtend");
    signalExtend.A(instructionMemory_outD);
    signalExtend.S(signExtend_out);

    // incremented pc buffer ID/EX
    myregister PC_IDEX("PC_IDEX");
    PC_IDEX.clk(clock);
    PC_IDEX.ld(pcLd_IDEX); // TODO: when CLK = 0
    PC_IDEX.clr(pcClr_IDEX); // TODO: when?
    PC_IDEX.d(pc_IFID);
    PC_IDEX.q(pc_IDEX); // TODO: where use?

    // instruction buffer ID/EX
    myregister Instruction_IDEX("Instruction_IDEX");
    Instruction_IDEX.clk(clock);
    Instruction_IDEX.ld(instructionMemoryLd_IDEX); // TODO: when CLK = 0
    Instruction_IDEX.clr(instructionMemoryClr_IDEX); // TODO: when?
    Instruction_IDEX.d(instructionMemory_IFID);
    Instruction_IDEX.q(instructionMemory_IDEX);

    // data read 1 buffer ID/EX
    myregister DataRead1_IDEX("DataRead1_IDEX");
    DataRead1_IDEX.clk(clock);
    DataRead1_IDEX.ld(dataRead1Ld_IDEX); // TODO: when CLK = 0
    DataRead1_IDEX.clr(dataRead1Clr_IDEX); // TODO: when?
    DataRead1_IDEX.d(data_read1);
    DataRead1_IDEX.q(dataRead1_IDEX);

    // data read 2 buffer ID/EX
    myregister DataRead2_IDEX("DataRead2_IDEX");
    DataRead2_IDEX.clk(clock);
    DataRead2_IDEX.ld(dataRead2Ld_IDEX); // TODO: when CLK = 0
    DataRead2_IDEX.clr(dataRead2Clr_IDEX); // TODO: when?
    DataRead2_IDEX.d(data_read2);
    DataRead2_IDEX.q(dataRead2_IDEX);

    // signal extend buffer ID/EX
    myregister SignalExtend_IDEX("SignalExtend_IDEX");
    SignalExtend_IDEX.clk(clock);
    SignalExtend_IDEX.ld(signalExtendLd_IDEX); // TODO: when CLK = 0
    SignalExtend_IDEX.clr(signalExtendClr_IDEX); // TODO: when?
    SignalExtend_IDEX.d(signExtend_out);
    SignalExtend_IDEX.q(signalExtend_IDEX);

    // --------------- EX/MEM sector ---------------

    mymux<myword> UlaMux("UlaMux");
    UlaMux.sel(ALUSrc);
    UlaMux.in1(dataRead2_IDEX);
    UlaMux.in2(signalExtend_IDEX);
    UlaMux.S(UlaMux_out);

    myulacontrol UlaControl("UlaControl");
    UlaControl.f(instructionMemory_outE);
    UlaControl.op(ALUop);
    UlaControl.S(ula_sel);

    myula Ula("Ula");
    Ula.alu_in1(dataRead1_IDEX);
    Ula.alu_in2(UlaMux_out);
    Ula.alu_sel(ula_sel);
    Ula.alu_out(ula_out);
    Ula.zero_out(ula_zero);
    Ula.c_out(ula_carry);
    Ula.clock(clock);

    mymemory DataMemory("DataMemory");
    DataMemory.read(MemRead);
    DataMemory.write(MemWrite);
    DataMemory.data(dataRead2_IDEX);
    DataMemory.addr(ula_out);
    DataMemory.out(dataMemory_out);
    DataMemory.clk(clock);

    load_memory(DataMemory, "-");

    mymux<myword> DataMemoryMux("DataMemoryMux");
    DataMemoryMux.sel(MemToReg);
    DataMemoryMux.in1(ula_out);
    DataMemoryMux.in2(dataMemory_out);
    DataMemoryMux.S(DataMemoryMux_out);

    myshifter<0, false> BitShifter("BitShifter");
    BitShifter.A(signalExtend_IDEX);
    BitShifter.S(BitShifter_out);

	myadder adderRight("adderRight");
	adderRight.A(adderLeft_out);
	adderRight.B(BitShifter_out);
	adderRight.S(adderRight_out);
	sc_signal<bool> right_co;adderRight.CO(right_co);

	sc_start(15, SC_SEC);
}