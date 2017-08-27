#include "resource_error.hpp"

/**
  * @defgroup resource_group Resource
  * @ingroup core
  */

namespace bolder { namespace resource {

Resource_error::Resource_error(Handle_error_type error_code) noexcept
    : code{error_code} {}

const char* Resource_error::what() const noexcept {
    switch (code) {
    case Handle_error_type::out_of_space:
        return "add entry to a full resource manager";
    case Handle_error_type::null_entry:
        return "modify or remove entry that does not contain value";
    case Handle_error_type::invalid_handle:
        return "modify or remove entry with an invalid handle";
    }
}

}} // namespace bolder::resource
