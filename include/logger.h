#ifndef CHESSPP_LOGGER_H
#define CHESSPP_LOGGER_H

#include <string>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

enum LogLevel {
    LOG_LEVEL_TRACE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL,
    LOG_LEVEL_UNK
};

class Logger {
public:
    static void log(LogLevel level, const string& msg, const char* file, int line);
    static void setMaxLogLevel(LogLevel level);
    Logger();

private:
    static LogLevel maxLogLevel;
    static string timeNow();
    static const char* levelToStr(LogLevel level);

};


#define LOG_TRACE(msg)          Logger::log(LOG_LEVEL_TRACE, msg, __FILE__, __LINE__)
#define LOG_DEBUG(msg)          Logger::log(LOG_LEVEL_DEBUG, msg, __FILE__, __LINE__)
#define LOG_INFO(msg)           Logger::log(LOG_LEVEL_INFO, msg, __FILE__, __LINE__)
#define LOG_WARN(msg)           Logger::log(LOG_LEVEL_WARN, msg, __FILE__, __LINE__)
#define LOG_ERROR(msg)          Logger::log(LOG_LEVEL_ERROR, msg, __FILE__, __LINE__)
#define LOG_FATAL(msg)          Logger::log(LOG_LEVEL_FATAL, msg, __FILE__, __LINE__)
#define SET_LOG_LEVEL(level)    Logger::setMaxLogLevel(level)

#endif
