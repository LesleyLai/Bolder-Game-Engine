#pragma once

/**
  * @file logger.hpp
  * @brief A logger class.
  *
  * This file contains the Logger class and some implementation details class.
  * g_logger is a global variable defined in this module.
  */

#include <string>
#include <mutex>
#include <vector>

#include "log_policy.hpp"
#include "log_level.hpp"
#include "log_message.hpp"

namespace bolder {
namespace logging {
/** @defgroup log Logger
 * @brief This module provides a simple logger.
 *
 * The logger is [policy-based](https://en.wikipedia.org/wiki/Policy-based_design).
 * Every policies are callback that get called when logger try to record
 * information.
 *
 * @see Log_policy How to define and use customized logging policics.
 *  @{
 */

class Logger {
public:
    Logger(const std::string& name);

    ~Logger();

    /// @brief Log the message
    void flush(const Log_message& message) const;

    void add_policy(const Log_policy& policy);

    /**
     * @brief Create a temporary Log_message to do logging.
     */
    Log_message operator()(Log_level level = Log_level::info) const;

private:
    std::string name_; // Name of the logger
    std::vector<Log_policy> policies_;
    mutable std::mutex mutex_; // Protect the logger
};


/**
 * @brief Globle logger
 *
 * Sample usage:
 * ```cpp
 * global_log(Log_level::error) << "Cannot open window\\n";
 * ```
 */
Log_message global_log(Log_level level);

/// @name Global logging macros
///@{
/// A bunch of short-cut macros for engine wide logging
#define BOLDER_LOG_level(level) ::bolder::logging::global_log( \
    ::bolder::logging::Log_level::level)

#define BOLDER_LOG_INFO BOLDER_LOG_level(info)
#define BOLDER_LOG_DEBUG BOLDER_LOG_level(debug)
#define BOLDER_LOG_WARNING BOLDER_LOG_level(warning)
#define BOLDER_LOG_ERROR BOLDER_LOG_level(error)
#define BOLDER_LOG_FATAL BOLDER_LOG_level(fatal)
///@}

/** @}*/
} // namespace logging
} // namespace bolder
