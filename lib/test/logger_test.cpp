#include "doctest.h"
#include <sstream>

#include "util/logger.hpp"

using namespace bolder;

class Log_test_policy {
public:
    Log_test_policy(std::ostringstream& ss);
    ~Log_test_policy();

    void bind_sstream(std::shared_ptr<std::ostringstream> ss);

    void operator()(const logging::logging_info& info);

private:
    std::ostringstream& ss_;
};

TEST_CASE("Get correct log level string from to_string") {
    REQUIRE_EQ(to_string(logging::Log_level::warning), "[Warning]");

}

TEST_CASE("logger work with stream style logging") {
    std::ostringstream ss;
    Logger test_logger {"[Test]"};
    test_logger.add_policy(Log_test_policy{ss});
    test_logger(logging::Log_level::debug) << "Test output " << std::hex << 42;
    REQUIRE_EQ(ss.str(), "[Debug] Test output 2a");
}

// Implementation details of the log test policy
Log_test_policy::Log_test_policy(std::ostringstream& ss) : ss_{ss} {}
Log_test_policy::~Log_test_policy() {}

void Log_test_policy::operator()(const logging::logging_info& info) {
    ss_ << info.level << " " << info.msg;
}
