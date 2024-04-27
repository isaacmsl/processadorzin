#include "systemc.h"
#include "../global.h"

SC_MODULE(myinstructionspliter) {
    sc_in<myword> instruction;
    sc_out<myaddressword> instructionMemory_outA, instructionMemory_outB, instructionMemory_outC;
    sc_out<myshortword> instructionMemory_outD;
    sc_out<my6bitword> instructionMemory_outE, instructionMemory_outF;

    void m() {
        myaddressword A, B, C;
        myshortword D;
        my6bitword E, F;
        myword instruction_ = instruction.read();

        for (int i{0}; i < MYWORD_LENGTH;i ++) {

            bool i_bit = instruction_.get_bit(i);
            
            if (i <= 15) {
                D.set_bit(i, i_bit);
                if (i <= 5) {E.set_bit(i, i_bit);}
                if (i >= 11) {C.set_bit(i - 11, i_bit);}
            }
            else {
                if (i <= 20) {B.set_bit(i - 16, i_bit);}
                else if (i <= 25) {A.set_bit(i - 21, i_bit);}
                else {F.set_bit(i - 26, i_bit);}
            }

        }

        instructionMemory_outA.write(A);
        instructionMemory_outB.write(B);
        instructionMemory_outC.write(C);
        instructionMemory_outD.write(D);
        instructionMemory_outE.write(E);
        instructionMemory_outF.write(F);
    }

    SC_CTOR(myinstructionspliter) {
        SC_METHOD(m);
		sensitive << instruction;
    }
};
