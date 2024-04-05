#include "systemc.h"
#include "components/arithmetic/myadder.h"
#include "global.h"

int sc_main(int argc, char* argv[]) {
    
	sc_signal<myword> ASig, BSig, SSig, COSig;
	sc_clock TestClk("TestClock", 10, SC_NS, 0.5);

	myadder Somador("adder1");
	Somador.A(ASig);
	Somador.B(BSig);
	Somador.S(SSig);
	Somador.CO(COSig);

	sc_start();

	return 0;
}
