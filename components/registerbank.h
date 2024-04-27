#ifndef REGISTERBANK_H
#define REGISTERBANK_H

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
        if (clk.read() && write.read()) {
            bank[ my_to_int<myaddressword>(addr_write.read()) % banksize ] = data.read();

        } else {
            out1.write(bank[ my_to_int<myaddressword>(addr1.read()) % banksize ]);
            out2.write(bank[ my_to_int<myaddressword>(addr2.read()) % banksize ]);
        }

        //std::cout << bank[1] << '\n';
    }

    SC_CTOR(myregisterbank): clk("CLK") {
        SC_METHOD(m);
		sensitive << clk.pos() << addr1 << addr2 << data << addr_write << write;
    }
};

#endif