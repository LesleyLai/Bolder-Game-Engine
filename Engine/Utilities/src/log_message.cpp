#include "logger.hpp"
#include "log_message.hpp"

using namespace bolder::logging;

Log_message::~Log_message() {
    owner_->flush(*this);
}

/**
 * @brief Move constructor
 * @param msg The message to move from
 */
Log_message::Log_message(Log_message&& msg) :
    buffer_(std::move(msg.buffer_)),
    owner_(std::move(msg.owner_)),
    level_(std::move(msg.level_)){
    msg.owner_ = nullptr;
}

/**
 * @brief Move assignment
 * @param msg The message to move
 */
Log_message& Log_message::operator=(Log_message&& msg) {
    std::swap(buffer_, msg.buffer_);
    std::swap(level_, msg.level_);
    owner_ = std::move(msg.owner_);
    msg.owner_ = nullptr;
    return *this;
}

Log_message::Log_message(const Logger* owner, Log_level level) :
    owner_{owner}, level_{level} {
}
