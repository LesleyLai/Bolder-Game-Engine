#include "opengl_program.hpp"
#include "opengl_shader.hpp"
#include "doctest.h"

using namespace bolder::graphics::GL;

constexpr const char * vertex_shader_source = {
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0"
};

constexpr const char * fragment_shader_source = {
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.2f, 0.0f, 1.0f);\n"
    "}\n\0"
};

TEST_CASE("[OpenGL] Shader and shader program") {
    Shader vertex_shader {vertex_shader_source,
                Shader::Type::Vertex};

    REQUIRE_EQ(vertex_shader.compile(), true);

    Shader fragment_shader {fragment_shader_source,
                Shader::Type::Fragment};

    REQUIRE_EQ(vertex_shader.compile(), true);
    REQUIRE_EQ(fragment_shader.compile(), true);

    Program shader_program;
    shader_program.attach(vertex_shader);
    shader_program.attach(fragment_shader);
    REQUIRE_EQ(shader_program.link(), true);

}
