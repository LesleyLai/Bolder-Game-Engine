#pragma once

/**
 * @file Vec4.hpp
 * @brief Header file for 4d float point vector.
 */

#include "vec3.hpp"

namespace bolder { namespace math {

/** \addtogroup math
 *  @{
 */

/// 4D float point vector type.
struct Vec4 : public Vector<4, float> {
    constexpr Vec4() : Vector<4, float>{{0,0}} {}
    constexpr Vec4(float x, float y, float z, float w)
        : Vector<4, float>{{x, y, z, w}} {}
    constexpr Vec4(Vec3 v, float w) : Vector<4, float>{{v.x(), v.y(), v.z(), w}} {}

    constexpr float x() const {return (*this)[0];}
    constexpr float y() const {return (*this)[1];}
    constexpr float z() const {return (*this)[2];}
    constexpr float w() const {return (*this)[3];}
};


/** @}*/
}} // namespace bolder::math
