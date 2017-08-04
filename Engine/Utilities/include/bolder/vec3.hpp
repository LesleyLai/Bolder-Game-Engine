#pragma once

/**
 * @file Vec3.hpp
 * @brief Header file for 3d float point vector.
 */

#include "vec2.hpp"

namespace bolder { namespace math {

/** \addtogroup math
 *  @{
 */


/// 3D float point vector type.
struct Vec3 : public Vector<3, float> {
    constexpr Vec3() : Vector<3, float>{{0,0}} {}
    constexpr Vec3(float x, float y, float z) : Vector<3, float>{{x, y, z}} {}
    constexpr Vec3(Vec2 v, float z) : Vector<3, float>{{v.x(), v.y(), z}} {}

    constexpr float x() const {return (*this)[0];}
    constexpr float y() const {return (*this)[1];}
    constexpr float z() const {return (*this)[2];}
};

/**
 * @brief Returns the cross product between the specified vectors.
 * @related Vec3
 */
constexpr Vec3 cross(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3 {lhs.y() * rhs.z() - lhs.z() * rhs.y(),
                lhs.z() * rhs.x() - lhs.x() * rhs.z(),
                lhs.x() * rhs.y() - lhs.y() * rhs.x()};
}

/** @}*/
}} // namespace bolder::math
