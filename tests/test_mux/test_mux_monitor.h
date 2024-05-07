#include "systemc.h"
#include <iomanip>

using namespace std;

template<typename T>
SC_MODULE(mon_mux) {
    sc_in<bool> clk, sel;
    sc_in<T> A,B,S;

    void monitor() {
        cout << setw(15) << "Time" << " ";
        cout << setw(MYWORD_LENGTH) << "A" << " ";
        cout << setw(MYWORD_LENGTH) << "B" << " ";
        cout << setw(MYWORD_LENGTH) << "S" << " ";
        cout << setw(MYWORD_LENGTH + 2) << "sel" << " ";
        cout << setw(MYWORD_LENGTH + 2) << "clk" << endl;

        while(true) {
            cout << setw(15) << sc_time_stamp() << " ";
            cout << setw(MYWORD_LENGTH) << A.read() << " ";
            cout << setw(MYWORD_LENGTH) << B.read() << " ";
            cout << setw(MYWORD_LENGTH) << S.read() << " ";
            cout << setw(MYWORD_LENGTH + 2) << sel.read() << " ";
            cout << setw(MYWORD_LENGTH + 2) << clk.read() << " " << endl;
            wait();
        }
    }

    SC_CTOR(mon_mux) {
        SC_THREAD(monitor);
        sensitive << clk.pos();
    }
};