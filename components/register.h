#include "systemc.h"
#include "../global.h"

template<int clk_type>
SC_MODULE(myregister) {
    sc_in<bool> clk, clr, ld;
    sc_in<myword> d;
    sc_out<myword> q;

    void m() {
        if (clk.read() == clk_type) {
            if (false) {//clr.read()
                q.write(0);
            } else if (true) { //l.read()
                q.write(d);
            }
        }
    }

    SC_CTOR(myregister): clk("CLK") {
        SC_METHOD(m);
		sensitive << clk;
    }
};
