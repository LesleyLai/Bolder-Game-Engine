#include "logger.hpp"
#include "date_time.hpp"

#include <iostream>
#include <utility>
#include <fstream>
#include <stdexcept>


namespace bolder { namespace logging {

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

void check_file_opened(const std::ofstream& file) {
    if (!file.is_open()) {
        throw std::runtime_error{"LOGGER: Unable to open an output file stream"};
    }
}

}

/**
 * @brief Constructs logger with its name
 * @param name The name of the logger
 */
Logger::Logger(bolder::String_literal name)
    : name_{name} {

}

Logger::~Logger() {

}

/**
 * @brief Logs the message
 * @param message The message need to be logged
 */
void Logger::flush(const Message& message) const {

    auto time = std::chrono::system_clock::now();

    Info info{std::move(time), name_,
                message.level_, message.buffer_.str()};

    for (auto policy : policies_) {
        policy(info);
    }

}

/// Adds a policy to the logger
void Logger::add_policy(const Log_policy& policy)
{
    policies_.push_back(policy);
}

/**
 * @brief Create a temporary Message to do logging.
 * @param level Level of the logging
 */
Message Logger::operator()(Level level) const {
    return Message {this, level};
}

/**
 * @brief Global logger
 *
 * Sample usage:
 * ```cpp
 * global_log(bolder::logging::Level::error) << "Cannot open window";
 * ```
 * An easier way is to use BOLDER_LOG_* Macros
 * @see Global logging macros
 */
Message global_log(Level level) {
    return Global_logger::instance()(level);
}

/// Destructor output the message to its owner logger
Message::~Message() {
    owner_->flush(*this);
}

/**
 * @brief Move constructor
 * @param msg The message to move from
 */
Message::Message(Message&& msg) :
    buffer_(std::move(msg.buffer_)),
    owner_(std::move(msg.owner_)),
    level_(std::move(msg.level_)){
    msg.owner_ = nullptr;
}

/**
 * @brief Move assignment
 * @param msg The message to move
 */
Message& Message::operator=(Message&& msg) {
    std::swap(buffer_, msg.buffer_);
    std::swap(level_, msg.level_);
    owner_ = std::move(msg.owner_);
    msg.owner_ = nullptr;
    return *this;
}

Message::Message(const Logger* owner, Level level) :
    owner_{owner}, level_{level} {
}

std::ostream& operator<<(std::ostream& os, Level level)
{
    switch (level) {
    case Level::info:
        os << "[Info]";
        break;
    case Level::debug:
        os << "[Debug]";
        break;
    case Level::warning:
        os << "[Warning]";
        break;
    case Level::error:
        os << "[Error]";
        break;
    case Level::fatal:
        os << "[Fatal]";
        break;
    }

    return os;
}

std::string to_string(bolder::logging::Level level)
{
    std::stringstream ss;
    ss << level;
    return ss.str();
}

/// Default constructor
Log_file_policy::Log_file_policy(){}

/**
 * @brief Constructs a Log_file_policy connect to a file
 * @param filename Name of the file to open.
 */
Log_file_policy::Log_file_policy(const std::string& filename)
    : file_ptr_{std::make_shared<std::ofstream>(filename)}
{
    check_file_opened(*file_ptr_);
}


/**
 * @brief Puts logging information to a file
 * @param info A bundle of logging information
 */
void Log_file_policy::operator()(const Info& info)
{
    *file_ptr_ << date_time_string(info.time) << ' ';
    *file_ptr_ << info.level << " " << info.msg << "\n";
}


/**
 * @brief Lets the logger log into a file with filename
 * @param filename Name of the log file.
 */
void Log_file_policy::open_file(const std::string& filename)
{
    file_ptr_->open(filename);
    check_file_opened(*file_ptr_);
}

/// Closes the file that logger append to
void Log_file_policy::close_file()
{
    if (file_ptr_) file_ptr_->close();
}

/**
 * @brief Logging policy for stdout
 * @param info A bundle of logging information
 *
 * A logging policy of writing message to standard out.
 */
void Log_print_policy(const Info& info)
{
    auto output_stream = [&info]() -> decltype(std::cout)& {
        switch (info.level) {
        case Level::debug:
        case Level::info:
            return std::cout;
        case Level::warning:
        case Level::error:
        case Level::fatal:
            return std::cerr;
        }
    };

    output_stream() << info.logger_name << " "
                    << info.level << " "
                    << info.msg << std::endl;
}


}} // namespace bolder::logging
