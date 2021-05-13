/*
 * @Descripttion: 熟悉C++11多线程的使用
 * @version: 0.1
 * @Author: Mengbw
 * @Date: 2021-05-13 10:46:48
 * @LastEditors: Mengbw
 * @LastEditTime: 2021-05-13 11:20:10
 */

#include "timestamp.h"

#include <iostream>
#include <thread>
#include <mutex>

using std::cout;
using std::endl;
using std::thread;

std::mutex gm;

void func(int &cnt) {
  for (int i = 0; i < 100; i++) {
    std::this_thread::sleep_for(netlib::Microseconds(3));
    std::lock_guard<std::mutex> guard(gm);
    cnt++;
    cout << cnt << endl;
    //离开作用域后销毁解锁
  }
  return;
}

int n = 0;

int main() {
  //int n = 0;
  
  //传入引用如果不使用ref会导致编译错误
  thread t1(func, std::ref(n));
  thread t2(func, std::ref(n));
  // thread t1(func, n);
  // thread t2(func, n);
  cout << std::this_thread::get_id() << endl;
  cout << t1.get_id() << endl;
  cout << t2.get_id() << endl;

  t1.join();
  t2.join();


  return 0;
}
