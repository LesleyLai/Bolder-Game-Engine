#pragma once

#include <memory>
#include <string>

namespace bolder { namespace platform {

// Display for all the platform. Display can be a window on desktop or fullscreen.
class Display
{
public:
    Display(const char* title);
    ~Display();

    int width() const;
    int height() const;

    // Returns whether the display should close
    bool should_close() const;

    void update();

private:
    struct Display_impl;
    std::unique_ptr<Display_impl> impl_;
};

} }

