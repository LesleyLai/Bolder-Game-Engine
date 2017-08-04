#pragma once

/**
  * @file logger.hpp
  * @brief A logger class.
  *
  * This file contains the Logger module.
  * global_log is the global logger defined in this module. There are also
  * Global logging macros to use the global_log with shorthand notation.
  */

#include <chrono>
#include <functional>
#include <memory>
#include <vector>
#include <sstream>

#include "string_literal.hpp"

namespace bolder {
namespace logging {
class Logger;

/** @addtogroup log
 * @{
 */

/**
 * @brief The Level enum
 */
enum class Level {
    /// Verbose information mainly useful to represent current progress of
    /// application.
    info = 0,
    /// Informational events most useful for developers to debug application,
    /// should output nothing in Release mode.
    debug,
    /// Information representing potential errors in the use of engine.
    warning,
    /// Error event that are not likely severely influence the engine.
    error,
    /// Very severe error event that will presumably lead the engine to crash.
    fatal,
};

/// output a string represent of level to ostream os
std::ostream& operator<<(std::ostream& os, Level level);

/// Return a string represent of level
std::string to_string(Level level);

/**
 * @brief The output information of a logger
 */
struct Info {
    std::chrono::system_clock::time_point time; ///< Time point of logging
    String_literal logger_name; ///< The logger's name
    Level level; ///< Log severity level
    std::string msg; ///< Logging message
};

/** @brief Prototype of log policies
 *
 * Logging policies are callback with a Info argument.
 */
using Log_policy = std::function<void(const Info& info)>;

/// A logging policy of writing message to a file
class Log_file_policy {
public:
    Log_file_policy();
    Log_file_policy(const std::string& filename);

    void operator()(const Info& info);

    void open_file(const std::string& filename);
    void close_file();

private:
    std::shared_ptr<std::ofstream> file_ptr_;
};

/// Logging policy for stdout
void Log_print_policy(const Info& info);

/**
 * @brief Object to accumulate whole message
 *
 * This class is the backend of the Logger class. It will accumulate messages
 * and send them back while destruction. Outside code cannot create a
 * Message, instead Logger will create temporary Message objects whenever
 * user put new message to logger.
 *
 * @see Logger
 */
class Message {
public:
    Message(Message&& msg);
    Message& operator=(Message&& msg);

    ~Message();

    template <typename T>
    Message& operator<< (const T& value);

private:
    friend class Logger; // Only logger can initialize Message onject

    Message(const Logger* owner, Level level);

    std::ostringstream buffer_;
    const Logger* owner_;
    Level level_;
};

/// A Logger object output information according to its policies
class Logger {
public:
    Logger(String_literal name);
    ~Logger();

    void flush(const Message& message) const;

    void add_policy(const Log_policy& policy);

    /// Create a temporary Message to do logging.
    Message operator()(Level level = Level::info) const;

private:
    const String_literal name_; // Name of the logger
    std::vector<Log_policy> policies_;
};

/// Accumulate a variable of type to into log message
template <typename T>
Message& Message::operator<< (const T& value) {
    buffer_ << value;
    return *this;
}

/// Global logger
Message global_log(Level level);

/// @name Global logging macros
///@{
/// A bunch of short-cut macros for engine wide logging
#define BOLDER_Level(level) ::bolder::logging::global_log( \
    ::bolder::logging::Level::level)

#define BOLDER_LOG_INFO BOLDER_Level(info)
#define BOLDER_LOG_DEBUG BOLDER_Level(debug)
#define BOLDER_LOG_WARNING BOLDER_Level(warning)
#define BOLDER_LOG_ERROR BOLDER_Level(error)
#define BOLDER_LOG_FATAL BOLDER_Level(fatal)
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
