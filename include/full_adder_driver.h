#include <iostream>
#include "systemc.h"
 
SC_MODULE(driver){
    sc_out <bool> d_a, d_b, d_cin;
 
    ifstream infile;
    void driver_prc();
 
    SC_CTOR(driver){
        SC_THREAD(driver_prc);
        infile.open("../data/full_adder_driver_data.in"); //the data path is right when you are running exec program in 'build' folder.
        if(!infile){
            cerr << "in driver, Error: Unable to open vector file, full_adder_driver_data.in! \n";
            sc_stop();
        }
    }
 
    ~driver(){
        infile.close();
    }
 
};
 
void driver::driver_prc(){
    bool t_a, t_b, t_cin;
    while(infile >> t_a >> t_b >> t_cin){
        d_a.write(t_a);
        d_b.write(t_b);
        d_cin.write(t_cin);
 
        wait(5, SC_NS);
    }
 
}