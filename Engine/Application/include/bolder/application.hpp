#pragma once

#include <memory>
#include <string>
#include "engine.hpp"

namespace bolder {

class Engine;

class Application
{
public:
    Application() noexcept;
    Application(const char* title) noexcept;

    virtual ~Application();

    /**
     * @brief exec Runs the application
     * @param argc number of command line arguments
     * @param argv array of command line arguments strings
     * @return return value return back to the system
     */
    int exec(int argc, char** argv) noexcept;

    /**
     * @brief Initializes the application.
     *
     * Override this function to customize the initialization of the
     * application.
     */
    virtual void initialize() = 0;

    /**
     * @brief Crash report function
     *
     * Override this function to customize crash report.
     */
    virtual void report_crash(const std::string& message) noexcept;

protected:
    /// Return the engine object contained in the application
    Engine& engine() const;

private:
    std::unique_ptr<Engine> engine_;
    const char * title_ = nullptr;
};

}

