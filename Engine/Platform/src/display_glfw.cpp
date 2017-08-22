#include <iostream>
#include <iomanip>

#include "GLFW/glfw3.h"
#include "bolder/logger.hpp"
#include "bolder/exception.hpp"
#include "display.hpp"


using namespace bolder;
using namespace bolder::platform;

namespace {
void glfw_error_callback(int, const char* description) {
    BOLDER_LOG_FATAL <<  description;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    std::cout << width << ',' << height << std::endl;
    //glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //if (key == GLFW_KEY_E && action == GLFW_PRESS)
        //activate_airship();;
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    //std::cout << xpos << ',' << ypos << std::endl;
}

}

struct Display::Display_impl {
    Display_impl(const char* title) {
        glfwInit();
        glfwSetErrorCallback(glfw_error_callback);
        window = glfwCreateWindow(800, 600, title, nullptr, nullptr);
        if (!window) {
            throw Runtime_error {"GLFW Cannot create a window."};
        }
        BOLDER_LOG_INFO << "Platform layer with GLFW initialized";

        glfwMakeContextCurrent(window);

        glfwSetCursorPosCallback(window, cursor_pos_callback);
        glfwSetKeyCallback(window, key_callback);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    }

    ~Display_impl() {
        if (window) {
            glfwDestroyWindow(window);
        }
        glfwTerminate();
        BOLDER_LOG_INFO << "Platform layer with GLFW terminated";
    }

    GLFWwindow* window = nullptr;
};

Display::Display(const char* title)
    : impl_{std::make_unique<Display_impl>(title)}
{
}

Display::~Display() {

}

std::pair<int, int> Display::dimension() const
{
    int width, height;
    glfwGetWindowSize(impl_->window, &width, &height);
    return std::make_pair(width, height);
}

bool Display::closed() const
{
    return glfwWindowShouldClose(impl_->window);
}

void Display::update() const
{
    glfwSwapBuffers(impl_->window);

    // Check if any events have been activated (key pressed, mouse moved etc.)
    // and call corresponding response functions
    glfwPollEvents();
}
