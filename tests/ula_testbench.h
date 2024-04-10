/*
    Utilizando testbench da ULA feita por Jorge Ugalde (*adaptada)
    Origem: https://www.edaplayground.com/x/5te3
*/

#include "systemc.h"
#include "../components/ula.h"

void test_ula() {
  sc_signal<bool>  clock; 
  sc_signal<short> alu_in1;
  sc_signal<short> alu_in2;  
  sc_signal<short> alu_out;
  sc_signal<short> alu_sel; 
  
  sc_signal<bool>   c_out; 
  sc_signal<bool>   of_out;
    
  int i=0;
  my_ula alu("ALU");
  alu.alu_in1(alu_in1);
  alu.alu_in2(alu_in2);  
  alu.alu_out(alu_out);
  alu.clock(clock); 
  alu.alu_sel(alu_sel); 
  
  alu.c_out(c_out); 
  alu.of_out(of_out);
    
  sc_start(1, SC_NS);
  sc_trace_file *wf = sc_create_vcd_trace_file("ALU");
  
  sc_trace(wf, alu_in1, "alu_in1");
  sc_trace(wf, alu_in2, "alu_in2");
  sc_trace(wf, alu_out, "alu_out");
  sc_trace(wf, alu_sel, "alu_sel");
  sc_trace(wf, c_out, 	"c_out"  );
  sc_trace(wf, of_out, 	"of_out" );
  sc_trace(wf, clock, 	"clock"  );  
  

  alu_in1 = 0;  
  alu_in2 = 0;  
  clock =0;

//######################	SUMA	###############333
  alu_sel = 0;

  alu_in1 = 5;  
  alu_in2 = 4;   
  
  for (i=0;i<3;i++) {
    clock = 0; 
    sc_start(1, SC_NS);
    clock = 1; 
    sc_start(1, SC_NS);
  }  

  
//######################	SUMA	###############333
  alu_sel = 0;

  alu_in1 = 32000;  
  alu_in2 = 32000;   
  
  for (i=0;i<3;i++) {
    clock = 0; 
    sc_start(1, SC_NS);
    clock = 1; 
    sc_start(1, SC_NS);
  }    
  
  
//######################	RESTA	###############333
  alu_sel = 1;

  
  alu_in1 = 5;  
  alu_in2 = 4;   
  
  for (i=0;i<3;i++) {
    clock = 0; 
    sc_start(1, SC_NS);
    clock = 1; 
    sc_start(1, SC_NS);
  }    
  
//######################	PRODUCTO	###############333
  alu_sel = 2;

  alu_in1 = 5;  
  alu_in2 = 4;   
  
  for (i=0;i<3;i++) {
    clock = 0; 
    sc_start(1, SC_NS);
    clock = 1; 
    sc_start(1, SC_NS);
  }    
  
  
//######################	DIVISION	###############333
  alu_sel = 3;
 
  alu_in1 = 5;  
  alu_in2 = 4;   
  
  for (i=0;i<3;i++) {
    clock = 0; 
    sc_start(1, SC_NS);
    clock = 1; 
    sc_start(1, SC_NS);
  }     
  
  
//######################	OR	###############333
  alu_sel = 4;
  alu_in1 = 65535;  
  alu_in2 = 0;   
  
  for (i=0;i<3;i++) {
    clock = 0; 
    sc_start(1, SC_NS);
    clock = 1; 
    sc_start(1, SC_NS);
  }      
  
  
  
  
//######################	AND	###############333
  alu_sel = 5;
  
  alu_in1 = 65535;  
  alu_in2 = 0;  
  
  for (i=0;i<3;i++) {
    clock = 0; 
    sc_start(1, SC_NS);
    clock = 1; 
    sc_start(1, SC_NS);
  }     

  
//######################	XOR	###############333
  alu_sel = 6;
  
  alu_in1 = 65535;  
  alu_in2 = 0;   
  
  for (i=0;i<3;i++) {
    clock = 0; 
    sc_start(1, SC_NS);
    clock = 1; 
    sc_start(1, SC_NS);
  }    
  
  
  
//######################	SR	###############333
  alu_sel = 7;
  alu_in1 = 65535;  
  alu_in2 = 0;   
  
  for (i=0;i<3;i++) {
    clock = 0; 
    sc_start(1, SC_NS);
    clock = 1; 
    sc_start(1, SC_NS);
  }      
  
  
//######################	SL	###############333
  alu_sel = 8;
  alu_in1 = 65535;  
  alu_in2 = 0;   
  
  for (i=0;i<3;i++) {
    clock = 0; 
    sc_start(1, SC_NS);
    clock = 1; 
    sc_start(1, SC_NS);
  }    
  
  
//######################	NEGADO	###############333
  alu_sel = 9;
  alu_in1 = 65535;  
  alu_in2 = 0;   
  
  for (i=0;i<3;i++) {
    clock = 0; 
    sc_start(1, SC_NS);
    clock = 1; 
    sc_start(1, SC_NS);
  }
  

  sc_close_vcd_trace_file(wf);
}