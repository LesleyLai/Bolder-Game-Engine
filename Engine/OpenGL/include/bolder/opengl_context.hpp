#pragma once

namespace bolder { namespace graphics { namespace GL {

class OpenGL_context
{
public:
    /// Initialize OpenGL
    OpenGL_context();

    /// Renders the context
    void render();

private:
    unsigned int vao;
    unsigned int shader_program;
};

}}} // namespace bolder::graphics::GL
