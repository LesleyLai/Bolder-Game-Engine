#include <string>

#include "image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace bolder { namespace graphics {

Image::Image(const char* filename)
{
    stbi_set_flip_vertically_on_load(true);

    data_ = stbi_load(filename, &width_, &height_, &components_count_, 0);
    if (!data_) {
        throw Runtime_error {"Cannit load image " + std::string{filename}};
    }
}

Image::~Image()
{
    stbi_image_free(data_);
}

Image::Image(Image&& other)  :
    width_{other.width_},
    height_{other.height_},
    components_count_{other.components_count_},
    data_{other.data_}
{
    other.data_ = nullptr;
}

Image& Image::operator=(Image&& other)
{
    std::swap(other.width_, width_);
    std::swap(other.height_, height_);
    std::swap(other.components_count_, components_count_);
    std::swap(other.data_, data_);
    return *this;
}

Byte* Image::data() const
{
    return data_;
}

int Image::components_count() const
{
    return components_count_;
}

int Image::height() const
{
    return height_;
}

int Image::width() const
{
    return width_;
}

}}
