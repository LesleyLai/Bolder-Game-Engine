#include "graphics_system.hpp"
#include "bolder/event.hpp"
#include "bolder/events/window_resize.hpp"

namespace bolder { namespace graphics {

namespace detail {
class Window_resize_handler : public event::Handler_trait<Window_resize_event> {
public:
    Window_resize_handler(Graphics_system& system) : system_{system} {}

    void operator()(const Window_resize_event& event) {
        system_.set_view_port(0, 0, event.x, event.y);
    }

private:
    Graphics_system& system_;
};
}

using Resize_handler = detail::Window_resize_handler;

Graphics_system::Graphics_system(event::Channel& event_channel)
    : System{event_channel},
      window_resize_handler_{std::make_unique<Resize_handler>(*this)}
{
    channel().add_handler<Resize_handler::event_type>(*window_resize_handler_);
}

Graphics_system::~Graphics_system()
{
    channel().remove_handler<Resize_handler::event_type>(*window_resize_handler_);
}

}}
