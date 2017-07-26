#pragma once

/**
 * @file log_policy.hpp Logging policy
 * @brief Engine defined logging policies.
 */

#include <string>
#include <fstream>
#include <chrono>
#include <functional>
#include <memory>

#include "log_level.hpp"
#include "string_literal.hpp"

namespace bolder {
namespace logging {

/** \addtogroup log
 *  @{
 */

/**
 * @brief The output information of a logger
 */
struct logging_info {
    std::chrono::system_clock::time_point time; ///< Time point of logging
    String_literal logger_name; ///< The logger's name
    Log_level level; ///< Log severity level
    std::string msg; ///< Logging message
};

/** @brief Prototype of log policies
 *
 * Logging policies are callback with a logging_info argument.
 */
using Log_policy = std::function<void(const logging_info& info)>;

/**
 * @brief A logging policy of writing message to a file
 */
class Log_file_policy {
public:
    /// Default constructor
    Log_file_policy();

    /// Constructs a Log_file_policy connect to a file
    Log_file_policy(const std::string& filename);

    /// Puts logging information to a file
    void operator()(const logging_info& info);

    /// Lets the logger log into a file with filename
    void open_file(const std::string& filename);

    /// Closes the file that logger append to
    void close_file();

private:
    std::shared_ptr<std::ofstream> file_ptr_;
};

/**
 * @brief Logging policy for stdout
 * @param info A bundle of logging information
 *
 * A logging policy of writing message to standard out.
 */
void Log_print_policy(const logging_info& info);

/** @}*/

} // namespace logging
} // namespace bolder
