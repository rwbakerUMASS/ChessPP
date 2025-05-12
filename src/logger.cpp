#include "logger.h"

void Logger::log(LogLevel level, const string& msg, const char* file, int line) 
{
    if (maxLogLevel == LOG_LEVEL_UNK)
    {
        maxLogLevel = LOG_LEVEL_FATAL;
        Logger::log(LOG_LEVEL_FATAL,"Logger::log(): maxLogLevel was not set!",__FILE__,__LINE__);
    }

    if (level < maxLogLevel) {
        return;
    }

    ostringstream out;
    out << "[" << timeNow() << "] "
        << "[" << levelToStr(level) << "] "
        << "[" << file << ":" << line << "] " << msg << "\n";

    cerr << out.str();
    
    if (level == LOG_LEVEL_FATAL) {
        exit(EXIT_FAILURE);
    }
}

void Logger::setMaxLogLevel(LogLevel level) {
    maxLogLevel = level;
}

string Logger::timeNow() 
{
    time_t now = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return buf;
}

const char* Logger::levelToStr(LogLevel level) {
    switch (level) {
        case LOG_LEVEL_TRACE: return "TRACE";
        case LOG_LEVEL_DEBUG: return "DEBUG";
        case LOG_LEVEL_INFO:  return "INFO";
        case LOG_LEVEL_WARN:  return "WARN";
        case LOG_LEVEL_ERROR: return "ERROR";
        case LOG_LEVEL_FATAL: return "FATAL";
        default:              return "UNKNOWN";
    }
}
LogLevel Logger::maxLogLevel = LOG_LEVEL_UNK;