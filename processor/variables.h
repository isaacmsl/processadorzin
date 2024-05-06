#ifndef PROCESSOR_VARIABLES_H
#define PROCESSOR_VARIABLES_H

#include "systemc.h"
#include "../global.h"

// Signals

sc_clock myclock("clk", 1, SC_SEC, 0.5, 0, SC_SEC, false);

//
// ---------------------- BOOL ----------------------
//

sc_signal<bool>

ula_zero, ula_carry,
MemRead, MemWrite, MemToReg, RegDst, ALUSrc, RegWrite, Clr, PCSrc, PCSrc_, instMemWrite, instMemRead,

// ----------- IF/ID -----------
pcLd_IFID, pcClr_IFID, instructionMemoryLd_IFID, instructionMemoryClr_IFID,

// ----------- ID/EX -----------
pcLd_IDEX, pcClr_IDEX, instructionMemoryLd_IDEX, instructionMemoryClr_IDEX,
dataRead1Ld_IDEX, dataRead1Clr_IDEX, dataRead2Ld_IDEX, dataRead2Clr_IDEX,
signalExtendLd_IDEX, signalExtendClr_IDEX,
aluOpLd_IDEX, aluOpClr_IDEX, aluSrcLd_IDEX, aluSrcClr_IDEX, aluSrc_IDEX,

regDestLd_IDEX, regDestClr_IDEX, regDest_IDEX,
memWriteLd_IDEX, memWriteClr_IDEX, memReadLd_IDEX, memReadClr_IDEX, memRead_IDEX, memWrite_IDEX,
opCodeLd_IDEX, opCodeClr_IDEX,
regWriteLd_IDEX, regWriteClr_IDEX, regWrite_IDEX,
memToRegLd_IDEX, memToRegClr_IDEX, memToReg_IDEX,

instructionMemory_outBLd_IDEX, instructionMemory_outBClr_IDEX,
instructionMemory_outCLd_IDEX, instructionMemory_outCClr_IDEX,
instructionMemory_outELd_IDEX, instructionMemory_outEClr_IDEX,

// ----------- EX/MEM -----------
instructionMemoryLd_EXMEM, instructionMemoryClr_EXMEM, 
adderRightLd_EXMEM, adderRighClr_EXMEM, 
ulaResultLd_EXMEM, ulaResultClr_EXMEM,
zeroLd_EXMEM, zeroClr_EXMEM,
dataRead2Ld_EXMEM, dataRead2Clr_EXMEM,
registerMuxLd_EXMEM, registerMuxClr_EXMEM,

RegDest_EXMEM,
memRead_EXMEM, memWrite_EXMEM, memReadLd_EXMEM, memReadClr_EXMEM, memWriteLd_EXMEM, memWriteClr_EXMEM,
opCodeLd_EXMEM, opCodeClr_EXMEM,
regWriteLd_EXMEM, regWriteClr_EXMEM, regWrite_EXMEM,
memToReg_EXMEM, memToRegLd_EXMEM, memToRegClr_EXMEM,

// ----------- MEM/WB -----------
ulaResultLd_MEMWB, ulaResultClr_MEMWB,
memoryReadLd_MEMWB, memoryReadClr_MEMWB,
instructionMemoryLd_MEMWB, instructionMemoryClr_MEMWB,
regWrite_MEMWB, memToReg_MEMWB, memRead_MEMWB, memWrite_MEMWB, opCode_MEMWB,
regWriteLd_MEMWB, regWriteClr_MEMWB, memToRegLd_MEMWB, memToRegClr_MEMWB,
registerMuxLd_MEMWB, registerMuxClr_MEMWB;

//
// ---------------------- MYWORD ----------------------
//

sc_signal<myword>

data_read1, data_read2,
ula_zero_myword, instMemData,
instructionMemory_out, dataMemory_out,
ula_out, pc_out, signExtend_out, BitShifter_out,
adderRight_out, adderLeft_out,
ulaMux_out, DataMemoryMux_out, pcMux_out,

// ----------- IF/ID -----------

instructionMemory_IFID, pc_IFID,

// ----------- ID/EX -----------

instructionMemory_IDEX, pc_IDEX, dataRead1_IDEX, dataRead2_IDEX, signalExtend_IDEX,

// ----------- EX/MEM -----------

adderRight_EXMEM, instructionMemory_EXMEM,
ulaResult_EXMEM, zero_EXMEM,
aluOp_EXMEM, aluSrc_EXMEM, dataRead2_EXMEM,

// ----------- MEM/WB -----------

ulaResult_MEMWB,
memoryRead_MEMWB, instructionMemory_MEMWB;

//
// ---------------------- MYADDRESSWORD ----------------------
//

sc_signal<myaddressword> 

RegisterMux_out, RegisterMux_out_EXMEM, RegisterMux_out_MEMWB,
instructionMemory_outA, instructionMemory_outB, instructionMemory_outC,
instructionMemory_outB_IDEX, instructionMemory_outC_IDEX;

//
// ---------------------- MYSHORTWORD ----------------------
//

sc_signal<myshortword> 

instructionMemory_outD;

//
// ---------------------- MY6BIT ----------------------
//

sc_signal<my6bitword> 

instructionMemory_outE, instructionMemory_outF, // opcode, func
instructionMemory_outE_IDEX,
ALUop, 

aluOp_IDEX, opCode_IDEX, 
opCode_EXMEM,
aluOp_MEMWB;


#endif