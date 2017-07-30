#include <chrono>

#include "bolder/exception.hpp"
#include "bolder/engine.hpp"
#include "bolder/display.hpp"
#include "bolder/logger.hpp"
#include "bolder/opengl_context.hpp"

namespace {
    // Check if fps is too low and report to logger
    void check_fps_too_lower(int fps) {
        constexpr int fps_min = 30;
        if (fps < fps_min) {
            BOLDER_LOG_WARNING << "Low frame rate: " << fps << " fps";
            // Todo: Report snapshot of current status of game
        }
    }
}

namespace bolder {
namespace detail {
struct Engine_impl {
    platform::Display display;
    graphics::GL::OpenGL_context gl_context;

    Engine_impl(const char* title)
        : display{title},
          gl_context{} {

    }

    int exec(int argc, char** argv);

    void game_loop();
};

int Engine_impl::exec(int, char**) {
    game_loop();
    return 0;
}

void Engine_impl::game_loop()
{
    using namespace std::chrono;
    auto previous = high_resolution_clock::now();
    duration<double, std::milli> lag {0};

    // Time s(ms) between two update
    constexpr milliseconds ms_per_update {10};

    while (!display.closed()) {
        auto current = high_resolution_clock::now();
        const auto delta_time = current - previous;
        int fps = static_cast<int>(1s / delta_time);

        previous = current;
        lag += delta_time;

        // Todo: process input

        while (lag >= ms_per_update) {
            // Todo: None graphics update
            lag -= ms_per_update;
            // Todo: report error if update takes longer that ms_per_update
        }

        // Render
        gl_context.render();

        // Swap buffer and deal platform message
        display.update();

        check_fps_too_lower(fps);
        // Todo: Set upper limit of the frame rate
    }
}

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
