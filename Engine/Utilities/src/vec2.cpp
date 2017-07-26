#include "vec2.hpp"

using namespace bolder;

std::ostream& math::operator<<(std::ostream& os, const Vec2& v)
{
    os << "vec(" << v.x << ',' << v.y << ')';
    return os;
}
