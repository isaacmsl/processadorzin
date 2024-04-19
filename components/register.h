#include "systemc.h"
#include "../global.h"

SC_MODULE(myregister) {
    sc_in<bool> clk, clr, ld;
    sc_in<myword> d;
    sc_out<myword> q;

    void m() {
        if (clr) {
            q.write(0);
        } else if (ld) {
            q.write(d);
        }
    }

    SC_CTOR(myregister): clk("CLK") {
        SC_METHOD(m);
		sensitive << clk.pos();
    }
};
