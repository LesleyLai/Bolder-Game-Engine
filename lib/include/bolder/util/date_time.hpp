#pragma once

#include <chrono>
#include <string>

namespace bolder {
namespace utility {

/// @brief Get a date/time string from a time_point of system clock
std::string date_time_string(const std::chrono::system_clock::time_point& time);

} // namespace utility
} // namespace bolder
