#pragma once

#include "vector.hpp"

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <ostream>

namespace bolder { namespace math {

/// A column major MxN matrices
template<typename T, size_t M, size_t N>
class Matrix {
    static_assert(M != 0, "Row number is not equal to 0");
    static_assert(N != 0, "Column number is not equal to 0");
public:
    static constexpr auto rows = M;
    static constexpr auto cols = N;
    using value_type = T;

    /// Default constructor creates a zero matrix
    Matrix() : elems_{} {}

    /**
     * @brief Constructs a matrix from numbers.
     */
    explicit constexpr Matrix(std::initializer_list<T> initList) {
        constexpr const auto size = M*N;
        const auto min = std::min(size, initList.size());
        auto iter = initList.begin();
        for (auto i = 0u; i != min; ++i) {
            elems_[i] = *iter;
            ++iter;
        }
        // Zero-fill any remaining elements
        for (auto i = min; i < size; ++i) { elems_[i] = T(0);}
    }

    /// Creates a Scalar matrix with all its diagonal entries equal to value
    explicit constexpr Matrix(const value_type& value) : elems_{} {
        for (auto row = 0u; row != M; ++row) {
            for (auto col = 0u; col != N; ++col) {
                if (row == col) {
                    elems_[N * row + col] = value;
                } else {
                    elems_[N * row + col] = 0;
                }
            }
        }
    }

    Vector<T, N>& operator[] (size_t i)
    { return reinterpret_cast<Vector<T, N> &>(elems_[i*N]); }
    const Vector<T, N>& operator[] (size_t i) const
    { return reinterpret_cast<const Vector<T, N> &>(elems_[i*N]); }

    /**
     * @brief Return a pointer to the underlying data of the matrix
     */
    constexpr const T* data() const {
        return static_cast<const T*>(elems_);
    }

    /**
     * @brief Returns an identity matrix
     * @note Sets all additional column to 0 if N > M
     */
    constexpr static Matrix identity() {
        return Matrix{};
    }



private:
    T elems_[M*N];
};

namespace detail {
template<typename T, size_t M, size_t N, typename Binary_op>
constexpr Matrix<T, M, N> binary_op(const Matrix<T, M, N>& lhs,
                                    const Matrix<T, M, N>& rhs,
                                    Binary_op f) {
    Matrix<T, M, N> result;
    for (auto i = 0u; i != M; ++i) {
        for (auto j = 0u; j != N; ++j) {
            result[i][j] = f(lhs[i][j], rhs[i][j]);
        }
    }
    return result;
}
}

template<typename T, size_t M, size_t N>
constexpr bool operator==(const Matrix<T, M, N>& lhs,
                          const Matrix<T, M, N>& rhs) {
    for (auto i = 0u; i != M; ++i) {
        for (auto j = 0u; j != N; ++j) {
            if (lhs[i][j] != rhs[i][j]) return false;
        }
    }
    return true;
}

template<typename T, size_t M, size_t N>
constexpr Matrix<T, M, N> operator+(const Matrix<T, M, N>& lhs,
                                    const Matrix<T, M, N>& rhs) {
    return detail::binary_op(lhs, rhs, std::plus<T>());
}

template<typename T, size_t M, size_t N>
constexpr Matrix<T, M, N> operator-(const Matrix<T, M, N>& lhs,
                                    const Matrix<T, M, N>& rhs) {
    return detail::binary_op(lhs, rhs, std::minus<T>());
}


template<typename T, size_t M, size_t N>
Matrix<T, M, N>& operator+=(Matrix<T, M, N>& lhs,
                            const Matrix<T, M, N>& rhs) {
    lhs = lhs + rhs;
    return lhs;
}

template<typename T, size_t M, size_t N>
Matrix<T, M, N>& operator-=(Matrix<T, M, N>& lhs,
                            const Matrix<T, M, N>& rhs) {
    lhs = lhs - rhs;
    return lhs;
}

template<typename T, size_t M, size_t L, size_t N>
constexpr Matrix<T, M, N> operator*(const Matrix<T, M, L>& lhs,
                                    const Matrix<T, L, N>& rhs) {
    Matrix<T, N, N> result;

    for (auto i = 0u; i != M; ++i) {
        for (auto j = 0u; j != N; ++j) {\
            result[j][i] = 0;
            for(auto k = 0u; k != L; ++k) {
                result[j][i] += lhs[k][i] * rhs[j][k];
            }
        }
    }

    return result;
}

template<typename T, size_t M1, size_t N, size_t col2>
Matrix<T, N, N>& operator*=(Matrix<T, M1, N>& lhs,
                            const Matrix<T, N, col2>& rhs) {
    lhs = lhs * rhs;
    return lhs;
}

template<typename T, size_t M, size_t N>
std::ostream& operator<<(std::ostream& os,
                         const Matrix<T, M, N>& m) {
    os << "mat(\n";

    for (auto row = 0u; row != M; ++row) {
        constexpr auto last_col = N - 1;
        for (auto col = 0u; col != last_col; ++col) {
            os << m[row][col] << ',';
        }
        os << m[row][last_col] << '\n';
    }

    os << ')';
    return os;
}

using Mat2 = Matrix<float, 2, 2>;
using Mat3 = Matrix<float, 3, 3>;
using Mat4 = Matrix<float, 4, 4>;  ///< @brief 4x4 float point matrix type
extern template class Matrix<float, 2, 2>;
extern template class Matrix<float, 3, 3>;
extern template class Matrix<float, 4, 4>;

}} // namespace bolder::math
