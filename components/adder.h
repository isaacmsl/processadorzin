#ifndef ADDER_H
#define ADDER_H

#include "systemc.h"
#include "../global.h"

#include <iomanip>

SC_MODULE(myadder) {
    sc_in<myword> A, B;
    sc_out<myword> S;
    sc_out<bool> CO;

    void bitwise_sum() {
        myword sum; // value to be returned
        myword a = A.read();
        myword b = B.read();
        bool carry = 0;

        // bitwise sum
        for (int i{0};i < MYWORD_LENGTH;i ++) {

            bool xor_ = a.get_bit(i) ^ b.get_bit(i);
            bool and_ = a.get_bit(i) & b.get_bit(i);

            sum.set_bit(i, xor_ ^ carry);

            carry = and_ | (xor_ & carry);
        }

        S.write(sum);
        CO.write(carry);
    }

    SC_CTOR(myadder) : A("A"), B("B") {
        SC_METHOD(bitwise_sum);
		sensitive << A << B;
    }
};

#endif