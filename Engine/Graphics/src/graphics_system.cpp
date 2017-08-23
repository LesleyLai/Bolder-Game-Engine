#include "graphics_system.hpp"
#include "bolder/event.hpp"
#include "bolder/events/input_events.hpp"

namespace bolder { namespace graphics {

using namespace bolder::event;

namespace {
class Window_resize_handler : public event::Handler_trait<Window_resize> {
public:
    Window_resize_handler(Graphics_system& system) : system_{system} {}

    void operator()(const Window_resize& event) {
        system_.set_view_port(0, 0, event.x, event.y);
    }

private:
    Graphics_system& system_;
};
}

struct Graphics_system::Impl {
    Handler_raii<Window_resize_handler> window_resize_handler;

    Impl(event::Channel& channel,
         Graphics_system& system) : window_resize_handler{channel, system} {}
};

Graphics_system::Graphics_system(event::Channel& channel)
    : System{channel},
      impl_{std::make_unique<Impl>(channel, *this)}
{
    init_backend();
}

Graphics_system::~Graphics_system()
{
    shutdown_backend();
}

}}
