#pragma once

#include "glad/glad.h"

namespace bolder { namespace graphics { namespace GL {
class Shader;

class Shader_program {
public:
    Shader_program();

    /// Attaches a shader to this program
    void attach(const Shader& shader);

    /// Links the shader program; returns success or not
    bool link();

    /// Returns the OpenGL assigned id of this shader program
    unsigned int id() const;

    // Uses this shader program as current shader
    // Todo: remove this method and use a stateless way to manupulate shaders
    void use() const;

    /**
     * @brief Sets a glsl uniform variable
     * @tparam T Type of the variable
     * @param name Name of the variable in shader
     * @param value Value of the variable
     */
    template<typename T>
    void set_uniform(const char* name, const T& value) const;

private:
    unsigned int id_;
};

}}} // namespace bolder::graphics::GL
