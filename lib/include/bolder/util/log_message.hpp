#pragma once

/**
  * @file log_message.hpp
  * @brief Contains message to log.
  */


#include <sstream>
#include "log_level.hpp"

namespace bolder {
namespace logging {

class Logger;
/** \addtogroup log
 *  @{
 */

/**
 * @brief Object to accumulate whole message
 *
 * Log_message is the backend of the Logger class. It will accumulate messages
 * and send them back while destruction. Outside code cannot create a
 * Log_message, instead Logger will create temporary Log_message objects whenever
 * user put new message to logger.
 *
 * @see Logger
 */
class Log_message {
public:
    /// Move constructor
    Log_message(Log_message&& msg);

    /// Move assignment
    Log_message& operator=(Log_message&& msg);

    /// Destructor output the message to its owner logger
    ~Log_message();

    /// Accumulate a variable of type to into log message
    template <typename T>
    Log_message& operator<< (const T& value);

private:
    friend class Logger; // Only logger can initialize Log_message onject

    Log_message(const Logger* owner, Log_level level);

    std::ostringstream buffer_;
    const Logger* owner_;
    Log_level level_;
};

template <typename T>
Log_message& Log_message::operator<< (const T& value) {
    buffer_ << value;
    return *this;
}

/** @}*/
} // namespace logging
}
