#include "util/logger.hpp"
#include <utility>

using namespace bolder;

Logger<Log_debug_policy> bolder::g_logger {};

Logger_base::Logger_base(std::unique_ptr<Log_policy_interface> policy)
    : policy_{std::move(policy)}
{

}

Logger_base::~Logger_base()
{

}

/**
 * @brief Log the message
 * @param message The message need to be logged
 */
void Logger_base::flush(const Log_message& message) const {
    policy_->write(message.level_, message.buffer_.str());
}

Log_message Logger_base::operator()(Log_level level) const
{
    return Log_message {this, level};
}

Log_policy_interface* Logger_base::policy() const
{
    return policy_.get();
}

Log_message::Log_message(Log_message&& msg) :
    buffer_(std::move(msg.buffer_)),
    owner_(std::move(msg.owner_)),
    level_(std::move(msg.level_)){
    msg.owner_ = nullptr;
}

Log_message& Log_message::operator=(Log_message&& msg) {
    std::swap(buffer_, msg.buffer_);
    std::swap(level_, msg.level_);
    owner_ = std::move(msg.owner_);
    msg.owner_ = nullptr;
    return *this;
}

Log_message::Log_message(const Logger_base* owner, Log_level level) :
    owner_{owner}, level_{level} {
}

Log_message& Log_message::operator<<(std::ostream&(*fn)(std::ostream&)) {
    fn(buffer_);
    return *this;
}
