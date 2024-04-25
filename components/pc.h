#include "systemc.h"
#include "../global.h"

SC_MODULE(mypc) {
    sc_in<bool> clk;
    sc_in<mipsword> d;
    sc_out<mipsword> q;

    void m() {
        q.write(d);
    }

    SC_CTOR(mypc): clk("CLK") {
        SC_METHOD(m);
		sensitive << clk.pos();
    }
};
