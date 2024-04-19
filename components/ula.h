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
  sc_in<myword>   alu_sel;
                 
  sc_out<myword>  alu_out; 
  sc_out<bool>   c_out; 
  sc_in_clk      clock;
  
  void alu () {

    short alu_in1_int = word_to_int(alu_in1.read());
    short alu_in2_int = word_to_int(alu_in2.read());
    short read_ = word_to_int(alu_sel.read());

    c_out.write(0);

    if(read_ == 0)//Suma
    {
        alu_out.write(alu_in1_int + alu_in2_int);
        c_out.write((alu_in1_int + alu_in2_int) >= (1 << MYWORD_LENGTH));
    }

    if(read_ == 1)//Resta
    {	
        alu_out.write(alu_in1_int - alu_in2_int);
    }

    if(read_ == 2)//Multiplicacion
    {
        alu_out.write(alu_in1_int * alu_in2_int);
    }

    if(read_ == 3)//Division
    {	
        alu_out.write(alu_in1_int / alu_in2_int);
    }

    if(read_ == 4)//OR
    {	
        alu_out.write(alu_in1_int | alu_in2_int);          
    }

    if(read_ == 5)//AND
    {	
        alu_out.write(alu_in1_int & alu_in2_int);          
    }

    if(read_ == 6)//XOR
    {
        alu_out.write(alu_in1_int ^ alu_in2_int);  
    }   

    if(read_ == 7)//Shift Right
    {	
        alu_out.write(alu_in1_int >> 1);           
    }  

    if(read_ == 8)//Shift Left
    {
        alu_out.write(alu_in1_int << 1);            
    }

    if(read_ == 9)//Negate
    {	
        alu_out.write(~alu_in1_int);  
    }  
    
  }
    
  SC_CTOR(myula) {
        SC_METHOD(alu);
        sensitive << clock.pos();
    } 
};