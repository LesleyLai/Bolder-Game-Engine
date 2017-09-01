#pragma once

#include "glad/glad.h"

namespace bolder { namespace graphics {

class Image;

namespace GL {

struct Texture2d {
    void init(const Image& image, bool use_mipmap);

    void bind() const noexcept {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    void unbind() const noexcept {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    unsigned int id = 0;
};

}}} // namespace bolder::graphics::GL
