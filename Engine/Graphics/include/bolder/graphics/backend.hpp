#pragma once

/**
 * @file backend.hpp
 * @brief Interface to graphics backend
 */

#include "bolder/graphics/image.hpp"
#include "draw_call.hpp"
#include "resource_handles.hpp"

namespace bolder { namespace graphics { namespace backend {

struct Context;

/// Initialize the graphics backend if it is not already initialized yet
void init();

/// Clear the screen
void clear();

void render(const Context& context, Draw_call draw_call);

/// Sets the viewport
void set_view_port(int x, int y, int width, int height);

/// Create a backend::Context
Context* create_context();

/// destory a backend::Context
void destory_context(Context* context);

/// Create a Texture
Texture_handle create_texture2d(Context* context, const Image& image, bool use_mipmap);

void destory_texture2d(Context* context, Texture_handle handle);

Vertex_buffer_handle create_vertex_buffer(Context* context,
                                          uint32 vertex_count, uint32 stride,
                                          const float* data);

void destroy_vertex_buffer(Context* context, Vertex_buffer_handle handle);

//Vertex_buffer_handle create_vertex_buffer(unsigned int vertex_count,
//                                      unsigned int stride,
//                                      const void* initial_data);

//Vertex_buffer_handle create_dynamic_vertex_buffer(unsigned int vertex_count,
//                                             unsigned int stride);


Index_buffer_handle create_index_buffer(Context* context,
                                        uint32 indices_count, uint32 data[]);

void destroy_index_buffer(Context* context, Index_buffer_handle handle);


}}} // namespace bolder::graphics::backend
