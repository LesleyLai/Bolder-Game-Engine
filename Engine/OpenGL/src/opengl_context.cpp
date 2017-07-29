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

    glClearColor(0, 0, 1, 1);
}

bool test_shader_compile_success(unsigned int shader) {
    int  success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, nullptr, info_log);
        BOLDER_LOG_ERROR << "Vertex shader compilation failed: "
                         << info_log;
        return false;
    }
    return true;
}

// Returns shader program of the compiled shader
unsigned int compile_shaders() {
    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    const char *vertex_shader_source = {
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0"
    };

    const char * fragment_shader_source = {
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.2f, 0.0f, 1.0f);\n"
        "}\n\0"
    };

    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);

    test_shader_compile_success(vertex_shader);

    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);

    test_shader_compile_success(fragment_shader);

    unsigned int shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    int  success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success) {
        char info_log[512];
        glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
        BOLDER_LOG_ERROR << "Shader program linking failed: "
                         << info_log;
    }

    glUseProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}

}

OpenGL_context::OpenGL_context()
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


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    //  Copies data into a buffer used by opengl
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);

    // copy our index array in a element buffer for OpenGL to use
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    //  Sets the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          static_cast<void*>(0));
    glEnableVertexAttribArray(0);
    // use our shader program when we want to render an object
    shader_program = compile_shaders();

}

void OpenGL_context::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
