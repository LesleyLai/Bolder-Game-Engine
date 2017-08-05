#pragma once

#include <array>
#include <cmath>
#include <ostream>
#include <functional>

/**
 * @file vector.hpp
 * @brief Header file for the general fixed sized vector template.
 */

namespace bolder { namespace math {

/** \addtogroup math
 *  @{
 */

/**
 * @brief 2D,3D,4D vectors
 */
template <size_t size, typename T>
struct Vector {
    using size_type = size_t;
    using value_type = T;

    constexpr Vector() {}

    constexpr Vector(std::array<T, size> data) : elems_{data} {}

    ///@{
    /**
     * @brief Returns the element of index i
     * @warning No bound checking.
     */
    value_type& operator[](size_type i);
    constexpr const value_type& operator[](size_type i) const;
    ///@}

    Vector& operator+=(const Vector& rhs);
    Vector& operator-=(const Vector& rhs);
    Vector& operator*=(T rhs);
    Vector& operator/=(T rhs);

    constexpr Vector operator-() const;

    constexpr value_type length_square() const;
    value_type length() const;

private:
    std::array<T,size> elems_;
};

template <size_t size, typename T>
inline T &Vector<size, T>::operator[](size_type i)
{
    return elems_[i];
}

template <size_t size, typename T>
constexpr const T &Vector<size, T>::operator[](size_type i) const
{
    return elems_[i];
}

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
template<size_t size, typename T>
inline Vector<size, T>& Vector<size, T>::operator+=(const Vector<size, T>& rhs)
{
    for (auto i = 0u; i != size; ++i) {
        elems_[i] += rhs[i];
    }
    return *this;
}

/// Subtracts rhs from this vector
template<size_t size, typename T>
inline Vector<size, T>& Vector<size, T>::operator-=(const Vector<size, T>& rhs)
{
    for (auto i = 0u; i != size; ++i) {
        elems_[i] -= rhs[i];
    }
    return *this;
}

/// Multiplies a scalar rhs to this vector
template<size_t size, typename T>
inline Vector<size, T>& Vector<size, T>::operator*=(T rhs) {
    for (auto i = 0u; i != size; ++i) {
        elems_[i] *= rhs;
    }
    return *this;
}

/// Divides a scalar rhs to this vector
template<size_t size, typename T>
inline Vector<size, T>& Vector<size, T>::operator/=(T rhs) {
    for (auto i = 0u; i != size; ++i) {
        elems_[i] /= rhs;
    }
    return *this;
}

/// Return the negation of the vector
template<size_t size, typename T>
constexpr Vector<size, T> Vector<size, T>::operator-() const {
    Vector<size, T> result;
    for (auto i = 0u; i != size; ++i) {
        result[i] = -elems_[i];
    }
    return result;
}


/**
 * @brief Returns the squared length of this vector.
 *
 * When it is not necessary to get the exact length of a vector, it is advised
 * to use this method instead of length.
 *
 * @see length
 */
template<size_t size, typename T>
constexpr T Vector<size, T>::length_square() const
{
    return dot(*this, *this);
}


/**
 * @brief Returns the length of the vector.
 *
 * @note Uses length_square if it is not necessary to get the exact length of a
 * vector.
 * @see length_square
 */
template<size_t size, typename T>
inline T Vector<size, T>::length() const {
     return std::sqrt(length_square());
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

