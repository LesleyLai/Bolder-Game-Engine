#pragma once

#include <memory>
#include "bolder/string_literal.hpp"

namespace bolder { namespace platform {

// Display for all the platform. Display can be a window on desktop or fullscreen.
class Display
{
public:
    Display(String_literal title);
    ~Display();

    // Returns a (width, height) pair
    std::pair<int, int> dimension() const;

    // Returns whether the display is closed
    bool closed() const;

    void update() const;

private:
    struct Display_impl;
    std::unique_ptr<Display_impl> impl_;
};

}}

