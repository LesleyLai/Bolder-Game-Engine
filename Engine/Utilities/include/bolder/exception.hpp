#pragma once

#include <stdexcept>
#include <string>

/**
 * @file exception.hpp
 * @brief Header file for exception hierarchy classes.
 */

namespace bolder {

/// All exceptions used by bolder game engine inherit from this class
struct Exception : std::exception {
public:
    Exception() noexcept;
    Exception(const char* message) noexcept;

    /// returns an explanatory string
    virtual char const* what() const noexcept;

private:
    char const* msg_;
};

/// Trying to use not implemented features
struct Unimplemented : Exception {
public:
    Unimplemented() noexcept;
};

/// Arguments of a function is invalid
struct Invalid_argument : Exception {
public:
    Invalid_argument() noexcept;
};

struct Runtime_error : Exception {
public:
    Runtime_error(const char* message) noexcept;
    Runtime_error(const std::string& message) noexcept;
};

}
