#include "file_util.hpp"
#include "exception.hpp"

#include <fstream>
#include <sstream>

using namespace bolder;

std::string utility::load_file(const char* filename)
{
    std::ifstream in {filename};
    if (in) {
        std::ostringstream ss;
        ss << in.rdbuf();
        return ss.str();
    }
    auto message = std::string("cannot open file " ) + filename;
    throw Exception {message.c_str()};
}
