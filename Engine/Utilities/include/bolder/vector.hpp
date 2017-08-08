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
    value_type& operator[](size_type i) {return elems_[i];} \
    constexpr const value_type& operator[](size_type i) const {return elems_[i];} \
                                        \
    constexpr value_type length_square() const {return dot(*this, *this);} \
    constexpr value_type length() const {return std::sqrt(length_square());} \


/** \addtogroup math
 *  @{
 */

/**
 * @brief Template of fix-sized vectors
 */
template <size_t size, typename T>
struct Vector {
    std::array<T,size> elems_;

    BOLDER_VECTOR_IMPL_MIXIN(size)
};

using Vec2 = Vector<2, float>; ///< @brief 2D float point vector type
using Vec3 = Vector<3, float>; ///< @brief 3D float point vector type
using Vec4 = Vector<4, float>; ///< @brief 4D float point vector type

/**
 * @brief 2D Vector specialization
 * @see Vector
 */
template <typename T>
struct Vector<2, T> {
    union {
        struct { T x, y; };
        T elems_[2];
    };

    BOLDER_VECTOR_IMPL_MIXIN(2)

    Vector(T xx, T yy) : x{xx}, y{yy} {}
};

/**
 * @brief 3D Vector specialization
 * @see Vector
 */
template <typename T>
struct Vector<3, T> {
    union {
        struct { T x, y, z; };
        struct { Vector<2, T> xy; };
        T elems_[3];
    };


    BOLDER_VECTOR_IMPL_MIXIN(3)

    Vector(T xx, T yy, T zz) : x{xx}, y{yy}, z{zz} {}
    Vector(Vector<2, T> xy, T zz) : x{xy.x}, y{xy.y}, z{zz} {}
};

/**
 * @brief 4D Vector specialization
 * @see Vector
 */
template <typename T>
struct Vector<4, T> {
    union {
        struct { T x, y, z, w; };
        struct { Vector<2, T> xy; };
        struct { Vector<3, T> xyz; };
        T elems_[4];
    };

    BOLDER_VECTOR_IMPL_MIXIN(4)

    Vector(T xx, T yy, T zz, T ww) : x{xx}, y{yy}, z{zz}, w{ww} {}
    Vector(Vector<3, T> xyz, T ww) : x{xyz.x}, y{xyz.y}, z{xyz.z}, w{ww} {}
};

#undef BOLDER_VECTOR_IMPL_MIXIN

namespace detail {
template <size_t size, typename T, typename Binary_op>
constexpr Vector<size, T> two_vec_binary_op(const Vector<size, T>& lhs,
                                               const Vector<size, T>& rhs,
                                               Binary_op f) {
    Vector<size, T> result;
    for (auto i = 0u; i != size; ++i) {
        result[i] = f(lhs[i], rhs[i]);
    }
    return result;
}

template <size_t size, typename T, typename Binary_op>
constexpr Vector<size, T> vec_elem_binary_op(const Vector<size, T>& lhs,
                                               const T& rhs,
                                               Binary_op f) {
    Vector<size, T> result;
    for (auto i = 0u; i != size; ++i) {
        result[i] = f(lhs[i], rhs);
    }
    return result;
}

}

