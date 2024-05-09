#include "systemc.h"
#include "../global.h"

SC_MODULE(mycontrol) {
    sc_in<bool> clk, clr, zero;
    sc_in<my6bitword> opcode;
    sc_out<bool> RegWrite, RegDst, ALUSrc, MemWrite, MemRead, MemToReg, PCSrc;
    sc_out<my6bitword> ALUop;


    void n() {
        typedef enum {S0=0, S1=1, S2=2} state_e;
        state_e state = S0;

        while(true) {
            if(clr.read() == false) {
                switch(state) {
                    case S0: // initializing processor
                        // Reseting signals
                        RegWrite.write(0);
                        RegDst.write(0);
                        ALUSrc.write(0);
                        MemWrite.write(0);
                        MemRead.write(0);
                        MemToReg.write(0);
                        PCSrc.write(0);

                        state = S1;
                    break;
                    case S1: // processing next instruction

                        if (clk.read() == 1) {
                            break;
                        }

                        int opcode_int = word_to_int(opcode.read());
                        ALUop.write(opcode_int);
                        
                        
                        switch(opcode_int) {

                            case unit:
                            RegWrite.write(0);
                            RegDst.write(0);
                            ALUSrc.write(0);
                            MemWrite.write(0);
                            MemRead.write(0);
                            MemToReg.write(0);
                            PCSrc.write(0);
                            break;

                            case op_add:
                            RegWrite.write(1);
                            RegDst.write(0);
                            ALUSrc.write(1);
                            MemWrite.write(0);
                            MemRead.write(0);
                            MemToReg.write(1);
                            PCSrc.write(0);
                            break;

                            case op_sub: ALUSrc.write(1);break;

                            case op_mult: ALUSrc.write(1);break;

                            case op_div: ALUSrc.write(1);break;

                            case op_and: ALUSrc.write(1);break;

                            case op_or: ALUSrc.write(1);break;

                            case op_xor: ALUSrc.write(1);break;

                            case op_shiftleft: ALUSrc.write(1);break;

                            case op_shiftright: ALUSrc.write(1);break;

                            case op_negate: ALUSrc.write(1);break;

                            case op_ld: ALUop.write(op_add);ALUSrc.write(1);MemRead.write(1);RegWrite.write(1);MemToReg.write(1);break;

                            case op_st: ALUop.write(op_add);ALUSrc.write(1);MemWrite.write(1);break;

                            case op_j: PCSrc.write(1);break;

                            case op_jn: ALUop.write(op_sub);break;

                            case op_jz: ALUop.write(op_sub);break;

                        }
                    break;
                }
            }        
            else {
                state = S0;
            }

            std::cout << "S1 " << RegWrite.read() <<
                            RegDst.read() <<
                            ALUSrc.read() <<
                            MemWrite.read() <<
                            MemRead.read() <<
                            MemToReg.read() <<
                            PCSrc.read() << '\n';

            wait();
        }

        // writting into registers

        //case op_st: ALUop.write(op_add);RegWrite.write(1);ALUSrc.write(1);MemRead.write(1);break;

        //std::cout << opcode_int << '\n';

    }

    SC_CTOR(mycontrol) {
        SC_THREAD(n);
		sensitive << clk;
    }
};
