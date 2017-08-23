#pragma once

#include <memory>
#include "bolder/system.hpp"

namespace bolder { namespace graphics {

/**
 * @brief Represents a base class of render API backends
 */
class Graphics_system  : public System
{
public:
    Graphics_system(event::Channel& channel);
    ~Graphics_system();

    /// Initialization function defined by graphics backend
    void init_backend();

    /// Shutdown function defined by graphics backend
    void shutdown_backend();

    void render();

    /// Sets the viewport
    void set_view_port(int x, int y, int width, int height);

private:
    // Implimentation details used cross all graphics backends
    struct Impl;
    std::unique_ptr<Impl> impl_;

    // Implimentation details used by the graphics backend
    struct Backend_impl;
    Backend_impl* backend_impl_ = nullptr;
};

}}

