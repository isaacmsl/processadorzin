#include "systemc.h"
#include "../../components/adder.h"
#include "../../global.h"
#include "test_adder_testbench.h"
#include "test_adder_monitor.h"

void test_adder() {
    
	sc_signal<myword> A, B, S;
	sc_signal<bool> CO;
	sc_clock clock("clk", 1, SC_SEC, 0.5, 0, SC_SEC, false);

	testbench<myword> Tb("Testbench");
	Tb.A(A);
	Tb.B(B);
	Tb.clk(clock);

	mon<myword> Monitor1("Monitor");
	Monitor1.A(A);
	Monitor1.B(B);
	Monitor1.S(S);
	Monitor1.CO(CO);
	Monitor1.clk(clock);

	myadder Somador("adder1");
	Somador.A(A);
	Somador.B(B);
	Somador.S(S);
	Somador.CO(CO);

	sc_start(5, SC_SEC);
}