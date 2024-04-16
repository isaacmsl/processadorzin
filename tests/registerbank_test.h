#include "systemc.h"
#include "../global.h"
#include "monitors/mon_registerbank.h"
#include "registerbank_testbench.h"
#include "../components/registerbank.h"

void registerbank_test() {
    sc_signal<myword> data;
    sc_signal<sc_bv<8>> addr1, addr2, addr_write;
    sc_signal<myword> out1, out2;
	sc_clock TestClk("TestClock", 10, SC_NS, 0.1);

	testbench<myword> Tb("Testbench");
    Tb.clk(TestClk);
    Tb.data(data);
    Tb.addr1(addr1);
    Tb.addr2(addr2);
    Tb.addr_write(addr_write);

	mon_registerbank<myword> Monitor1("Monitor");
    Monitor1.clk(TestClk);
    Monitor1.data(data);
    Monitor1.addr1(addr1);
    Monitor1.addr2(addr2);
    Monitor1.addr_write(addr_write);
    Monitor1.out1(out1);
    Monitor1.out2(out2);
        
	myregisterbank Bank("Bank");
    Bank.clk(TestClk);
    Bank.data(data);
    Bank.addr1(addr1);
    Bank.addr2(addr2);
    Bank.addr_write(addr_write);
    Bank.out1(out1);
    Bank.out2(out2);
    
	sc_start();
}