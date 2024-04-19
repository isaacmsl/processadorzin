#include "systemc.h"
#include "../global.h"

SC_MODULE(mymux) {
    sc_in<bool> sel;
    sc_in<myword> in1, in2;
    sc_out<myword> S;

    void m() {
        S.write(sel ? in1 : in2);
    }

    SC_CTOR(mymux) {
        SC_METHOD(m);
		sensitive << sel << in1 << in2;
    }
};
