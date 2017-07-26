#include <sstream>
#include "doctest.h"

#include "Vec2.hpp"

using namespace bolder::math;

TEST_CASE("[math] 2D Vectors") {
    Vec2 v{1, 2};
    Vec2 v2{3, 5};
    const Vec2 sum {4, 7};
    const Vec2 diff {-2, -3};
    const Vec2 two_v {2,4};
    const Vec2 half_v {0.5, 1};

    SUBCASE("Size of Vec2 is 2") {
        REQUIRE_EQ(v.size(), 2);
    }

    SUBCASE("Array-style indexing from 2D Vectors") {
        REQUIRE_EQ(v[1], doctest::Approx(2));
    }

    SUBCASE("Print Vec2") {
        std::stringstream ss;
        ss << v;
        REQUIRE_EQ(ss.str(), "vec(1,2)");
    }

    SUBCASE("Comparison of Vec2") {
        REQUIRE((v == Vec2{1, 2}));
        REQUIRE((v != Vec2{2, 2}));
    }

    SUBCASE("Unary arithmetics of Vec2") {
        SUBCASE("+=") {
            v+=v2;
            REQUIRE_EQ(v, sum);
        }

        SUBCASE("+=") {
            v-=v2;
            REQUIRE_EQ(v, diff);
        }

        SUBCASE("*=") {
            v*=2;
            REQUIRE_EQ(v, two_v);
        }

        SUBCASE("/=") {
            v/=2;
            REQUIRE_EQ(v, half_v);
        }
    }

    SUBCASE("Binary arithmetics of Vec2") {
        SUBCASE("+") {
            REQUIRE_EQ(v + v2, sum);
        }

        SUBCASE("-") {
            REQUIRE_EQ(v - v2, diff);
        }

        SUBCASE("*") {
            REQUIRE_EQ(v * 2, two_v);
            REQUIRE_EQ(2 * v, two_v);
        }

        SUBCASE("/") {
            REQUIRE_EQ(v / 2, half_v);
        }

        SUBCASE("dot product") {
            REQUIRE_EQ(dot(v, v2), Vec2{3, 10});
        }
    }

}
