#pragma once

/**
 * @file vec2.hpp
 * @brief Header file for 2d float point vector.
 */

#include <ostream>

namespace bolder { namespace math {

/** \addtogroup math
 *  @{
 */

/// 2D float point vector type.
struct Vec2 {
    using size_type = size_t;

    union {
        struct{ float x, y; };
        struct{ float u, v; };
        float elems[2];
    };

    constexpr Vec2() : x{0}, y{0} {}
    constexpr Vec2(float xx, float yy) : x{xx}, y{yy} {}

    /// Returns the size of Vec2
    constexpr size_type size() const { return 2; }

    ///@{
    /**
     * @brief Returns the element of index i
     * @warning No bound checking.
     */
    float & operator[](size_type i);
    constexpr float const & operator[](size_type i) const;
    ///@}

    constexpr Vec2 operator-() const;
    Vec2& operator+=(const Vec2& rhs);
    Vec2& operator-=(const Vec2& rhs);
    Vec2& operator*=(float rhs);
    Vec2& operator/=(float rhs);

    constexpr float length_square() const;
    float length() const;

    friend std::ostream& operator<<(std::ostream& os, const Vec2& v);
};

std::ostream& operator<<(std::ostream& os, const Vec2& v);

inline float &Vec2::operator[](Vec2::size_type i)
{
    return elems[i];
}

constexpr const float &Vec2::operator[](Vec2::size_type i) const
{
    return elems[i];
}

/// Return the negation of the vector
constexpr Vec2 Vec2::operator-() const
{
    return Vec2{-x, -y};
}

/// Adds rhs to this vector
inline Vec2& Vec2::operator+=(const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

/// Subtracts rhs from this vector
inline Vec2& Vec2::operator-=(const Vec2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

/// Multiplies a scalar rhs to this vector
inline Vec2& Vec2::operator*=(float rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
}

/// Divides a scalar rhs to this vector
inline Vec2& Vec2::operator/=(float rhs) {
    x /= rhs;
    y /= rhs;
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
constexpr float Vec2::length_square() const
{
    return x * x + y * y;
}

/**
 * @brief Returns the dot product between the specified vectors.
 * @related Vec2
 */
constexpr Vec2 dot(const Vec2& lhs, const Vec2& rhs)
{
    return Vec2 {lhs.x * rhs.x, rhs.y * lhs.y};
}

/**
 * @brief Returns the sum of two vector.
 * @related Vec2
 */
constexpr Vec2 operator+(const Vec2& lhs, const Vec2& rhs)
{
    return Vec2 {lhs.x + rhs.x, rhs.y + lhs.y};
}

/**
 * @brief Returns the result of subtract rhs vector from lhs vector.
 * @related Vec2
 */
constexpr Vec2 operator-(const Vec2& lhs, const Vec2& rhs)
{
    return Vec2 {lhs.x - rhs.x, lhs.y - rhs.y};
}

/**
 * @brief Calculates the scalar product of vector with the given value.
 * @related Vec2
 */
constexpr Vec2 operator*(const Vec2& lhs, float rhs)
{
    return Vec2 {lhs.x * rhs, lhs.y * rhs};
}

/**
 * @brief Calculates the scalar product of vector with the given value.
 * @related Vec2
 */
constexpr Vec2 operator*(float lhs, const Vec2& rhs)
{
    return rhs * lhs;
}

/**
 * @brief Calculates the scalar division of this vector with the given value.
 * @related Vec2
 */
constexpr Vec2 operator/(const Vec2& lhs, float rhs)
{
    return Vec2 {lhs.x / rhs, lhs.y / rhs};
}

/**
 * @brief Determines if two given vectors are equal.
 * @related Vec2
 */
constexpr bool operator==(const Vec2& lhs, const Vec2& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

/**
 * @brief Determines if two given vectors are not equal.
 * @related Vec2
 */
constexpr bool operator!=(const Vec2& lhs, const Vec2& rhs) {
    return !(lhs == rhs);
}

/** @}*/
}} // namespace bolder::math
