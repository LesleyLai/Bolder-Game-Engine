#pragma once

#include <memory>
#include "bolder/system.hpp"

namespace bolder {

namespace graphics {

namespace detail {
    class Window_resize_handler;
}

/**
 * @brief Represents a base class of render API backends
 */
class Graphics_system : public System
{
public:
    Graphics_system(event::Channel& channel);
    ~Graphics_system();

    virtual void render() = 0;

    /// Sets the viewport
    virtual void set_view_port(int x, int y, int width, int height) = 0;

private:
    std::unique_ptr<detail::Window_resize_handler> window_resize_handler_;
};

}}

