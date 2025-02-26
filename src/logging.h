#pragma once

#include <list>
#include <string>

const std::string vformat(const char* const zcFormat, ...);

namespace logging {

enum LogLevel { Debug = 0, Info, Warning, Error };

struct LogMessage {
    std::string source;
    std::string message;
    LogLevel level;
};

class Logger {
   public:
    void log(std::string message, std::string source, LogLevel level = Info);
    std::list<LogMessage> recent;
    int historyLength = 20;
    bool newMessages = false;
};

std::string levelName(LogLevel level);

}   // namespace logging

extern logging::Logger logger;
