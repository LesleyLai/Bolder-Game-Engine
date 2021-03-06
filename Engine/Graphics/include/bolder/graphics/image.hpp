#pragma once

#include "bolder/byte.hpp"
#include "bolder/exception.hpp"

namespace bolder { namespace graphics {

class Image {
public:
    /// Default constructor
    Image() {}

    /// Create an image from file
    Image(const char* filename);
    ~Image();

    /// Copy constructor
    Image(const Image& other) = delete;

    /// Copy assignment
    Image& operator=(const Image& other) = delete;

    /// Move constructor
    Image(Image&& other);

    /// Move assignment
    Image& operator=(Image&& other);


    int width() const;
    int height() const;
    int components_count() const;
    Byte* data() const;


private:
    int width_ = 0;
    int height_ = 0;
    int components_count_;
    Byte* data_;
};

}}
