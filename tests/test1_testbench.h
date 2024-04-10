#include "systemc.h"

template<typename T>
SC_MODULE(testbench) {
    sc_in<bool> Clk;
    sc_out<T> A, B;

    void TbGen_bit() {
        A.write(false);
        B.write(false);

        wait();

        A.write(false);
        B.write(true);

        wait();

        A.write(true);
        B.write(false);

        wait();

        A.write(true);
        B.write(true);

        wait();

        sc_stop();
    }

    void TbGen_word() {

        wait();

        A.write("00000000000000000000000000000000");
        B.write("00000000000000000000000000000001");

        wait();

        A.write("00000000000000000000000000011000");
        B.write("00000000000000000000000000001001");

        wait();

        sc_stop();
    }

    SC_CTOR(testbench) {
        SC_THREAD(TbGen_word);
        sensitive << Clk.pos();
    }
};
