#include "systemc.h"
#include "../../components/ula.h"
#include "../../global.h"
#include "test_ula_testbench.h"
#include "test_ula_monitor.h"

void test_ula() {
    
	sc_signal<myword> A, B, S, sel;
	sc_signal<bool> CO;
	sc_clock clock("clk", 1, SC_SEC, 0.5, 0, SC_SEC, false);

	testbench<myword> Tb("Testbench");
	Tb.sel(sel);
	Tb.A(A);
	Tb.B(B);
	Tb.clk(clock);

	mon<myword> Monitor1("Monitor");
	Monitor1.sel(sel);
	Monitor1.A(A);
	Monitor1.B(B);
	Monitor1.S(S);
	Monitor1.CO(CO);
	Monitor1.clk(clock);

	myula Ula("ula");
	Ula.alu_sel(sel);
	Ula.alu_in1(A);
	Ula.alu_in2(B);
	Ula.alu_out(S);
	Ula.c_out(CO);
	Ula.clock(clock);

	sc_start(5, SC_SEC);
}