#include "file_util.hpp"
#include "exception.hpp"

#include <fstream>
#include <sstream>


namespace bolder { namespace file_util {

std::string load(const char* filename)
{
    std::ifstream in {filename};
    if (in) {
        std::ostringstream ss;
        ss << in.rdbuf();
        return ss.str();
    }
    auto message = std::string("cannot open file " ) + filename;
    throw Runtime_error {message.c_str()};
}

}}
