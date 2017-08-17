#pragma once

#include <memory>
#include "opengl_buffer.hpp"
#include "opengl_vertex_array.hpp"

namespace bolder { namespace graphics { namespace GL {

struct Program;

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
    std::unique_ptr<Vertex_array> vao;
    std::unique_ptr<Index_buffer> ibo;
    std::unique_ptr<Program> shader_program;
};

/** @}*/

}}} // namespace bolder::graphics::GL
