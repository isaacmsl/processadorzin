#include "systemc.h"
#include "../global.h"

SC_MODULE(mymemory) {
    const static int memSize = 1 << 10;

    sc_in<bool> clk, write, read;
    sc_in<myword> addr, data;
    sc_out<myword> out;
    std::array<myword, memSize> ram_array;

    void m() {
        // getting addr as int
        int addr_as_int = word_to_int(addr.read())  % (memSize);
        // writting
        if (write.read()) {
            ram_array[addr_as_int] = data.read();
        } else if (read.read()) {
            // reading
            out.write(ram_array[addr_as_int]);
        }
    }

    SC_CTOR(mymemory): clk("CLK") {
        SC_METHOD(m);
		sensitive << clk;
    }
};
