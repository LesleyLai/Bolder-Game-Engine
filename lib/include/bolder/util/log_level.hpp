#pragma once

#include <string>

namespace bolder {
/** \addtogroup log
 *  @{
 */

/**
 * @brief The Log_level enum
 */
enum class Log_level {
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

/**
 * @brief A helper to get a string represent the Log_level
 */
std::string to_string(Log_level level);

/** @}*/
}
