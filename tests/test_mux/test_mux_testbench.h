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

        std::cout << "C?\n";

        wait();

        sel.write(0);

        std::cout << "A?\n";

        wait();

        std::cout << "B?\n";

        sc_stop();
    }

    SC_CTOR(testbench) {
        SC_THREAD(m);
        sensitive << clk.pos();
    }
};