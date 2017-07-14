#include "util/logger.hpp"
#include <utility>

using namespace bolder;

Logger<Log_debug_policy> bolder::bolder_logger {};

Logger_base::Logger_base(std::unique_ptr<Log_policy_interface> policy)
    : policy_{std::move(policy)} {

}

Logger_base::~Logger_base() {

}

/**
 * @brief Log the message
 * @param message The message need to be logged
 */
void Logger_base::flush(const Log_message& message) const {

    auto time = std::chrono::system_clock::now();
    auto level = to_string(message.level_);

    logging_info info{std::move(time), std::move(level), message.buffer_.str()};

    std::lock_guard<std::mutex> lock(mutex_);
    policy_->write(info);
}

/**
 * @brief Create a temporary Log_message to do logging.
 * @param level Level of the logging
 */
Log_message Logger_base::operator()(Log_level level) const {
    return Log_message {this, level};
}

Log_policy_interface* Logger_base::policy() const {
    return policy_.get();
}
