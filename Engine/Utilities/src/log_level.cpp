#include <sstream>
#include "log_level.hpp"

std::ostream& bolder::logging::operator<<(std::ostream& os,
                                          const Log_level level)
{
    switch (level) {
    case Log_level::info:
        os << "[Info]";
        break;
    case Log_level::debug:
        os << "[Debug]";
        break;
    case Log_level::warning:
        os << "[Warning]";
        break;
    case Log_level::error:
        os << "[Error]";
        break;
    case Log_level::fatal:
        os << "[Fatal]";
        break;
    }

    return os;
}

std::string bolder::logging::to_string(bolder::logging::Log_level level)
{
    std::stringstream ss;
    ss << level;
    return ss.str();
}
