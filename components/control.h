#include "systemc.h"
#include "../global.h"

SC_MODULE(mycontrol) {
    sc_in<bool> clk, clr, zero;
    sc_in<my6bitword> opcode;
    sc_out<bool> RegWrite, RegDst, ALUSrc, MemWrite, MemRead, MemToReg, PCSrc;
    sc_out<my6bitword> ALUop;
    sc_in<my6bitword> func;


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

                        // Diferencia quando precisamos identificar a operação pelo func
                        if (opcode_int == op_ula_regs) {
                            ALUop.write(func);
                        } else {
                            ALUop.write(opcode_int);
                        }
                        
                        switch(opcode_int) {

                            // "Do nothing"
                            case unit:
                            RegWrite.write(0);
                            RegDst.write(0);
                            ALUSrc.write(0);
                            MemWrite.write(0);
                            MemRead.write(0);
                            MemToReg.write(0);
                            PCSrc.write(0);
                            break;

                            // Ula operations
                            case op_add:
                            case op_mult:
                            case op_sub:
                            case op_div:
                            case op_and:
                            case op_or:
                            case op_xor:
                            case op_shiftleft:
                            case op_shiftright:
                            case op_negate:
                            RegWrite.write(1);
                            RegDst.write(0);
                            ALUSrc.write(1);
                            MemWrite.write(0);
                            MemRead.write(0);
                            MemToReg.write(1);
                            PCSrc.write(0);
                            break;
                            
                            case op_ula_regs:
                            RegWrite.write(1);
                            RegDst.write(1);
                            ALUSrc.write(0);
                            MemWrite.write(0);
                            MemRead.write(0);
                            MemToReg.write(1);
                            PCSrc.write(0);
                            break;

                            case op_ld:
                            PCSrc.write(0);         // continua incrementando o PC sem jump
                            ALUop.write(op_add);    // força a soma para o deslocamento reg + imediate
                            ALUSrc.write(1);        // vai somar com o imediate
                            MemRead.write(1);       // vai ler da memória de dados
                            MemWrite.write(0);      // não vai escrever na memória de dados
                            RegWrite.write(1);      // já que vai escrever no registrador
                            MemToReg.write(0);      // vem da memória de dados
                            break;

                            case op_st:
                            PCSrc.write(0);         // continua incrementando o PC sem jump
                            ALUop.write(op_add);    // força a soma para o deslocamento reg + imediate
                            ALUSrc.write(1);        // vai somar com o imediate
                            MemRead.write(0);       // não vai ler da memória de dados
                            MemWrite.write(1);      // vai escrever na memória de dados
                            RegWrite.write(0);      // não vai escrever no registrador
                            break;

                            case op_j:
                            RegWrite.write(0);
                            RegDst.write(0);
                            ALUSrc.write(0);
                            MemWrite.write(0);
                            MemRead.write(0);
                            MemToReg.write(0);
                            PCSrc.write(1);
                            ALUop.write(op_sub);
                            break;

                            case op_jn: ALUop.write(op_sub);break;

                            case op_jz: ALUop.write(op_sub);break;

                        }
                    break;
                }
            }        
            else {
                state = S0;
            }

            // std::cout << "S1 " << RegWrite.read() <<
            //                 RegDst.read() <<
            //                 ALUSrc.read() <<
            //                 MemWrite.read() <<
            //                 MemRead.read() <<
            //                 MemToReg.read() <<
            //                 PCSrc.read() << '\n';

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
