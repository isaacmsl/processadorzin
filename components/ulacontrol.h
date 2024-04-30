#include "systemc.h"
#include "../global.h"

SC_MODULE(myulacontrol) {
    sc_in<my6bitword> op, f;
    sc_out<my6bitword> S;

    void m() {

        // logic with f and op

        S.write(op);
    }

    SC_CTOR(myulacontrol) {
        SC_METHOD(m);
		sensitive << op << f;
    }
};
