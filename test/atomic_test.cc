/*
 * @Descripttion: 测试原子操作
 * @version: 0.1
 * @Author: Mengbw
 * @Date: 2021-05-13 09:50:20
 * @LastEditors: Mengbw
 * @LastEditTime: 2021-05-13 10:00:53
 */

#include "atomicint.h"

#include <iostream>

int main () {

  netlib::AtomicInt32 int32(5);
  netlib::AtomicInt64 int64(3);

  std::cout << "sizeof : " << sizeof int32 
            << "("  << int32 << ")" << std::endl;

  std::cout << "sizeof : " << sizeof int64 
            << "("  << int64 << ")" << std::endl;
  
  std::cout << int32++ << std::endl;
  std::cout << ++int32 << std::endl;
  std::cout << ++int64 << std::endl;
  std::cout << int64++ << std::endl;
  std::cout << (int64+=4) << std::endl;

  return 0;
}