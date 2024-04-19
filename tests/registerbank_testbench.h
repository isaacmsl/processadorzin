#include "systemc.h"

template<typename T>
SC_MODULE(testbench) {
    sc_in<bool> clk;
    sc_out<myword> data;
    sc_out<myword> addr1, addr2, addr_write;

    void TbGen_word() {

        // Write data 
        wait();

        data.write("01000000000000000000000000000010");
        addr_write.write("00000001");
        
        // Read data
        wait();

        addr1.write("00000001");

        wait();

        sc_stop();
    }

    SC_CTOR(testbench) {
        SC_THREAD(TbGen_word);
        sensitive << clk.pos();
    }
};
