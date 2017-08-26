#include "renderer.hpp"
#include "bolder/event.hpp"
#include "bolder/events/input_events.hpp"

namespace bolder { namespace graphics {

using namespace bolder::event;

namespace {
class Window_resize_handler : public event::Handler_trait<Window_resize> {
public:
    Window_resize_handler(Renderer& system) : system_{system} {}

    void operator()(const Window_resize& event) {
        system_.set_view_port(0, 0, event.x, event.y);
    }

private:
    Renderer& system_;
};
}

struct Renderer::Impl {
    Handler_raii<Window_resize_handler> window_resize_handler;

    Impl(event::Channel& channel,
         Renderer& system) : window_resize_handler{channel, system} {}
};

Renderer::Renderer(event::Channel& channel)
    : System{channel},
      impl_{std::make_unique<Impl>(channel, *this)}
{
    init_backend();
}

Renderer::~Renderer()
{
    shutdown_backend();
}

}}
