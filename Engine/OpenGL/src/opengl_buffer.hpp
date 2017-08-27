#pragma once
#include "glad/glad.h"

#include "bolder/integer.hpp"

namespace bolder { namespace graphics { namespace GL {

/**
 * @brief An OpenGL Vertex Buffer Object
 */
class Buffer {
public:
    Buffer(float* data, size_t size);

    void bind() const noexcept;
    void unbind() const noexcept;

private:
    unsigned int id_;
};


}}} // namespace bolder::graphics::GL
