#include "exception.hpp"
#include <stdexcept>

using namespace bolder;

Exception::Exception() noexcept
{

}

Exception::Exception(const char* message) noexcept : msg_{message}
{

}

const char* Exception::what() const noexcept
{
    return msg_ ? msg_ : "Unknown exception";
}

Unimplemented::Unimplemented() noexcept : Exception("Not implemented") {}

Invalid_argument::Invalid_argument() noexcept : Exception("Invalid argument") {}

Runtime_error::Runtime_error(const char* message) noexcept  : Exception{message}
{
}
