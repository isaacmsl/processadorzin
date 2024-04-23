#include "systemc.h"

template<typename T>
SC_MODULE(testbench) {
    sc_in<bool> clk;
    sc_out<bool> write, read;
    sc_out<T> addr, data;

    void m() {

        // Write data to memory
        write.write(1);
        read.write(0);
        data.write("01000000000000000000000000000010");
        addr.write("00000001");

        wait();

        // Read data from memory
        write.write(0);
        read.write(1);

        wait();

        // Read data from memory another position
        addr.write("00000100");

        wait();

        sc_stop();
    }

    SC_CTOR(testbench) {
        SC_THREAD(m);
        sensitive << clk;
    }
};