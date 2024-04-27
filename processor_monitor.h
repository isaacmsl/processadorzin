#include "systemc.h"
#include <iomanip>

using namespace std;

template<typename T>
SC_MODULE(mon) {
    sc_in<bool> clk;

    void monitor() {
        cout << setw(15) << "Time" << " ";
        cout << setw(MYWORD_LENGTH + 2) << "clk" << endl;

        while(true) {
            cout << setw(15) << sc_time_stamp() << " ";
            cout << setw(MYWORD_LENGTH + 2) << clk.read() << " " << endl;
            wait();
        }
    }

    SC_CTOR(mon) {
        SC_THREAD(monitor);
        sensitive << clk;
    }
};