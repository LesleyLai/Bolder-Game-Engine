#include "bolder/exception.hpp"
#include "bolder/engine.hpp"
#include "bolder/display.hpp"

using namespace bolder;

Engine::Engine(String_literal title)
    : display_{std::make_unique<platform::Display>(title)}
{
}

Engine::~Engine() = default;


int Engine::exec(int /*argc*/, char** /*argv*/)
{
    while (!display_->should_close()) {
        display_->update();
    }
    return 0;
}
