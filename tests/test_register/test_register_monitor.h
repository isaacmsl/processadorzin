#include "systemc.h"
#include <iomanip>

using namespace std;

template<typename T>
SC_MODULE(mon) {
    sc_in<bool> clr, ld, clk;
    sc_in<T> d, q;

    void monitor() {
        cout << setw(15) << "Time" << " ";
        cout << setw(1 + 3) << "clr" << " ";
        cout << setw(1 + 1) << "ld" << " ";
        cout << setw(MYWORD_LENGTH) << "d" << " ";
        cout << setw(MYWORD_LENGTH) << "q" << " ";
        cout << setw(MYWORD_LENGTH + 2) << "clk" << endl;

        while(true) {
            cout << setw(15) << sc_time_stamp() << " ";
            cout << setw(1 + 3) << clr.read() << " ";
            cout << setw(1 + 1) << ld.read() << " ";
            cout << setw(MYWORD_LENGTH) << d.read() << " ";
            cout << setw(MYWORD_LENGTH) << q.read() << " ";
            cout << setw(MYWORD_LENGTH + 2) << clk.read() << " " << endl;
            wait();
        }
    }

    SC_CTOR(mon) {
        SC_THREAD(monitor);
        sensitive << clk;
    }
};

