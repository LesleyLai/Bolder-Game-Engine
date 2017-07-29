#pragma once

#include "glad/glad.h"

class Shader_opengl {
public:
    /// OpenGL_shader type
    enum class Type {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
    };

    Shader_opengl(const char* source, Type type);
    ~Shader_opengl();

    /// Returns the OpenGl assigned id of this OpenGL_shader.
    GLuint id() const;

    /// Compiles this OpenGL_shader
    bool compile();

private:
    Type type_;
    const char* source_;
    GLuint id_;
};
