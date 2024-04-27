#include "systemc.h"
#include "../global.h"

#include <iomanip>

SC_MODULE(mysigextender) {
    sc_in<myshortword> A;
    sc_out<myword> S;

    void m() {
        S.write(A.read());
    }

    SC_CTOR(mysigextender) {
        SC_METHOD(m);
		sensitive << A;
    }
};
