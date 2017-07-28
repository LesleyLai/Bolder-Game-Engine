#include "bolder/engine.hpp"
#include "bolder/logger.hpp"
#include "bolder/exception.hpp"

void dump(const bolder::Exception& e) {
    BOLDER_LOG_FATAL << "Crash report:\n"
                     << e.what();
}

int main(int argc, char** argv) try {
    bolder::Engine engine {"Bolder Demo"};

    return engine.exec(argc, argv);
} catch(bolder::Exception& e) {
    dump(e);
} catch (...) {
}
