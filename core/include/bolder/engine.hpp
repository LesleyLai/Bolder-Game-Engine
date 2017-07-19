#pragma once

#include <memory>
#include "util/string_literal.hpp"

namespace bolder {

class Engine
{
public:
    Engine(utility::String_literal title);
    ~Engine();

    /// Run the engine
    int exec(int argc, char** argv);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
}