/// Adds rhs to this vector
/// @related Vector
template<size_t size, typename T>
inline Vector<size, T>& operator+=(Vector<size, T>& lhs,
                                   const Vector<size, T>& rhs)
{
    for (auto i = 0u; i != size; ++i) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

/// Subtracts rhs from this vector
/// @related Vector
template<size_t size, typename T>
inline Vector<size, T>& operator-=(Vector<size, T>& lhs,
                                   const Vector<size, T>& rhs)
{
    for (auto i = 0u; i != size; ++i) {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

/// Multiplies a scalar rhs to this vector
/// @related Vector
template<size_t size, typename T>
inline Vector<size, T>& operator*=(Vector<size, T>& lhs, T rhs) {
    for (auto i = 0u; i != size; ++i) {
        lhs[i] *= rhs;
    }
    return lhs;
}

/// Divides a scalar rhs to this vector
/// @related Vector
template<size_t size, typename T>
inline Vector<size, T>& operator/=(Vector<size, T>& lhs, T rhs) {
    for (auto i = 0u; i != size; ++i) {
        lhs[i] /= rhs;
    }
    return lhs;
}

/// Return the negation of the vector
/// @related Vector
template<size_t size, typename T>
constexpr Vector<size, T> operator-(const Vector<size, T>& vector) {
    Vector<size, T> result;
    for (auto i = 0u; i != size; ++i) {
        result[i] = -vector[i];
    }
    return result;
}

/**
 * @brief Returns the sum of two vector.
 * @related Vector
 */
template<size_t size, typename T>
constexpr Vector<size, T> operator+(const Vector<size, T>& lhs,
                                    const Vector<size, T>& rhs)
{
    return detail::two_vec_binary_op(lhs, rhs, std::plus<T>());
}

/**
 * @brief Returns the result of subtract rhs vector from lhs vector.
 * @related Vector
 */
template<size_t size, typename T>
constexpr Vector<size, T> operator-(const Vector<size, T>& lhs,
                                    const Vector<size, T>& rhs)
{
    return detail::two_vec_binary_op(lhs, rhs, std::minus<T>());
}

/**
 * @brief Calculates the scalar product of vector with the given value.
 * @related Vector
 */
template<size_t size, typename T>
constexpr Vector<size, T> operator*(const Vector<size, T>& lhs, float rhs)
{
    return detail::vec_elem_binary_op(lhs, rhs, std::multiplies<T>());
}

/**
 * @brief Calculates the scalar product of vector with the given value.
 * @related Vector
 */
template<size_t size, typename T>
constexpr Vector<size, T> operator*(float lhs, const Vector<size, T>& rhs)
{
    return rhs * lhs;
}

/**
 * @brief Calculates the scalar division of this vector with the given value.
 * @related Vector
 */
template<size_t size, typename T>
constexpr Vector<size, T> operator/(const Vector<size, T>& lhs, float rhs)
{
    return detail::vec_elem_binary_op(lhs, rhs, std::divides<T>());
}

/**
 * @brief Returns the dot product between the specified vectors.
 * @related Vector
 */
template<size_t size, typename T>
constexpr float dot(const Vector<size, T>& lhs, const Vector<size, T>& rhs)
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
constexpr Vector<3, T> cross(const Vector<3, T>& lhs, const Vector<3, T>& rhs)
{
    return Vector<3, T> {lhs.y * rhs.z - lhs.z * rhs.y,
                lhs.z * rhs.x - lhs.x * rhs.z,
                lhs.x * rhs.y - lhs.y * rhs.x};
}


/**
 * @brief Determines if two given vectors are equal.
 * @related Vector
 */
template<size_t size, typename T>
constexpr bool operator==(const Vector<size, T>& lhs,
                          const Vector<size, T>& rhs) {
    for (auto i = 0u; i != size; ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

/**
 * @brief Determines if two given vectors are not equal.
 * @related Vector
 */
template<size_t size, typename T>
constexpr bool operator!=(const Vector<size, T>& lhs,
                          const Vector<size, T>& rhs) {
    return !(lhs == rhs);
}

/**
 * @brief Outputs a string representive of vector to a stream
 * @related Vector
 */
template<size_t size, typename T>
std::ostream& operator<<(std::ostream& os, const Vector<size, T>& v)
{
    os << "vec(";
    for (size_t i = 0u, last = size - 1; i != size; ++i) {
        os << v[i];
        if (i != last) os << ',';
    }
    os << ")";
    return os;
}

extern template struct Vector<2, float>;
extern template struct Vector<3, float>;
extern template struct Vector<4, float>;

/** @}*/
}} // namespace bolder::math

