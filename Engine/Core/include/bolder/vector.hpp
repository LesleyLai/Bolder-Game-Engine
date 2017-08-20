#pragma once

#include <cmath>
#include <ostream>
#include <functional>

/**
 * @file vector.hpp
 * @brief Header file for the general fixed sized vector template.
 */

namespace bolder { namespace math {

/**
  * @brief Common functions for that all vector spetializations need
  *
  * @related Vector
  */
#define BOLDER_VECTOR_IMPL_MIXIN(n)     \
    using size_type = size_t;           \
    using value_type = T;               \
                                        \
    constexpr Vector() {}               \
                                        \
    /* Accessors */                     \
    value_type& operator[](size_type i) {return elems[i];} \
    constexpr const value_type& operator[](size_type i) const {return elems[i];} \
                                        \
    constexpr value_type length_square() const {return dot(*this, *this);} \
    constexpr value_type length() const {return std::sqrt(length_square());} \


/** \addtogroup math
 *  @{
 */

/**
 * @brief Template of fix-sized vectors
 */
template<typename T, size_t size>
struct Vector {
    T elems[size];

    BOLDER_VECTOR_IMPL_MIXIN(size)
};

/**
 * @brief 2D Vector specialization
 * @see Vector
 */
template <typename T>
struct Vector<T, 2> {
    union {
        struct { T x, y; };
        T elems[2];
    };

    BOLDER_VECTOR_IMPL_MIXIN(2)

    Vector(T xx, T yy) : x{xx}, y{yy} {}
};

/**
 * @brief 3D Vector specialization
 * @see Vector
 */
template <typename T>
struct Vector<T, 3> {
    union {
        struct { T x, y, z; };
        struct { Vector<T, 2> xy; };
        T elems[3];
    };


    BOLDER_VECTOR_IMPL_MIXIN(3)

    Vector(T xx, T yy, T zz) : x{xx}, y{yy}, z{zz} {}
    Vector(Vector<T, 2> xy, T zz) : x{xy.x}, y{xy.y}, z{zz} {}
};

/**
 * @brief 4D Vector specialization
 * @see Vector
 */
template <typename T>
struct Vector<T, 4> {
    union {
        struct { T x, y, z, w; };
        struct { Vector<T, 2> xy; };
        struct { Vector<T, 3> xyz; };
        T elems[4];
    };

    BOLDER_VECTOR_IMPL_MIXIN(4)

