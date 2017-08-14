#pragma once
#include <cstddef>
#include <cstdint>

namespace bolder { namespace graphics { namespace GL {

/**
 * @brief An OpenGL Vertex Buffer Object
 */
class Buffer {
public:
    Buffer(float* data, size_t size, int count);

    void bind() const noexcept;
    void unbind() const noexcept;

    int components_count() const;

private:
    unsigned int id_;
    int components_count_;
};

/**
 * @brief An OpenGL Vertex Buffer Object
 */
class Index_buffer {
public:
    Index_buffer(uint32_t* data, unsigned int size);

    void bind() const noexcept;
    void unbind() const noexcept;

    unsigned int size() const;

private:
    unsigned int id_;
    unsigned int size_;
};


}}} // namespace bolder::graphics::GL
