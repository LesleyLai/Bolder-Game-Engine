#include "math.hpp"
#include "vec3.hpp"

using namespace bolder;

std::ostream& math::operator<<(std::ostream& os, const Vec3& v)
{
    os << "vec(" << v.x << ',' << v.y << ',' << v.z << ')';
    return os;
}

/**
 * @brief Returns the length of the vector.
 *
 * @note Uses length_square if it is not necessary to get the exact length of a
 * vector.
 * @see length_square
 */
float math::Vec3::length() const
{
    return sqrt(length_square());
}
