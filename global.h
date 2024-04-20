#ifndef GLOBAL_H
#define GLOBAL_H
#include "systemc.h"

const int MYWORD_LENGTH = 4;
const int MYLONGWORD_LENGTH = 8;

using myword = sc_bv<MYWORD_LENGTH>;
using mylongword = sc_bv<MYLONGWORD_LENGTH>;

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