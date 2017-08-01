#pragma once

/**
 * @file Vec3.hpp
 * @brief Header file for 3d float point vector.
 */

#include "vec2.hpp"

namespace bolder { namespace math {

/** \addtogroup math
 *  @{
 */

/// 2D float point vector type.
struct Vec3 {
    using size_type = size_t;

    union {
        struct{ float x, y, z; };
        float elems[3];
    };

    constexpr Vec3() : x{0}, y{0}, z{0} {}
    constexpr Vec3(float xx, float yy, float zz) : x{xx}, y{yy}, z{zz} {}
    constexpr Vec3(Vec2 v, float zz) : x{v.x}, y{v.y}, z{zz} {}

    /// Returns the size of Vec3
    constexpr size_type size() const { return 3; }

    ///@{
    /**
     * @brief Returns the element of index i
     * @warning No bound checking.
     */
    float & operator[](size_type i);
    constexpr float const & operator[](size_type i) const;
    ///@}

    constexpr Vec3 operator-() const;
    Vec3& operator+=(const Vec3& rhs);
    Vec3& operator-=(const Vec3& rhs);
    Vec3& operator*=(float rhs);
    Vec3& operator/=(float rhs);

    constexpr float length_square() const;
    float length() const;

    friend std::ostream& operator<<(std::ostream& os, const Vec3& v);
};

std::ostream& operator<<(std::ostream& os, const Vec3& v);

inline float &Vec3::operator[](Vec3::size_type i)
{
    return elems[i];
}

constexpr const float &Vec3::operator[](Vec3::size_type i) const
{
    return elems[i];
}

/// Return the negation of the vector
constexpr Vec3 Vec3::operator-() const
{
    return Vec3{-x, -y, -z};
}

/// Adds rhs to this vector
inline Vec3& Vec3::operator+=(const Vec3& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

/// Subtracts rhs from this vector
inline Vec3& Vec3::operator-=(const Vec3& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

/// Multiplies a scalar rhs to this vector
inline Vec3& Vec3::operator*=(float rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

/// Divides a scalar rhs to this vector
inline Vec3& Vec3::operator/=(float rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
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
constexpr float Vec3::length_square() const
{
    return x * x + y * y + z * z;
}

/**
 * @brief Returns the dot product between the specified vectors.
 * @related Vec3
 */
constexpr Vec3 dot(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3 {lhs.x * rhs.x, rhs.y * lhs.y, rhs.z * lhs.z};
}

/**
 * @brief Returns the cross product between the specified vectors.
 * @related Vec3
 */
constexpr Vec3 cross(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3 {lhs.y * rhs.z - lhs.z * rhs.y,
                lhs.z * rhs.x - lhs.x * rhs.z,
                lhs.x * rhs.y - lhs.y * rhs.x};
}

/**
 * @brief Returns the sum of two vector.
 * @related Vec3
 */
constexpr Vec3 operator+(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3 {lhs.x + rhs.x, rhs.y + lhs.y, rhs.z + lhs.z};
}

/**
 * @brief Returns the result of subtract rhs vector from lhs vector.
 * @related Vec3
 */
constexpr Vec3 operator-(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3 {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

/**
 * @brief Calculates the scalar product of vector with the given value.
 * @related Vec3
 */
constexpr Vec3 operator*(const Vec3& lhs, float rhs)
{
    return Vec3 {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

/**
 * @brief Calculates the scalar product of vector with the given value.
 * @related Vec3
 */
constexpr Vec3 operator*(float lhs, const Vec3& rhs)
{
    return rhs * lhs;
}

/**
 * @brief Calculates the scalar division of this vector with the given value.
 * @related Vec3
 */
constexpr Vec3 operator/(const Vec3& lhs, float rhs)
{
    return Vec3 {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
}

/**
 * @brief Determines if two given vectors are equal.
 * @related Vec3
 */
constexpr bool operator==(const Vec3& lhs, const Vec3& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

/**
 * @brief Determines if two given vectors are not equal.
 * @related Vec3
 */
constexpr bool operator!=(const Vec3& lhs, const Vec3& rhs) {
    return !(lhs == rhs);
}

/** @}*/
}} // namespace bolder::math
