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