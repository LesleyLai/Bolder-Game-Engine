#pragma once

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
    constexpr size_type size() { return 2; }

    /// Returns the element of index i
    ///

    ///@{
    /**
     * @brief Returns the element of index i
     * @warning No bound checking.
     */
    constexpr float & operator[](size_type i);
    constexpr float const & operator[](size_type i) const;
    ///@}

    /// Adds rhs to this vector
    Vec2& operator+=(const Vec2& rhs);

    /// Subtracts rhs from this vector
    Vec2& operator-=(const Vec2& rhs);

    /// Multiplies a scalar rhs to this vector
    Vec2& operator*=(float rhs);

    /// Divides a scalar rhs to this vector
    Vec2& operator/=(float rhs);

    friend constexpr bool operator==(const Vec2& lhs, const Vec2& rhs);
    friend constexpr bool operator!=(const Vec2& lhs, const Vec2& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Vec2& v);
};

std::ostream& operator<<(std::ostream& os, const Vec2& v);

constexpr float &Vec2::operator[](Vec2::size_type i)
{
    return elems[i];
}

constexpr const float &Vec2::operator[](Vec2::size_type i) const
{
    return elems[i];
}

inline Vec2& Vec2::operator+=(const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

inline Vec2& Vec2::operator-=(const Vec2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

inline Vec2& Vec2::operator*=(float rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
}

inline Vec2& Vec2::operator/=(float rhs) {
    x /= rhs;
    y /= rhs;
    return *this;
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
 * @brief Calculates the scalar product of this vector with the given value.
 * @related Vec2
 */
constexpr Vec2 operator*(const Vec2& lhs, float rhs)
{
    return Vec2 {lhs.x * rhs, lhs.y * rhs};
}

/**
 * @brief Calculates the scalar product of this vector with the given value.
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
