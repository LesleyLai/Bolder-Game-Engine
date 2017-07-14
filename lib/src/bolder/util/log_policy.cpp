#include <iostream>
#include <stdexcept>
#include "util/log_policy.hpp"
#include "util/date_time.hpp"

using namespace bolder;

Log_policy_interface::~Log_policy_interface() {}

Log_file_policy::~Log_file_policy() {
}

void Log_file_policy::write(const logging_info& info)
{
    file_ << utility::date_time_string(info.time) << ' ';
    file_ << info.level << " " << info.msg << "\n";
}


/**
 * @brief Lets the logger log into a file with filename
 * @param filename Name of the log file.
 */
void Log_file_policy::open_file(const std::string& filename)
{
    file_.open(filename);
    if (!file_.is_open()) {
        throw std::runtime_error{"LOGGER: Unable to open an output file stream"};
    }
}

void Log_file_policy::close_file()
{
    if (file_) file_.close();
}

Log_debug_policy::~Log_debug_policy() {}

void Log_debug_policy::write(const logging_info& info)
{
#ifdef BOLDER_LOGGING_VERBOSE
    std::cout << "[bolder] " << info.level << " " << info.msg << "\n";
#endif
    Log_file_policy::write(info);
}
