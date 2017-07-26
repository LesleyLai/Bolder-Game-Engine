#include <ostream>

#include "doctest.h"

namespace bolder { namespace math {

struct vec2 {
    using size_type = size_t;

    union {
        struct{ float x, y; };
        struct{ float u, v; };
        float elems[2];
    };

    constexpr vec2() : x{0}, y{0} {}
    constexpr vec2(float x, float y) : x{x}, y{y} {}

    constexpr size_type size() { return 2; }

    constexpr float & operator[](size_type i);
    constexpr float const & operator[](size_type i) const;
};

constexpr float& vec2::operator[](vec2::size_type i)
{
    return elems[i];
}

constexpr const float &vec2::operator[](vec2::size_type i) const
{
    return elems[i];
}

}}

using namespace bolder::math;

TEST_CASE("[math] 2D Vectors") {
    vec2 v{1, 2};

    SUBCASE("Size of vec2 is 2") {
        REQUIRE_EQ(v.size(), 2);
    }

    SUBCASE("Array-style indexing from 2D Vectors") {
        REQUIRE_EQ(v[1], doctest::Approx(2));
    }
}
