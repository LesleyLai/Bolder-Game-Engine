#include "transform.hpp"

#include "doctest.h"

using namespace bolder::math;

TEST_CASE("Creates an orthographic matrix") {
    auto expectation = Mat4 {
        0.005f, 0, 0, 0,
        0, 0.005f, 0, 0,
        0, 0, -1, 0,
        -1, -1, 0, 1
    };

    auto projection = orthographic(0, 400, 0, 400, -1, 1);
    REQUIRE_EQ(projection, expectation);
}
