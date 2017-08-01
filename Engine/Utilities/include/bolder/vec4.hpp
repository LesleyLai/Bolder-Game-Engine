#pragma once

/**
 * @file Vec4.hpp
 * @brief Header file for 4d float point vector.
 */

#include "vec3.hpp"

namespace bolder { namespace math {

/** \addtogroup math
 *  @{
 */

/// 2D float point vector type.
struct Vec4 {
    using size_type = size_t;

    union {
        struct{ float x, y, z, w; };
        float elems[3];
    };

    constexpr Vec4() : x{0}, y{0}, z{0}, w{0} {}
    constexpr Vec4(float xx, float yy, float zz,  float ww)
        : x{xx}, y{yy}, z{zz}, w{ww} {}

    constexpr Vec4(Vec3 v, float ww) : x{v.x}, y{v.y}, z{v.z}, w{ww} {}

    /// Returns the size of Vec4
    constexpr size_type size() const { return 4; }

    ///@{
    /**
     * @brief Returns the element of index i
     * @warning No bound checking.
     */
    float & operator[](size_type i);
    constexpr float const & operator[](size_type i) const;
    ///@}

    constexpr Vec4 operator-() const;
    Vec4& operator+=(const Vec4& rhs);
    Vec4& operator-=(const Vec4& rhs);
    Vec4& operator*=(float rhs);
    Vec4& operator/=(float rhs);

    constexpr float length_square() const;
    float length() const;

    friend std::ostream& operator<<(std::ostream& os, const Vec4& v);
};

std::ostream& operator<<(std::ostream& os, const Vec4& v);

inline float &Vec4::operator[](Vec4::size_type i)
{
    return elems[i];
}

constexpr const float &Vec4::operator[](Vec4::size_type i) const
{
    return elems[i];
}

/// Return the negation of the vector
constexpr Vec4 Vec4::operator-() const
{
    return Vec4{-x, -y, -z, -w};
}

/// Adds rhs to this vector
inline Vec4& Vec4::operator+=(const Vec4& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

/// Subtracts rhs from this vector
inline Vec4& Vec4::operator-=(const Vec4& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

/// Multiplies a scalar rhs to this vector
inline Vec4& Vec4::operator*=(float rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
}

/// Divides a scalar rhs to this vector
inline Vec4& Vec4::operator/=(float rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    return *this;
}

/**
 * @brief Returns the squared length of this vector.
 *
 * When it is not necessary to get the exact length of a vector, it is advised
 * to use this method instead of length.
 *
 * @see length
 */
constexpr float Vec4::length_square() const
{
    return x * x + y * y + z * z + w * w;
}

/**
 * @brief Returns the dot product between the specified vectors.
 * @related Vec4
 */
constexpr Vec4 dot(const Vec4& lhs, const Vec4& rhs)
{
    return Vec4 {lhs.x * rhs.x, rhs.y * lhs.y, rhs.z * lhs.z, lhs.w * rhs.w};
}

/**
 * @brief Returns the sum of two vector.
 * @related Vec4
 */
constexpr Vec4 operator+(const Vec4& lhs, const Vec4& rhs)
{
    return Vec4 {lhs.x + rhs.x, rhs.y + lhs.y, rhs.z + lhs.z, lhs.w + rhs.w};
}

/**
 * @brief Returns the result of subtract rhs vector from lhs vector.
 * @related Vec4
 */
constexpr Vec4 operator-(const Vec4& lhs, const Vec4& rhs)
{
    return Vec4 {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w};
}

/**
 * @brief Calculates the scalar product of vector with the given value.
 * @related Vec4
 */
constexpr Vec4 operator*(const Vec4& lhs, float rhs)
{
    return Vec4 {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs};
}

/**
 * @brief Calculates the scalar product of vector with the given value.
 * @related Vec4
 */
constexpr Vec4 operator*(float lhs, const Vec4& rhs)
{
    return rhs * lhs;
}

/**
 * @brief Calculates the scalar division of this vector with the given value.
 * @related Vec4
 */
constexpr Vec4 operator/(const Vec4& lhs, float rhs)
{
    return Vec4 {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs};
}

/**
 * @brief Determines if two given vectors are equal.
 * @related Vec4
 */
constexpr bool operator==(const Vec4& lhs, const Vec4& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

/**
 * @brief Determines if two given vectors are not equal.
 * @related Vec4
 */
constexpr bool operator!=(const Vec4& lhs, const Vec4& rhs) {
    return !(lhs == rhs);
}

/** @}*/
}} // namespace bolder::math
