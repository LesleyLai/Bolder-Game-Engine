#include <string>

#include "image.hpp"

#include "stb/stb_image.h"

namespace bolder {

Image::Image(const char* filename)
{
    data_ = stbi_load(filename, &width_, &height_, &components_count_, 0);
    if (!data_) {
        throw Runtime_error {"Cannit load image " + std::string{filename}};
    }
}

bolder::Image::~Image()
{
    stbi_image_free(data_);
}

byte* Image::data() const
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

}
