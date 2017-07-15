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

namespace bolder {
/** @namespace logging
 *  @brief The namespace of all API relative to logging.
 *  @see log
 */
namespace logging {
/** @defgroup log Logging
 * @brief This module provides a simple logger.
 *
 * All of the module are inside namespace logging. The logger is
 * [policy-based](https://en.wikipedia.org/wiki/Policy-based_design).
 * Every policies are callback that get called when logger try to record
 * information.
 *
 * @see Log_policy Define a callback satisfy this prototype as customized
 * logging policies.
 *  @{
 */

/*!
 * @brief A Logger object output information according to its policies
 */
class Logger {
public:
    Logger(const std::string& name);

    ~Logger();

    /// @brief Logs the message
    void flush(const Log_message& message) const;

    /// @brief Adds a policy to the logger
    void add_policy(const Log_policy& policy);

    /**
     * @brief Create a temporary Log_message to do logging.
     */
    Log_message operator()(Log_level level = Log_level::info) const;

private:
    std::string name_; // Name of the logger
    std::vector<Log_policy> policies_;
};

/**
 * @brief Globle logger
 *
 * Sample usage:
 * ```cpp
 * global_log(bolder::logging::Log_level::error) << "Cannot open window\\n";
 * ```
 *
 * An easier way is to use BOLDER_LOG_* Macros
 * @see Global logging macros
 */
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
 * @brief Short-hand type alias to declear Logger without logging namespace.
 */
using Logger = logging::Logger;
/** @}*/

} // namespace bolder
