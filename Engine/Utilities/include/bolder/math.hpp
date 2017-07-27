#pragma once

#include <iostream>
#include <cmath>
#include <cfenv>
#include "exception.hpp"

namespace bolder { namespace math {

/** \addtogroup math
 *  @{
 */

inline float sqrt(float arg) {
    auto result = std::sqrt(arg);
    if (std::fetestexcept(FE_INVALID)) {
        throw Invalid_argument {};
    }
    return result;
}

/** @}*/
}} // namespace bolder::math
