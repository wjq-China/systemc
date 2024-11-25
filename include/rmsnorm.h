#include <cassert>
#include <cmath>
#include <iostream>
#include <systemc>
#include <vector>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

// RMSNorm 模块
SC_MODULE(RMSNorm) {
  sc_fifo_in<double> input_port;   // 输入端口
  sc_fifo_out<double> output_port; // 输出端口
  sc_fifo_out<double> rms_port;    // RMS输出端口 (供测试用)
  sc_out<bool> done;               // 信号：完成标志

  int d;                // 向量维度
  double epsilon;       // 防止除零的小常数
  vector<double> gamma; // 可学习参数

  SC_CTOR(RMSNorm) : d(5), epsilon(1e-8) {
    gamma.resize(d, 1.0);       // 初始化gamma为全1
    SC_THREAD(process_rmsnorm); // 线程定义
  }

  void set_gamma(const vector<double> &new_gamma) {
    assert(new_gamma.size() == d && "Gamma size must match vector dimension!");
    gamma = new_gamma;
  }

  void process_rmsnorm() {
    vector<double> input_vector(d);

    // 1. 读取输入数据
    for (int i = 0; i < d; ++i) {
      input_vector[i] = input_port.read();
    }

    // 2. 计算均方根值 (RMS)
    double sum_squares = 0.0;
    for (double val : input_vector) {
      sum_squares += val * val;
    }
    double rms = sqrt(sum_squares / d + epsilon);
    rms_port.write(rms);

    // 3. 归一化并应用 gamma 参数
    for (int i = 0; i < d; ++i) {
      double normalized = (input_vector[i] / rms) * gamma[i];
      output_port.write(normalized);
    }

    // 4. 标记完成
    done.write(true);
  }
};
