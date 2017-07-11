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
#include <sstream>
#include <memory>

#include "log_level.hpp"
#include "log_policy.hpp"

namespace bolder {
/** @defgroup log Logger
 * @brief This module provides a simple logger.
 *
 * The logger is [policy-based](https://en.wikipedia.org/wiki/Policy-based_design).
 *
 * @see Log_policy_interface How to define and use your own logging policy.
 *  @{
 */

class Log_message;

class Logger_base {
public:
    Logger_base(std::unique_ptr<Log_policy_interface> policy);
    virtual ~Logger_base();

    /// @brief Log the message
    void flush(const Log_message& message) const;

    /**
     * @brief Create a temporary Log_message to do logging.
     * @param level Level of the logging
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
};

template <typename Policy = Log_debug_policy>
class Logger : public Logger_base {
public:
    Logger()
        : Logger_base{std::unique_ptr<Log_policy_interface> {new Policy}}
    {

    }

    virtual ~Logger() {}

    /**
     * @brief Get a pointer to the policy class
     */
    Policy* policy() {
        return dynamic_cast<Policy*>(Logger_base::policy());
    }

};

/**
 * @brief Object to accumulate whole message
 */
class Log_message {
public:
    /**
     * @brief Move constructor
     * @param msg The message to move
     */
    Log_message(Log_message&& msg);

    /**
     * @brief Move assignment
     * @param msg The message to move
     */
    Log_message& operator=(Log_message&& msg);

    /**
      * @brief Destructor output the message to its owner logger
      */
    ~Log_message() {
        owner_->flush(*this);
    }

    /**
     * @brief Accumulate a variable of type to into log message
     */
    template <typename T>
    Log_message& operator<< (const T& value);

    /**
     * @brief Accumulate iostream manipulator function into log message
     */
    Log_message& operator<< (std::ostream& (*fn)(std::ostream& os));

private:
    friend class Logger_base; // Only logger can initialize Log_message onject

    Log_message(const Logger_base* owner, Log_level level);

    std::ostringstream buffer_;
    const Logger_base* owner_; // Owner of the message
    Log_level level_;
};

/**
 * @brief Globle logger
 *
 * Sample usage:
 * ```cpp
 * g_logger(Log_level::info) << "Hello world\n";
 * ```
 */
extern Logger<Log_debug_policy> g_logger;

/** @}*/

template <typename T>
Log_message& Log_message::operator<< (const T& value) {
    buffer_ << value;
    return *this;
}
}
