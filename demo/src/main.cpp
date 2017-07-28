#include "bolder/application.hpp"

class Demo : public bolder::Application {
    void initialize() {

    }
};

int main(int argc, char** argv) {
    Demo demo;
    return demo.exec(argc, argv);
}
