#pragma once

#include "glad/glad.h"

namespace bolder { namespace graphics { namespace GL {

class Shader {
public:
    /// OpenGL_shader type
    enum class Type {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
    };

    Shader(const char* source, Type type);
    ~Shader();

    /// Returns the OpenGl assigned id of this OpenGL_shader.
    unsigned int id() const;

    /// Compiles this OpenGL_shader
    bool compile();

private:
    Type type_;
    const char* source_;
    unsigned int id_;
};

}}} // namespace bolder::graphics::GL

