#pragma once

/**
 * @file exception.hpp
 * @brief Header file for exception hierarchy classes.
 */

namespace bolder {

/// All exceptions used by bolder game engine inherit from this class
class Exception {
public:
    Exception() noexcept;
    Exception(const char* message) noexcept;
    virtual ~Exception();

    /// returns an explanatory string
    virtual char const* what() const noexcept;

private:
    char const* msg_;
};

/// Trying to use not implemented features
class Not_implemented : public Exception {
public:
    Not_implemented();
};

/// Arguments of a function is invalid
class Invalid_argument : public Exception {
public:
    Invalid_argument();
};

}
