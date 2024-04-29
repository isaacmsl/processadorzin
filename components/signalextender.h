#include "systemc.h"
#include "../global.h"

#include <iomanip>

template<typename a, typename b>
SC_MODULE(mysigextender) {
    sc_in<a> A;
    sc_out<b> S;

    void m() {
        S.write(A.read());
    }

    SC_CTOR(mysigextender) {
        SC_METHOD(m);
		sensitive << A;
    }
};
