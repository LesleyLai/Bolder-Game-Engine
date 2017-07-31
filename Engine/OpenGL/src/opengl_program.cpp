#include "opengl_program.hpp"
#include "opengl_shader.hpp"
#include "bolder/logger.hpp"

using namespace bolder::graphics::GL;

Program::Program() : id_{glCreateProgram()} {

}

void Program::attach(const Shader& shader)
{
    glAttachShader(id_, shader.id());
}

bool bolder::graphics::GL::Program::link()
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

unsigned int Program::id() const
{
    return id_;
}

void Program::use() const
{
    glUseProgram(id_);
}

template<>
void Program::set_uniform(const char* name, const float& value) const
{
    glUniform1f(glGetUniformLocation(id_, name), value);
}

template<>
void Program::set_uniform(const char* name, const double& value) const
{
    glUniform1d(glGetUniformLocation(id_, name), value);
}

template<>
void Program::set_uniform(const char* name, const int& value) const
{
    glUniform1i(glGetUniformLocation(id_, name), value);
}

template<>
void Program::set_uniform(const char* name, const bool& value) const
{
    glUniform1i(glGetUniformLocation(id_, name), value);
}

template<>
void Program::set_uniform(const char* name, const unsigned int& value) const
{
    glUniform1ui(glGetUniformLocation(id_, name), value);
}
