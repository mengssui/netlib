#include "logger.h"
#include "timestamp.h"

namespace netlib {
  

//Logger
Logger::Logger(Logger::LogLevel loglevel) : loglevel_(loglevel) { }
Logger::~Logger() {}

void Logger::setLevel(Logger::LogLevel level) {
  loglevel_ = level;
}

Logger::LogLevel Logger::getLevel() {
  return loglevel_;
}

//全局的Logger对象
Logger netlib_global_log;

//LoggerStream
Logger::LoggerStream::LoggerStream(LogLevel level, const char *file_name, 
                                    int line, Logger &global_logger)
  : line_(line), level_(level), global_logger_(global_logger) {

    //构造now对象引用自身，然后之后往自身缓冲区加入内容
    std::ostringstream &now = *this; 
    now << timestamp_.getTimeFormat() << " ";
    now << '[' << file_name << "(" << line_ <<  ") : " 
        << global_logger.level_to_string[level_] << "] ";
  }

Logger::LoggerStream::~LoggerStream() {
  if (level_ < global_logger_.loglevel_) return;
  //加锁，访问cout对象是互斥的，防止输出日志乱序
  std::unique_lock<std::mutex> lock(global_logger_.log_mutex_);
  std::cout << this->str() << std::endl;
  if (level_ == FATAL) abort(); //如果是fatal错误，终止程序
}

} // namespace netlib 
