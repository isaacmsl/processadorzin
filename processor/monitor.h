#include "systemc.h"
#include "variables.h"
#include <iomanip>
#include <vector>

using namespace std;

template<typename T>
SC_MODULE(mon) {
    sc_in<bool> clk, bit_out;
    sc_in<myword> myword_out1, myword_out2, myword_out3;
    sc_in<myshortword> myshortword_out;
    sc_in<myaddressword> myadd_out;
    sc_in<my6bitword> my6bit_out;
    std::vector<int> regprint_inds = {0, 1, 2, 3, 4}, datamemory_inds = {}, instmemory_inds = {0, 1, 2, 3, 4};

    void monitor() {

        // Printing instructions
        for (int ind : instmemory_inds) {
            cout << "InstMemory[" << ind << "] = " << InstructionMemory.ram_array[ind] << '\n';
        }

        // Preparing headers

        cout << setw(8) << "Time" << " ";
        cout << setw(MYWORD_LENGTH + 1) << "out1" << " ";
        cout << setw(MYSHORTWORD_LENGTH + 1) << "short_out" << " ";
        cout << setw(6 + 1) << "6bit" << " ";
        cout << setw(5 + 1) << "5bit" << " ";
        cout << setw(MYWORD_LENGTH + 1) << "out2" << " ";
        cout << setw(MYWORD_LENGTH + 1) << "out3" << " ";
        cout << setw(3 + 1) << "1bit" << " ";
        cout << setw(3 + 1) << "clk" << endl;

        while(true) {
            cout << setw(8) << sc_time_stamp() << " ";
            cout << setw(MYWORD_LENGTH + 1) << myword_out1.read() << " ";
            cout << setw(MYSHORTWORD_LENGTH + 1) << myshortword_out.read() << " ";
            cout << setw(6 + 1) << my6bit_out.read() << " ";
            cout << setw(5 + 1) << myadd_out.read() << " ";
            cout << setw(MYWORD_LENGTH + 1) << myword_out2.read() << " ";
            cout << setw(MYWORD_LENGTH + 1) << myword_out3.read() << " ";
            cout << setw(3 + 1) << bit_out.read() << " ";
            cout << setw(3 + 1) << clk.read() << " " << endl;

            // Printing stored data

            for (int ind : regprint_inds) {
                cout << "Register[" << ind << "] = " << Registers.bank[ind] << '\n';
            }

            for (int ind : datamemory_inds) {
                cout << "DataMemory[" << ind << "] = " << DataMemory.ram_array[ind] << '\n';
            }

            // cout << "\n\n\n next cicle:\n";
            wait();
        }
    }

    SC_CTOR(mon) {
        SC_THREAD(monitor);
        sensitive << clk.pos();
    }
};