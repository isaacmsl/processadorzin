#include "systemc.h"
#include "../../components/mux.h"
#include "../../global.h"
#include "test_mux_testbench.h"
#include "test_mux_monitor.h"

void test_mux() {

	sc_signal<bool> sel, clk;
    sc_signal<myword> in1, in2, S;
	sc_clock clock("clk", 1, SC_SEC, 0.5, 0, SC_SEC, false);

	testbench<myword> Tb("Testbench");
	Tb.sel(sel);
	Tb.in1(in1);
	Tb.in2(in2);
	Tb.clk(clock);

	mymux<myword> Mux("Mux");
	Mux.sel(sel);
	Mux.clk(clk);
	Mux.in1(in1);
	Mux.in2(in2);
	Mux.S(S);

	mon_mux<myword> Monitor1("Monitor");
	Monitor1.sel(sel);
	Monitor1.A(in1);
	Monitor1.B(in2);
	Monitor1.S(S);
	Monitor1.clk(clock);

	sc_start(10, SC_SEC);
}