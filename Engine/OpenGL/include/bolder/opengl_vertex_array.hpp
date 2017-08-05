#pragma once

namespace bolder { namespace graphics { namespace GL {
class Buffer;

class Vertex_array {
public:
    Vertex_array();

    void bind() const;
    void unbind() const;

    void add_buffer(const Buffer& buffer, unsigned int index);
private:
    unsigned int id_;
};

}}} // namespace bolder::graphics::GL
