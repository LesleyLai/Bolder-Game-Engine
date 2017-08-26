#pragma once

/**
 * @file backend.hpp
 * @brief Interface to graphics backend
 */

namespace bolder { namespace graphics { namespace backend {

/// Initialize the graphics backend if it is not already initialized yet
void init();

void render();

/// Sets the viewport
void set_view_port(int x, int y, int width, int height);

}}} // namespace bolder::graphics::backend
