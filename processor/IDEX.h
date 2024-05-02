#include "systemc.h"
#include "variables.h"
#include "../global.h"

#include "../components/memory.h"
#include "../components/mux.h"
#include "../components/registerbank.h"
#include "../components/control.h"
#include "../components/signalextender.h"

#include "loader.h"

// --------------- ID/EX sector ---------------

SC_MODULE(myIDEX) {

    sc_in<bool> myclock;

    mycontrol Control{"Control"};
    myregister<my6bitword> AluOp_IDEX{"AluOp_IDEX"};
    mysigextender<myshortword, myword> signalExtend{"signalExtend"};
    myregisterbank Registers{"Registers"};
    myregister<bool> AluSrc_IDEX{"AluSrc_IDEX"};
    myregister<bool> RegDest_IDEX{"RegDest_IDEX"};
    myregister<bool> MemRead_IDEX{"MemRead_IDEX"};
    myregister<bool> MemWrite_IDEX{"MemWrite_IDEX"};
    myregister<myword> SignalExtend_IDEX{"SignalExtend_IDEX"};
    myregister<myword> DataRead2_IDEX{"DataRead2_IDEX"};
    myregister<myword> DataRead1_IDEX{"DataRead1_IDEX"};
    myregister<myword> Instruction_IDEX{"Instruction_IDEX"};
    myregister<myword> PC_IDEX{"PC_IDEX"};
    myregister<bool> MemToReg_IDEX{"MemToReg_IDEX"};
    myregister<bool> RegWrite_IDEX{"RegWrite_IDEX"};
    myregister<my6bitword> OpCode_IDEX{"OpCode_IDEX"};

    SC_CTOR(myIDEX) {

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

        Registers.write(regWrite_MEMWB);
        Registers.data(DataMemoryMux_out);
        Registers.addr1(instructionMemory_outA);
        Registers.addr2(instructionMemory_outB);
        Registers.addr_write(RegisterMux_out);
        Registers.out1(data_read1);
        Registers.out2(data_read2);
        Registers.clk(myclock);

        load_registers(Registers, "-");

        signalExtend.A(instructionMemory_outD);
        signalExtend.S(signExtend_out);

        // AluOp buffer ID/EX
        AluOp_IDEX.clk(myclock);
        AluOp_IDEX.ld(aluOpLd_IDEX); // TODO: when CLK = 0
        AluOp_IDEX.clr(aluOpClr_IDEX); // TODO: when?
        AluOp_IDEX.d(ALUop);
        AluOp_IDEX.q(aluOp_IDEX); // TODO: where use?

        // AluSrc buffer ID/EX
        AluSrc_IDEX.clk(myclock);
        AluSrc_IDEX.ld(aluSrcLd_IDEX); // TODO: when CLK = 0
        AluSrc_IDEX.clr(aluSrcClr_IDEX); // TODO: when?
        AluSrc_IDEX.d(ALUSrc);
        AluSrc_IDEX.q(aluSrc_IDEX);

        // RegDest buffer ID/EX
        RegDest_IDEX.clk(myclock);
        RegDest_IDEX.ld(regDestLd_IDEX); // TODO: when CLK = 0
        RegDest_IDEX.clr(regDestClr_IDEX); // TODO: when?
        RegDest_IDEX.d(RegDst);
        RegDest_IDEX.q(regDest_IDEX); // TODO: where use?

        // MemRead buffer ID/EX
        MemRead_IDEX.clk(myclock);
        MemRead_IDEX.ld(memReadLd_IDEX); // TODO: when CLK = 0
        MemRead_IDEX.clr(memReadClr_IDEX); // TODO: when?
        MemRead_IDEX.d(MemRead);
        MemRead_IDEX.q(memRead_IDEX); // TODO: where use? 

        // MemWrite buffer ID/EX
        MemWrite_IDEX.clk(myclock);
        MemWrite_IDEX.ld(memWriteLd_IDEX); // TODO: when CLK = 0
        MemWrite_IDEX.clr(memWriteClr_IDEX); // TODO: when?
        MemWrite_IDEX.d(MemWrite);
        MemWrite_IDEX.q(memWrite_IDEX); // TODO: where use?  

        // OpCode buffer ID/EX
        OpCode_IDEX.clk(myclock);
        OpCode_IDEX.ld(opCodeLd_IDEX); // TODO: when CLK = 0
        OpCode_IDEX.clr(opCodeClr_IDEX); // TODO: when?
        OpCode_IDEX.d(instructionMemory_outF);
        OpCode_IDEX.q(opCode_IDEX); // TODO: where use?

        // RegWrite buffer ID/EX
        RegWrite_IDEX.clk(myclock);
        RegWrite_IDEX.ld(regWriteLd_IDEX); // TODO: when CLK = 0
        RegWrite_IDEX.clr(regWriteClr_IDEX); // TODO: when?
        RegWrite_IDEX.d(RegWrite);
        RegWrite_IDEX.q(regWrite_IDEX); // TODO: where use?

        // MemToReg buffer ID/EX
        MemToReg_IDEX.clk(myclock);
        MemToReg_IDEX.ld(memToRegLd_IDEX); // TODO: when CLK = 0
        MemToReg_IDEX.clr(memToRegClr_IDEX); // TODO: when?
        MemToReg_IDEX.d(MemToReg);
        MemToReg_IDEX.q(memToReg_IDEX); // TODO: where use?

        // incremented pc buffer ID/EX
        PC_IDEX.clk(myclock);
        PC_IDEX.ld(pcLd_IDEX); // TODO: when CLK = 0
        PC_IDEX.clr(pcClr_IDEX); // TODO: when?
        PC_IDEX.d(pc_IFID);
        PC_IDEX.q(pc_IDEX); // TODO: where use?

        // instruction buffer ID/EX
        Instruction_IDEX.clk(myclock);
        Instruction_IDEX.ld(instructionMemoryLd_IDEX); // TODO: when CLK = 0
        Instruction_IDEX.clr(instructionMemoryClr_IDEX); // TODO: when?
        Instruction_IDEX.d(instructionMemory_IFID);
        Instruction_IDEX.q(instructionMemory_IDEX);

        // data read 1 buffer ID/EX
        DataRead1_IDEX.clk(myclock);
        DataRead1_IDEX.ld(dataRead1Ld_IDEX); // TODO: when CLK = 0
        DataRead1_IDEX.clr(dataRead1Clr_IDEX); // TODO: when?
        DataRead1_IDEX.d(data_read1);
        DataRead1_IDEX.q(dataRead1_IDEX);

        // data read 2 buffer ID/EX
        DataRead2_IDEX.clk(myclock);
        DataRead2_IDEX.ld(dataRead2Ld_IDEX); // TODO: when CLK = 0
        DataRead2_IDEX.clr(dataRead2Clr_IDEX); // TODO: when?
        DataRead2_IDEX.d(data_read2);
        DataRead2_IDEX.q(dataRead2_IDEX);

        // signal extend buffer ID/EX
        SignalExtend_IDEX.clk(myclock);
        SignalExtend_IDEX.ld(signalExtendLd_IDEX); // TODO: when CLK = 0
        SignalExtend_IDEX.clr(signalExtendClr_IDEX); // TODO: when?
        SignalExtend_IDEX.d(signExtend_out);
        SignalExtend_IDEX.q(signalExtend_IDEX);

    }
};