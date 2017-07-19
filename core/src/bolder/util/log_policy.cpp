#include <iostream>
#include <stdexcept>
#include "util/log_policy.hpp"
#include "util/date_time.hpp"

using namespace bolder::logging;

namespace {
inline void check_file_opened(const std::ofstream& file) {
    if (!file.is_open()) {
        throw std::runtime_error{"LOGGER: Unable to open an output file stream"};
    }
}
}

Log_file_policy::Log_file_policy()
{

}

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
void Log_file_policy::operator()(const logging_info& info)
{
    *file_ptr_ << utility::date_time_string(info.time) << ' ';
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

void Log_file_policy::close_file()
{
    if (file_ptr_) file_ptr_->close();
}

void bolder::logging::Log_print_policy(const logging_info& info)
{
    std::cout << info.logger_name << " " <<
                 info.level << " " << info.msg << "\n";
}
