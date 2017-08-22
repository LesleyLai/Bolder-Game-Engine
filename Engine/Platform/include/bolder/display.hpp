#pragma once

#include <memory>
#include "bolder/string_literal.hpp"

namespace bolder {

namespace event {
    class Channel;
}

namespace platform {

namespace detail {
struct Display_impl;
}

// Display for all the platform. Display can be a window on desktop or fullscreen.
class Display
{
public:

    Display(const char* title, event::Channel& channel);
    ~Display();

    // Returns a (width, height) pair
    std::pair<int, int> dimension() const;

    // Returns whether the display is closed
    bool closed() const;

    void update() const;

private:
    std::unique_ptr<detail::Display_impl> impl_;
};

}}
