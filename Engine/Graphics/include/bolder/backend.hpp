#pragma once

/**
 * @file backend.hpp
 * @brief Interface to graphics backend
 */

namespace bolder { namespace graphics { namespace backend {

struct Context;

/// Initialize the graphics backend if it is not already initialized yet
void init();

void render(const Context& context);

/// Sets the viewport
void set_view_port(int x, int y, int width, int height);

/// Create a backend::Context
Context* create_context();

/// destory a backend::Context
void destory_context(Context* context);

//Vertex_buffer_handle Create_vertex_buffer(unsigned int vertex_Count,
//                                      unsigned int stride,
//                                      const void* initial_data);

//Vertex_buffer_handle Create_dynamic_vertex_buffer(unsigned int vertex_Count,
//                                             unsigned int stride);

//void Destroy_vertex_buffer(Vertex_buffer_handle handle);

//Index_buffer_handle Create_index_buffer(unsigned int index_count,
//                                    Index_buffer::Format format,
//                                    const void* initial_data);

//void DestroyIndexBuffer(Index_buffer_handle handle);

}}} // namespace bolder::graphics::backend
