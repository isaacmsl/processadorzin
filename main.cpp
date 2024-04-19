#include "systemc.h"
//#include "tests/ula_testbench.h"
//#include "tests/test1_tests.h"
// #include "tests/test2_tests.h"
#include "tests/test_adder/test_adder.h"

int sc_main(int argc, char* argv[]) {

	test_adder();

	return 0;
}