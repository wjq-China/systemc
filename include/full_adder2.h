#include "systemc.h"
 
SC_MODULE(full_adder2){
    sc_in<bool> a, b, carry_in;
    sc_out<bool> sum, carry_out;
 
    void full_addr_prc();
 
    SC_CTOR(full_adder2){
    
    SC_METHOD(full_addr_prc);
    sensitive <<a <<b <<carry_in;
    }
 
};
 
void full_adder2::full_addr_prc()
{
    sum = a^b^carry_in;
    carry_out = a & carry_in | b & carry_in | a &b;
 
}