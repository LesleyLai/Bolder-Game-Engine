#pragma once

namespace bolder { namespace graphics { namespace GL {

class Texture {
public:
    Texture();

    void bind() const noexcept;

    unsigned int id() const { return id_; }

private:
    unsigned int id_;
};

}}} // namespace bolder::graphics::GL
