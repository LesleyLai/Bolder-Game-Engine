#include "opengl_shader.hpp"
#include "bolder/logger.hpp"
#include "bolder/exception.hpp"

namespace bolder { namespace graphics { namespace GL {

Shader::Shader(const char* source, Shader::Type type) :
    type{type},
    source{source},
    id{glCreateShader(GLenum(type))}
{
}

Shader::~Shader()
{
    glDeleteShader(id);
}

void Shader::compile()
{
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);
    check_compiled();
}

void Shader::check_compiled() const
{
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        char info_log[512];
        glGetShaderInfoLog(id, 512, nullptr, info_log);

        throw bolder::Runtime_error{info_log};
    }
}

}}} // namespace bolder::graphics::GL
