#include "systemc.h"

template<typename T>
SC_MODULE(testbench) {
    sc_in<bool> clk;
    sc_out<T> A, B;

    void m() {

        wait();

        A.write("0001");
        B.write("0001");

        wait();

        wait();

        A.write("1111");
        B.write("0001");

        wait();

        sc_stop();
    }

    SC_CTOR(testbench) {
        SC_THREAD(m);
        sensitive << clk.pos();
    }
};