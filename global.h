#ifndef GLOBAL_H
#define GLOBAL_H
#include "systemc.h"

const int MYWORD_LENGTH = 32;
const int MYSHORTWORD_LENGTH = 16;
const int MYADDRESSWORD_LENGTH = 5;

using myword = sc_bv<MYWORD_LENGTH>;
using myshortword = sc_bv<MYSHORTWORD_LENGTH>;
using my6bitword = sc_bv<6>;
using myaddressword = sc_bv<MYADDRESSWORD_LENGTH>;

enum opcodes {
    op_add, // add register1 with immediate and writes at register2 (index 0)
    op_sub, // sub register1 with immediate (index 1)
    op_mult, // mult register1 with immediate (index 2)
    op_div, // div register1 with immediate (index 3)
    op_or, // 'or' register1 with immediate (index 4)
    op_and, // 'and' register1 with immediate (index 5)
    op_xor, // 'xor' register1 with immediate (index 6)
    op_shiftright, // shiftright register1 by 'immediate' (index 7)
    op_shiftleft, // shiftleft register1 by 'immediate' (index 8)
    op_negate, // negate immediate (index 9)
    op_ld, // load word in memory with address 'immediate + register1' to register2 (index 10)
    op_st, // store register2 in memory in address 'immediate + register1' (index 11)
    op_j, // jump 'immediate' instructions (index 12)
    op_jn, // jump 'immediate' instructions if register1 - register2 < 0 (index 13)
    op_jz, // jump 'immediate' instructions if register1 - register2 == 0 (index 14)
};

int word_to_int(myword myword_addr) {
    int addr_as_int = 0;
    int base = 1;
    for (int i = 0; i < myword_addr.length(); i++) {
        addr_as_int += myword_addr.get_bit(i) * base;
        base = base * 2;
    }

    return addr_as_int;
}

template<typename T>
int my_to_int(T my_addr) {
    int addr_as_int = 0;
    int base = 1;
    for (int i = 0; i < my_addr.length(); i++) {
        addr_as_int += my_addr.get_bit(i) * base;
        base = base * 2;
    }

    return addr_as_int;
}

// 32 0's  00000000000000000000000000000000

#endif