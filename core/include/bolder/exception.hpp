#pragma once

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

}
