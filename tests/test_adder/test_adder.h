#include "systemc.h"
#include "../../components/myadder.h"
#include "../../global.h"
#include "test_adder_testbench.h"
#include "test_adder_monitor.h"

void test_adder() {
    
	sc_signal<myword> ASig, BSig, SSig;
	sc_signal<bool> COSig;
	sc_clock clock("clock", 10, 0.5, 0.1);

	testbench<myword> Tb("Testbench");
	Tb.A(ASig);
	Tb.B(BSig);
	Tb.clk(clock);

	mon<myword> Monitor1("Monitor");
	Monitor1.A(ASig);
	Monitor1.B(BSig);
	Monitor1.S(SSig);
	Monitor1.CO(COSig);
	Monitor1.clk(clock);

	myadder Somador("adder1");
	Somador.A(ASig);
	Somador.B(BSig);
	Somador.S(SSig);
	Somador.CO(COSig);

	sc_start();
}