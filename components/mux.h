#include "systemc.h"
#include "../global.h"

template<typename T>
SC_MODULE(mymux) {
    sc_in<bool> sel;
    sc_in<T> in1, in2;
    sc_out<T> S;

    void m() {
        S.write(sel ? in1 : in2);
    }

    SC_CTOR(mymux) {
        SC_METHOD(m);
		sensitive << sel << in1 << in2;
    }
};
