#include "GLFW/glfw3.h"
#include "util/logger.hpp"
#include "exception.hpp"
#include "engine.hpp"

using namespace bolder;

namespace  {
void glfw_error_callback(int, const char* description) {
    BOLDER_LOG_FATAL <<  description;
}
}

struct Engine::Impl {
    GLFWwindow* window;

    Impl(utility::String_literal title);
    ~Impl();

    void game_loop();
};

Engine::Engine(utility::String_literal title)
    : impl_{std::make_unique<Impl>(title)} {
}

Engine::~Engine() = default;


int Engine::exec(int argc, char** argv)
{
    impl_->game_loop();
    return 0;
}

Engine::Impl::Impl(utility::String_literal title) {
    glfwInit();
    glfwSetErrorCallback(glfw_error_callback);
    window = glfwCreateWindow(640, 480, title, nullptr, nullptr);
    if (!window) {
        std::exit(1);
    }
}

Engine::Impl::~Impl() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Engine::Impl::game_loop()
{
    while (!glfwWindowShouldClose(window))
    {
        //render(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
