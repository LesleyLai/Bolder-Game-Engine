#include <queue>

#include "renderer.hpp"
#include "backend.hpp"
#include "bolder/event.hpp"
#include "bolder/events/input_events.hpp"
#include "bolder/graphics/draw_call.hpp"

namespace bolder { namespace graphics {

namespace {
class Window_resize_handler : public event::Handler_trait<event::Window_resize> {
public:
    Window_resize_handler() {}

    void operator()(const event::Window_resize& event) {
        backend::set_view_port(0, 0, event.x, event.y);
    }
};
}

struct Renderer::Impl {
    event::Handler_raii<Window_resize_handler> window_resize_handler;
    backend::Context* context;
    std::queue<Draw_call> draw_calls;

    Index_buffer_handle rect_ibo;
    Texture_handle texture;
    Vertex_buffer_handle vbo;

    Impl(event::Channel& channel)
        : window_resize_handler{channel},
          context{backend::create_context()}
    {
        unsigned int indices[] = {0, 1, 3,
                                  1, 2, 3};
        rect_ibo = backend::create_index_buffer(context, 6, indices);
        texture = backend::create_texture2d(context,
                                            Image{"textures/container.jpg"},
                                            true);

        float vertices[] = {
            // positions          // texture coords
             0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
             0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left
        };
        constexpr auto vertices_count = sizeof(vertices) / sizeof(float);
        constexpr auto stride = 5 * sizeof(float);
        vbo = backend::create_vertex_buffer(context,
                                            vertices_count,
                                            stride,
                                            vertices);
    }

    ~Impl() {
        backend::destory_context(context);
    }

    void render() {
        draw_calls.push(Draw_call{rect_ibo, texture});

        backend::clear();
        while (!draw_calls.empty()) {
            backend::render(*context, draw_calls.front());
            draw_calls.pop();
        }

    }
};

Renderer::Renderer(event::Channel& channel)
    : System{channel}
{
    backend::init();
    impl_ = std::make_unique<Impl>(channel);
}

Renderer::~Renderer()
{
}

void Renderer::render()
{
    impl_->render();
}

}}
