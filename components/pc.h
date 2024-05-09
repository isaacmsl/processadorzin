#include "systemc.h"
#include "../global.h"

SC_MODULE(mypc) {
    sc_in<bool> clk;
    sc_in<myword> d;
    sc_out<myword> q;
    bool l = false;

    void m() {
        if (l) {
            pc_out.write(1);
            l = false;
        } else {
            q.write(d);
        }
        //std::cout << d << " pc\n";
    }

    SC_CTOR(mypc): clk("CLK") {
        SC_METHOD(m);
		sensitive << clk.pos();
    }
};
