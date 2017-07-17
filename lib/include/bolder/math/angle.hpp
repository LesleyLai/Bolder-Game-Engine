#pragma once

#include <ostream>

/**
 * @file angle.hpp
 * @brief float point Degrees and Radians classes, along with literal operators.
 */

namespace bolder {
namespace math {

/** \addtogroup math
 *  @{
 */

/// Constant pi
constexpr float pi =
        3.1415926535897932384626433832795028841971693993751058209749445923078164062f;

namespace detail {
constexpr float deg2rad = pi / 180;
constexpr float rad2deg = 180 / pi;
}

class Degree;

/// The Radian class
class Radian
{
public:
    /// Default constructor
    constexpr Radian() : value_{0} {}

    /// Degree to Radian conversion function
    constexpr Radian(Degree degree);

    /// Construct radian from a number
    constexpr explicit Radian(float value) : value_{value} {}

    /// Gets value of underlying float
    constexpr float value() const { return value_; }

    constexpr Radian operator-() const { return Radian{-value_}; }
    Radian& operator+=(Radian rhs);
    Radian& operator-=(Radian rhs);
    Radian& operator*=(float rhs);
    Radian& operator/=(float rhs);

private:
    float value_;
};

/// The Degree class
class Degree
{
public:
    constexpr Degree() : value_{0} {}

    /// Radian to Degree conversion function
    constexpr Degree(Radian radian);

    /// Constructs degree from a number
    constexpr explicit Degree(float value);

    /// Gets value of underlying float
    constexpr float value() const { return value_; }

    constexpr Degree operator-() const { return Degree{-value_}; }

    Degree& operator+=(Degree rhs);
    Degree& operator-=(Degree rhs);
    Degree& operator*=(float rhs);
    Degree& operator/=(float rhs);


private:
    float value_;
};

// Binary arithmetic operations of Radian and Degree
constexpr Radian operator+(Radian lhs, Radian rhs) {
    return Radian(lhs.value() + rhs.value());
}

constexpr Radian operator-(Radian lhs, Radian rhs) {
    return Radian(lhs.value() - rhs.value());
}

constexpr Radian operator*(Radian lhs, float rhs) {
    return Radian(lhs.value() * rhs);
}

constexpr Radian operator*(float lhs, Radian rhs) {
    return Radian(lhs * rhs.value());
}

constexpr float operator/(Radian lhs, Radian rhs) {
    return lhs.value() / rhs.value();
}

constexpr Radian operator/(Radian lhs, float rhs) {
    return Radian(lhs.value() / rhs);
}

constexpr Degree operator+(Degree lhs, Degree rhs) {
    return Degree(lhs.value() + rhs.value());
}

constexpr Degree operator-(Degree lhs, Degree rhs) {
    return Degree(lhs.value() - rhs.value());
}

constexpr Degree operator*(Degree lhs, float rhs) {
    return Degree(lhs.value() * rhs);
}

constexpr Degree operator*(float lhs, Degree rhs) {
    return Degree(lhs * rhs.value());
}

constexpr float operator/(Degree lhs, Degree rhs) {
    return lhs.value() / rhs.value();
}

constexpr Degree operator/(Degree lhs, float rhs) {
    return Degree(lhs.value() / rhs);
}

// Comparison operations of Radian and Degree
constexpr bool operator==(Radian lhs, Radian rhs) {
    return lhs.value() == rhs.value();
}

constexpr bool operator!=(Radian lhs, Radian rhs) {
    return lhs.value() != rhs.value();
}

constexpr bool operator<(Radian lhs, Radian rhs) {
    return lhs.value() < rhs.value();
}

constexpr bool operator>(Radian lhs, Radian rhs) {
    return lhs.value() > rhs.value();
}

constexpr bool operator<=(Radian lhs, Radian rhs) {
    return lhs.value() <= rhs.value();
}

constexpr bool operator>=(Radian lhs, Radian rhs) {
    return lhs.value() >= rhs.value();
}

constexpr bool operator==(Degree lhs, Degree rhs) {
    return lhs.value() == rhs.value();
}

constexpr bool operator!=(Degree lhs, Degree rhs) {
    return lhs.value() != rhs.value();
}

constexpr bool operator<(Degree lhs, Degree rhs) {
    return lhs.value() < rhs.value();
}

constexpr bool operator>(Degree lhs, Degree rhs) {
    return lhs.value() > rhs.value();
}

constexpr bool operator<=(Degree lhs, Degree rhs) {
    return lhs.value() <= rhs.value();
}

constexpr bool operator>=(Degree lhs, Degree rhs) {
    return lhs.value() >= rhs.value();
}


// Implementation of the member functions

inline Radian &Radian::operator+=(Radian rhs) {
    value_ += rhs.value(); return *this;
}

inline Radian &Radian::operator-=(Radian rhs) {
    value_ -= rhs.value(); return *this;
}

inline Radian &Radian::operator*=(float rhs) {
    value_ *= rhs; return *this;
}

inline Radian &Radian::operator/=(float rhs) {
    value_ /= rhs; return *this;
}

inline Degree &Degree::operator+=(Degree rhs) {
    value_ += rhs.value(); return *this;
}

inline Degree &Degree::operator-=(Degree rhs) {
    value_ -= rhs.value(); return *this;
}

inline Degree &Degree::operator*=(float rhs) {
    value_ *= rhs; return *this;
}

inline Degree &Degree::operator/=(float rhs) {
    value_ /= rhs; return *this;
}

inline constexpr Radian::Radian(Degree degree)
    :value_{degree.value() * detail::deg2rad} {}

inline constexpr Degree::Degree(Radian radian)
    :value_{radian.value() * detail::rad2deg} {}

inline constexpr Degree::Degree(float value) :value_{value} {}

// Output Radian and Degree into stream
std::ostream& operator<<(std::ostream& os, Radian radian);
std::ostream& operator<<(std::ostream& os, Degree degree);

/// Literal for radian
constexpr Radian operator"" _rad(long double r) {
    return Radian(static_cast<float>(r));
}

/// Literal for degree
constexpr Degree operator"" _deg(long double d) {
    return Degree(static_cast<float>(d));
}

/** @}*/
} // namespace math
} // namespace bolder
