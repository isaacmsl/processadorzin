#ifndef MUX_H
#define MUX_H

#include "systemc.h"
#include "../global.h"

template<typename T>
SC_MODULE(mymux) {
    sc_in<bool> sel, clk;
    sc_in<T> in1, in2;
    sc_out<T> S;

    void m() {
        S.write(sel.read() ? in2 : in1);
    }

    SC_CTOR(mymux) {
        SC_METHOD(m);
		sensitive << in2 << in1 << sel;
    }
};


// transformar UlaMux e Ula em um componente só??
#endif