#pragma once

#include <array>
#include <algorithm>
#include <cstdlib>
#include <ostream>

/**
 * @file vector.hpp
 * @brief Header file for the general fixed sized vector template.
 */

namespace bolder { namespace math {

template <size_t size, typename T>
struct Vector {
    using size_type = size_t;

    ///@{
    /**
     * @brief Returns the element of index i
     * @warning No bound checking.
     */
    T& operator[](size_type i);
    constexpr const Ts
    & operator[](size_type i) const;
    ///@}

    Vector& operator+=(const Vector& rhs);
    Vector& operator-=(const Vector& rhs);
    Vector& operator*=(T rhs);
    Vector& operator/=(T rhs);

    constexpr T length_square() const;

    std::array<T, size> elems;
};

template <size_t size, typename T>
inline T &Vector<size, T>::operator[](size_type i)
{
    return elems[i];
}

template <size_t size, typename T>
constexpr const T &Vector<size, T>::operator[](size_type i) const
{
    return elems[i];
}

/// Adds rhs to this vector
template<size_t size, typename T>
inline Vector<size, T>& Vector<size, T>::operator+=(const Vector<size, T>& rhs)
{
    for (auto i = 0u; i != size; ++i) {
        elems[i] += rhs[i];
    }
    return *this;
}

/// Subtracts rhs from this vector
template<size_t size, typename T>
inline Vector<size, T>& Vector<size, T>::operator-=(const Vector<size, T>& rhs)
{
    for (auto i = 0u; i != size; ++i) {
        elems[i] -= rhs[i];
    }
    return *this;
}

/// Multiplies a scalar rhs to this vector
template<size_t size, typename T>
inline Vector<size, T>& Vector<size, T>::operator*=(T rhs) {    
    for (auto i = 0u; i != size; ++i) {
        elems[i] *= rhs;
    }
    return *this;
}

/// Divides a scalar rhs to this vector
template<size_t size, typename T>
inline Vector<size, T>& Vector<size, T>::operator/=(T rhs) {
    for (auto i = 0u; i != size; ++i) {
        elems[i] /= rhs;
    }
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
template<size_t size, typename T>
constexpr T Vector<size, T>::length_square() const
{
    T result = 0;
    for (auto i = 0u; i != size; ++i) {
        result += elems[i] * elems[i];
    }
    return result;
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

}} // namespace bolder::math

