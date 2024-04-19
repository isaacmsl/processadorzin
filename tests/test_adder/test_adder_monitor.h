#include "systemc.h"
#include <iomanip>

using namespace std;

template<typename T>
SC_MODULE(mon) {
    sc_in<bool> clk, CO;
    sc_in<T> A,B,S;

    void monitor() {
        cout << setw(10) << "Time";
        cout << setw(MYWORD_LENGTH) << "A";
        cout << setw(MYWORD_LENGTH) << "B";
        cout << setw(MYWORD_LENGTH + 2) << "CO";
        cout << setw(MYWORD_LENGTH) << "S" << endl;
        while(true) {
            cout << setw(10) << sc_time_stamp();
            cout << setw(MYWORD_LENGTH) << A.read() << " ";
            cout << setw(MYWORD_LENGTH) << B.read() << " ";
            cout << setw(MYWORD_LENGTH + 2) << CO.read() << " ";
            cout << setw(MYWORD_LENGTH) << S.read() << " " << endl;
            wait();
        }
    }

    SC_CTOR(mon) {
        SC_THREAD(monitor);
        sensitive << clk.pos();
    }
};
