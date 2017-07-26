#include "angle.hpp"

using namespace bolder;

std::ostream& math::operator<<(std::ostream& os, math::Radian radian)
{
    os << radian.value() / math::pi << "_radians";
    return os;
}

std::ostream& math::operator<<(std::ostream& os, math::Degree degree)
{
    os << degree.value() << "_degrees";
    return os;
}
