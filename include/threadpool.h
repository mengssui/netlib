/*
 * @Descripttion: 线程池的封装 
 * @version: 0.1
 * @Author: Mengbw
 * @Date: 2021-05-13 15:35:48
 * @LastEditors: Mengbw
 * @LastEditTime: 2021-05-15 16:22:50
 */
#ifndef NETLIB_THREAD_POOL_
#define NETLIB_THREAD_POOL_

#include "noncopyable.h"
#include "atomicint.h"

#include <string>
#include <condition_variable> 
#include <vector>
#include <deque>
#include <functional>
#include <thread>
#include <mutex>

namespace netlib {


class ThreadPool : public Noncopyable {
public:
  typedef std::function<void()> Task;
  typedef std::unique_ptr<std::thread> ThreadPtr; //指向线程对象的智能指针
  explicit ThreadPool(const std::string &name = std::string());
  ~ThreadPool();

  /**
   * @description: 开启线程池
   * @param {int} numthreads : 线程池线程队列的数量
   * @return {*}
   */
  void start(int numthreads = 0);
  void stop();
  void stopAfterFinishAllTasks();

  void runTask(const Task &onetask);

private:
  void runInThread();              //线程执行函数
  Task getTask();
  std::string name_;               //线程池名称
  std::condition_variable cond_;   //条件变量
  std::mutex mutex_;               //互斥锁 
  std::deque<Task> tasks_;         //任务队列
  netlib::AtomicBool running_;     //线程池是否运行中
  std::vector<ThreadPtr> threads_; //线程对象的指针的数组
};

} // namespace netlib

#endif //NETLIB_THREAD_POOL_