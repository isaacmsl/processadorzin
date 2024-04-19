#ifndef GLOBAL_H
#define GLOBAL_H
#include "systemc.h"

const int MYWORD_LENGTH = 4;

using myword = sc_bv<MYWORD_LENGTH>;
using tp = std::tuple<bool, bool>;

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