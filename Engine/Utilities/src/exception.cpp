#include "exception.hpp"
#include <stdexcept>

using namespace bolder;

Exception::Exception() noexcept
{

}

Exception::Exception(const char* message) noexcept : msg_{message}
{

}

Exception::~Exception() {}

const char* Exception::what() const noexcept
{
    return msg_ ? msg_ : "Unknown exception";
}

Not_implemented::Not_implemented() : Exception("Not implemented") {}

Invalid_argument::Invalid_argument() : Exception("Invalid argument") {}
