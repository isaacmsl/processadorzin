#include "systemc.h"

template<typename T>
SC_MODULE(testbench) {
    sc_in<bool> Clk;
    sc_out<T> A;
    sc_out<bool> Clr, LoadSig; 

    void TbGen_word() {

        wait();

        Clr.write(false);
        LoadSig.write("1");

        wait();
        
        A.write("00000000000000000000000000010101");

        wait();

        LoadSig.write("0");

        wait();

        A.write("00000000000000000000001110000000");

        wait();

        Clr.write("1");

        
        wait();
        sc_stop();
    }

    SC_CTOR(testbench) {
        SC_THREAD(TbGen_word);
        sensitive << Clk.pos();
    }
};
