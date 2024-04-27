#include "systemc.h"
#include "global.h"
#include "reader.h"
#include "components/adder.h"
#include "components/bitshifter.h"
#include "components/ulacontrol.h"
#include "components/control.h"
#include "components/instructionspliter.h"
#include "components/memory.h"
#include "components/mux.h"
#include "components/pc.h"
#include "components/registerbank.h"
#include "components/signalextender.h"
#include "components/ula.h"
#include "processor_monitor.h"



void processor() {
    
    sc_clock clock("clk", 1, SC_SEC, 0.5, 0, SC_SEC, false);

    // Signals

    sc_signal<bool> instructionMemory_read, MemRead, MemWrite, MemToReg, 
                    ula_zero, ula_carry,
                    RegDst, ALUSrc, RegWrite, PCSrc, InstMemWrite;
    
    sc_signal<myword> instructionMemory_out, dataMemory_out,
                        ula_out,
                        UlaMux_out, DataMemoryMux_out, pcMux_out,
                        data_read1, data_read2,
                        signExtend_out,
                        Left2BitShifter_out,
                        adderRight_out, adderLeft_out,
                        pc_out,
                        InstMemData;
    
    sc_signal<myaddressword> address_write,
                            RegisterMux_out,
                            instructionMemory_outA, instructionMemory_outB, instructionMemory_outC;

    sc_signal<myshortword> instructionMemory_outD;

    sc_signal<my6bitword> ALUop, instructionMemory_outE, instructionMemory_outF; // opcode, func

    sc_signal<myopword> ula_sel;

    // Monitor

    mon<myword> Monitor("Monitor");
	Monitor.clk(clock);
    Monitor.myword_out1(instructionMemory_out);
    Monitor.myword_out2(signExtend_out);
    Monitor.my6bit_out(instructionMemory_outF);
    Monitor.myshortword_out(instructionMemory_outD);
    Monitor.myword_out3(ula_out);
    Monitor.bit_out(ALUSrc);
    
    // --------------- processor ---------------

    instructionMemory_read.write(1);

    mymemory InstructionMemory("InstructionMemory");

    InstructionMemory.read(instructionMemory_read);
    InstructionMemory.write(InstMemWrite);
    InstructionMemory.data(InstMemData);
    InstructionMemory.addr(pc_out);
    InstructionMemory.out(instructionMemory_out);
    InstructionMemory.clk(clock);

    load_instructions(InstructionMemory, "-");

    // splitting instructionMemory_out to A,B,C ...
    myinstructionspliter InstructionSpliter("InstructionSpliter");
    InstructionSpliter.instruction(instructionMemory_out);
    InstructionSpliter.instructionMemory_outA(instructionMemory_outA);
    InstructionSpliter.instructionMemory_outB(instructionMemory_outB);
    InstructionSpliter.instructionMemory_outC(instructionMemory_outC);
    InstructionSpliter.instructionMemory_outD(instructionMemory_outD);
    InstructionSpliter.instructionMemory_outE(instructionMemory_outE);
    InstructionSpliter.instructionMemory_outF(instructionMemory_outF);

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

    mysigextender signalExtend("signalExtend");
    signalExtend.A(instructionMemory_outD);
    signalExtend.S(signExtend_out);

    mymux<myword> UlaMux("UlaMux");
    UlaMux.sel(ALUSrc);
    UlaMux.in1(data_read2);
    UlaMux.in2(signExtend_out);
    UlaMux.S(UlaMux_out);

    myulacontrol UlaControl("UlaControl");
    UlaControl.f(instructionMemory_outE);
    UlaControl.op(ALUop);
    UlaControl.S(ula_sel);

    myula Ula("Ula");
    Ula.alu_in1(data_read1);
    Ula.alu_in2(UlaMux_out);
    Ula.alu_sel(ula_sel);
    Ula.alu_out(ula_out);
    Ula.zero_out(ula_zero);
    Ula.c_out(ula_carry);
    Ula.clock(clock);

    mymemory DataMemory("DataMemory");
    DataMemory.read(MemRead);
    DataMemory.write(MemWrite);
    DataMemory.data(data_read2);
    DataMemory.addr(ula_out);
    DataMemory.out(dataMemory_out);
    DataMemory.clk(clock);

    mymux<myword> DataMemoryMux("DataMemoryMux");
    DataMemoryMux.sel(MemToReg);
    DataMemoryMux.in1(dataMemory_out);
    DataMemoryMux.in2(ula_out);
    DataMemoryMux.S(DataMemoryMux_out);

    // north part

    mypc pc("pc");
    pc.d(pcMux_out);
    pc.q(pc_out);
    pc.clk(clock);

    sc_signal<myword> four;
    four.write(myword(4));

    myadder adderLeft("adderLeft");
	adderLeft.A(pc_out);
	adderLeft.B(four);
	adderLeft.S(adderLeft_out);
    sc_signal<bool> left_co;adderLeft.CO(left_co);

    myshifter<2, false> Left2BitShifter("Left2BitShifter");
    Left2BitShifter.A(signExtend_out);
    Left2BitShifter.S(Left2BitShifter_out);

	myadder adderRight("adderRight");
	adderRight.A(adderLeft_out);
	adderRight.B(Left2BitShifter_out);
	adderRight.S(adderRight_out);
	sc_signal<bool> right_co;adderRight.CO(right_co);

    mymux<myword> pcMux("pcMux");
    pcMux.sel(PCSrc);
    pcMux.in1(adderLeft_out);
    pcMux.in2(adderRight_out);
    pcMux.S(pcMux_out);

	sc_start(15, SC_SEC);
}