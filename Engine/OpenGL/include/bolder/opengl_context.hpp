#pragma once

namespace bolder { namespace graphics { namespace GL {

class OpenGL_context
{
public:
    /// Initialize OpenGL
    OpenGL_context();

    /// Renders the context
    void update();
};

}}} // namespace bolder::graphics::GL
