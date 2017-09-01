#pragma once
#include "glad/glad.h"

#include "bolder/integer.hpp"

namespace bolder { namespace graphics { namespace GL {

// An OpenGL Vertex Buffer Object
struct Vertex_buffer {
    unsigned int id;
    GLsizei stride;

    void init(const float* data, size_t size, GLsizei stride_in) {
        stride = stride_in;
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER,
                     static_cast<GLsizeiptr>(size * sizeof(float)),
                     data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void bind() const noexcept {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void unbind() const noexcept {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};

}}}
