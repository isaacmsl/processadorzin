#include "systemc.h"

SC_MODULE(mycmp) {
	sc_in<bool> A, B;
	sc_out<bool> S;

	void do_cmp() {
		S.write( (A.read() = B.read()) );
	}

	SC_CTOR(mycmp) {
		SC_METHOD(do_cmp);
		sensitive << A << B;
	}
};
