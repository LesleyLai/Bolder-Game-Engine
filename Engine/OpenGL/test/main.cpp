#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Window_mock {
public:
    Window_mock() {
        glfwInit();
        glfwWindowHint(GLFW_VISIBLE, false);

        window_ = glfwCreateWindow(800, 600, "dummy", nullptr, nullptr);
        if (!window_) {
            std::cerr << "Error: cannot create a dummy window dor OpenGL.\n";
            std::exit(1);
        }
        glfwMakeContextCurrent(window_);
    }

    ~Window_mock() {
        if (window_) {
            glfwDestroyWindow(window_);
        }
        glfwTerminate();
    }

private:
    GLFWwindow* window_;
};

void load_GL() {
    if(!gladLoadGL()) {
        std::cerr << "Error: cannot load OpenGL.\n";
        std::exit(1);
    }

    if (!GLAD_GL_VERSION_3_0) {
        std::cerr << "The system do not support OpenGL 3.0 or later version.\n";
        std::exit(1);
    }
}

int main(int argc, char** argv) {
    Window_mock window;
    load_GL();

    doctest::Context context;

    context.setOption("abort-after", 5); // stop test execution after 5 failed assertions
    context.setOption("order-by", "name"); // sort the test cases by their name

    context.applyCommandLine(argc, argv);

    int res = context.run();

    if(context.shouldExit())
        return res;

    return res; // the result from doctest is propagated here as well
}
