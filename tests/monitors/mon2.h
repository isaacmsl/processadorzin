#include "systemc.h"
#include <iomanip>

using namespace std;

template<typename T>
SC_MODULE(mon) {
    sc_in<bool> Clk, Clr, LoadSig;
    sc_in<T> A, S;

    void monitor() {
        cout << setw(10) << "Time";
        cout << setw(2) << "A";
        cout << setw(32) << "S";
        cout << setw(32) << "Clr";
        cout << setw(5) << "LoadSig" << endl;
        while(true) {
            cout << setw(10) << sc_time_stamp();
            cout << setw(32) << A.read() << " ";
            cout << setw(32) << S.read() << " ";
            cout << setw(2) << Clr.read() << " ";
            cout << setw(2) << LoadSig.read() << " " << endl;
            wait();
        }
    }

    SC_CTOR(mon) {
        SC_THREAD(monitor);
        sensitive << Clk.pos();
    }
};
