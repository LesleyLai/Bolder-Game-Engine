#include "opengl_vertex_array.hpp"
#include "vertex_buffer.hpp"

namespace bolder { namespace graphics { namespace GL {

Vertex_array::Vertex_array()
{
    glGenVertexArrays(1, &id_);
}

void Vertex_array::bind() const noexcept
{
    glBindVertexArray(id_);
}

void Vertex_array::unbind() const noexcept
{
    glBindVertexArray(0);
}

void Vertex_array::bind_attributes(const Vertex_buffer& buffer,
                                   unsigned int index,
                                   GLint count,
                                   std::intptr_t offset)
{
    bind();
    buffer.bind();

    //  Sets the vertex attributes pointers
    glVertexAttribPointer(index,
                          count,
                          GL_FLOAT,
                          GL_FALSE,
                          buffer.stride,
                          reinterpret_cast<const GLvoid*>(offset));
    glEnableVertexAttribArray(index);

    buffer.unbind();
    unbind();
}

}}} // namespace bolder::graphics::GL
