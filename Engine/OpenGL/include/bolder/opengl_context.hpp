#pragma once

#include <memory>

namespace bolder { namespace graphics { namespace GL {

class Shader_program;

class OpenGL_context
{
public:
    /// Initialize OpenGL
    OpenGL_context();
    ~OpenGL_context();

    /// Renders the context
    void render();

private:
    unsigned int vao;
    std::unique_ptr<Shader_program> shader_program;
};

}}} // namespace bolder::graphics::GL
