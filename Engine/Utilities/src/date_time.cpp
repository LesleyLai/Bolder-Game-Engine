#include <iomanip>
#include <sstream>
#include <ctime>
#include "date_time.hpp"

/**
 * @brief Get a date/time string from a time_point of system clock
 * @param time The time point we want to output the string
 * @return A string represent time with format Y-m-d h:m:s
 */
std::string bolder::utility::date_time_string(
        const std::chrono::system_clock::time_point& time) {
    const auto time_c = std::chrono::system_clock::to_time_t(time);

    std::stringstream ss;

    auto tm = localtime(&time_c);
    ss << std::put_time(tm, "%Y-%m-%d %X");
    return ss.str();
}
