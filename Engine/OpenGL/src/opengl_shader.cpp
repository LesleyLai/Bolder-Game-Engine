#include "opengl_shader.hpp"
#include "bolder/logger.hpp"

namespace  {
bool is_shader_compiled(unsigned int shader) {
    int  success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, nullptr, info_log);
        BOLDER_LOG_ERROR << "Vertex shader compilation failed:\n"
                         << info_log;
        return false;
    }
    return true;
}
}

using namespace bolder::graphics::GL;

Shader::Shader(const char* source, Shader::Type type) :
    type_{type},
    source_{source},
    id_{glCreateShader(GLenum(type_))}
{
}

Shader::~Shader()
{
    glDeleteShader(id_);
}

unsigned int Shader::id() const
{
    return id_;
}

bool Shader::compile()
{
    glShaderSource(id_, 1, &source_, nullptr);
    glCompileShader(id_);
    return is_shader_compiled(id_);
}
