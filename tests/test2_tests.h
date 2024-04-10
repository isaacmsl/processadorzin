#include "systemc.h"
#include "../global.h"
#include "monitors/mon2.h"
#include "test2_testbench.h"
#include "../components/register.h"

void test_2() {
    
	sc_signal<myword> ASig, SSig;
	sc_signal<bool> LoadSig, ClrSig;
	sc_clock TestClk("TestClock", 10, SC_NS, 0.1);

	testbench<myword> Tb("Testbench");
	Tb.A(ASig);
	Tb.Clr(ClrSig);
	Tb.LoadSig(LoadSig);
	Tb.Clk(TestClk);

	mon<myword> Monitor1("Monitor");
	Monitor1.A(ASig);
	Monitor1.Clr(ClrSig);
	Monitor1.LoadSig(LoadSig);
	Monitor1.S(SSig);
	Monitor1.Clk(TestClk);

	myregister Registrador("register1");
	Registrador.clk(TestClk);
	Registrador.clr(ClrSig);
	Registrador.ld(LoadSig);
	Registrador.d(ASig);
	Registrador.q(SSig);

	sc_start();
}