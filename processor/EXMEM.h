#include "systemc.h"
#include "variables.h"
#include "../global.h"

#include "../components/memory.h"
#include "../components/mux.h"
#include "../components/ula.h"
#include "../components/ulacontrol.h"
#include "../components/bitshifter.h"
#include "../components/register.h"
#include "../components/adder.h"
#include "../components/signalextender.h"

// --------------- EX/MEM sector ---------------

SC_MODULE(myEXMEM) {

    sc_in<bool> myclock;

    myregister<myword> DataRead2_EXMEM{"DataRead2_EXMEM"};
    myregister<myword> Zero_EXMEM{"Zero_EXMEM"};
    mysigextender<bool, myword> signalExtend0{"signalExtend0"};
    myregister<myword> UlaResult_EXMEM{"UlaResult_EXMEM"};
    myregister<myword> Instruction_EXMEM{"Instruction_EXMEM"};
    myregister<myword> AdderRight_EXMEM{"adderRight_EXMEM"};
    myregister<bool> MemToReg_EXMEM{"MemToReg_EXMEM"};
    myregister<bool> RegWrite_EXMEM{"RegWrite_EXMEM"};
    myregister<my6bitword> OpCode_EXMEM{"OpCode_EXMEM"};
    myregister<bool> MemWrite_EXMEM{"MemWrite_EXMEM"};
    myregister<bool> MemRead_EXMEM{"MemRead_EXMEM"};
    myadder adderRight{"adderRight"};
    myshifter<0, false> BitShifter{"BitShifter"};
    myula Ula{"Ula"};
    mymux<myaddressword> RegisterMux{"RegisterMux"};
    myulacontrol UlaControl{"UlaControl"};
    mymux<myword> UlaMux{"UlaMux"};
    sc_signal<bool> right_co;


    SC_CTOR(myEXMEM) {

        UlaMux.sel(aluSrc_IDEX);
        UlaMux.in1(dataRead2_IDEX);
        UlaMux.in2(signalExtend_IDEX);
        UlaMux.S(ulaMux_out);

        UlaControl.f(instructionMemory_outE);
        UlaControl.op(aluOp_IDEX);
        UlaControl.S(ula_sel);

        RegisterMux.sel(regDest_IDEX);
        RegisterMux.in1(instructionMemory_outB);
        RegisterMux.in2(instructionMemory_outC);
        RegisterMux.S(RegisterMux_out);

        Ula.alu_in1(dataRead1_IDEX);
        Ula.alu_in2(ulaMux_out);
        Ula.alu_sel(ula_sel);
        Ula.alu_out(ula_out);
        Ula.zero_out(ula_zero);
        Ula.c_out(ula_carry);
        Ula.clock(myclock);

        BitShifter.A(signalExtend_IDEX);
        BitShifter.S(BitShifter_out);

        adderRight.A(adderLeft_out);
        adderRight.B(BitShifter_out);
        adderRight.S(adderRight_out);
        adderRight.CO(right_co);

        // MemRead buffer EX/MEM
        MemRead_EXMEM.clk(myclock);
        MemRead_EXMEM.ld(memReadLd_EXMEM); // TODO: when CLK = 0
        MemRead_EXMEM.clr(memReadClr_EXMEM); // TODO: when?
        MemRead_EXMEM.d(memRead_IDEX);
        MemRead_EXMEM.q(memRead_EXMEM); // TODO: where use? 

        // MemWrite buffer EX/MEM
        MemWrite_EXMEM.clk(myclock);
        MemWrite_EXMEM.ld(memWriteLd_EXMEM); // TODO: when CLK = 0
        MemWrite_EXMEM.clr(memWriteClr_EXMEM); // TODO: when?
        MemWrite_EXMEM.d(memWrite_IDEX);
        MemWrite_EXMEM.q(memWrite_EXMEM); // TODO: where use?  

        // OpCode buffer EX/MEM
        OpCode_EXMEM.clk(myclock);
        OpCode_EXMEM.ld(opCodeLd_EXMEM); // TODO: when CLK = 0
        OpCode_EXMEM.clr(opCodeClr_EXMEM); // TODO: when?
        OpCode_EXMEM.d(opCode_IDEX);
        OpCode_EXMEM.q(opCode_EXMEM); // TODO: where use?

        // RegWrite buffer EX/MEM
        RegWrite_EXMEM.clk(myclock);
        RegWrite_EXMEM.ld(regWriteLd_EXMEM); // TODO: when CLK = 0
        RegWrite_EXMEM.clr(regWriteClr_EXMEM); // TODO: when?
        RegWrite_EXMEM.d(regDest_IDEX);
        RegWrite_EXMEM.q(regWrite_EXMEM); // TODO: where use?

        // MemToReg buffer EX/MEM
        MemToReg_EXMEM.clk(myclock);
        MemToReg_EXMEM.ld(memToRegLd_EXMEM); // TODO: when CLK = 0
        MemToReg_EXMEM.clr(memToRegClr_EXMEM); // TODO: when?
        MemToReg_EXMEM.d(memToReg_IDEX);
        MemToReg_EXMEM.q(memToReg_EXMEM); // TODO: where use?

        // adderRight buffer EX/MEM
        AdderRight_EXMEM.clk(myclock);
        AdderRight_EXMEM.ld(adderRightLd_EXMEM); // TODO: when CLK = 0
        AdderRight_EXMEM.clr(adderRighClr_EXMEM); // TODO: when?
        AdderRight_EXMEM.d(adderRight_out);
        AdderRight_EXMEM.q(adderRight_EXMEM);

        // instruction buffer EX/MEM
        Instruction_EXMEM.clk(myclock);
        Instruction_EXMEM.ld(instructionMemoryLd_EXMEM); // TODO: when CLK = 0
        Instruction_EXMEM.clr(instructionMemoryClr_EXMEM); // TODO: when?
        Instruction_EXMEM.d(instructionMemory_IDEX);
        Instruction_EXMEM.q(instructionMemory_EXMEM);

        // Ula result buffer EX/MEM
        UlaResult_EXMEM.clk(myclock);
        UlaResult_EXMEM.ld(ulaResultLd_EXMEM); // TODO: when CLK = 0
        UlaResult_EXMEM.clr(ulaResultClr_EXMEM); // TODO: when?
        UlaResult_EXMEM.d(ula_out);
        UlaResult_EXMEM.q(ulaResult_EXMEM);

        signalExtend0.A(ula_zero);
        signalExtend0.S(ula_zero_myword);

        // Zero buffer EX/MEM
        Zero_EXMEM.clk(myclock);
        Zero_EXMEM.ld(zeroLd_EXMEM); // TODO: when CLK = 0
        Zero_EXMEM.clr(zeroClr_EXMEM); // TODO: when?
        Zero_EXMEM.d(ula_zero_myword);
        Zero_EXMEM.q(zero_EXMEM);

        // data read 2 buffer EX/MEM
        DataRead2_EXMEM.clk(myclock);
        DataRead2_EXMEM.ld(dataRead2Ld_EXMEM); // TODO: when CLK = 0
        DataRead2_EXMEM.clr(dataRead2Clr_EXMEM); // TODO: when?
        DataRead2_EXMEM.d(dataRead2_IDEX);
        DataRead2_EXMEM.q(dataRead2_EXMEM);

    }
};