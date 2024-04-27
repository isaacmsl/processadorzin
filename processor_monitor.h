#include "systemc.h"
#include <iomanip>

using namespace std;

template<typename T>
SC_MODULE(mon) {
    sc_in<bool> clk, bit_out;
    sc_in<myword> myword_out1, myword_out2, myword_out3;
    sc_in<myshortword> myshortword_out;
    sc_in<my6bitword> my6bit_out;

    void monitor() {
        cout << setw(8) << "Time" << " ";
        cout << setw(MYWORD_LENGTH + 1) << "out1" << " ";
        cout << setw(MYSHORTWORD_LENGTH + 1) << "short_out" << " ";
        cout << setw(6 + 1) << "6bit" << " ";
        cout << setw(MYWORD_LENGTH + 1) << "out2" << " ";
        cout << setw(MYWORD_LENGTH + 1) << "out3" << " ";
        cout << setw(3 + 1) << "1bit" << " ";
        cout << setw(3 + 1) << "clk" << endl;

        while(true) {
            cout << setw(8) << sc_time_stamp() << " ";
            cout << setw(MYWORD_LENGTH + 1) << myword_out1.read() << " ";
            cout << setw(MYSHORTWORD_LENGTH + 1) << myshortword_out.read() << " ";
            cout << setw(6 + 1) << my6bit_out.read() << " ";
            cout << setw(MYWORD_LENGTH + 1) << myword_out2.read() << " ";
            cout << setw(MYWORD_LENGTH + 1) << myword_out3.read() << " ";
            cout << setw(3 + 1) << bit_out.read() << " ";
            cout << setw(3 + 1) << clk.read() << " " << endl;
            wait();
        }
    }

    SC_CTOR(mon) {
        SC_THREAD(monitor);
        sensitive << clk;
    }
};