#include "bolder/engine.hpp"

int main(int argc, char** argv) {
    bolder::Engine engine {"Bolder Demo"};

    return engine.exec(argc, argv);
}
