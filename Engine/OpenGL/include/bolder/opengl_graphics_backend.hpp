#pragma once

#include <memory>
#include "bolder/graphics_system.hpp"
#include "opengl_buffer.hpp"
#include "opengl_vertex_array.hpp"

namespace bolder { namespace graphics { namespace GL {

struct Program;

/**
 * @ingroup opengl
 * @brief Context of OpenGL
 */
class OpenGL_graphics_backend : public Graphics_system
{
public:
    /// Initialize OpenGL
    OpenGL_graphics_backend();

    /// Destructor
    ~OpenGL_graphics_backend();

    /// Renders the context
    void render() override;

    /// Sets the viewport
    void set_view_port(int x, int y, int width, int height) override;

private:
    std::unique_ptr<Vertex_array> vao;
    std::unique_ptr<Index_buffer> ibo;
    std::unique_ptr<Program> shader_program;
};

/** @}*/

}}} // namespace bolder::graphics::GL
