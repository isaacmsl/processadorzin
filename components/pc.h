#include "systemc.h"
#include "../global.h"

SC_MODULE(mypc) {
    sc_in<bool> clk;
    sc_in<myword> d;
    sc_out<myword> q;

    void m() {
        q.write(d);
    }

    SC_CTOR(mypc): clk("CLK") {
        SC_METHOD(m);
		sensitive << clk.pos();
    }
};
