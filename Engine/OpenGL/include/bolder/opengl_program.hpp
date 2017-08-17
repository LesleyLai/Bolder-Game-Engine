#pragma once

#include "bolder/matrix.hpp"

namespace bolder { namespace graphics { namespace GL {
struct Shader;

/**
 * @ingroup opengl
 * @brief An OpenGL shader program
 */
struct Program {
    /// The OpenGL assigned id of this shader program
    const unsigned int id;

    Program();

    /// Attaches a shader to this program
    void attach(const Shader& shader);

    /// Links the shader program; returns success or not
    bool link();

    // Uses this shader program as current shader
    // Todo: remove this method and use a stateless way to manupulate shaders
    void use() const;

    ///@{
    void set_uniform(const char* name, float value) const;
    void set_uniform(const char* name, double value) const;
    void set_uniform(const char* name, int value) const;
    void set_uniform(const char* name, bool value) const;
    void set_uniform(const char* name, unsigned int value) const;
    ///@}

};




}}} // namespace bolder::graphics::GL
