#include "opengl_context.hpp"

#include "glad/glad.h"

#include "bolder/logger.hpp"
#include "bolder/exception.hpp"

using namespace bolder;
using namespace bolder::graphics::GL;

namespace {
void load_GL() {
    if(!gladLoadGL()) {
        throw Runtime_error {"Cannot load Opengl."};
    }

    if (!GLAD_GL_VERSION_3_0) {
        BOLDER_LOG_ERROR << "The system do not support OpenGL 3.0 or "
                            "later version.";
    }

    BOLDER_LOG_INFO << "OpenGL "  << glGetString(GL_VERSION);
    BOLDER_LOG_INFO << "GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION);

    glClearColor(255, 0, 0, 255);
}

}

OpenGL_context::OpenGL_context()
{
    load_GL();
}

void OpenGL_context::update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
