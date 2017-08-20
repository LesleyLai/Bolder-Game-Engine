#include <sstream>
#include "doctest.h"

#include "bolder/vector.hpp"

using namespace bolder::math;

TEST_CASE("[math] Vectors") {
    Vec3 v{1, 2, 3};
    Vec3 v2{3, 5, 7};
    const Vec3 sum {4, 7, 10};
    const Vec3 diff {-2, -3, -4};
    const Vec3 two_v {2, 4, 6};
    const Vec3 half_v {0.5, 1, 1.5};

    SUBCASE("Construct Vector from a smaller vector and a scalar") {
        Vec2 v3 {3, 5};
        REQUIRE_EQ(Vec3{v3, 7}, v2);
        REQUIRE_EQ(Vec4{v2, 9}, Vec4{3, 5, 7, 9});
    }

    SUBCASE("Array-style indexing for Vectors") {
        REQUIRE_EQ(v[2], doctest::Approx(3));
    }

    SUBCASE("Print Vector") {
        std::stringstream ss;
        ss << v;
        REQUIRE_EQ(ss.str(), "vec(1,2,3)");
    }

    SUBCASE("Comparison of Vector") {
        REQUIRE((v == Vec3{1, 2, 3}));
        REQUIRE((v != Vec3{2, 2, 3}));
    }

    SUBCASE("Unary operations of Vector") {
        SUBCASE("+=") {
            v+=v2;
            REQUIRE_EQ(v, sum);
        }

        SUBCASE("+=") {
            v-=v2;
            REQUIRE_EQ(v, diff);
        }

        SUBCASE("*=") {
            v*=2.f;
            REQUIRE_EQ(v, two_v);
        }

        SUBCASE("/=") {
            v/=2.f;
            REQUIRE_EQ(v, half_v);
        }

        SUBCASE("Negation") {
            REQUIRE_EQ(-v, Vec3{-1, -2, -3});
        }
    }

    SUBCASE("Binary operations of Vector") {
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
            REQUIRE_EQ(dot(v, v2), doctest::Approx(34));
        }

        SUBCASE("cross product") {
            REQUIRE_EQ(cross(v, v2), Vec3{-1, 2, -1});
        }
    }

    SUBCASE("Length of the Vector") {
        REQUIRE_EQ(v.length_square(), doctest::Approx(14));
        REQUIRE_EQ(v.length(), doctest::Approx(std::sqrt(14)));
    }
}
