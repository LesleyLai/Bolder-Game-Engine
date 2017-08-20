#include <iostream>

#include "doctest.h"
#include "bolder/math.hpp"

using namespace bolder;

TEST_CASE("[math] Square root") {
    auto r = 1.9f;

    REQUIRE_EQ(math::sqrt(r), doctest::Approx(std::sqrt(r)));

    SUBCASE("Throw Invalid_argument") {
        REQUIRE_THROWS_AS(math::sqrt(-r), Invalid_argument);
    }
}

