#include "systemc.h"
#include "../global.h"

#include <iomanip>

SC_MODULE(mysigextender) {
    sc_in<myword> A;
    sc_out<mylongword> S;

    void m() {
        S.write(A.read());
    }

    SC_CTOR(mysigextender) {
        SC_METHOD(m);
		sensitive << A;
    }
};
