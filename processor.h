#include "systemc.h"
#include "global.h"
#include "components/adder.h"
#include "components/ulacontrol.h"
#include "components/control.h"
#include "components/memory.h"
#include "components/mux.h"
#include "components/pc.h"
#include "components/registerbank.h"
#include "components/signalextender.h"
#include "components/ula.h"


void processor() {
    
    sc_clock clock("clk", 1, SC_SEC, 0.5, 0, SC_SEC, false);

    // Signals

    sc_signal<bool> dataMemory_write, dataMemory_read, instructionMemory_read,
                    ula_zero, ula_carry,
                    RegDst;
    
    sc_signal<myword> instructionMemory_out, dataMemory_out, instructionMemory_addr, dataMemory_addr,
                        dataMemory_data,
                        ula_out, ula_sel,
                        address_read1, address_read2, address_write,
                        RegisterMux_out,
                        data_read1, data_read2;
                        

    // Components
    
    myregisterbank Registers("Registers"); // complete
    Registers.data(RegisterMux_out);
    Registers.addr1(address_read1);
    Registers.addr2(address_read2);
    Registers.addr_write(address_write);
    Registers.out1(data_read1);
    Registers.out2(data_read2);
    Registers.clk(clock);

    myula Ula("Ula"); // complete
    Ula.alu_in1(data_read1);
    Ula.alu_in2(data_read2);
    Ula.alu_sel(ula_sel);
    Ula.alu_out(ula_out);
    Ula.zero_out(ula_zero);
    Ula.c_out(ula_carry);

    mymemory InstructionMemory("InstructionMemory"); // complete
    InstructionMemory.read(instructionMemory_read);
    InstructionMemory.write(sc_signal<bool>(0));
    InstructionMemory.data(sc_signal<myword>(0));
    InstructionMemory.addr(instructionMemory_addr);
    InstructionMemory.out(instructionMemory_out);
    InstructionMemory.clk(clock);

    mymemory DataMemory("DataMemory"); // complete
    DataMemory.read(dataMemory_read);
    DataMemory.write(dataMemory_write);
    DataMemory.data(dataMemory_data);
    DataMemory.addr(dataMemory_addr);
    DataMemory.out(dataMemory_out);
    DataMemory.clk(clock);

    mycontrol Control("Control");
	Control.opcode(instructionMemory_out); // not the entire instruction!!!!!
    Control.zero(ula_zero);
    Control.MemWrite(dataMemory_write);
    Control.MemRead(dataMemory_read);
    Control.RegDst(RegDst);

    mymux RegisterMux("RegisterMux"); // complete
    RegisterMux.sel(RegDst);
    RegisterMux.in1(instructionMemory_out); // not the entire instruction!!!!!
    RegisterMux.in2(instructionMemory_out); // not the entire instruction!!!!!
    RegisterMux.S(RegisterMux_out);

    /*
	myadder Somador("adder1");
	Somador.A(A);
	Somador.B(B);
	Somador.S(S);
	Somador.CO(CO);
    */

	sc_start(15, SC_SEC);
}