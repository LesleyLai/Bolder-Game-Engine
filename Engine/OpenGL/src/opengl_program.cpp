#include "opengl_program.hpp"
#include "opengl_shader.hpp"
#include "bolder/logger.hpp"

namespace bolder { namespace graphics { namespace GL {

Program::Program() : id{glCreateProgram()} {

}

void Program::attach(const Shader& shader)
{
    glAttachShader(id, shader.id);
}

bool bolder::graphics::GL::Program::link()
{
    glLinkProgram(id);

    int  success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success) {
        char info_log[512];
        glGetProgramInfoLog(id, 512, nullptr, info_log);
        BOLDER_LOG_ERROR << "Shader program linking failed: "
                         << info_log;
        return false;
    }
    return true;
}

void Program::use() const
{
    glUseProgram(id);
}

/**
 * @brief Sets a glsl uniform variable
 * @param name Name of the variable in shader
 * @param value Value of the variable
 */
void Program::set_uniform(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name), value);
}

void Program::set_uniform(const char* name, double value) const
{
    glUniform1d(glGetUniformLocation(id, name), value);
}

void Program::set_uniform(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name), value);
}

void Program::set_uniform(const char* name, bool value) const
{
    glUniform1i(glGetUniformLocation(id, name), value);
}

void Program::set_uniform(const char* name, unsigned int value) const
{
    glUniform1ui(glGetUniformLocation(id, name), value);
}

void Program::set_uniform(const char* name, const math::Mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, value.data());
}


}}} // namespace bolder::graphics::GL
