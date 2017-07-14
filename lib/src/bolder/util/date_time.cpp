#include <ctime>
#include <iomanip>
#include <sstream>
#include "util/date_time.hpp"

using namespace bolder;
using namespace std::chrono;

/**
 * @brief Get a date/time string from a time_point of system clock
 * @param time The time point we want to output the string
 * @return A string represent time with format Y-m-d h:m:s
 */
std::string utility::date_time_string(const system_clock::time_point& time)
{
    const auto time_c = std::chrono::system_clock::to_time_t(time);

    std::stringstream ss;
    std::tm tm;
    localtime_s(&tm, &time_c);
    ss << std::put_time(&tm, "%Y-%m-%d %X");
    return ss.str();
}
