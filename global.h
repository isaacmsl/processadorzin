#ifndef GLOBAL_H
#define GLOBAL_H
#include "systemc.h"

using mybyte = sc_bv<8>;
using myword = sc_bv<32>;
using tp = std::tuple<bool, bool>;

int word_to_int(myword myword_addr) {
    int addr_as_int = 0;

    for (int i{myword_addr.length() - 1};i >= 0;i --) {
        addr_as_int += myword_addr.get_bit(i) << ((myword_addr.length() - 1) - i);
    }

    return addr_as_int
}

// 32 0's  00000000000000000000000000000000

#endif