#include "opengl_buffer.hpp"

namespace bolder { namespace graphics { namespace GL {

Buffer::Buffer(float* data, size_t size)
{
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(size * sizeof(float)),
                 data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::bind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void Buffer::unbind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}}} // namespace bolder::graphics::GL
