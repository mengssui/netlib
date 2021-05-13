/*
 * @Descripttion: 不可复制的基类
 * @version: 0.1
 * @Author: Mengbw
 * @Date: 2021-05-13 15:38:41
 * @LastEditors: Mengbw
 * @LastEditTime: 2021-05-13 15:45:30
 */
#ifndef NON_COPYABLE_H_
#define NON_COPYABLE_H_

namespace netlib {
  
class Noncopyable {
public:
  Noncopyable() {}
  ~Noncopyable() {}
private:
  Noncopyable(const Noncopyable &) = delete;
  Noncopyable& operator=(const Noncopyable &rhs) {}
};

} // namespace netlib

#endif //NON_COPYABLE_H_
