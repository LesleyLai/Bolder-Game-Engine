#pragma once

/**
 * @file vec2.hpp
 * @brief Header file for 2d float point vector.
 */

#include <ostream>
#include "vector.hpp"

namespace bolder { namespace math {

/** \addtogroup math
 *  @{
 */

/// 2D float point vector type.
struct Vec2 : public Vector<2, float> {
    constexpr Vec2() : Vector<2, float>{{0,0}} {}
    constexpr Vec2(float x, float y) : Vector<2, float>{{x, y}} {}

    constexpr float x() const {return (*this)[0];}
    constexpr float y() const {return (*this)[1];}

};

/** @}*/
}} // namespace bolder::math
