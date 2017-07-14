#include "util/logger.hpp"
#include "util/log_message.hpp"

using namespace bolder;

Log_message::~Log_message() {
    owner_->flush(*this);
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
