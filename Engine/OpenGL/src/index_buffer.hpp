#pragma once

#include "glad/glad.h"

#include "bolder/integer.hpp"

namespace bolder { namespace graphics { namespace GL {

// An OpenGL Vertex Buffer Object
struct Index_buffer {
    unsigned int id;
    unsigned int size;

    void init(uint32* data, unsigned int size_in) {
        size = size_in;
        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     static_cast<GLsizeiptr>(size * sizeof(uint32)),
                     data, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void bind() const noexcept {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void unbind() const noexcept {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
};

}}}
