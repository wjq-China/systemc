#include "systemc.h"
 
SC_MODULE(monitor){
    sc_in<bool> m_a, m_b, m_cin, m_sum, m_cout;
 
    ofstream outfile;
    void monitor_prc();
 
    SC_CTOR(monitor){
        SC_METHOD(monitor_prc);
        sensitive << m_a << m_b << m_cin << m_sum << m_cout;
        outfile.open("full_adder.out"); //the out file can be find in your exec program folder path.
    }
 
    ~monitor(){
        outfile.close();
    }
 
};
 
inline void monitor::monitor_prc()
{
    outfile << "At time: " << sc_time_stamp() <<"::";
    outfile <<"(a, b, carry_in): ";
    outfile << m_a << m_b << m_cin;
    outfile << " (sum, carry_out): " << m_sum << m_cout << "\n";
    
}