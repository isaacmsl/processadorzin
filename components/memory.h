#include "systemc.h"
#include "../global.h"

SC_MODULE(mymemory) {
    sc_in<bool> clk, write;
    sc_in<myword> addr, info;
    sc_out<myword> out;
    std::array<myword, 8*8> ram_array;

    void m() {

        // getting addr as int
        int addr_as_int = word_to_int(addr.read());

        // writting
        if (clk && write) {
            ram_array[addr_as_int] = info.read();
        } else if (!clk) {
            // getting information at addr_as_int
            out.write(ram_array[addr_as_int]);
        }
    }

    SC_CTOR(mymemory): clk("CLK") {
        SC_METHOD(m);
		sensitive_pos << clk;
    }
};
