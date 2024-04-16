#include "systemc.h"
#include <iomanip>

using namespace std;

template<typename T>
SC_MODULE(mon_registerbank) {
    sc_in<myword> data;
    sc_in<sc_bv<8>> addr1, addr2, addr_write;
    sc_in<myword> out1, out2;
    sc_in<bool> clk;

    void monitor() {
        cout << setw(10) << "Time";
        cout << setw(2) << "Data";
        cout << setw(2) << "Addr1";
        cout << setw(3) << "Addr2";
        cout << setw(2) << "Addr_Write";
        cout << setw(2) << "Out1";
        cout << setw(2) << "Out2" << endl;

        while(true) {
            cout << setw(10) << sc_time_stamp();
            cout << setw(32) << data.read() << " ";
            cout << setw(8) << addr1.read() << " ";
            cout << setw(8) << addr2.read() << " ";
            cout << setw(8) << addr_write.read() << " ";
            cout << setw(32) << out1.read() << " ";
            cout << setw(32) << out2.read() << " " << endl;
            wait();
        }
    }

    SC_CTOR(mon_registerbank) {
        SC_THREAD(monitor);
        sensitive << clk.pos();
    }
};
