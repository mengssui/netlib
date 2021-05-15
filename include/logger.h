/*
 * @Descripttion: 日志类
 * @version: 0.1
 * @Author: Mengbw
 * @Date: 2021-05-14 15:47:37
 * @LastEditors: Mengbw
 * @LastEditTime: 2021-05-14 20:42:24
 */
#ifndef LOGGER_H_
#define LOGGER_H_

#include "timestamp.h"

#include <map>
#include <string>
#include <sstream>
#include <mutex>
#include <iostream>


namespace netlib {

class Logger {
public:
  enum LogLevel { //日志等级
    INFO,    //0
    WARNING, //1
    DEBUG,   //... 
    ERROR,
    FATAL
  }; 
  Logger(LogLevel loglevel = INFO);
  ~Logger();
  void setLevel(LogLevel level);
  LogLevel getLevel();
  
  class LoggerStream : public std::ostringstream {
    public:
      LoggerStream(LogLevel level, const char *file_name, int line, Logger &global_logger);
      ~LoggerStream();
    private:
      int line_;
      Timestamp timestamp_;
      LogLevel level_;
      Logger &global_logger_;
  };

  std::map<LogLevel, std::string> level_to_string {
    {INFO, "INFO"},
    {WARNING, "WARNING"},
    {DEBUG, "DEBUG"},
    {ERROR, "ERROR"},
    {FATAL, "FATAL"}
  };
private:
  LogLevel loglevel_;
  std::mutex log_mutex_;
};

//创建一个netlib全局log对象
extern netlib::Logger netlib_global_log;

} // namespace netlib


#define LOG(level) netlib::Logger::LoggerStream\
                    (level, __FILE__, __LINE__, netlib::netlib_global_log)
#define LOG_INFO    LOG(netlib::Logger::LogLevel::INFO)
#define LOG_WARNING LOG(netlib::Logger::LogLevel::WARNING)
#define LOG_DEBUG    LOG(netlib::Logger::LogLevel::DEBUG)
#define LOG_ERROR    LOG(netlib::Logger::LogLevel::ERROR)
#define LOG_FATAL    LOG(netlib::Logger::LogLevel::FATAL)
#define SET_LOG_LEVEL(level) netlib::netlib_global_log.setLevel(level)

#endif //LOGGER_H_