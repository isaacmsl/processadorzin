#ifndef GLOBAL_H
#define GLOBAL_H
#include "systemc.h"
#include <vector>

const int MYWORD_LENGTH = 32;
const int MYSHORTWORD_LENGTH = 16;
const int MYADDRESSWORD_LENGTH = 5;

using myword = sc_bv<MYWORD_LENGTH>;
using myshortword = sc_bv<MYSHORTWORD_LENGTH>;
using my6bitword = sc_bv<6>;
using myaddressword = sc_bv<MYADDRESSWORD_LENGTH>;
//using mychangecheckword = sc_bv<8 + MYWORD_LENGTH * 2>;

enum opcodes {
    unit,
    op_add, // add register1 with immediate and writes at register2 (index 1)
    op_sub, // sub register1 with immediate (index 2)
    op_mult, // mult register1 with immediate (index 3)
    op_div, // div register1 with immediate (index 4)
    op_or, // 'or' register1 with immediate (index 5)
    op_and, // 'and' register1 with immediate (index 6)
    op_xor, // 'xor' register1 with immediate (index 7)
    op_shiftright, // shiftright register1 by 'immediate' (index 8)
    op_shiftleft, // shiftleft register1 by 'immediate' (index 9)
    op_negate, // negate immediate (index 10)
    op_ld, // load word in memory with address 'immediate + register1' to register2 (index 11)
    op_st, // store register2 in memory in address 'immediate + register1' (index 12)
    op_j, // jump 'immediate' instructions (index 13)
    op_jn, // jump 'immediate' instructions if register1 - register2 < 0 (index 14)
    op_jz, // jump 'immediate' instructions if register1 - register2 == 0 (index 15)
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

/*
template<typename T>
mychangecheckword to_change_check(std::vector<bool> b_list, std::vector<T> t_list) {
    mychangecheckword a;

    // coding b_list into the first 8 bits
    for (int i{0};i < std::min(8, (int)b_list.size());i ++) {
        a.set_bit(i, b_list[i]);
    }

    // coding t_list into the last 64 bits
    for (int i{0};i < std::min(2, (int)t_list.size());i ++) {
        int l = t_list[i].length();
        for (int j{0};j < l;j++) {
            a.set_bit(8 + i * MYADDRESSWORD_LENGTH + j, t_list[i].get_bit(j));
        }
    }

    return a;
}
*/

// 32 0's  00000000000000000000000000000000

#endif