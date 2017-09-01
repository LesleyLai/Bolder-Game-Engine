#pragma once

#include "resource_handles.hpp"

namespace bolder { namespace graphics {
struct Draw_call {
    Index_buffer_handle ibo_handle;
    Texture_handle texture_handle;
};

}} // namespace bolder::graphics
