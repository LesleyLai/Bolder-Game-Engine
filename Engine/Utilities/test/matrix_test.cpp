#include "doctest.h"

#include "exception.hpp"

#include <algorithm>
#include <ostream>

namespace bolder { namespace math {

/// A column major 4x4 matrices
class Mat4 {
public:
    /// Returns an identity 4x4 matrix
    constexpr static Mat4 identity();

    /// Creates an orthographic projection matrix
    constexpr static Mat4 orthographic(const float& left, const float& right,
                             const float& bottom, const float& top,
                             const float& z_near, const float& z_far);

    /// Default constructor creates an identity matrix.
    constexpr Mat4();

    constexpr Mat4(
            const float& x0, const float& y0, const float& z0, const float& w0,
            const float& x1, const float& y1, const float& z1, const float& w1,
            const float& x2, const float& y2, const float& z2, const float& w2,
            const float& x3, const float& y3, const float& z3, const float& w3);

    /// Creates a Scalar matrix with all its diagonal entries equal to value
    constexpr Mat4(const float& value);

    Mat4& operator+=(const Mat4& rhs);
    Mat4& operator*=(const Mat4& rhs);

    friend bool operator==(const Mat4& lhs, const Mat4& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Mat4& m);

    constexpr friend Mat4 operator+(const Mat4& lhs, const Mat4& rhs);
    constexpr friend Mat4 operator*(const Mat4& lhs, const Mat4& rhs);

private:
    float elem_[16];
};

bool operator==(const Mat4& lhs, const Mat4& rhs);
std::ostream& operator<<(std::ostream& os, const Mat4& m);

Mat4& Mat4::operator+=(const Mat4& rhs) {
    for (int i = 0; i != 16; ++i) {
        elem_[i] += rhs.elem_[i];
    }
    return *this;
}

Mat4& Mat4::operator*=(const Mat4& rhs) {
    *this = *this * rhs;
    return *this;
}

constexpr Mat4 operator+(const Mat4& lhs, const Mat4& rhs) {
    Mat4 result {};
    for (int i = 0; i != 16; ++i) {
        result.elem_[i] = lhs.elem_[i] + rhs.elem_[i];
    }
    return result;
}


constexpr Mat4 operator*(const Mat4& lhs, const Mat4& rhs) {
    Mat4 result {};
    for (int y = 0; y != 4; ++y) {
        for (int x = 0; x != 4; ++x) {
            float sum = 0;
            for (int k = 0; k != 4; ++k) {
                sum += lhs.elem_[x + k * 4] * rhs.elem_[k + y * 4];
            }
            result.elem_[4 * y + x] = sum;
        }
    }

    return result;
}
}}

using namespace bolder::math;

constexpr Mat4 Mat4::identity()
{
    return Mat4{};
}

constexpr Mat4 Mat4::orthographic(const float& left, const float& right,
                        const float& bottom, const float& top,
                        const float& z_near, const float& z_far)
{
    return true ? throw Unimplemented{} : Mat4{};
}

constexpr Mat4::Mat4() : Mat4(1)
{
}

/// Constructs a matrix from 16 numbers

/**
 * @brief Constructs a matrix from 16 numbers.
 */
constexpr Mat4::Mat4(
        const float& x0, const float& y0, const float& z0, const float& w0,
        const float& x1, const float& y1, const float& z1, const float& w1,
        const float& x2, const float& y2, const float& z2, const float& w2,
        const float& x3, const float& y3, const float& z3, const float& w3) :
    elem_ {x0, y0, z0, w0,
           x1, y1, z1, w1,
           x2, y2, z2, w2,
           x3, y3, z3, w3}
{
}

constexpr Mat4::Mat4(const float& v)
    :Mat4 {v, 0, 0, 0,
           0, v, 0, 0,
           0, 0, v, 0,
           0, 0, 0, v}

{
}

bool bolder::math::operator==(const Mat4& lhs, const Mat4& rhs) {
    return std::equal(std::begin(lhs.elem_),
                      std::end(lhs.elem_),
                      std::begin(rhs.elem_),
                      std::end(rhs.elem_));
}

std::ostream& bolder::math::operator<<(std::ostream& os, const Mat4& m) {
    const auto elem = m.elem_;
    os << "mat("
       << '{' << elem[0] << ',' << elem[1] << ',' << elem[2] << ',' << elem[3] << '}'
       << '{' << elem[4] << ',' << elem[5] << ',' << elem[6] << ',' << elem[7] << '}'
       << '{' << elem[8] << ',' << elem[9] << ',' << elem[10] << ',' << elem[11] << '}'
       << '{' << elem[12] << ',' << elem[13] << ',' << elem[14] << ',' << elem[15] << '}'
       << ")";

    return os;
}

TEST_CASE("4x4 Matrix") {
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

    SUBCASE("Default constructor creates an identity matrix") {
        const Mat4 identity {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
        };

        const Mat4 mat;
        REQUIRE_EQ(mat, identity);
    }

    SUBCASE("Addition") {
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
