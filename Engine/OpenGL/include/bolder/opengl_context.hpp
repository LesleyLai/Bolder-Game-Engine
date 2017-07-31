#pragma once

#include <memory>

namespace bolder { namespace graphics { namespace GL {

class Program;

/**
 * @ingroup opengl
 * @brief Context of OpenGL
 */
class OpenGL_context
{
public:
    /// Initialize OpenGL
    OpenGL_context();

    /// Destructor
    ~OpenGL_context();

    /// Renders the context
    void render();

private:
    unsigned int vao;
    std::unique_ptr<Program> shader_program;
};

/** @}*/

}}} // namespace bolder::graphics::GL
