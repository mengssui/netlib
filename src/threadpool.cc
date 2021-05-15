#include "threadpool.h"

#include <cassert>
#include <iostream>
#include <algorithm>

namespace netlib {

ThreadPool::ThreadPool(const std::string &name)
  : name_(name), running_(false) {
  }
ThreadPool::~ThreadPool(){
  //如果线程池在运行就停止
  //退出作用域自动停止运行
  if (running_) {
    stop();
  }
}

void ThreadPool::start(int numthreads) {
  //assert不在std命名空间
  assert(threads_.empty());
  running_ = true; //运行开始
  threads_.reserve(numthreads);
  for (int i = 0; i < numthreads; i++) {
    //类的成员函数有默认this指针
    threads_.push_back(std::unique_ptr<std::thread>(
                       new std::thread(&ThreadPool::runInThread, this)));
  }
}

void ThreadPool::stopAfterFinishAllTasks() {
  //FIXME:@mengbw,如下实现有BUG,多线程加入任务时候有BUG
  //FIXME:单线程输入任务也不行
  //完成所有的task之后再停止线程池
  size_t size;
  {
    std::unique_lock<std::mutex> lock(mutex_);
    size = tasks_.size();
  }
  if (size <= 0) {
    stop();
  }
}

void ThreadPool::stop() {
  if (running_ == false) return; //允许多次调用
  { //减少锁的粒度
    std::unique_lock<std::mutex> lock(mutex_);
    running_ = false;
    //因为notify会释放锁，因此要先加锁之后才能够释放，否则报错
    cond_.notify_all(); //唤醒所有的线程，设置running_为false，停止运行
  }
  //等待所有线程结束
  //for_each(threads_.begin(), threads_.end(), std::bind(&std::thread::join, std::placeholders::_1));
  for (auto it = threads_.begin(); it != threads_.end(); it++) {
    (*it)->join(); //等待所有线程执行结束
  }
  return; 
}

void ThreadPool::runTask(const Task &task) {
  //加入一个任务到任务队列
  if (threads_.empty()) { //如果线程池为空， 只有一个主线程，那就在主线程运行
    task();
  } else {
    std::unique_lock<std::mutex> loclock(mutex_);
    tasks_.push_back(task);
    cond_.notify_one();
  }
}

/**
 * @description: 线程执行函数
 * @param {*} 
 * @return {*}
 */
void ThreadPool::runInThread() {
  while (running_) {
    //取任务
    Task task = getTask();
    //执行任务
    if (task) task();
  }
  return;
}

/*
 * @description: 获取任务队列的一个任务
 * @param {*}
 * @return {Task} 返回Task任务
 */
ThreadPool::Task ThreadPool::getTask() {
  //访问临界区加锁
  std::unique_lock<std::mutex> loclock(mutex_);
  //必须时候while，防止虚假唤醒
  while (tasks_.empty() && running_) {
    cond_.wait(loclock);
  }
  //当有任务才取出任务并且执行,否则这里会导致段错误的BUG
  Task task; 
  if (!tasks_.empty()) {
    task = tasks_.front();
    tasks_.pop_front();
  }
  return task;
}

} // namespace netlib
