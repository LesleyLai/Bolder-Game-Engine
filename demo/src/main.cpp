#include "bolder/application.hpp"

class Demo : public bolder::Application {
public:
    Demo() : bolder::Application("Demo") {}

    void initialize() override {}
};

int main(int argc, char** argv) {
    Demo demo;
    return demo.exec(argc, argv);
}
