#include "systemc.h"
#include "../../components/memory.h"
#include "../../global.h"
#include "test_memory_testbench.h"
#include "test_memory_monitor.h"

void test_memory() {
    sc_signal<bool> write, read;
    sc_signal<myword> addr, data, out;
	sc_clock clock("clk", 1, SC_SEC, 0.5, 0, SC_SEC, false);

	testbench<myword> Tb("Testbench");
	Tb.write(write);
	Tb.read(read);
	Tb.addr(addr);
	Tb.data(data);
	Tb.clk(clock);

	mon<myword> Monitor1("Monitor");
	Monitor1.write(write);
	Monitor1.read(read);
	Monitor1.addr(addr);
	Monitor1.data(data);
	Monitor1.out(out);
	Monitor1.clk(clock);

	mymemory Memory("memory1");
	Memory.write(write);
	Memory.read(read);
	Memory.addr(addr);
	Memory.data(data);
	Memory.out(out);
	Memory.clk(clock);

	sc_start(5, SC_SEC);
}