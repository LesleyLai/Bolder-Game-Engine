#include "opengl_vertex_array.hpp"
#include "opengl_buffer.hpp"
#include "glad/glad.h"

namespace bolder { namespace graphics { namespace GL {

Vertex_array::Vertex_array()
{
    glGenVertexArrays(1, &id_);
}

void Vertex_array::bind() const
{
    glBindVertexArray(id_);
}

void Vertex_array::unbind() const
{
    glBindVertexArray(0);
}

void Vertex_array::add_buffer(const Buffer& buffer, unsigned int index)
{
    bind();
    buffer.bind();

    //  Sets the vertex attributes pointers
    glVertexAttribPointer(index, buffer.components_count(),
                          GL_FLOAT,
                          GL_FALSE,
                          /*3 * sizeof(float)*/0,
                          static_cast<void*>(0));
    glEnableVertexAttribArray(index);

    buffer.unbind();
    unbind();
}

}}} // namespace bolder::graphics::GL
