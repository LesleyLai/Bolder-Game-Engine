#include <cmath>

#include "bolder/graphics_system.hpp"

#include "opengl_buffer.hpp"
#include "opengl_shader.hpp"
#include "opengl_program.hpp"
#include "opengl_vertex_array.hpp"
#include "opengl_texture.hpp"

#include "bolder/logger.hpp"
#include "bolder/exception.hpp"
#include "bolder/file_util.hpp"
#include "bolder/transform.hpp"

using namespace bolder;
using namespace bolder::graphics::GL;

/** @defgroup opengl OpenGL
 * @brief This module provides a thin wrapper of OpenGL.
 */

namespace bolder { namespace graphics {

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

    glClearColor(0, 0, 1, 1);
}

// Returns shader program of the compiled shader
auto compile_shaders() {
    auto vert_string = file_util::load("sprite.vert");
    const char* vert_src = vert_string.c_str();
    Shader vertex_shader {vert_src, Shader::Type::Vertex};
    vertex_shader.compile();

    auto frag_string = file_util::load("sprite.frag");
    const char* frag_src = frag_string.c_str();
    Shader fragment_shader {frag_src, Shader::Type::Fragment};
    fragment_shader.compile();

    Program program;
    program.attach(vertex_shader);
    program.attach(fragment_shader);
    program.link();

    return program;
}

void check_error() {
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        auto error_string_from_enum = [](GLenum error) {
            switch(error) {
            case GL_INVALID_OPERATION:
                return "Invalid operation";
            case GL_INVALID_ENUM:
                return "Invalid enum";
            case GL_INVALID_VALUE:
                return "Invalid value";
            case GL_OUT_OF_MEMORY:
                return "Out of memory";
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                return "Invalid framebuffer operation";
            default:
                return "unknown error";
            }
        };

        const char* error_string = error_string_from_enum(error);
        BOLDER_LOG_ERROR << "OpenGL: " << error_string;
    }
}

}

struct Graphics_system::Backend_impl {
    Vertex_array vao;
    Index_buffer ibo;
    Program shader_program;
    Texture texture;

    Backend_impl(unsigned int indices[])
        : vao{},
          ibo{indices, 6},
          shader_program{compile_shaders()}
    {
        vao.bind();
        shader_program.use();
    }
};

void Graphics_system::init_backend()
{

    load_GL();

    float vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left
    };

    unsigned int indices[] = {0, 1, 3,
                              1, 2, 3};

    backend_impl_ = new Backend_impl(indices);

    constexpr auto buffer_size = sizeof(vertices) / sizeof(float);
    constexpr auto stride = 5 * sizeof(float);
    Buffer vbo(vertices, buffer_size);
    backend_impl_->vao.bind_attributes(vbo, 0, 3, stride, 0 * sizeof(float));
    backend_impl_->vao.bind_attributes(vbo, 1, 2, stride, 3 * sizeof(float));
}

void Graphics_system::shutdown_backend()
{
    delete backend_impl_;
}

void Graphics_system::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    using namespace std::chrono;

    auto projection = math::orthographic(-1, 1, -1, 1, -1, 1);

    backend_impl_->shader_program.set_uniform("projection", projection);
    backend_impl_->shader_program.use();

    backend_impl_->vao.bind();
    backend_impl_->ibo.bind();
    backend_impl_->texture.bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(backend_impl_->ibo.size()),
                   GL_UNSIGNED_INT, nullptr);

    backend_impl_->ibo.unbind();
    backend_impl_->vao.unbind();

    check_error();
}

void Graphics_system::set_view_port(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

}} // namespace bolder::graphics
