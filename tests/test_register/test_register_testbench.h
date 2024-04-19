#include "systemc.h"

template<typename T>
SC_MODULE(testbench) {
    sc_in<bool> clk;
    sc_out<bool> ld, clr;
    sc_out<T> d;

    void m() {

        d.write("0011");
        ld.write(0);
        clr.write(0);

        wait();

        d.write("0011");
        ld.write(1);
        clr.write(0);

        wait();

        d.write("1001");
        ld.write(0);
        clr.write(0);

        wait();

        d.write("1001");
        ld.write(0);
        clr.write(1);

        wait();

        wait();

        sc_stop();
    }

    SC_CTOR(testbench) {
        SC_THREAD(m);
        sensitive << clk;
    }
};