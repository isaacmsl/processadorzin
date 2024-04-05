#include "systemc.h"

SC_MODULE(mynot) {
	sc_in<bool> A;
	sc_out<bool> S;

	void do_not() {
		S.write( (~A.read()) );
	}

	SC_CTOR(mynot) {
		SC_METHOD(do_not);
		sensitive << A << B;
	}
};
