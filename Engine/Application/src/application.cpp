#include "application.hpp"
#include "bolder/logger.hpp"
#include "bolder/exception.hpp"

static constexpr const char* default_title = "Bolder game engine application";

using namespace bolder;

Application::Application() noexcept {}

Application::Application(const char* title) noexcept
{
    title_ = title;
}

Application::~Application()
{

}

int Application::exec(int argc, char** argv) noexcept
try {
    title_ = title_ ? title_ : default_title;
    engine_ = std::make_unique<Engine>(title_);
    initialize();
    return engine_->exec(argc, argv);
} catch(const bolder::Exception& e) {
    report_crash(e.what());
    return 1;
} catch (const std::exception& e) {
    report_crash(std::string{"C++ exception: "} + e.what());
    return 1;
} catch (...) {
    report_crash("Unknown C++ exception");
    return 1;
}

void Application::report_crash(const std::string& message) noexcept
{
    BOLDER_LOG_FATAL << "Crash report:\n" << message;
}

Engine& Application::engine() const
{
    return *engine_;
}