    Vector(T xx, T yy, T zz, T ww) : x{xx}, y{yy}, z{zz}, w{ww} {}
    Vector(Vector<T, 3> xyz, T ww) : x{xyz.x}, y{xyz.y}, z{xyz.z}, w{ww} {}
};

#undef BOLDER_VECTOR_IMPL_MIXIN

namespace detail {
template <size_t size, typename T, typename Binary_op>
constexpr Vector<T, size> binary_op(const Vector<T, size>& lhs,
                                               const Vector<T, size>& rhs,
                                               Binary_op f) {
    Vector<T, size> result;
    for (auto i = 0u; i != size; ++i) {
        result[i] = f(lhs[i], rhs[i]);
    }
    return result;
}

template <size_t size, typename T, typename Binary_op>
constexpr Vector<T, size> binary_op(const Vector<T, size>& lhs,
                                               const T& rhs,
                                               Binary_op f) {
    Vector<T, size> result;
    for (auto i = 0u; i != size; ++i) {
        result[i] = f(lhs[i], rhs);
    }
    return result;
}

}

/// Adds rhs to this vector
/// @related Vector
template<typename T, size_t size>
inline Vector<T, size>& operator+=(Vector<T, size>& lhs,
                                   const Vector<T, size>& rhs)
{
    for (auto i = 0u; i != size; ++i) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

/// Subtracts rhs from this vector
/// @related Vector
template<typename T, size_t size>
inline Vector<T, size>& operator-=(Vector<T, size>& lhs,
                                   const Vector<T, size>& rhs)
{
    for (auto i = 0u; i != size; ++i) {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

/// Multiplies a scalar rhs to this vector
/// @related Vector
template<typename T, size_t size>
inline Vector<T, size>& operator*=(Vector<T, size>& lhs, T rhs) {
    for (auto i = 0u; i != size; ++i) {
        lhs[i] *= rhs;
    }
    return lhs;
}

/// Divides a scalar rhs to this vector
/// @related Vector
template<typename T, size_t size>
inline Vector<T, size>& operator/=(Vector<T, size>& lhs, T rhs) {
    for (auto i = 0u; i != size; ++i) {
        lhs[i] /= rhs;
    }
    return lhs;
}

/// Return the negation of the vector
/// @related Vector
template<typename T, size_t size>
constexpr Vector<T, size> operator-(const Vector<T, size>& vector) {
    Vector<T, size> result;
    for (auto i = 0u; i != size; ++i) {
        result[i] = -vector[i];
    }
    return result;
}

/**
 * @brief Returns the sum of two vector.
 * @related Vector
 */
template<typename T, size_t size>
constexpr Vector<T, size> operator+(const Vector<T, size>& lhs,
                                    const Vector<T, size>& rhs)
{
    return detail::binary_op(lhs, rhs, std::plus<T>());
}

/**
 * @brief Returns the result of subtract rhs vector from lhs vector.
 * @related Vector
 */
template<typename T, size_t size>
constexpr Vector<T, size> operator-(const Vector<T, size>& lhs,
                                    const Vector<T, size>& rhs)
{
    return detail::binary_op(lhs, rhs, std::minus<T>());
}

/**
 * @brief Calculates the scalar product of vector with the given value.
 * @related Vector
 */
template<typename T, size_t size>
constexpr Vector<T, size> operator*(const Vector<T, size>& lhs, float rhs)
{
    return detail::binary_op(lhs, rhs, std::multiplies<T>());
}

/**
 * @brief Calculates the scalar product of vector with the given value.
 * @related Vector
 */
template<typename T, size_t size>
constexpr Vector<T, size> operator*(float lhs, const Vector<T, size>& rhs)
{
    return rhs * lhs;
}

/**
 * @brief Calculates the scalar division of this vector with the given value.
 * @related Vector
 */
template<typename T, size_t size>
constexpr Vector<T, size> operator/(const Vector<T, size>& lhs, float rhs)
{
    return detail::binary_op(lhs, rhs, std::divides<T>());
}

/**
 * @brief Returns the dot product between the specified vectors.
 * @related Vector
 */
template<typename T, size_t size>
constexpr float dot(const Vector<T, size>& lhs, const Vector<T, size>& rhs)
{
    T result = 0;
    for (auto i = 0u; i != size; ++i) {
        result += lhs[i] * rhs[i];
    }
    return result;
}

/**
 * @brief Returns the cross product between the specified vectors.
 * @related Vec3
 */
template<typename T>
constexpr Vector<T, 3> cross(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs)
{
    return Vector<T, 3> {lhs.y * rhs.z - lhs.z * rhs.y,
                lhs.z * rhs.x - lhs.x * rhs.z,
                lhs.x * rhs.y - lhs.y * rhs.x};
}


/**
 * @brief Determines if two given vectors are equal.
 * @related Vector
 */
template<typename T, size_t size>
constexpr bool operator==(const Vector<T, size>& lhs,
                          const Vector<T, size>& rhs) {
    for (auto i = 0u; i != size; ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

/**
 * @brief Determines if two given vectors are not equal.
 * @related Vector
 */
template<typename T, size_t size>
constexpr bool operator!=(const Vector<T, size>& lhs,
                          const Vector<T, size>& rhs) {
    return !(lhs == rhs);
}

/**
 * @brief Outputs a string representive of vector to a stream
 * @related Vector
 */
template<typename T, size_t size>
std::ostream& operator<<(std::ostream& os, const Vector<T, size>& v)
{
    os << "vec(";
    for (size_t i = 0u, last = size - 1; i != size; ++i) {
        os << v[i];
        if (i != last) os << ',';
    }
    os << ")";
    return os;
}

using Vec2 = Vector<float, 2>; ///< @brief 2D float point vector type
using Vec3 = Vector<float, 3>; ///< @brief 3D float point vector type
using Vec4 = Vector<float, 4>; ///< @brief 4D float point vector type

extern template struct Vector<float, 2>;
extern template struct Vector<float, 3>;
extern template struct Vector<float, 4>;

/** @}*/
}} // namespace bolder::math

