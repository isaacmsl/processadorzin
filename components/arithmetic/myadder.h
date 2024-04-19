#include "systemc.h"
#include "global.h"

#include <iomanip>

using std::get;

SC_MODULE(myadder) {
    sc_in<myword> A, B;
    sc_out<myword> S;
    sc_out<bool> CO;

    tp add(bool a, bool b) {
        return tp(a ^ b, a && b);
    }

    void bitwise_sum() {
        myword sum; // value to be returned
        myword a = A.read();
        myword b = B.read();
        bool carry = 0;

        int word_lenght = A.read().length();

        // bitwise sum
        for (int i{0};i < word_lenght;i ++) {

            bool a_b = get<0>(add(a.get_bit(i), b.get_bit(i))); // getting the 'XOR' part of the sum
            tp a_b_carry = add(a_b, carry); // adding carry to the result

            sum.set_bit(i, get<0>(a_b_carry));

            carry = get<1>(a_b_carry); //updating carry
        }

        S.write(sum);
        CO.write(carry);
    }

    SC_CTOR(myadder) : A("A"), B("B") {
        SC_METHOD(bitwise_sum);
		sensitive << A << B;
    }
};
