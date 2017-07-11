#include "doctest.h"
#include "util/logger.hpp"
#include <sstream>
#include <memory>
#include <utility>

using namespace bolder;

class Log_test_policy : public Log_policy_interface {
public:
    Log_test_policy() {}
    ~Log_test_policy();

    void bind_sstream(std::shared_ptr<std::ostringstream> ss);

    void write(Log_level level, const std::string& msg) override;

private:
    std::shared_ptr<std::ostringstream> ss_;
};

TEST_CASE("Get correct log level string from to_string") {
    REQUIRE(to_string(Log_level::notice) == "Notice");
}

TEST_CASE("logger work with stream style logging") {
    auto ss_ptr = std::make_shared<std::ostringstream>();
    Logger<Log_test_policy> test_logger;
    test_logger.policy()->bind_sstream(ss_ptr);

    test_logger(Log_level::debug) << "Test output " << std::hex << 42;
    REQUIRE(ss_ptr->str() == "<Debug> Test output 2a");
}

// =============================================================================
// Implementation details of the log test policy
// =============================================================================
Log_test_policy::~Log_test_policy() {}

void Log_test_policy::bind_sstream(std::shared_ptr<std::ostringstream> ss) {
    ss_ = ss;
}

void Log_test_policy::write(Log_level level, const std::string& msg) {

    *(ss_) << "<" << to_string(level) << "> " << msg;
}
