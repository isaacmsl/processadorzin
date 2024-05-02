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
    Monitor.myword_out1(data_read2);
    Monitor.myword_out2(ula_out);
    Monitor.my6bit_out(instructionMemory_outF);
    Monitor.myadd_out(RegisterMux_out);
    Monitor.myshortword_out(instructionMemory_outD);
    Monitor.myword_out3(DataMemoryMux_out);
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