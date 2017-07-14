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

#include "log_level.hpp"
#include "log_policy.hpp"
#include "log_message.hpp"

namespace bolder {
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
    void add_policy(Log_policy&& policy);

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

/// @name FunsGroupedInDoxygen
///@{
/// A bunch of short-cut macros for engine wide logging
#ifdef BOLDER_LOGGING_VERBOSE
#define BOLDER_LOG_FILE_LINE __FILE__ << ":" << __LINE__ << " \n"
#define BOLDER_LOG_INFO bolder::global_log(Log_level::info) << BOLDER_LOG_FILE_LINE
#define BOLDER_LOG_DEBUG bolder::global_log(Log_level::debug) << BOLDER_LOG_FILE_LINE
#define BOLDER_LOG_WARNING bolder::global_log(Log_level::warning) << BOLDER_LOG_FILE_LINE
#define BOLDER_LOG_ERROR bolder::global_log(Log_level::error) << BOLDER_LOG_FILE_LINE
#define BOLDER_LOG_FATAL bolder::global_log(Log_level::fatal) << BOLDER_LOG_FILE_LINE
#undef BOLDER_LOG_FILE_LINE
#else
#define BOLDER_LOG_INFO bolder::global_log(Log_level::info)
#define BOLDER_LOG_DEBUG bolder::global_log(Log_level::debug)
#define BOLDER_LOG_WARNING bolder::global_log(Log_level::warning)
#define BOLDER_LOG_ERROR bolder::global_log(Log_level::error)
#define BOLDER_LOG_FATAL bolder::global_log(Log_level::fatal)
#endif
///@}

/** @}*/
} // namespace bolder
