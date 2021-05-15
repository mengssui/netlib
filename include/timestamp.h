/*
 * @Descripttion: 时间戳类,仅拥有两个静态公开成员返回当前时间戳和过n微秒后的时间戳
 * @version: 0.1
 * @Author: Mengbw
 * @Date: 2021-05-12 09:39:46
 * @LastEditors: Mengbw
 * @LastEditTime: 2021-05-14 20:27:43
 */
#ifndef NETLIB_TIMESTAMP_H_
#define NETLIB_TIMESTAMP_H_

#include "copyable.h"

#include <chrono>
#include <string>
#include <ctime>

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
  static std::string getTimeFormat() {
    time_t t = Clock::to_time_t(now());
    tm* local = localtime(&t);
    char buf[64] = {0};
    strftime(buf, 64, "%Y-%m-%d %H:%M:%S", local);
    return std::string(buf);
  }
};

} // namespace netlib

#endif //NETLIB_TIMESTAMP_H_
