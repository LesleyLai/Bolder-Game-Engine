#include <cmath>

#include "opengl_graphics_backend.hpp"
#include "opengl_buffer.hpp"
#include "opengl_shader.hpp"
#include "opengl_program.hpp"

#include "bolder/logger.hpp"
#include "bolder/exception.hpp"
#include "bolder/file_util.hpp"

using namespace bolder;
using namespace bolder::graphics::GL;

/** @defgroup opengl OpenGL
 * @brief This module provides a thin wrapper of OpenGL.
 */

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
    auto vertex_shader_source = file_util::load("sprite.vert");
    const char* vert_src = vertex_shader_source.c_str();
    Shader vertex_shader {vert_src, Shader::Type::Vertex};
    vertex_shader.compile();

    auto fragment_shader_source = file_util::load("sprite.frag");
    const char* frag_src = fragment_shader_source.c_str();
    Shader fragment_shader {frag_src, Shader::Type::Fragment};
    fragment_shader.compile();

    auto program = std::make_unique<Program>();
    program->attach(vertex_shader);
    program->attach(fragment_shader);
    program->link();

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

OpenGL_graphics_backend::OpenGL_graphics_backend(event::Channel& channel)
    : Graphics_system{channel}
{
    load_GL();

    float triangles[] = {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
       -0.5f,  0.5f, 0.0f,
    };

    unsigned int indices[] = {0, 1, 3,
                              1, 2, 3};

    vao = std::make_unique<Vertex_array>();
    vao->bind();

    Buffer vbo(triangles, 4 * 3, 3);


    vbo.bind();
    vao->add_buffer(vbo, 0);

    ibo = std::make_unique<Index_buffer>(indices, 6);

    shader_program = compile_shaders();
    shader_program->use();

}

OpenGL_graphics_backend::~OpenGL_graphics_backend()
{

}

void OpenGL_graphics_backend::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    using namespace std::chrono;

    auto current = high_resolution_clock::now();
    auto time = duration_cast<duration<float, std::ratio<1,3>>>(
                current.time_since_epoch());
    auto gv = std::sin(time.count());
    shader_program->set_uniform("gv", gv);
    shader_program->use();

    vao->bind();
    ibo->bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(ibo->size()),
                   GL_UNSIGNED_INT, nullptr);
    ibo->unbind();
    vao->unbind();

    check_error();
}

void OpenGL_graphics_backend::set_view_port(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}
