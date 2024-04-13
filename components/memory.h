#include "systemc.h"
#include "../global.h"

SC_MODULE(mymemory) {
    sc_in<bool> clk, write;
    sc_in<myword> addr, info;
    sc_out<myword> out;
    std::array<myword, 8*8> ram_array;

    void m() {

        // getting addr as int
        int addr_as_int = 0;
        myword myword_addr = addr.read();
        for (int i{myword_addr.length() - 1};i >= 0;i --) {
            addr_as_int += myword_addr.get_bit(i) << (i - myword_addr.length() - 1);
        }

        // writting
        if (clk && write) {
            ram_array[addr_as_int] = info.read();
        } 

        // getting information at addr_as_int
        out.write(ram_array[addr_as_int]);
    }

    SC_CTOR(mymemory): clk("CLK") {
        SC_METHOD(m);
		sensitive_pos << clk;
    }
};
