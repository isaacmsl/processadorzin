#include "systemc.h"
#include "../global.h"

SC_MODULE(myregister) {
    sc_in<bool> clk, clr, ld;
    sc_in<myword> d;
    sc_out<myword> q;

    void m() {
        if (clr) {
            q.write("00000000000000000000000000000000");
        } else if (clk && ld) {
            q.write(d);
        }
    }

    SC_CTOR(myregister): clk("CLK"), clr("CLR") {
        SC_METHOD(m);
        sensitive << clr;
		sensitive_pos << clk;
    }
};
