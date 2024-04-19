#include "systemc.h"
#include "../global.h"

SC_MODULE(myalucontrol) {
    sc_in<myword> op, f;
    sc_out<myword> S;

    void m() {
        S.write(op);
    }

    SC_CTOR(myalucontrol) {
        SC_METHOD(m);
		sensitive << op << f;
    }
};
