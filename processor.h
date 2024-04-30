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
                    pcLd_IDEX, pcClr_IDEX, instructionMemoryLd_IDEX, instructionMemoryClr_IDEX,
                    instructionMemoryLd_EXMEM, instructionMemoryClr_EXMEM, 
                    dataRead1Ld_IDEX, dataRead1Clr_IDEX, signalExtendLd_IDEX, signalExtendClr_IDEX,
                    dataRead2Ld_IDEX, dataRead2Clr_IDEX,
                    adderRightLd_EXMEM, adderRighClr_EXMEM, 
                    ulaResultLd_EXMEM, ulaResultClr_EXMEM,
                    zeroLd_EXMEM, zeroClr_EXMEM,
                    dataRead2Ld_EXMEM, dataRead2Clr_EXMEM,
                    ulaResultLd_MEMWB, ulaResultClr_MEMWB,
                    memoryReadLd_MEMWB, memoryReadClr_MEMWB,
                    instructionMemoryLd_MEMWB, instructionMemoryClr_MEMWB,
                    aluOpLd_IDEX, aluOpClr_IDEX,
                    aluSrcLd_IDEX, aluSrcClr_IDEX,
                    regDestLd_IDEX, regDestClr_IDEX,
                    memReadLd_IDEX, memReadClr_IDEX,
                    memWriteLd_IDEX, memWriteClr_IDEX,
                    opCodeLd_IDEX, opCodeClr_IDEX,
                    regWriteLd_IDEX, regWriteClr_IDEX,
                    memToRegLd_IDEX, memToRegClr_IDEX;
    
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
                        instructionMemory_IDEX, pc_IDEX, dataRead1_IDEX, dataRead2_IDEX, signalExtend_IDEX,
                        adderRight_EXMEM, instructionMemory_EXMEM,
                        ulaResult_EXMEM, zero_EXMEM, ula_zero_myword,
                        dataRead2_EXMEM, ulaResult_MEMWB,
                        memoryRead_MEMWB, instructionMemory_MEMWB,
                        aluOp_IDEX, aluSrc_IDEX, regDest_IDEX, memRead_IDEX, memWrite_IDEX, opCode_IDEX, regWrite_IDEX, memToReg_IDEX;

    
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
    Monitor.myadd_out(RegisterMux_out);
    Monitor.myshortword_out(instructionMemory_outD);
    Monitor.myword_out3(DataMemoryMux_out);
    Monitor.bit_out(RegWrite);
    
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

    sc_signal<myword> address_displacement;
    address_displacement.write(myword(1));

    myadder adderLeft("adderLeft");
	adderLeft.A(pc_out);
	adderLeft.B(address_displacement);
	adderLeft.S(adderLeft_out);
    sc_signal<bool> left_co;adderLeft.CO(left_co);

    mymemory<1> InstructionMemory("InstructionMemory");

    InstructionMemory.read(instructionMemory_read);
    InstructionMemory.write(InstMemWrite);
    InstructionMemory.data(InstMemData);
    InstructionMemory.addr(pc_out);
    InstructionMemory.out(instructionMemory_out);
    InstructionMemory.clk(clock);

    load_instructions(InstructionMemory, "-");

    // incremented pc buffer IF/ID
    myregister<1> PC_IFID("PC_IFID");
    PC_IFID.clk(clock);
    PC_IFID.ld(pcLd_IFID); // TODO: when CLK = 1
    PC_IFID.clr(pcClr_IFID); // TODO: when?
    PC_IFID.d(adderLeft_out);
    PC_IFID.q(pc_IFID); // used to buffer in ID/EX

    // instruction buffer IF/ID
    myregister<1> Instruction_IFID("Instruction_IFID");
    Instruction_IFID.clk(clock);
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

    myregisterbank Registers("Registers");
    Registers.write(regWrite_MEMWB);
    Registers.data(DataMemoryMux_out);
    Registers.addr1(instructionMemory_outA);
    Registers.addr2(instructionMemory_outB);
    Registers.addr_write(RegisterMux_out);
    Registers.out1(data_read1);
    Registers.out2(data_read2);
    Registers.clk(clock);

    load_registers(Registers, "-");

    mysigextender<myshortword, myword> signalExtend("signalExtend");
    signalExtend.A(instructionMemory_outD);
    signalExtend.S(signExtend_out);

    // AluOp buffer ID/EX
    myregister<0> AluOp_IDEX("AluOp_IDEX");
    AluOp_IDEX.clk(clock);
    AluOp_IDEX.ld(aluOpLd_IDEX); // TODO: when CLK = 0
    AluOp_IDEX.clr(aluOpClr_IDEX); // TODO: when?
    AluOp_IDEX.d(ALUop);
    AluOp_IDEX.q(aluOp_IDEX); // TODO: where use?

    // AluSrc buffer ID/EX
    myregister<0> AluSrc_IDEX("AluSrc_IDEX");
    AluSrc_IDEX.clk(clock);
    AluSrc_IDEX.ld(aluSrcLd_IDEX); // TODO: when CLK = 0
    AluSrc_IDEX.clr(aluSrcClr_IDEX); // TODO: when?
    AluSrc_IDEX.d(ALUSrc);
    AluSrc_IDEX.q(aluSrc_IDEX);

    // RegDest buffer ID/EX
    myregister<0> RegDest_IDEX("RegDest_IDEX");
    RegDest_IDEX.clk(clock);
    RegDest_IDEX.ld(regDestLd_IDEX); // TODO: when CLK = 0
    RegDest_IDEX.clr(regDestClr_IDEX); // TODO: when?
    RegDest_IDEX.d(RegDst);
    RegDest_IDEX.q(regDest_IDEX); // TODO: where use?

    // MemRead buffer ID/EX
    myregister<0> MemRead_IDEX("MemRead_IDEX");
    MemRead_IDEX.clk(clock);
    MemRead_IDEX.ld(memReadLd_IDEX); // TODO: when CLK = 0
    MemRead_IDEX.clr(memReadClr_IDEX); // TODO: when?
    MemRead_IDEX.d(MemRead);
    MemRead_IDEX.q(memRead_IDEX); // TODO: where use? 

    // MemWrite buffer ID/EX
    myregister<0> MemWrite_IDEX("MemWrite_IDEX");
    MemWrite_IDEX.clk(clock);
    MemWrite_IDEX.ld(memWriteLd_IDEX); // TODO: when CLK = 0
    MemWrite_IDEX.clr(memWriteClr_IDEX); // TODO: when?
    MemWrite_IDEX.d(MemWrite);
    MemWrite_IDEX.q(memWrite_IDEX); // TODO: where use?  

    // OpCode buffer ID/EX
    myregister<0> OpCode_IDEX("OpCode_IDEX");
    OpCode_IDEX.clk(clock);
    OpCode_IDEX.ld(opCodeLd_IDEX); // TODO: when CLK = 0
    OpCode_IDEX.clr(opCodeClr_IDEX); // TODO: when?
    OpCode_IDEX.d(instructionMemory_outF);
    OpCode_IDEX.q(opCode_IDEX); // TODO: where use?

    // RegWrite buffer ID/EX
    myregister<0> RegWrite_IDEX("RegWrite_IDEX");
    RegWrite_IDEX.clk(clock);
    RegWrite_IDEX.ld(regWriteLd_IDEX); // TODO: when CLK = 0
    RegWrite_IDEX.clr(regWriteClr_IDEX); // TODO: when?
    RegWrite_IDEX.d(RegWrite);
    RegWrite_IDEX.q(regWrite_IDEX); // TODO: where use?

    // MemToReg buffer ID/EX
    myregister<0> MemToReg_IDEX("MemToReg_IDEX");
    MemToReg_IDEX.clk(clock);
    MemToReg_IDEX.ld(memToRegLd_IDEX); // TODO: when CLK = 0
    MemToReg_IDEX.clr(memToRegClr_IDEX); // TODO: when?
    MemToReg_IDEX.d(MemToReg);
    MemToReg_IDEX.q(memToReg_IDEX); // TODO: where use?

    // incremented pc buffer ID/EX
    myregister<0> PC_IDEX("PC_IDEX");
    PC_IDEX.clk(clock);
    PC_IDEX.ld(pcLd_IDEX); // TODO: when CLK = 0
    PC_IDEX.clr(pcClr_IDEX); // TODO: when?
    PC_IDEX.d(pc_IFID);
    PC_IDEX.q(pc_IDEX); // TODO: where use?

    // instruction buffer ID/EX
    myregister<0> Instruction_IDEX("Instruction_IDEX");
    Instruction_IDEX.clk(clock);
    Instruction_IDEX.ld(instructionMemoryLd_IDEX); // TODO: when CLK = 0
    Instruction_IDEX.clr(instructionMemoryClr_IDEX); // TODO: when?
    Instruction_IDEX.d(instructionMemory_IFID);
    Instruction_IDEX.q(instructionMemory_IDEX);

    // data read 1 buffer ID/EX
    myregister<0> DataRead1_IDEX("DataRead1_IDEX");
    DataRead1_IDEX.clk(clock);
    DataRead1_IDEX.ld(dataRead1Ld_IDEX); // TODO: when CLK = 0
    DataRead1_IDEX.clr(dataRead1Clr_IDEX); // TODO: when?
    DataRead1_IDEX.d(data_read1);
    DataRead1_IDEX.q(dataRead1_IDEX);

    // data read 2 buffer ID/EX
    myregister<0> DataRead2_IDEX("DataRead2_IDEX");
    DataRead2_IDEX.clk(clock);
    DataRead2_IDEX.ld(dataRead2Ld_IDEX); // TODO: when CLK = 0
    DataRead2_IDEX.clr(dataRead2Clr_IDEX); // TODO: when?
    DataRead2_IDEX.d(data_read2);
    DataRead2_IDEX.q(dataRead2_IDEX);

    // signal extend buffer ID/EX
    myregister<0> SignalExtend_IDEX("SignalExtend_IDEX");
    SignalExtend_IDEX.clk(clock);
    SignalExtend_IDEX.ld(signalExtendLd_IDEX); // TODO: when CLK = 0
    SignalExtend_IDEX.clr(signalExtendClr_IDEX); // TODO: when?
    SignalExtend_IDEX.d(signExtend_out);
    SignalExtend_IDEX.q(signalExtend_IDEX);

    // --------------- EX/MEM sector ---------------

    mymux<myword> UlaMux("UlaMux");
    UlaMux.sel(aluSrc_IDEX);
    UlaMux.in1(dataRead2_IDEX);
    UlaMux.in2(signalExtend_IDEX);
    UlaMux.S(UlaMux_out);

    myulacontrol UlaControl("UlaControl");
    UlaControl.f(instructionMemory_outE);
    UlaControl.op(aluOp_IDEX);
    UlaControl.S(ula_sel);

    mymux<myaddressword> RegisterMux("RegisterMux");
    RegisterMux.sel(regDest_IDEX);
    RegisterMux.in1(instructionMemory_outB);
    RegisterMux.in2(instructionMemory_outC);
    RegisterMux.S(RegisterMux_out);

    myula Ula("Ula");
    Ula.alu_in1(dataRead1_IDEX);
    Ula.alu_in2(UlaMux_out);
    Ula.alu_sel(ula_sel);
    Ula.alu_out(ula_out);
    Ula.zero_out(ula_zero);
    Ula.c_out(ula_carry);
    Ula.clock(clock);

    myshifter<0, false> BitShifter("BitShifter");
    BitShifter.A(signalExtend_IDEX);
    BitShifter.S(BitShifter_out);

	myadder adderRight("adderRight");
	adderRight.A(adderLeft_out);
	adderRight.B(BitShifter_out);
	adderRight.S(adderRight_out);
	sc_signal<bool> right_co;adderRight.CO(right_co);

    // MemRead buffer EX/MEM
    myregister<0> MemRead_EXMEM("MemRead_EXMEM");
    MemRead_EXMEM.clk(clock);
    MemRead_EXMEM.ld(memReadLd_EXMEM); // TODO: when CLK = 0
    MemRead_EXMEM.clr(memReadClr_EXMEM); // TODO: when?
    MemRead_EXMEM.d(memRead_IDEX);
    MemRead_EXMEM.q(memRead_EXMEM); // TODO: where use? 

    // MemWrite buffer EX/MEM
    myregister<0> MemWrite_EXMEM("MemWrite_EXMEM");
    MemWrite_EXMEM.clk(clock);
    MemWrite_EXMEM.ld(memWriteLd_EXMEM); // TODO: when CLK = 0
    MemWrite_EXMEM.clr(memWriteClr_EXMEM); // TODO: when?
    MemWrite_EXMEM.d(MemWrite_IDEX);
    MemWrite_EXMEM.q(memWrite_EXMEM); // TODO: where use?  

    // OpCode buffer EX/MEM
    myregister<0> OpCode_EXMEM("OpCode_EXMEM");
    OpCode_EXMEM.clk(clock);
    OpCode_EXMEM.ld(opCodeLd_EXMEM); // TODO: when CLK = 0
    OpCode_EXMEM.clr(opCodeClr_EXMEM); // TODO: when?
    OpCode_EXMEM.d(opCode_IDEX);
    OpCode_EXMEM.q(opCode_EXMEM); // TODO: where use?

    // RegWrite buffer EX/MEM
    myregister<0> RegWrite_EXMEM("RegWrite_EXMEM");
    RegWrite_EXMEM.clk(clock);
    RegWrite_EXMEM.ld(regWriteLd_EXMEM); // TODO: when CLK = 0
    RegWrite_EXMEM.clr(regWriteClr_EXMEM); // TODO: when?
    RegWrite_EXMEM.d(RegDest_IDEX);
    RegWrite_EXMEM.q(regWrite_EXMEM); // TODO: where use?

    // MemToReg buffer EX/MEM
    myregister<0> MemToReg_EXMEM("MemToReg_EXMEM");
    MemToReg_EXMEM.clk(clock);
    MemToReg_EXMEM.ld(memToRegLd_EXMEM); // TODO: when CLK = 0
    MemToReg_EXMEM.clr(memToRegClr_EXMEM); // TODO: when?
    MemToReg_EXMEM.d(MemToReg_IDEX);
    MemToReg_EXMEM.q(memToReg_EXMEM); // TODO: where use?

    // adderRight buffer EX/MEM
    myregister<0> AdderRight_EXMEM("adderRight_EXMEM");
    AdderRight_EXMEM.clk(clock);
    AdderRight_EXMEM.ld(adderRightLd_EXMEM); // TODO: when CLK = 0
    AdderRight_EXMEM.clr(adderRighClr_EXMEM); // TODO: when?
    AdderRight_EXMEM.d(adderRight_out);
    AdderRight_EXMEM.q(adderRight_EXMEM);

    // instruction buffer EX/MEM
    myregister<0> Instruction_EXMEM("Instruction_EXMEM");
    Instruction_EXMEM.clk(clock);
    Instruction_EXMEM.ld(instructionMemoryLd_EXMEM); // TODO: when CLK = 0
    Instruction_EXMEM.clr(instructionMemoryClr_EXMEM); // TODO: when?
    Instruction_EXMEM.d(instructionMemory_IDEX);
    Instruction_EXMEM.q(instructionMemory_EXMEM);

    // Ula result buffer EX/MEM
    myregister<0> UlaResult_EXMEM("UlaResult_EXMEM");
    UlaResult_EXMEM.clk(clock);
    UlaResult_EXMEM.ld(ulaResultLd_EXMEM); // TODO: when CLK = 0
    UlaResult_EXMEM.clr(ulaResultClr_EXMEM); // TODO: when?
    UlaResult_EXMEM.d(ula_out);
    UlaResult_EXMEM.q(ulaResult_EXMEM);

    mysigextender<bool, myword> signalExtend0("signalExtend0");
    signalExtend0.A(ula_zero);
    signalExtend0.S(ula_zero_myword);

    // Zero buffer EX/MEM
    myregister<0> Zero_EXMEM("Zero_EXMEM");
    Zero_EXMEM.clk(clock);
    Zero_EXMEM.ld(zeroLd_EXMEM); // TODO: when CLK = 0
    Zero_EXMEM.clr(zeroClr_EXMEM); // TODO: when?
    Zero_EXMEM.d(ula_zero_myword);
    Zero_EXMEM.q(zero_EXMEM);

    // data read 2 buffer EX/MEM
    myregister<0> DataRead2_EXMEM("DataRead2_EXMEM");
    DataRead2_EXMEM.clk(clock);
    DataRead2_EXMEM.ld(dataRead2Ld_EXMEM); // TODO: when CLK = 0
    DataRead2_EXMEM.clr(dataRead2Clr_EXMEM); // TODO: when?
    DataRead2_EXMEM.d(dataRead2_IDEX);
    DataRead2_EXMEM.q(dataRead2_EXMEM);

    // --------------- MEM/WB sector ---------------

    myprePCSrc prePCSrc("PCScrc");
    prePCSrc.PCSrc(PCSrc);
    prePCSrc.Ula_out(ula_out);
    prePCSrc.opcode(opCode_EXMEM);
    prePCSrc.PCSrc_(PCSrc_);

    mymemory<0> DataMemory("DataMemory");
    DataMemory.read(memRead_EXMEM);
    DataMemory.write(memWrite_EXMEM);
    DataMemory.data(dataRead2_EXMEM);
    DataMemory.addr(ulaResult_EXMEM);
    DataMemory.out(dataMemory_out);
    DataMemory.clk(clock);

    load_memory(DataMemory, "-");

    // RegWrite buffer EX/MEM
    myregister<0> RegWrite_MEMWB("RegWrite_MEMWB");
    RegWrite_MEMWB.clk(clock);
    RegWrite_MEMWB.ld(regWriteLd_MEMWB); // TODO: when CLK = 0
    RegWrite_MEMWB.clr(regWriteClr_MEMWB); // TODO: when?
    RegWrite_MEMWB.d(RegDest_EXMEM);
    RegWrite_MEMWB.q(regWrite_MEMWB); // TODO: where use?

    // MemToReg buffer EX/MEM
    myregister<0> MemToReg_MEMWB("MemToReg_MEMWB");
    MemToReg_MEMWB.clk(clock);
    MemToReg_MEMWB.ld(memToRegLd_MEMWB); // TODO: when CLK = 0
    MemToReg_MEMWB.clr(memToRegClr_MEMWB); // TODO: when?
    MemToReg_MEMWB.d(MemToReg_EXMEM);
    MemToReg_MEMWB.q(memToReg_MEMWB); // TODO: where use?

    // instruction buffer MEM/WB
    myregister<0> Instruction_MEMWB("Instruction_MEMWB");
    Instruction_MEMWB.clk(clock);
    Instruction_MEMWB.ld(instructionMemoryLd_MEMWB); // TODO: when CLK = 0
    Instruction_MEMWB.clr(instructionMemoryClr_MEMWB); // TODO: when?
    Instruction_MEMWB.d(instructionMemory_EXMEM);
    Instruction_MEMWB.q(instructionMemory_MEMWB);

    // MemoryRead buffer MEM/WB
    myregister<0> MemoryRead_MEMWB("MemoryRead_MEMWB");
    MemoryRead_MEMWB.clk(clock);
    MemoryRead_MEMWB.ld(memoryReadLd_MEMWB); // TODO: when CLK = 0
    MemoryRead_MEMWB.clr(memoryReadClr_MEMWB); // TODO: when?
    MemoryRead_MEMWB.d(dataMemory_out);
    MemoryRead_MEMWB.q(memoryRead_MEMWB);

    // Ula result buffer MEM/WB
    myregister<0> UlaResult_MEMWB("UlaResult_MEMWB");
    UlaResult_MEMWB.clk(clock);
    UlaResult_MEMWB.ld(ulaResultLd_MEMWB); // TODO: when CLK = 0
    UlaResult_MEMWB.clr(ulaResultClr_MEMWB); // TODO: when?
    UlaResult_MEMWB.d(ulaResult_EXMEM);
    UlaResult_MEMWB.q(ulaResult_MEMWB);

    // --------------- FINAL sector ---------------

    mymux<myword> DataMemoryMux("DataMemoryMux");
    DataMemoryMux.sel(memToReg_MEMWB);
    DataMemoryMux.in1(ulaResult_MEMWB);
    DataMemoryMux.in2(memoryRead_MEMWB);
    DataMemoryMux.S(DataMemoryMux_out);

	sc_start(15, SC_SEC);
}