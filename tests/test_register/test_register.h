#include "systemc.h"
#include "../../components/register.h"
#include "../../global.h"
#include "test_register_testbench.h"
#include "test_register_monitor.h"

void test_register() {
    
	sc_signal<myword> d, q;
	sc_signal<bool> clr, ld;
	sc_clock clock("clk", 1, SC_SEC, 0.5, 0, SC_SEC, false);

	testbench<myword> Tb("Testbench");
	Tb.clr(clr);
	Tb.ld(ld);
	Tb.d(d);
	Tb.clk(clock);

	mon<myword> Monitor1("Monitor");
	Monitor1.clr(clr);
	Monitor1.ld(ld);
	Monitor1.d(d);
	Monitor1.q(q);
	Monitor1.clk(clock);

	myregister Registrador("adder1");
	Registrador.clr(clr);
	Registrador.ld(ld);
	Registrador.d(d);
	Registrador.q(q);
	Registrador.clk(clock);

	sc_start(5, SC_SEC);
}