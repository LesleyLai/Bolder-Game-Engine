#include "bolder/exception.hpp"
#include "bolder/engine.hpp"
#include "bolder/display.hpp"
#include "bolder/opengl_context.hpp"

namespace bolder {
namespace detail {
struct Engine_impl {
    platform::Display display;
    graphics::GL::OpenGL_context gl_context;

    Engine_impl(const char* title)
        : display{title},
          gl_context{} {

    }

    int exec(int /*argc*/, char** /*argv*/) {
        while (!display.closed()) {
            gl_context.render();
            display.update();
        }
        return 0;
    }
};

}

Engine::Engine(const char* title)
    : impl_{std::make_unique<detail::Engine_impl>(title)}
{
}

Engine::~Engine() = default;


int Engine::exec(int argc, char** argv)
{
    return impl_->exec(argc, argv);
}

}
