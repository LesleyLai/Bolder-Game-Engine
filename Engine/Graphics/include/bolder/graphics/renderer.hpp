#pragma once

#include <memory>
#include "bolder/system.hpp"

namespace bolder { namespace graphics {

/**
 * @brief Represents a base class of render API backends
 */
class Renderer : public System
{
public:
    Renderer(event::Channel& channel);
    ~Renderer();

    void render();

private:

    // Implimentation details used cross all graphics backends
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}}

