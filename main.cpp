#include <systemc>
using namespace sc_core;
using namespace std;

SC_MODULE(DeltaExample) {
  sc_signal<int> a, b, c;

  void process_a() {
    a.write(1);
    cout << "a updated to " << a.read() << " at " << sc_time_stamp() << endl;
  }

  void process_b() {
    b.write(a.read() + 1); // b 依赖于 a
    cout << "b updated to " << b.read() << " at " << sc_time_stamp() << endl;
  }

  void process_c() {
    c.write(b.read() + 1); // c 依赖于 b
    cout << "c updated to " << c.read() << " at " << sc_time_stamp() << endl;
  }

  SC_CTOR(DeltaExample) {
    SC_METHOD(process_a);
    sensitive << clk.pos(); // 在时钟上升沿触发

    SC_METHOD(process_b);
    sensitive << a; // 对 a 的变化敏感

    SC_METHOD(process_c);
    sensitive << b; // 对 b 的变化敏感
  }

  sc_in<bool> clk; // 时钟信号
};

int sc_main(int argc, char *argv[]) {
  sc_clock clk("clk", 10, SC_NS); // 10ns 的时钟
  DeltaExample delta_example("delta_example");
  delta_example.clk(clk);

  sc_start(10, SC_NS); // 仿真 10ns
  return 0;
}
