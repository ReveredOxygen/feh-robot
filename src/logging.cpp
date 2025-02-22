#include "logging.h"

#include <cstdarg>
// #include <iostream>
#include <vector>

using namespace std;
using namespace logging;

Logger logger;

// requires at least C++11
// taken from https://stackoverflow.com/a/49812018
const std::string vformat(const char* const zcFormat, ...) {
    // initialize use of the variable argument array
    va_list vaArgs;
    va_start(vaArgs, zcFormat);

    // reliably acquire the size
    // from a copy of the variable argument array
    // and a functionally reliable call to mock the formatting
    va_list vaArgsCopy;
    va_copy(vaArgsCopy, vaArgs);
    const int iLen = std::vsnprintf(NULL, 0, zcFormat, vaArgsCopy);
    va_end(vaArgsCopy);

    // return a formatted string without risking memory mismanagement
    // and without assuming any compiler or platform specific behavior
    std::vector<char> zc(iLen + 1);
    std::vsnprintf(zc.data(), zc.size(), zcFormat, vaArgs);
    va_end(vaArgs);
    return std::string(zc.data(), iLen);
}

string logging::levelName(LogLevel level) {
    switch (level) {
        case Debug:
            return "DEBUG";
        case Info:
            return "INFO";
        case Warning:
            return "WARN";
        case Error:
            return "ERROR";
    }
}

void Logger::log(string message, string source, LogLevel level) {
    // cout << '[' << source << ' ' << levelName(level) << ']' << ' ' << message
    //      << endl;

    recent.push_back(
        LogMessage{source : source, message : message, level : level});

    if (recent.size() > historyLength) {
        recent.pop_front();
    }
}
