#pragma once

#include <memory>
#include "bolder/string_literal.hpp"

namespace bolder {

namespace detail {
struct Engine_impl;
}

class Engine
{
public:
    Engine(String_literal title);
    ~Engine();

    /// Run the engine
    int exec(int argc, char** argv);

private:
    std::unique_ptr<detail::Engine_impl> impl_;
};
}
