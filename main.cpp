#include "systemc.h"
//#include "tests/ula_testbench.h"
//#include "tests/test1_tests.h"
// #include "tests/test2_tests.h"
#include "tests/registerbank_test.h"

int sc_main(int argc, char* argv[]) {

	registerbank_test();

	return 0;
}