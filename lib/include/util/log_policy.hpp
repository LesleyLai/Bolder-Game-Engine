#pragma once

#include <string>
#include <fstream>
#include "log_level.hpp"

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
class Log_policy_interface {
public:
    virtual ~Log_policy_interface();

    virtual void write(Log_level level, const std::string& msg) = 0;
};

/**
 * @brief Logging policy for debugging.
 *
 * A logging policy of writing message both to a file and to standard out
 * in debugging mode. It behaves like Log_file_policy in release mode.
 */
class Log_debug_policy : public Log_policy_interface {
public:
    virtual ~Log_debug_policy();

    void write(Log_level level, const std::string& msg) override;

    /**
     * @brief Lets the logger log into a file with filename
     * @param filename Name of the log file.
     */
    void open_file(const std::string& filename);

    /**
     * @brief Closes the file that logger append to
     */
    void close_file();

private:
    std::ofstream file_;
};

/**
 * @brief A logging policy of writing message to a file
 */
class Log_file_policy : public Log_policy_interface {
    virtual ~Log_file_policy();

    void write(Log_level level, const std::string& msg) override;

    /**
     * @brief Lets the logger log into a file with filename
     * @param filename Name of the log file.
     */
    void open_file(const std::string& filename);

    /**
     * @brief Closes the file that logger append to
     */
    void close_file();

private:
    std::ofstream file_;
};
/** @}*/

} // namespace bolder
