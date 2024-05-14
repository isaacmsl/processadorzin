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
    Monitor.myword_out1(pc_out);
    Monitor.myshortword_out(instructionMemory_outD); //aka opcode
    Monitor.my6bit_out(instructionMemory_outF); //instructionMemory_outF
    Monitor.myadd_out(instructionMemory_outB);//RegisterMux_out_MEMWB
    Monitor.myword_out2(ula_out);
    Monitor.myword_out3(pcMux_out); //DataMemoryMux_out
    Monitor.bit_out(PCSrc_outMEMWB);
    Monitor.names = {"pc_out", "imm", "instF", "instB", "ula_out", "pcMux", "PCSrc"};
    Monitor.regprint_inds = {};//{0, 1, 2, 3, 4};
    Monitor.datamemory_inds = {};
    Monitor.instmemory_inds = {0, 1, 2, 3, 4};
    
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