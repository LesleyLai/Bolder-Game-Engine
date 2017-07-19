#pragma once

#include <cstddef>

namespace bolder {
namespace utility {

/**
 * @brief A compile time string
 */
struct String_literal {
public:
    /// Construct a String_literal class from a string literal
    template<size_t n>
    constexpr String_literal(const char(&arr)[n])
        : data_{arr},
          size_{n}
    {
        static_assert(n != 0, "Empty string literal is not allowed");
    }

    constexpr operator const char* () {return data_;}

    constexpr size_t size() const {return size_;}

private:
    const char* data_;
    const size_t size_;
};

}
}
