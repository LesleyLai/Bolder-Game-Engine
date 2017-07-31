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

void Shader_program::use() const
{
    glUseProgram(id_);
}


template<>
void Shader_program::set_uniform(const char* name, const float& value) const
{
    glUniform1f(glGetUniformLocation(id_, name), value);
}

template<>
void Shader_program::set_uniform(const char* name, const double& value) const
{
    glUniform1d(glGetUniformLocation(id_, name), value);
}

template<>
void Shader_program::set_uniform(const char* name, const int& value) const
{
    glUniform1i(glGetUniformLocation(id_, name), value);
}

template<>
void Shader_program::set_uniform(const char* name, const bool& value) const
{
    glUniform1i(glGetUniformLocation(id_, name), value);
}

template<>
void Shader_program::set_uniform(const char* name, const unsigned int& value) const
{
    glUniform1ui(glGetUniformLocation(id_, name), value);
}
