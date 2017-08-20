#pragma once

#include <memory>

namespace bolder {

namespace detail {
struct Engine_impl;
}

/// This class manages all the states and the main loop of the game engine
class Engine
{
public:
    Engine(const char* title);
    ~Engine();

    /// Run the engine
    int exec(int argc, char** argv);

private:
    std::unique_ptr<detail::Engine_impl> impl_;
};
}
