/*
 * @Descripttion: 时间戳类,仅拥有两个静态公开成员返回当前时间戳和过n微秒后的时间戳
 * @version: 0.1
 * @Author: Mengbw
 * @Date: 2021-05-12 09:39:46
 * @LastEditors: Mengbw
 * @LastEditTime: 2021-05-12 16:15:06
 */
#ifndef NETLIB_TIMESTAMP_H_
#define NETLIB_TIMESTAMP_H_

#include "copyable.h"

#include <iostream>
#include <chrono>

namespace netlib {

using Microseconds = std::chrono::microseconds;
using Milliseconds = std::chrono::milliseconds;
using Second = std::chrono::seconds;
using Clock = std::chrono::system_clock;

//以微秒为单位
using nowtimestamp =  std::chrono::time_point<Clock>;

class Timestamp : public netlib::Copyable,
                  public Clock 
{
  public:
  static nowtimestamp now() {
    return Clock::now();
  }
  static nowtimestamp nowAfter(Microseconds interval) {
    return now() + interval;
  }
};
  

} // namespace netlib

//重载左移运算符
std::ostream &operator<<(std::ostream &out, const netlib::Timestamp &rhs) {
  out << std::chrono::system_clock::to_time_t(rhs.now());
  return out;
}


#endif //NETLIB_TIMESTAMP_H_
