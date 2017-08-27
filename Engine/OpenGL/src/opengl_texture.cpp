#include <string>

#include "bolder/graphics/image.hpp"
#include "opengl_texture.hpp"

#include "glad/glad.h"

namespace bolder { namespace graphics { namespace GL {

Texture2d::Texture2d(const Image& image)
{
    glGenTextures(1, &id_);
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    auto get_image_format = [](const Image& image) {
        auto unsupport_channel_num = [](int channels) {
            throw Runtime_error {std::to_string(channels) +
                        " image components in image file is not support"};
        };

        const auto channels = image.components_count();

        switch (channels) {
        case 3: // rgb
            return GL_RGB;
        case 4: // rgba
            return GL_RGBA;
        case 1: // grey
        case 2: // grey, alpha
        default:
            unsupport_channel_num(channels);
        }
    };

    auto format = get_image_format(image);

    glTexImage2D(GL_TEXTURE_2D, 0, format, image.width(), image.height(),
                 0, static_cast<GLenum>(format), GL_UNSIGNED_BYTE, image.data());
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture2d::bind() const noexcept
{
    glBindTexture(GL_TEXTURE_2D, id_);
}

}}} // namespace bolder::graphics::GL
