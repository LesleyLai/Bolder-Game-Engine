#include <sstream>
#include "doctest.h"

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

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

    SUBCASE("Unary operations of Vec2") {
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

        SUBCASE("Negation") {
            REQUIRE_EQ(-v, Vec2{-1, -2});
        }
    }

    SUBCASE("Binary operations of Vec2") {
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

    SUBCASE("Length of the vector") {
        REQUIRE_EQ(v.length_square(), doctest::Approx(5));
        REQUIRE_EQ(v.length(), doctest::Approx(std::sqrt(5)));
    }
}

TEST_CASE("[math] 3D Vectors") {
    Vec3 v{1, 2, 3};
    Vec3 v2{3, 5, 7};
    const Vec3 sum {4, 7, 10};
    const Vec3 diff {-2, -3, -4};
    const Vec3 two_v {2, 4, 6};
    const Vec3 half_v {0.5, 1, 1.5};

    SUBCASE("Construct Vec3 from Vec2") {
        Vec2 v3 {3, 5};
        REQUIRE_EQ(Vec3{v3, 7}, v2);
    }

    SUBCASE("Size of Vec3 is 3") {
        REQUIRE_EQ(v.size(), 3);
    }

    SUBCASE("Array-style indexing from 3D Vectors") {
        REQUIRE_EQ(v[2], doctest::Approx(3));
    }

    SUBCASE("Print Vec3") {
        std::stringstream ss;
        ss << v;
        REQUIRE_EQ(ss.str(), "vec(1,2,3)");
    }

    SUBCASE("Comparison of Vec3") {
        REQUIRE((v == Vec3{1, 2, 3}));
        REQUIRE((v != Vec3{2, 2, 3}));
    }

    SUBCASE("Unary operations of Vec3") {
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

        SUBCASE("Negation") {
            REQUIRE_EQ(-v, Vec3{-1, -2, -3});
        }
    }

    SUBCASE("Binary operations of Vec3") {
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
            REQUIRE_EQ(dot(v, v2), Vec3{3, 10, 21});
        }

        SUBCASE("cross product") {
            REQUIRE_EQ(cross(v, v2), Vec3{-1, 2, -1});
        }
    }

    SUBCASE("Length of the vector") {
        REQUIRE_EQ(v.length_square(), doctest::Approx(14));
        REQUIRE_EQ(v.length(), doctest::Approx(std::sqrt(14)));
    }
}

TEST_CASE("[math] 4D Vectors") {
    Vec4 v{1, 2, 3, 4};
    Vec4 v2{3, 5, 7, 9};
    const Vec4 sum {4, 7, 10, 13};
    const Vec4 diff {-2, -3, -4, -5};
    const Vec4 two_v {2, 4, 6, 8};
    const Vec4 half_v {0.5, 1, 1.5, 2};

    SUBCASE("Construct Vec4 from Vec3") {
        Vec3 v3 {3, 5, 7};
        REQUIRE_EQ(Vec4{v3, 9}, v2);
    }

    SUBCASE("Size of Vec4 is 4") {
        REQUIRE_EQ(v.size(), 4);
    }

    SUBCASE("Array-style indexing from 3D Vectors") {
        REQUIRE_EQ(v[3], doctest::Approx(4));
    }

    SUBCASE("Print Vec2") {
        std::stringstream ss;
        ss << v;
        REQUIRE_EQ(ss.str(), "vec(1,2,3,4)");
    }

    SUBCASE("Comparison of Vec4") {
        REQUIRE((v == Vec4{1, 2, 3, 4}));
        REQUIRE((v != Vec4{2, 2, 3, 4}));
    }

    SUBCASE("Unary operations of Vec4") {
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

        SUBCASE("Negation") {
            REQUIRE_EQ(-v, Vec4{-1, -2, -3, -4});
        }
    }

    SUBCASE("Binary operations of Vec4") {
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
            REQUIRE_EQ(dot(v, v2), Vec4{3, 10, 21, 36});
        }
    }

    SUBCASE("Length of the vector") {
        constexpr float length_square = 30;
        REQUIRE_EQ(v.length_square(), doctest::Approx(length_square));
        REQUIRE_EQ(v.length(), doctest::Approx(std::sqrt(length_square)));
    }
}

