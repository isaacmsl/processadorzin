#include "systemc.h"
#include "../global.h"

#include <iomanip>

template<int N, bool Right>
SC_MODULE(myshifter) {
    sc_in<myword> A;
    sc_out<myword> S;

    void m() {
        if (Right) {
            S.write(A.read() >> N);
        }
        else {
            S.write(A.read() << N);
        }
    }

    SC_CTOR(myshifter) {
        SC_METHOD(m);
		sensitive << A;
    }
};
