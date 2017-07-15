#include "util/logger.hpp"
#include <utility>

using namespace bolder::logging;

/** @defgroup log Logging
 * @brief This module provides a simple logger.
 *
 * All of the module are inside namespace logging. The logger is
 * [policy-based](https://en.wikipedia.org/wiki/Policy-based_design).
 * Every policies are callback that get called when logger try to record
 * information.
 */

namespace  {
// A singleton of the global logger
struct Global_logger {
public:
    static Logger& instance();

private:
    Global_logger();

    Logger logger_;
};


Logger& Global_logger::instance()
{
    static Global_logger instance;
    return instance.logger_;
}

Global_logger::Global_logger() : logger_{"[Bolder]"}
{
    std::string file = "bolderGameEngine.log";
#ifdef BOLDER_LOGGING_VERBOSE
    logger_.add_policy(Log_print_policy);
    logger_.add_policy(Log_file_policy{file});
#else
    logger_.add_policy(Log_file_policy{file});
#endif
}

}

/**
 * @brief Constructs logger with its name
 * @param name The name of the logger
 */
Logger::Logger(const std::string& name)
    : name_{name} {

}

Logger::~Logger() {

}

/**
 * @brief Log the message
 * @param message The message need to be logged
 */
void Logger::flush(const Log_message& message) const {

    auto time = std::chrono::system_clock::now();
    auto level = to_string(message.level_);

    logging_info info{std::move(time), name_,
                std::move(level), message.buffer_.str()};

    for (auto policy : policies_) {
        policy(info);
    }

}

void Logger::add_policy(const Log_policy& policy)
{
    policies_.push_back(policy);
}

/**
 * @brief Create a temporary Log_message to do logging.
 * @param level Level of the logging
 */
Log_message Logger::operator()(Log_level level) const {
    return Log_message {this, level};
}

/**
 * @brief Global logger
 *
 * Sample usage:
 * ```cpp
 * global_log(bolder::logging::Log_level::error) << "Cannot open window\\n";
 * ```
 * An easier way is to use BOLDER_LOG_* Macros
 * @see Global logging macros
 */
Log_message bolder::logging::global_log(Log_level level) {
    return Global_logger::instance()(level);
}
