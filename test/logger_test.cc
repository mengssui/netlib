/*
 * @Descripttion: 测试日志的使用
 * @version: 0.1
 * @Author: Mengbw
 * @Date: 2021-05-14 19:30:51
 * @LastEditors: Mengbw
 * @LastEditTime: 2021-05-15 20:58:17
 */

#include "threadpool.h"
#include "timestamp.h"
#include "logger.h"

class Output {
public:
  Output();
  void outputInfo(int num) {
    //logStream的基类重载了 左移 <<  运算符
    // LOG_INFO  << " " << num << " " << std::this_thread::get_id();
    std::cout << "Hi" << std::endl;
  }
  ~Output();
};

Output::Output(/* args */) { }

Output::~Output() { }


int main () {
  Output out;
  netlib::ThreadPool tp("my_thread_pool"); 
  // LOG_INFO << "main function";

  tp.start(4);

  for (int i = 0; i < 100; i++) {
    tp.runTask(std::bind(&Output::outputInfo, &out, i));
  }
  

  std::this_thread::sleep_for(netlib::Second(2));
  tp.stop();
  std::this_thread::sleep_for(netlib::Second(3));
   
  LOG_INFO << std::this_thread::get_id();

  //如果子线程完成所有的任务时候，会出现的段错误@mengbw
  //FIXED:@mengbw: 错误原因:由于pop_front从空的vector pop导致错误[已修复]

  return 0;
}