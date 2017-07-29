#pragma once

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
    void use();

private:
    unsigned int id_;
};

}}} // namespace bolder::graphics::GL
