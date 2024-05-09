#include "systemc.h"
#include "../global.h"

#include "monitor.h"
#include "IFID.h"
#include "IDEX.h"
#include "EXMEM.h"
#include "MEMWB.h"

#include "variables.h"

inline void processor() {

    sc_clock myclock("clk_legal", 1, SC_SEC, 0.5, 0, SC_SEC, false);

    //
    // ---------------------- MONITOR ----------------------
    //

    mon<myword> Monitor("Monitor");
	Monitor.clk(myclock);
    Monitor.myword_out1(dataRead2_IDEX);
    Monitor.my6bit_out(ALUop); //instructionMemory_outF
    Monitor.myadd_out(RegisterMux_out_MEMWB);//RegisterMux_out_MEMWB  instructionMemory_outA
    Monitor.myshortword_out(instructionMemory_outD); //aka opcode
    Monitor.myword_out2(pc_out);
    Monitor.myword_out3(signalExtend_IDEX); //DataMemoryMux_out
    Monitor.bit_out(RegWrite);
    
    //
    // ---------------------- PROCESSOR ----------------------
    //

    myIFID ifid("ifid");
    ifid.myclock(myclock);

    myIDEX idex("idex");
    idex.myclock(myclock);

    myEXMEM exmen("exmen");
    exmen.myclock(myclock);

    myMEMWB memwb("memwb");
    memwb.myclock(myclock);

    sc_start(15, SC_SEC);
}