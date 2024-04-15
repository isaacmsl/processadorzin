#include "systemc.h"
#include "../global.h"
#include "register.h"

SC_MODULE(myregisterbank) {
    sc_in<bool> clk;
    sc_in<myword> data;
    sc_in<sc_bv<8>> addr1, addr2, addr_write;
    sc_out<myword> out1, out2;
    std::array<myword, 8> bank;

    void m() {

        if (clk) {
            bank[ word_to_int(addr_write.read()) ] = data.read();
        }

        out1.write(bank[ word_to_int(addr1.read()) ]);
        out2.write(bank[ word_to_int(addr2.read()) ]);
    }

    SC_CTOR(myregisterbank): clk("CLK") {
        SC_METHOD(m);
		sensitive_pos << clk;
    }
};
