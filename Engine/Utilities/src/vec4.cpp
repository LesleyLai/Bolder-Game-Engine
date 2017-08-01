#include "math.hpp"
#include "vec4.hpp"

using namespace bolder;

std::ostream& math::operator<<(std::ostream& os, const Vec4& v)
{
    os << "vec(" << v.x << ',' << v.y << ',' << v.z << ',' << v.w << ')';
    return os;
}

/**
 * @brief Returns the length of the vector.
 *
 * @note Uses length_square if it is not necessary to get the exact length of a
 * vector.
 * @see length_square
 */
float math::Vec4::length() const
{
    return sqrt(length_square());
}
