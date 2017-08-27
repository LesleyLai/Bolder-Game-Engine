#pragma once

#include "bolder/exception.hpp"

namespace bolder { namespace resource {

enum class Handle_error_type {
    out_of_space, ///< Add resource to an manager that are full
    null_entry, ///< Modify an entry that do not contains any value
    invalid_handle, ///< Modify Handle_manager with invalid handle
};

struct Resource_error : Runtime_error {
    Resource_error(Handle_error_type error_code) noexcept;

    const char* what() const noexcept override;

    const Handle_error_type code;
};

}} // namespace bolder::resource
