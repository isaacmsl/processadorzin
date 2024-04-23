#include "systemc.h"
#include <iomanip>

using namespace std;

template<typename T>
SC_MODULE(mon) {
    sc_in<bool> write, read, clk;
    sc_in<T> addr, data, out;
    
    void monitor() {
        cout << setw(15) << "Time" << " ";
        cout << setw(MYWORD_LENGTH) << "addr" << " ";
        cout << setw(MYWORD_LENGTH) << "data" << " ";
        cout << setw(MYWORD_LENGTH + 1) << "out" << " ";
        cout << setw(2) << "write" << " ";
        cout << setw(2) << "read" << " ";
        cout << setw(2) << "clk" << endl;

        while(true) {
            cout << setw(15) << sc_time_stamp() << " ";
            cout << setw(MYWORD_LENGTH) << addr.read() << " ";
            cout << setw(MYWORD_LENGTH) << data.read() << " ";
            cout << setw(MYWORD_LENGTH + 1) << out.read() << " ";
            cout << setw(2) << write.read() << " ";
            cout << setw(2) << read.read() << " ";
            cout << setw(2) << clk.read() << endl;
            wait();
        }
    }

    SC_CTOR(mon) {
        SC_THREAD(monitor);
        sensitive << clk;
    }
};