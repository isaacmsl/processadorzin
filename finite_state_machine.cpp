#include "systemc.h"

SC_MODULE(fsm) {

    sc_in<bool> clk, reset, is_valid, is_half;
    sc_out<bool> is_dispensed_coffee;

    SC_CTOR(fsm) {
        SC_THREAD(fsm_thread);
        sensitive << clk.pos();
    }

};