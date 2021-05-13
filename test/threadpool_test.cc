/*
 * @Descripttion: 测试线程池功能
 * @version: 0.1
 * @Author: Mengbw
 * @Date: 2021-05-13 18:08:08
 * @LastEditors: Mengbw
 * @LastEditTime: 2021-05-13 21:37:08
 */

#include "threadpool.h"
#include "timestamp.h"
#include <iostream>
using std::cout;
using std::endl;


void func() {
  cout << std::this_thread::get_id();
  cout << " hi!" << endl;
}

int main () {
  cout << "main" << endl;
  netlib::ThreadPool tp1(std::string("tp1"));

  //开启线程池
  tp1.start(2);

  for (int i = 0; i < 200; i++) {
    // tp1.runTask([i]()
                //  {cout << "tp<" << i << ">" << "hi" << endl;});
    tp1.runTask(func); 
  }

  //tp1.stopAfterFinishAllTasks();
  //tp1.stop();

  return 0;
}