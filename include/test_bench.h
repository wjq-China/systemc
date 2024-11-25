#include "rmsnorm.h"
SC_MODULE(Testbench) {
  sc_fifo<double> input_fifo;  // 输入 FIFO
  sc_fifo<double> output_fifo; // 输出 FIFO
  sc_fifo<double> rms_fifo;    // RMS FIFO
  sc_signal<bool> done_signal; // 完成信号

  RMSNorm *rmsnorm; // RMSNorm 模块实例

  SC_CTOR(Testbench) {
    // 初始化模块
    rmsnorm = new RMSNorm("RMSNorm");
    rmsnorm->input_port(input_fifo);
    rmsnorm->output_port(output_fifo);
    rmsnorm->rms_port(rms_fifo);
    rmsnorm->done(done_signal);

    SC_THREAD(generate_inputs); // 输入生成线程
    SC_THREAD(check_outputs);   // 输出验证线程
  }

  void generate_inputs() {
    // 输入数据
    vector<double> inputs = {1.0, 2.0, 3.0, 4.0, 5.0};
    for (double val : inputs) {
      input_fifo.write(val);
    }
  }

  void check_outputs() {
    wait(10, SC_NS); // 模拟等待模块完成

    // 检查 RMS 值
    double rms = rms_fifo.read();
    cout << "RMS: " << rms << endl;

    // 读取输出结果
    vector<double> expected_output = {0.3015, 0.6030, 0.9045, 1.2060, 1.5076};
    for (double expected : expected_output) {
      double output = output_fifo.read();
      cout << "Output: " << output << ", Expected: " << expected << endl;

      // 断言输出正确
      assert(abs(output - expected) < 1e-3 && "Output mismatch!");
    }

    if (done_signal.read()) {
      cout << "RMSNorm computation completed successfully." << endl;
    } else {
      cout << "RMSNorm computation not completed!" << endl;
    }

    sc_stop(); // 结束仿真
  }
};
