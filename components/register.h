#ifndef REGISTER_H
#define REGISTER_H

#include "systemc.h"
#include "../global.h"

template<typename dq_type>
SC_MODULE(myregister) {
    sc_in<bool> clk, clr, ld;
    sc_in<dq_type> d;
    sc_out<dq_type> q;

    void m() {
        if (false) {//clr.read()
            q.write(0);
        } else if (true) { //l.read()
            q.write(d);
        }
    }

    SC_CTOR(myregister): clk("CLK") {
        SC_METHOD(m);
		sensitive << clk.pos();
    }
};

#endif
