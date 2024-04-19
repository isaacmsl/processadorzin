#include "systemc.h"
#include <iomanip>

using namespace std;

template<typename T>
SC_MODULE(mon) {
    sc_in<bool> clk, CO;
    sc_in<T> A,B,S;

    void monitor() {
        cout << setw(15) << "Time" << " ";
        cout << setw(MYWORD_LENGTH) << "A" << " ";
        cout << setw(MYWORD_LENGTH) << "B" << " ";
        cout << setw(MYWORD_LENGTH + 1) << "CO" << " ";
        cout << setw(MYWORD_LENGTH) << "S" << " ";
        cout << setw(MYWORD_LENGTH + 2) << "clk" << endl;

        while(true) {
            cout << setw(15) << sc_time_stamp() << " ";
            cout << setw(MYWORD_LENGTH) << A.read() << " ";
            cout << setw(MYWORD_LENGTH) << B.read() << " ";
            cout << setw(MYWORD_LENGTH + 1) << CO.read() << " ";
            cout << setw(MYWORD_LENGTH) << S.read() << " ";
            cout << setw(MYWORD_LENGTH + 2) << clk.read() << " " << endl;
            wait();
        }
    }

    SC_CTOR(mon) {
        SC_THREAD(monitor);
        sensitive << clk;
    }
};
