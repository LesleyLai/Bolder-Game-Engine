#include "util/logger.hpp"
#include <utility>

using namespace bolder::logging;

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

    std::lock_guard<std::mutex> lock(mutex_);
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

Log_message bolder::logging::global_log(Log_level level) {
    std::string file = "bolderGameEngine.log";
    static Logger bolder_logger {"[Bolder]"};
#ifdef BOLDER_LOGGING_VERBOSE
    bolder_logger.add_policy(Log_print_policy);
    bolder_logger.add_policy(Log_file_policy{file});
#else
    bolder_logger.add_policy(Log_file_policy{file});
#endif
    return bolder_logger(level);
}
