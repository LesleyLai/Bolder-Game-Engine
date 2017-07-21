#pragma once

#include <memory>
#include "util/string_literal.hpp"

namespace bolder {

namespace platform {
class Display;
}

class Engine
{
public:
    Engine(utility::String_literal title);
    ~Engine();

    /// Run the engine
    int exec(int argc, char** argv);

private:
    std::unique_ptr<platform::Display> display_;
};
}
