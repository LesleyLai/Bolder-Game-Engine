#include "opengl_shader.hpp"

#include "doctest.h"

constexpr const char * vertex_shader_source = {
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0"
};

TEST_CASE("[OpenGL] OpenGL_shader") {
    Shader_opengl vertex_shader {vertex_shader_source,
                Shader_opengl::Type::Vertex};

    SUBCASE("Can compile shader") {
        REQUIRE_EQ(vertex_shader.compile(), true);
    }

}
