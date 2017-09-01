#include <array>
#include <atomic>
#include <cmath>

#include "bolder/graphics/backend.hpp"

#include "opengl_shader.hpp"
#include "opengl_program.hpp"
#include "opengl_vertex_array.hpp"
#include "texture.hpp"
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"

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

#ifndef NDEBUG
void check_gl_error() {
    auto error = glGetError();
    if (error == GL_NO_ERROR) return;

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
#endif

}

struct Context {
    Handle_manager<Index_buffer_handle, Index_buffer> ibos;
    Handle_manager<Vertex_buffer_handle, Vertex_buffer> vbos;
    Handle_manager<Texture_handle, Texture2d> textures_;

    Vertex_array vao;
    Program shader_program;

    Context()
        : shader_program{compile_shaders()}
    {    }
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
}

void clear() {
    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void render(const Context& context, Draw_call draw_call)
{
    auto projection = math::orthographic(-1, 1, -1, 1, -1, 1);

    context.shader_program.use();
    context.shader_program.set_uniform("projection", projection);

    auto ibo = *context.ibos[draw_call.ibo_handle];
    auto texture = *context.textures_[draw_call.texture_handle];

    context.vao.bind();
    ibo.bind();
    texture.bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(ibo.size),
                   GL_UNSIGNED_INT, nullptr);
    ibo.unbind();
    texture.unbind();
    context.vao.unbind();

#ifndef NDEBUG
    check_gl_error();
#endif
}

void set_view_port(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

Context* create_context() {
    auto context = new Context();
    return context;
}

void destory_context(Context* context) {
    delete context;
}

Vertex_buffer_handle create_vertex_buffer(Context* context,
                                          uint32 vertex_count,
                                          uint32 stride,
                                          const float* data) {
    Vertex_buffer vbo;
    vbo.init(data, vertex_count, static_cast<GLsizei>(stride));

    // Todo: generalize vao binding stuff
    context->vao.bind_attributes(vbo, 0, 3, 0 * sizeof(float));
    context->vao.bind_attributes(vbo, 1, 2, 3 * sizeof(float));
    return context->vbos.add(vbo);
}

void destroy_vertex_buffer(Context* context, Vertex_buffer_handle handle) {
    context->vbos.remove(handle);
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

Texture_handle create_texture2d(Context* context,
                                const Image& image,
                                bool use_mipmap) {
    Texture2d texture;
    texture.init(image, use_mipmap);
    return context->textures_.add(texture);
}

void destory_texture2d(Context* context, Texture_handle handle) {
    context->textures_.remove(handle);
}

}}} // namespace bolder::graphics::backend
