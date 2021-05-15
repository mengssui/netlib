/*
 * @Descripttion: chrono学习及使用
 * @version: 0.1
 * @Author: Mengbw
 * @Date: 2021-05-12 11:07:40
 * @LastEditors: Mengbw
 * @LastEditTime: 2021-05-14 20:28:06
 */
#include "timestamp.h"

#include <iostream>
#include <chrono>
#include <ctime>

using std::chrono::system_clock;
//using Timestamp = std::chrono::time_point<system_clock>;
using std::cout;
using std::endl;

int main () {
  auto now = netlib::Timestamp::now();

  auto nowafter = netlib::Timestamp::nowAfter(netlib::Microseconds(232));
  cout << std::chrono::duration_cast<netlib::Microseconds>(nowafter - now).count() << endl;
  cout << std::chrono::system_clock::to_time_t(netlib::Timestamp::now()) << endl;
  cout << netlib::Timestamp::getTimeFormat() << endl;
  cout << netlib::Timestamp::getTimeFormat() << endl;

  return 0;
}

