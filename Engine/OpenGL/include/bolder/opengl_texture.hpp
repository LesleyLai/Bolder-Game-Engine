#pragma once

namespace bolder {

class Image;

namespace graphics { namespace GL {

class Texture {
public:
    Texture(const Image& image);

    void bind() const noexcept;

    unsigned int id() const { return id_; }

private:
    unsigned int id_;
};

}}} // namespace bolder::graphics::GL
