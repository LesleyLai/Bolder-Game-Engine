#ifndef OPENGL_CONTEXT_HPP
#define OPENGL_CONTEXT_HPP

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



#endif // OPENGL_CONTEXT_HPP
