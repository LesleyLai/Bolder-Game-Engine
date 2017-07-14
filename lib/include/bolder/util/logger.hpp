#pragma once

/**
  * @file logger.hpp
  * @brief A logger class.
  *
  * This file contains the Logger class and some implementation details class.
  * g_logger is a global variable defined in this module.
  */

#include <ostream>
#include <string>
#include <memory>
#include <mutex>

#include "log_level.hpp"
#include "log_policy.hpp"
#include "log_message.hpp"

namespace bolder {
/** @defgroup log Logger
 * @brief This module provides a simple logger.
 *
 * The logger is [policy-based](https://en.wikipedia.org/wiki/Policy-based_design).
 *
 * @see Log_policy_interface How to define and use your own logging policy.
 *  @{
 */

class Logger_base {
public:
    Logger_base(std::unique_ptr<Log_policy_interface> policy);
    virtual ~Logger_base();

    /// @brief Log the message
    void flush(const Log_message& message) const;

    /**
     * @brief Create a temporary Log_message to do logging.
     */
    Log_message operator()(Log_level level = Log_level::info) const;

protected:
    /**
     * @brief Access the logging policy of the logger
     * @return a pointer to the logging policy
     */
    Log_policy_interface* policy() const;

private:
    std::unique_ptr<Log_policy_interface> policy_;
    mutable std::mutex mutex_; // Protect the logger
};

template <typename Policy>
class Logger : public Logger_base {
public:
    Logger()
        : Logger_base{std::unique_ptr<Log_policy_interface> {
                      std::make_unique<Policy>()}}
    {

    }

    virtual ~Logger() {}

    /**
     * @brief Get a pointer to the policy class
     */
    Policy* policy() {
        return static_cast<Policy*>(Logger_base::policy());
    }
};

/**
 * @brief Globle logger
 *
 * Sample usage:
 * ```cpp
 * bolder_logger(Log_level::info) << "Hello world\\n";
 * ```
 */
extern Logger<Log_debug_policy> bolder_logger;

/** @}*/
} // namespace bolder
