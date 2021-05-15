<!--
 * @Descripttion: 
 * @version: 0.1
 * @Author: Mengbw
 * @Date: 2021-05-14 21:11:38
 * @LastEditors: Mengbw
 * @LastEditTime: 2021-05-15 20:37:43
-->
# 线程池的设计

> 线程池是典型的生产者和消费者的模型

线程池组成：任务队列、线程池构成
- 任务封装采用 `function` 以及 `typedef` 实现类型别名
- 任务队列：采用vector
- 线程池：`vector`可以扩容，并且使用`unique_ptr`指针指向线程能够进行RAII管理 

关键操作：
1. 取任务，加锁，如果任务队列空需要阻塞
```c++
  //伪代码
  lock(lock)
  while(tasks_.empty()) cond_wait();
  //仅当task不空的时候才执行函数，有可能队列为空了，取出来的task就是end()
  tasks_front();
  if (task) task();
```
2. 添加任务，加锁，并且要通知线程
```c++
  //伪代码,因为队列是无界的，否则要也要用另一个条件变量 
  lock(lock)
  push_back(task);
  notify_one();
```
3. 停止所有线程，首先停止各个线程的循环run，之后调用join
```C++
  //伪代码
  lock(lock);
  notify_all(); //唤醒所有线程，因为该函数会解锁，所以要先加锁
  running_ = false;
  for_each(tasks_) join
```
4. 线程函数
```C++
  //伪代码
  while(running_) {
    gettask();
    task();
  }
```
5. 添加任务方式
```C++
  runTask()
  bind(func,args);
  对于普通函数、成员函数要注意，因为还成员函数有默认的 this 指针
  例如：普通函数 func
  bind(func);
  成员函数 A::func
  bind(&A::fund, this);
```

## BUG
1. 当test程序，新建的线程输出所有的任务时候就会段错误
```sh
2021-05-15 19:49:51 [/home/mengbw/MyNetworkLib/test/logger_test.cc(32) : INFO] main function
2021-05-15 19:49:51 [/home/mengbw/MyNetworkLib/test/logger_test.cc(19) : INFO]  0 140077929879296
2021-05-15 19:49:51 [/home/mengbw/MyNetworkLib/test/logger_test.cc(19) : INFO]  2 140077929879296
2021-05-15 19:49:51 [/home/mengbw/MyNetworkLib/test/logger_test.cc(19) : INFO]  3 140077929879296
2021-05-15 19:49:51 [/home/mengbw/MyNetworkLib/test/logger_test.cc(19) : INFO]  1 140077921486592
2021-05-15 19:49:51 [/home/mengbw/MyNetworkLib/test/logger_test.cc(19) : INFO]  4 140077929879296
2021-05-15 19:49:51 [/home/mengbw/MyNetworkLib/test/logger_test.cc(19) : INFO]  5 140077921486592
2021-05-15 19:49:51 [/home/mengbw/MyNetworkLib/test/logger_test.cc(19) : INFO]  6 140077929879296
2021-05-15 19:49:51 [/home/mengbw/MyNetworkLib/test/logger_test.cc(19) : INFO]  7 140077921486592
2021-05-15 19:49:51 [/home/mengbw/MyNetworkLib/test/logger_test.cc(19) : INFO]  8 140077929879296
2021-05-15 19:49:51 [/home/mengbw/MyNetworkLib/test/logger_test.cc(19) : INFO]  9 140077921486592
2021-05-15 19:49:51 [/home/mengbw/MyNetworkLib/test/logger_test.cc(45) : INFO] 140077947311936
[2]    3477 segmentation fault  ./logger_test
```
==经过两天的修改，意外的修改终于找到了BUG==


## DEBUG经历

1. 经过不断的尝试发现，段错误并不是偶发的，而是仅当子线程均执行完，才会导致段错误
2. 使用gdb尝试，gdb并没有找到段错误的语句 
3. 使用dmesg和nm尝试，能够找到是一个libc-2.23.so库错误，但是根据其位置并没有找到对应的函数
4. 重新阅读程序，找问题。
5. 猜测由于子进程全部退出才会产生段错误，可能应该与任务队列相关，任务队列空的时候依然对其操作可能产生了段错误
6. 分析代码发现可能是其中pop_front在队列非空的情况下依然pop因此出错
7. F12进入pop_front源码发现果然没有判断是否为空的语句
8. 加上`非空条件判断`就行了