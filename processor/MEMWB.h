#include "systemc.h"
#include "variables.h"
#include "../global.h"

#include "../components/prePCSrc.h"
#include "../components/memory.h"
#include "../components/register.h"
#include "../components/mux.h"

#include "loader.h"

// --------------- MEM/WB sector ---------------

SC_MODULE(myMEMWB) {

    sc_in<bool> myclock;

    mymux<myword> DataMemoryMux{"DataMemoryMux"};
    myregister<myword> UlaResult_MEMWB{"UlaResult_MEMWB"};
    myregister<myword> MemoryRead_MEMWB{"MemoryRead_MEMWB"};
    myregister<myword> Instruction_MEMWB{"Instruction_MEMWB"};
    myregister<bool> MemToReg_MEMWB{"MemToReg_MEMWB"};
    myregister<bool> RegWrite_MEMWB{"RegWrite_MEMWB"};
    myregister<myaddressword> RegisterMux_MEMWB{"RegisterMux_MEMWB"};
    mymemory<0> DataMemory{"DataMemory"};
    myprePCSrc prePCSrc{"PCScrc"};


    SC_CTOR(myMEMWB) {

        prePCSrc.PCSrc(PCSrc);
        prePCSrc.Ula_out(ula_out);
        prePCSrc.opcode(opCode_EXMEM);
        prePCSrc.PCSrc_(PCSrc_);

        DataMemory.read(memRead_EXMEM);
        DataMemory.write(memWrite_EXMEM);
        DataMemory.data(dataRead2_EXMEM);
        DataMemory.addr(ulaResult_EXMEM);
        DataMemory.out(dataMemory_out);
        DataMemory.clk(myclock);

        load_memory(DataMemory, "-");

        // RegWrite buffer EX/MEM
        RegWrite_MEMWB.clk(myclock);
        RegWrite_MEMWB.ld(regWriteLd_MEMWB); // TODO: when CLK = 0
        RegWrite_MEMWB.clr(regWriteClr_MEMWB); // TODO: when?
        RegWrite_MEMWB.d(regWrite_IDEX);
        RegWrite_MEMWB.q(regWrite_MEMWB); // TODO: where use?

        // MemToReg buffer EX/MEM
        MemToReg_MEMWB.clk(myclock);
        MemToReg_MEMWB.ld(memToRegLd_MEMWB); // TODO: when CLK = 0
        MemToReg_MEMWB.clr(memToRegClr_MEMWB); // TODO: when?
        MemToReg_MEMWB.d(memToReg_EXMEM);
        MemToReg_MEMWB.q(memToReg_MEMWB); // TODO: where use?

        // instruction buffer MEM/WB
        Instruction_MEMWB.clk(myclock);
        Instruction_MEMWB.ld(instructionMemoryLd_MEMWB); // TODO: when CLK = 0
        Instruction_MEMWB.clr(instructionMemoryClr_MEMWB); // TODO: when?
        Instruction_MEMWB.d(instructionMemory_EXMEM);
        Instruction_MEMWB.q(instructionMemory_MEMWB);

        // MemoryRead buffer MEM/WB
        MemoryRead_MEMWB.clk(myclock);
        MemoryRead_MEMWB.ld(memoryReadLd_MEMWB); // TODO: when CLK = 0
        MemoryRead_MEMWB.clr(memoryReadClr_MEMWB); // TODO: when?
        MemoryRead_MEMWB.d(dataMemory_out);
        MemoryRead_MEMWB.q(memoryRead_MEMWB);

        // Ula result buffer MEM/WB
        UlaResult_MEMWB.clk(myclock);
        UlaResult_MEMWB.ld(ulaResultLd_MEMWB); // TODO: when CLK = 0
        UlaResult_MEMWB.clr(ulaResultClr_MEMWB); // TODO: when?
        UlaResult_MEMWB.d(ulaResult_EXMEM);
        UlaResult_MEMWB.q(ulaResult_MEMWB);


        // RegisterMux buffer MEM/WB
        RegisterMux_MEMWB.clk(myclock);
        RegisterMux_MEMWB.ld(registerMuxLd_MEMWB);
        RegisterMux_MEMWB.clr(registerMuxClr_MEMWB);
        RegisterMux_MEMWB.d(RegisterMux_out_EXMEM);
        RegisterMux_MEMWB.q(RegisterMux_out_MEMWB);

        // --------------- FINAL sector ---------------

        DataMemoryMux.sel(memToReg_MEMWB);
        DataMemoryMux.in1(memoryRead_MEMWB);
        DataMemoryMux.in2(ulaResult_MEMWB);
        DataMemoryMux.S(DataMemoryMux_out);

    }
};