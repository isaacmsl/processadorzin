#include "systemc.h"
#include "../logic/myand.h"
#include "../logic/myxor.h"
#include "../../global.h"

SC_MODULE(myadder_1bit) {
    sc_in<bool> A, B;
    sc_out<bool> S;
    sc_out<bool> CO;
    myand n1;
    myxor x2;

    SC_CTOR(myadder_1bit): n1("N1"), x2("X2") {
        n1.A(A);
        n1.B(B);
        n1.CO(CO);

        x2.A(A);
        x2.B(B);
        x2.S(S);
    }
};
