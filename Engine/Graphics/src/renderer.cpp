#include "renderer.hpp"
#include "backend.hpp"
#include "bolder/event.hpp"
#include "bolder/events/input_events.hpp"

namespace bolder { namespace graphics {

namespace {
class Window_resize_handler : public event::Handler_trait<event::Window_resize> {
public:
    Window_resize_handler() {}

    void operator()(const event::Window_resize& event) {
        backend::set_view_port(0, 0, event.x, event.y);
    }
};
}

struct Renderer::Impl {
    event::Handler_raii<Window_resize_handler> window_resize_handler;

    Impl(event::Channel& channel) : window_resize_handler{channel} {}
};

Renderer::Renderer(event::Channel& channel)
    : System{channel},
      impl_{std::make_unique<Impl>(channel)}
{
    backend::init();
}

Renderer::~Renderer()
{
}

void Renderer::render()
{
    backend::render();
}

}}
