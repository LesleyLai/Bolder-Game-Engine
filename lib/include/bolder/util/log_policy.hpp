#pragma once

#include <string>
#include <fstream>
#include <chrono>

/**
 * @file log_policy.hpp Logging policy
 * @brief Engine defined logging policies.
 *
 * Logging policies are class with a "write" function to log its argument into.
 */

namespace bolder {
/** \addtogroup log
 *  @{
 */

/**
 * @brief The output information of a logger
 */
struct logging_info {
    std::chrono::system_clock::time_point time; ///< Time point of logging
    std::string level; ///< string of log level
    std::string msg;
};

class Log_policy_interface {
public:
    virtual ~Log_policy_interface();

    /**
     * @brief Write the log message according to the policy
     * @param msg The log message to write
     */
    virtual void write(const logging_info&) = 0;
};

/**
 * @brief A logging policy of writing message to a file
 */
class Log_file_policy : public Log_policy_interface {
public:
    virtual ~Log_file_policy();

    void write(const logging_info& info) override;

    /// @brief Lets the logger log into a file with filename
    void open_file(const std::string& filename);

    /**
     * @brief Closes the file that logger append to
     */
    void close_file();

private:
    std::ofstream file_;
};

/**
 * @brief Logging policy for debugging.
 *
 * A logging policy of writing message both to a file and to standard out
 * in debugging mode. It behaves like Log_file_policy in release mode.
 */
class Log_debug_policy : public Log_file_policy {
public:
    virtual ~Log_debug_policy();

    void write(const logging_info& info) override;
};

/** @}*/

} // namespace bolder
