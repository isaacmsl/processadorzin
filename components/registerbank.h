#include "systemc.h"
#include "../global.h"
#include "register.h"

SC_MODULE(myregisterbank) {
    const static int banksize = 1 << MYADDRESSWORD_LENGTH;

    sc_in<bool> clk, write;
    sc_in<myword> data;
    sc_in<myaddressword> addr1, addr2, addr_write;
    sc_out<myword> out1, out2;
    std::array<myword, banksize> bank;

    void m() {
        if (clk.read()) {
            bank[ word_to_int(addr_write.read()) % banksize ] = data.read();
        } else if (!(clk.read()) && write.read()) {
            out1.write(bank[ word_to_int(addr1.read()) % banksize ]);
            out2.write(bank[ word_to_int(addr2.read()) % banksize ]);
        }
    }

    SC_CTOR(myregisterbank): clk("CLK") {
        SC_METHOD(m);
		sensitive << clk.pos();
    }
};
