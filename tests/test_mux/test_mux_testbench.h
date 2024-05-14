#include "systemc.h"

template<typename T>
SC_MODULE(testbench) {
    sc_in<bool> clk;
    sc_out<bool> sel;
    sc_out<T> in1, in2;

    void m() {

        in1.write("1");
        in2.write("101");
        sel.write(1);

        wait();

        sel.write(0);

        wait();

        sc_stop();
    }

    SC_CTOR(testbench) {
        SC_THREAD(m);
        sensitive << clk.pos();
    }
};