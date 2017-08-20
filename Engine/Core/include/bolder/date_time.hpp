#pragma once

/**
  * @file date_time.hpp
  * @brief Utilitie functions concern about date and time.
  */

#include <chrono>
#include <string>

namespace bolder {

/** @addtogroup utilities
 * @{
 */

/**
 * @brief Getss a date/time string from a time_point of system clock
 */
std::string date_time_string(const std::chrono::system_clock::time_point& time);

/** @}*/

} // namespace bolder
