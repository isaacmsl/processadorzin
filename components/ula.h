/*
    Utilizando ULA feita por Jorge Ugalde (*adaptada)
    Origem: https://www.edaplayground.com/x/5te3
*/


#include "systemc.h"
#include "../global.h"

//	  alu_sel
//0	  00			Suma
//1	  01			Resta	
//2   10			Multiplicacion
//3   11			Division
//4   100			OR
//5   101			AND
//6   110			XOR
//7   111			Shift Right
//8   1000			Shift Left
//9   1001			Negate

SC_MODULE (myula) {
  
  sc_in<myword>   alu_in1;
  sc_in<myword>   alu_in2;
  sc_in<myopword>   alu_sel;
                 
  sc_out<myword>  alu_out;
  sc_out<bool>   c_out;
  sc_out<bool>   zero_out;
  sc_in_clk      clock;
  
  void alu () {

    short alu_in1_int = word_to_int(alu_in1.read());
    short alu_in2_int = word_to_int(alu_in2.read());
    short read_ = word_to_int(alu_sel.read());

    c_out.write(0);
    zero_out.write(1);

    if(read_ == op_add)//Suma
    {
        alu_out.write(alu_in1_int + alu_in2_int);
        c_out.write((alu_in1_int + alu_in2_int) >= (1 << MYSHORTWORD_LENGTH));
    }

    if(read_ == op_sub)//Resta
    {	
        alu_out.write(alu_in1_int - alu_in2_int);
        zero_out.write(alu_in1_int - alu_in2_int == 0 ? 0 : 1);
    }

    if(read_ == op_mult)//Multiplicacion
    {
        alu_out.write(alu_in1_int * alu_in2_int);
    }

    if(read_ == op_div)//Division
    {	
        alu_out.write(alu_in1_int / alu_in2_int);
    }

    if(read_ == op_or)//OR
    {	
        alu_out.write(alu_in1_int | alu_in2_int);          
    }

    if(read_ == op_and)//AND
    {	
        alu_out.write(alu_in1_int & alu_in2_int);          
    }

    if(read_ == op_xor)//XOR
    {
        alu_out.write(alu_in1_int ^ alu_in2_int);  
    }   

    if(read_ == op_shiftright)//Shift Right
    {	
        alu_out.write(alu_in1_int >> 1);           
    }  

    if(read_ == op_shiftleft)//Shift Left
    {
        alu_out.write(alu_in1_int << 1);            
    }

    if(read_ == op_negate)//Negate
    {	
        alu_out.write(~alu_in1_int);  
    }

    if (read_ == op_slt)
    {
        // TODO
    }

    /*
    if (read_ == op_lw)
    {
        alu_out.write(alu_in2);
    }

    if (read_ == op_sw)
    {
        alu_out.write(alu_in2);
    }

    if (read_ == op_beq)
    {
        if (alu_in1_int == alu_in2_int) {
            alu_out.write()
        }
    }
    */
    
  }
    
  SC_CTOR(myula) {
        SC_METHOD(alu);
        sensitive << clock.pos();
    } 
};