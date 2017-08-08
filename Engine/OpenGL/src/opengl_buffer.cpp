#include "opengl_buffer.hpp"
#include "glad/glad.h"

namespace bolder { namespace graphics { namespace GL {

Buffer::Buffer(float* data, size_t size, int count) : components_count_{count}
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

int Buffer::components_count() const
{
    return components_count_;
}

Index_buffer::Index_buffer(uint32_t* data, unsigned int size) : size_{size}
{
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(size * sizeof(uint32_t)),
                 data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Index_buffer::bind() const noexcept
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

void Index_buffer::unbind() const noexcept
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int Index_buffer::size() const
{
    return size_;
}

}}} // namespace bolder::graphics::GL
