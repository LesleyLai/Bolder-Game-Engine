#pragma once

#include <cstdint>

namespace bolder { namespace graphics { namespace GL {
class Buffer;

class Vertex_array {
public:
    Vertex_array();

    void bind() const noexcept;
    void unbind() const noexcept;

    /**
     * @brief Defines an array of generic vertex attribute data from buffer
     * @param buffer The buffer to bind
     * @param index the index of the vertex attribute.
     * @param count the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
     * @param stride the byte offset between consecutive generic vertex attributes.
     * @param offset a byte offset of the first component of the first generic vertex attribute in the buffer
     */
    void bind_attributes(const Buffer& buffer,
                         unsigned int index,
                         unsigned int count,
                         unsigned int stride,
                         std::intptr_t offset);
private:
    unsigned int id_;
};

}}} // namespace bolder::graphics::GL
