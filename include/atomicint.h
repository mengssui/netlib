/*
 * @Descripttion: 原子操作
 * @version: 0.1
 * @Author: Mengbw
 * @Date: 2021-05-13 09:34:18
 * @LastEditors: Mengbw
 * @LastEditTime: 2021-05-13 10:02:29
 */
#ifndef NETLIB_ATOMIC_INT_
#define NETLIB_ATOMIC_INT_

#include <atomic>

//原子操作使用C++11的atimic中的int和long 的特化版本即可
namespace netlib {

  typedef std::atomic_int AtomicInt32;
  typedef std::atomic_long AtomicInt64;
  
} // namespace netlib 





#endif //NETLIB_ATOMIC_INT_