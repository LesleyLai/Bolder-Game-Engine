#include <chrono>
#include <thread>

#include "bolder/exception.hpp"
#include "engine.hpp"
#include "bolder/display.hpp"
#include "bolder/event.hpp"
#include "bolder/logger.hpp"
#include "bolder/renderer.hpp"

namespace {
    // Check if fps is too low and report to logger
    void check_fps_too_lower(double fps) {
        constexpr double fps_min = 30;
        if (fps < fps_min) {
            BOLDER_LOG_WARNING << "Low frame rate: " << fps << " fps";
            // Todo: Report snapshot of current status of game
        }
    }
}

namespace bolder {
namespace detail {
struct Engine_impl {
    event::Channel channel;
    platform::Display display;
    std::unique_ptr<graphics::Renderer> graphics;

    Engine_impl(const char* title)
        : channel{},
          display{title, channel},
          graphics{std::make_unique<graphics::Renderer>(channel)} {

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
    using Ms = duration<double, std::milli>;

    auto previous = high_resolution_clock::now();
    Ms lag {0};

    // Time s(ms) between two update
    constexpr milliseconds ms_per_update {10};

    while (!display.closed()) {
        auto current = high_resolution_clock::now();
        const auto delta_time = duration_cast<Ms>(current - previous);

        lag += delta_time;

        // Todo: process input

        while (lag >= ms_per_update) {
            // Todo: None graphics update
            lag -= ms_per_update;
            // Todo: report error if update takes longer that ms_per_update
        }

        // Render
        graphics->render();

        // Swap buffer and deal platform message
        display.update();

        previous = current;
        double fps = 1s / delta_time;

        check_fps_too_lower(fps);
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
