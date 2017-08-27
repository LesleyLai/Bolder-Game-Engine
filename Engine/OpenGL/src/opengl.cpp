#include <array>
#include <atomic>
#include <cmath>

#include "bolder/graphics/backend.hpp"

#include "opengl_buffer.hpp"
#include "opengl_shader.hpp"
#include "opengl_program.hpp"
#include "opengl_vertex_array.hpp"
#include "opengl_texture.hpp"
#include "index_buffer.hpp"

#include "bolder/graphics/image.hpp"
#include "bolder/logger.hpp"
#include "bolder/exception.hpp"
#include "bolder/file_util.hpp"
#include "bolder/transform.hpp"
#include "bolder/handle_manager.hpp"

/** @defgroup opengl OpenGL
 * @brief This module provides the graphics backend that use OpenGL.
 */

namespace bolder { namespace graphics { namespace backend {

using namespace GL;
using namespace resource;

namespace {

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

struct Context {
    Handle_manager<Index_buffer_handle, Index_buffer> ibos;

    Vertex_array vao;
    Program shader_program;
    Texture2d texture;

    Context()
        : shader_program{compile_shaders()},
          texture{Image{"textures/container.jpg"}}
    {
    }
};

void init() {
    static std::atomic_bool have_load {false};
    if (have_load) return;
    have_load = true;

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

void clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void render(const Context& context, Draw_call draw_call)
{
    check_error();

    auto projection = math::orthographic(-1, 1, -1, 1, -1, 1);

    context.shader_program.set_uniform("projection", projection);

    context.shader_program.use();

    auto ibo = context.ibos[draw_call.ibo_handle];

    context.vao.bind();
    ibo->bind();
    context.texture.bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(ibo->size),
                   GL_UNSIGNED_INT, nullptr);
    ibo->unbind();
    context.vao.unbind();

}

void set_view_port(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

Context* create_context() {
    float vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left
    };

    auto context = new Context();
    constexpr auto buffer_size = sizeof(vertices) / sizeof(float);
    constexpr auto stride = 5 * sizeof(float);
    Buffer vbo(vertices, buffer_size);
    context->vao.bind_attributes(vbo, 0, 3, stride, 0 * sizeof(float));
    context->vao.bind_attributes(vbo, 1, 2, stride, 3 * sizeof(float));
    return context;
}

void destory_context(Context* context) {
    delete context;
}

Index_buffer_handle create_index_buffer(Context* context,
                                        size_t indices_count, uint32 data[]) {
    Index_buffer ibo;
    ibo.init(data, indices_count);
    return context->ibos.add(ibo);
}

void Destroy_index_buffer(Context* context, Index_buffer_handle handle) {
    context->ibos.remove(handle);
}

}}} // namespace bolder::graphics::backend
