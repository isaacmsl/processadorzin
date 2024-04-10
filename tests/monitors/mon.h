#include "systemc.h"
#include <iomanip>

using namespace std;

template<typename T>
SC_MODULE(mon) {
    sc_in<bool> Clk, CO;
    sc_in<T> A,B,S;

    void monitor() {
        cout << setw(10) << "Time";
        cout << setw(2) << "A";
        cout << setw(2) << "B";
        cout << setw(3) << "CO";
        cout << setw(2) << "S" << endl;
        while(true) {
            cout << setw(10) << sc_time_stamp();
            cout << setw(32) << A.read() << " ";
            cout << setw(32) << B.read() << " ";
            cout << setw(32) << CO.read() << " ";
            cout << setw(32) << S.read() << " " << endl;
            wait();
        }
    }

    SC_CTOR(mon) {
        SC_THREAD(monitor);
        sensitive << Clk.pos();
    }
};
