#include "util/log_level.hpp"

std::string bolder::to_string(Log_level level) {
    switch (level) {
    case Log_level::info:
        return "Info";
    case Log_level::debug:
        return "Debug";
    case Log_level::notice:
        return "Notice";
    case Log_level::warning:
        return "Warning";
    case Log_level::error:
        return "Error";
    case Log_level::fatal:
        return "Fatal";
    }
    throw std::invalid_argument("Unexpect input of to_string(Log_level) function");
}
