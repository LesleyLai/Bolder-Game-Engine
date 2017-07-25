#include "GLFW/glfw3.h"
#include "bolder/util/logger.hpp"
#include "display.hpp"

using namespace bolder::platform;

namespace  {
void glfw_error_callback(int, const char* /*description*/) {
    //BOLDER_LOG_FATAL <<  description;
}
}

struct Display::Display_impl {
    Display_impl(const char* title) {
        glfwInit();
        glfwSetErrorCallback(glfw_error_callback);
        window = glfwCreateWindow(640, 480, title, nullptr, nullptr);
        if (!window) {
            std::exit(1);
        }
    }

    ~Display_impl() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    GLFWwindow* window;
};

Display::Display(const char* title)
    : impl_{std::make_unique<Display_impl>(title)}
{

}

Display::~Display() {

}

int Display::width() const
{
    return 640;
}

int Display::height() const
{
    return 480;
}

bool Display::should_close() const
{
    return glfwWindowShouldClose(impl_->window);
}

void Display::update()
{
    glfwSwapBuffers(impl_->window);
    glfwPollEvents();
}
