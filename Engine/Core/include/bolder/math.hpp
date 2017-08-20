#pragma once

#include <cmath>
#include "exception.hpp"

namespace bolder { namespace math {

/** \addtogroup math
 *  @{
 */

/**
 * @brief Returns the square root of arg
 * @param arg The input to find square root
 * @throw bolder::Invalid_argument if the input is negative or nan
 */
inline float sqrt(float arg) {
    return (arg < 0 || std::isnan(arg))
            ? (throw Invalid_argument{})
            : std::sqrt(arg);
}

/** @}*/
}} // namespace bolder::math
