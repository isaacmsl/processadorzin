#include "systemc.h"
#include "../global.h"

#include <iomanip>

SC_MODULE(myprePCSrc) {
    sc_in<bool> PCSrc;
    sc_in<bool> UlaZero_out;
    //sc_in<my6bitword> opcode;
    sc_out<bool> PCSrc_out;

    // TODO: ajeitar isso
    void m() {

        /*
        int op_code = my_to_int<my6bitword>(opcode.read());

        if (op_code == op_jn) {
            PCSrc_out.write(PCSrc.read() || (word_to_int(Ula_out.read()) < 0));
        }
        else if (op_code == op_jz) {
            PCSrc_out.write(PCSrc.read() || (word_to_int(Ula_out.read()) == 0));
        }
        */

        PCSrc_out.write(UlaZero_out && PCSrc);
    }

    SC_CTOR(myprePCSrc) {
        SC_METHOD(m);
		sensitive << PCSrc << UlaZero_out;
    }
};
