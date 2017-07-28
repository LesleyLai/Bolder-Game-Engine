#pragma once

#include <stdexcept>

/**
 * @file exception.hpp
 * @brief Header file for exception hierarchy classes.
 */

namespace bolder {

/// All exceptions used by bolder game engine inherit from this class
class Exception : std::exception {
public:
    Exception() noexcept;
    Exception(const char* message) noexcept;

    /// returns an explanatory string
    virtual char const* what() const noexcept;

private:
    char const* msg_;
};

/// Trying to use not implemented features
class Unimplemented : public Exception {
public:
    Unimplemented() noexcept;
};

/// Arguments of a function is invalid
class Invalid_argument : public Exception {
public:
    Invalid_argument() noexcept;
};

class Runtime_error : public Exception {
public:
    Runtime_error(const char* message) noexcept;
};


}
