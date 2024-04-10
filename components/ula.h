/*
    Utilizando ULA feita por Jorge Ugalde (*adaptada)
    Origem: https://www.edaplayground.com/x/5te3
*/


#include "systemc.h"
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

SC_MODULE (my_ula) {
  
  sc_in<short>   alu_in1;  
  sc_in<short>   alu_in2;  
  sc_in<short>   alu_sel;   
                 
  sc_out<short>  alu_out; 
  sc_out<bool>   c_out; 
  sc_out<bool> 	 of_out;  
  sc_in_clk      clock; 
  bool           b_true = 1;
  bool           b_false = 0;  
  
  void alu () {

    if(alu_sel.read() == 0)//Suma
    {
        c_out.write(b_false);	
        of_out.write(b_false);          
        cout<<"Ejecutando Suma"<<endl;
        
        alu_out.write(alu_in1 + alu_in2);
        if(alu_in1 + alu_in2 > 65535)
        {
            of_out.write(b_true);
        }
        else {
            if (((alu_in1&alu_in2) | (alu_in1^alu_in2)) == 65535)
            {
                cout<<"CARRY ON"<<endl;
                c_out.write(b_true);	
            }
            if (((alu_in1&alu_in2) | (alu_in1^alu_in2)) == 0)
            {
                cout<<"CARRY OFF"<<endl;
                c_out.write(b_false);	
            }                  
        }
    }

    if(alu_sel.read() == 1)//Resta
    {
        c_out.write(b_false);	
        of_out.write(b_false);   
        cout<<"Ejecutando Resta"<<endl;
        alu_out.write(alu_in1-alu_in2);
    }

    if(alu_sel.read() == 2)//Multiplicacion
    {
        c_out.write(b_false);	
        of_out.write(b_false);  
        cout<<"Ejecutando Multiplicacion"<<endl;
        alu_out.write(alu_in1*alu_in2);
    }

    if(alu_sel.read() == 3)//Division
    {
        c_out.write(b_false);	
        of_out.write(b_false);  
        cout<<"Ejecutando Division"<<endl;
        alu_out.write(alu_in1/alu_in2);
    
    }

    if(alu_sel.read() == 4)//OR
    {
        c_out.write(b_false);	
        of_out.write(b_false);  
        cout<<"Ejecutando OR"<<endl;
        alu_out.write(alu_in1|alu_in2);          
    }

    if(alu_sel.read() == 5)//AND
    {
        c_out.write(b_false);	
        of_out.write(b_false);  
        cout<<"Ejecutando AND"<<endl;
        alu_out.write(alu_in1&alu_in2);          
    }

    if(alu_sel.read() == 6)//XOR
    {
        c_out.write(b_false);	
        of_out.write(b_false);  
        cout<<"Ejecutando XOR"<<endl;
        alu_out.write(alu_in1^alu_in2);  
    }   

    if(alu_sel.read() == 7)//Shift Right
    {
        c_out.write(b_false);	
        of_out.write(b_false);  
        cout<<"Ejecutando SR"<<endl;
        alu_out.write(alu_in1>>1);           
    }  

    if(alu_sel.read() == 8)//Shift Left
    {
        c_out.write(b_false);	
        of_out.write(b_false);  
        cout<<"Ejecutando SL"<<endl;
        alu_out.write(alu_in1<<1);            
    }

    if(alu_sel.read() == 9)//Negate
    {
        c_out.write(b_false);	
        of_out.write(b_false);  
        cout<<"Ejecutando NEGATE"<<endl;
        alu_out.write(~alu_in1);  
    }  
    
  }
    
  SC_CTOR(my_ula) {
        SC_METHOD(alu);
        //sensitive << reset;
        sensitive << clock.pos();
    } 
};