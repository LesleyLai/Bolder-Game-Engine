#include <iostream>
#include "util/log_policy.hpp"

using namespace bolder;

Log_policy_interface::~Log_policy_interface() {}

Log_debug_policy::~Log_debug_policy() {}

void Log_debug_policy::write(Log_level level, const std::string& msg)
{
    std::cout << msg << "\n";
    file_ << msg << "\n";
}

void Log_debug_policy::open_file(const std::string& filename)
{
    file_.open(filename);
    if (!file_.is_open()) {
        throw std::runtime_error{"LOGGER: Unable to open an output file stream"};
    }
}

void Log_debug_policy::close_file()
{
    if (file_) file_.close();
}

Log_file_policy::~Log_file_policy() {
}

void Log_file_policy::write(Log_level level, const std::string& msg)
{
    file_ << msg << "\n";
}

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
