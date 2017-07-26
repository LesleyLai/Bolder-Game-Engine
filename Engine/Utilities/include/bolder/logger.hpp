#pragma once

/**
  * @file logger.hpp
  * @brief A logger class.
  *
  * This file contains the Logger class.
  * global_log is the global logger defined in this module. There are also
  * Global logging macros to use the global_log with shorthand notation.
  */

#include <string>
#include <vector>

#include "log_policy.hpp"
#include "log_level.hpp"
#include "log_message.hpp"
#include "string_literal.hpp"

namespace bolder {
namespace logging {
/** @addtogroup log
 * @{
 */

/// A Logger object output information according to its policies
class Logger {
public:
    Logger(String_literal name);

    ~Logger();

    /// Logs the message
    void flush(const Log_message& message) const;

    /// Adds a policy to the logger
    void add_policy(const Log_policy& policy);

    /// Create a temporary Log_message to do logging.
    Log_message operator()(Log_level level = Log_level::info) const;

private:
    const String_literal name_; // Name of the logger
    std::vector<Log_policy> policies_;
};

/// Global logger
Log_message global_log(Log_level level);

/// @name Global logging macros
///@{
/// A bunch of short-cut macros for engine wide logging
#define BOLDER_LOG_LEVEL(level) ::bolder::logging::global_log( \
    ::bolder::logging::Log_level::level)

#define BOLDER_LOG_INFO BOLDER_LOG_LEVEL(info)
#define BOLDER_LOG_DEBUG BOLDER_LOG_LEVEL(debug)
#define BOLDER_LOG_WARNING BOLDER_LOG_LEVEL(warning)
#define BOLDER_LOG_ERROR BOLDER_LOG_LEVEL(error)
#define BOLDER_LOG_FATAL BOLDER_LOG_LEVEL(fatal)
///@}

/** @}*/
} // namespace logging

/** @addtogroup log
 *  @{
 */

/// Short-hand type alias to declear Logger without logging namespace.
using Logger = logging::Logger;
/** @}*/

} // namespace bolder
