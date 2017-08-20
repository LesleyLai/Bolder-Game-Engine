#include "doctest.h"
#include "bolder/matrix.hpp"

using namespace bolder::math;

TEST_CASE("Default constructor zero initialized vector") {
    const Mat4 zero {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
    };

    const Mat4 mat;
    REQUIRE_EQ(mat, zero);
}

TEST_CASE("One-argument constructor creates a diagnal matrix") {
    const Mat4 identity {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    };

    const Mat4 mat(1);
    REQUIRE_EQ(mat, identity);
}

TEST_CASE("4x4 Matrix arithmetic") {
    const Mat4 left {
        11, 3, 7, 5,
        12, 6, 8, 3,
        8, 9, 1, 2,
        3, 13, 1, 5,
    };

    const Mat4 right {
        3, 5, 1, 8,
        2, 2, 4, 0,
        5, 7, 2, 3,
        6, 4, 1, 5,
    };

    SUBCASE("Addition") {
        const Mat4 diff {
            8, -2, 6, -3,
            10, 4, 4, 3,
            3, 2, -1, -1,
            -3, 9, 0, 0,
        };


        SUBCASE("Unary") {
            auto mat = left;
            mat -= right;
            REQUIRE_EQ(mat, diff);
        }

        SUBCASE("Binary") {
            REQUIRE_EQ(left - right, diff);
        }
    }

    SUBCASE("subtraction") {
        const Mat4 sum {
            14, 8, 8, 13,
            14, 8, 12, 3,
            13, 16, 3, 5,
            9, 17, 2, 10,
        };


        SUBCASE("Unary") {
            auto mat = left;
            mat += right;
            REQUIRE_EQ(mat, sum);
        }

        SUBCASE("Binary") {
            REQUIRE_EQ(left + right, sum);
        }
    }

    SUBCASE("multiplication") {
        const Mat4 product {
            125, 152, 70, 72,
            78, 54, 34, 24,
            164, 114, 96, 65,
            137, 116, 80, 69,
        };

        SUBCASE("Unary") {
            auto mat = left;
            mat *= right;
            REQUIRE_EQ(mat, product);
        }

        SUBCASE("Binary") {
            REQUIRE_EQ(left * right, product);
        }
    }
}
