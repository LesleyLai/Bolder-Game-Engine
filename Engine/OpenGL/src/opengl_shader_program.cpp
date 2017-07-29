#include "opengl_shader_program.hpp"
#include "opengl_shader.hpp"
#include "bolder/logger.hpp"

using namespace bolder::graphics::GL;

Shader_program::Shader_program() : id_{glCreateProgram()} {

}

void Shader_program::attach(const Shader& shader)
{
    glAttachShader(id_, shader.id());
}

bool bolder::graphics::GL::Shader_program::link()
{
    glLinkProgram(id_);

    int  success;
    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if(!success) {
        char info_log[512];
        glGetProgramInfoLog(id_, 512, nullptr, info_log);
        BOLDER_LOG_ERROR << "Shader program linking failed: "
                         << info_log;
        return false;
    }
    return true;
}

unsigned int Shader_program::id() const
{
    return id_;
}

void Shader_program::use()
{
    glUseProgram(id_);
}
