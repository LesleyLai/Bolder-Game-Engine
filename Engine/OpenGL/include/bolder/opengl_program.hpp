#pragma once

namespace bolder { namespace graphics { namespace GL {
class Shader;

/**
 * @ingroup opengl
 * @brief An OpenGL shader program
 */
class Program {
public:
    Program();

    /// Attaches a shader to this program
    void attach(const Shader& shader);

    /// Links the shader program; returns success or not
    bool link();

    /// Returns the OpenGL assigned id of this shader program
    unsigned int id() const;

    // Uses this shader program as current shader
    // Todo: remove this method and use a stateless way to manupulate shaders
    void use() const;

    /// Sets a glsl uniform variable
    template<typename T>
    void set_uniform(const char* name, const T& value) const;

private:
    unsigned int id_;
};

/**
 * @brief Sets a glsl uniform variable
 * @tparam T Type of the variable. T can be float, double, int, unsighed int,
 * and bool (treat as int)
 * @param name Name of the variable in shader
 * @param value Value of the variable
 */
template<typename T>
void Program::set_uniform(const char*, const T&) const {
    static_assert(false, "unsupport uniform type");
}

template<>
void Program::set_uniform(const char* name, const float& value) const;

template<>
void Program::set_uniform(const char* name, const double& value) const;

template<>
void Program::set_uniform(const char* name, const int& value) const;

template<>
void Program::set_uniform(const char* name, const bool& value) const;

template<>
void Program::set_uniform(const char* name, const unsigned int& value) const;

}}} // namespace bolder::graphics::GL
