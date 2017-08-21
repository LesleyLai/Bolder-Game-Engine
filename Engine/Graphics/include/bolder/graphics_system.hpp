#pragma once

#include <memory>
#include "bolder/system.hpp"

namespace bolder { namespace graphics {

/**
 * @brief Represents a base class of render API backends
 */
class Graphics_system : public System
{
public:
    Graphics_system();

    virtual void render() = 0;
};

}}

