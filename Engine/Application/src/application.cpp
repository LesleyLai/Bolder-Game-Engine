#include "application.hpp"
#include "bolder/logger.hpp"
#include "bolder/exception.hpp"

using namespace bolder;

Application::Application() noexcept {}

int Application::exec(int argc, char** argv) noexcept
try {
    engine_ = std::make_unique<Engine>("Bolder Demo");
    initialize();
    return engine_->exec(argc, argv);
} catch(const bolder::Exception& e) {
    dump(e);
    return 1;
} catch (const std::exception& e) {
    BOLDER_LOG_FATAL << "C++ exception: " << e.what();
    return 1;
} catch (...) {
    BOLDER_LOG_FATAL << "Unknown exception";
    return 1;
}

void Application::dump(const bolder::Exception& e) noexcept
{
    BOLDER_LOG_FATAL << "Crash report:\n"
                     << e.what();
}

Engine& Application::engine() const
{
    return *engine_;
}

Application::~Application()
{

}
