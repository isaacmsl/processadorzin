#include "systemc.h"
#include "../global.h"

SC_MODULE(mymemory) {
    sc_in<bool> clk, write, read;
    sc_in<myword> addr, data;
    sc_out<myword> out;
    std::array<myword, 1 << MYWORD_LENGTH> ram_array;

    void m() {
        // getting addr as int
        int addr_as_int = word_to_int(addr.read());
        // writting
        if (write) {
            ram_array[addr_as_int] = data.read();
        } else if (read) {
            // reading
            out.write(ram_array[addr_as_int]);
        }
    }

    SC_CTOR(mymemory): clk("CLK") {
        SC_METHOD(m);
		sensitive << clk;
    }
};
