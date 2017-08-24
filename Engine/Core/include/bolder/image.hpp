#pragma once

#include "bolder/exception.hpp"

namespace bolder {

using byte = unsigned char;

class Image {
public:
    Image(const char* filename);
    ~Image();

    int width() const;
    int height() const;
    int components_count() const;
    byte* data() const;


private:
    int width_;
    int height_;
    int components_count_;
    byte* data_;
};

}
