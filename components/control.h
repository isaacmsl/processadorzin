#include "systemc.h"
#include "../global.h"

SC_MODULE(mycontrol) {
    sc_in<bool> zero;
    sc_in<myword> opcode, func;
    sc_out<bool> RegWrite, RegDst, ALUSrc, MemWrite, MemRead, MemToReg, PCSrc;
    sc_out<myword> ALUop;

    void m() {
        // Reseting signals
        RegWrite.write(0);
        RegDst.write(0);
        ALUSrc.write(0);
        MemWrite.write(0);
        MemRead.write(0);
        MemToReg.write(0);
        PCSrc.write(0);

        int opcode_int = word_to_int(opcode.read());
        ALUop.write(opcode_int);
        
        switch(opcode_int) {

            case op_add: RegDst.write(1);RegWrite.write(1);break;

            case op_sub: RegDst.write(1);RegWrite.write(1);break;

            case op_and: RegDst.write(1);RegWrite.write(1);break;

            case op_or: RegDst.write(1);RegWrite.write(1);break;

            case op_slt: RegDst.write(1);RegWrite.write(1);break;

            case op_lw: ALUop.write(op_add);RegWrite.write(1);ALUSrc.write(1);MemRead.write(1);MemToReg.write(1);break;

            case op_sw: ALUop.write(op_add);ALUSrc.write(1);MemWrite.write(1);break;

            case op_beq: ALUop.write(op_sub);break;

        }

    }

    SC_CTOR(mycontrol) {
        SC_METHOD(m);
		sensitive << opcode << func << zero;
    }
};
