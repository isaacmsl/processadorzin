#include "systemc.h"
#include "../global.h"

SC_MODULE(myulacontrol) {
    sc_in<myword> op, f;
    sc_out<myword> S;

    void m() {
        S.write(op);
    }

    SC_CTOR(myulacontrol) {
        SC_METHOD(m);
		sensitive << op << f;
    }
};
