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
using myopword = my6bitword;

enum opcodes {
    op_add, //0
    op_sub,
    op_mult,
    op_div,
    op_or,
    op_and,
    op_xor,
    op_shiftright,
    op_shiftleft,
    op_negate,
    op_slt,
    op_lw,
    op_sw,
    op_beq //13
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

// 32 0's  00000000000000000000000000000000

#endif