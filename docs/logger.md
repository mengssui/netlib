# 日志类设计实现

> 功能：根据设置的日志等级打印输出

## 日志级别
1. INFO
2. WARNING
3. DEBUG
4. ERROR
5. FATAL

## 实现思路
> Logger类中定义了LoggerStream类，其继承了ostringstream，主要是为了使用stringsteram中的缓冲区。

> 创建LoggerStream临时对象，当期退出当前行时候进行析构，然后输出日志

> 为了实现多线程的日志，使得所有的临时对象要获得同一个锁，因此使Logger有一个mutex，并且创建一个`全局的Logger`对象，需要将该对象引用传递给所有的LoggerStream临时对象

